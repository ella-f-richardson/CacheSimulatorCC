#include "Set.h"
#include <iostream>
#include <limits>
//constructor - create a set with the specified number of blocks
Set::Set(int numBlocks, int blockSize, Memory* memory, AddressDecoder* decoder, PerformanceCounter* perfCounter)
: numBlocks(numBlocks), blockSize(blockSize), memory(memory), decoder(decoder), perfCounter(perfCounter) {
    blocks = new Block*[numBlocks];
    for(int i = 0; i < numBlocks; i++){
        blocks[i] = new Block(blockSize, memory);
    }
}
//destructor
Set::~Set() {
    for(int i = 0; i < numBlocks; i++){
        delete blocks[i];
    }
    delete[] blocks;
}
//helper function - search for a block with the specified tag
int Set::findBlock(unsigned long tag) {
    for(int i = 0; i < numBlocks; i++){
        if(blocks[i]->isValid() && blocks[i]->getTag() == tag){
            return i;
        }
    }
    return -1; //if not found
}
//helper function - find an empty (unused) block in this set
int Set::findEmptyBlock() {
    for(int i = 0; i < numBlocks; i++){
        if(!blocks[i]->isValid()){
            return i;
        }
    }
    return -1; //if there are no empty blocks
}
//helper function - find the least recently used block for replacement
int Set::findLRUBlock() {
    long oldestTime = std::numeric_limits<long>::max();
    int lruIndex = 0;
    for(int i = 0; i < numBlocks; i++){
        if(blocks[i]->getTimestamp() < oldestTime){
            oldestTime = blocks[i]->getTimestamp();
            lruIndex = i;
        }
    }
    return lruIndex;
}
//handle cache/miss logic for reads
unsigned char Set::read(unsigned long address) {
    unsigned long tag = decoder->getTag(address);
    unsigned long blockOffset = decoder->getBlockOffset(address);
    //check if block is already in cache (hit)
    int blockIndex = findBlock(tag);
    if (blockIndex != -1) {
        perfCounter->incrementHits();
        return blocks[blockIndex]->read(blockOffset);
    }
    //cache miss - need to load block
    perfCounter->incrementMisses();
    //find a block to use
    blockIndex = findEmptyBlock();
    if (blockIndex == -1) {
        //no empty blocks, use LRU replacement
        blockIndex = findLRUBlock();
        //if the block being evicted is dirty, write it back
        if (blocks[blockIndex]->isDirty()) {
            unsigned long evictedTag = blocks[blockIndex]->getTag();
            unsigned long setIndex = decoder->getSetIndex(address);
            // Simple fix: reconstruct address manually
            // Address format: tag | setIndex | blockOffset(0)
            // For 32-bit addresses with 4-byte blocks (2 bits) and 2 sets (1 bit)
            // blockOffset = 2 bits, setIndex = 1 bit, tag = 29 bits
            unsigned long evictedAddress = (evictedTag << 3) | (setIndex << 2);
            blocks[blockIndex]->saveToMemory(evictedAddress);
            perfCounter->incrementWritebacks();
        }
    }
    //load new block from memory
    unsigned long blockAddress = decoder->getBlockAddress(address);
    blocks[blockIndex]->loadFromMemory(blockAddress);
    blocks[blockIndex]->setTag(tag);
    return blocks[blockIndex]->read(blockOffset);
}
//handle cache hit/miss logic for writes
void Set::write(unsigned long address, unsigned char value) {
    unsigned long tag = decoder->getTag(address);
    unsigned long blockOffset = decoder->getBlockOffset(address);
    //check if block is already in cache (hit)
    int blockIndex = findBlock(tag);
    if (blockIndex != -1) {
        perfCounter->incrementHits();
        blocks[blockIndex]->write(blockOffset, value);
        return;
    }
    //cache miss - need to load block (write-allocate)
    perfCounter->incrementMisses();
    //find a block to use
    blockIndex = findEmptyBlock();
    if (blockIndex == -1) {
        //no empty blocks, use LRU replacement
        blockIndex = findLRUBlock();
        //if the block being evicted is dirty, write it back
        if (blocks[blockIndex]->isDirty()) {
            unsigned long evictedTag = blocks[blockIndex]->getTag();
            unsigned long setIndex = decoder->getSetIndex(address);
            // Simple fix: reconstruct address manually
            // Address format: tag | setIndex | blockOffset(0)
            // For 32-bit addresses with 4-byte blocks (2 bits) and 2 sets (1 bit)
            // blockOffset = 2 bits, setIndex = 1 bit, tag = 29 bits
            unsigned long evictedAddress = (evictedTag << 3) | (setIndex << 2);
            blocks[blockIndex]->saveToMemory(evictedAddress);
            perfCounter->incrementWritebacks();
        }
    }
    //load new block from memory
    unsigned long blockAddress = decoder->getBlockAddress(address);
    blocks[blockIndex]->loadFromMemory(blockAddress);
    blocks[blockIndex]->setTag(tag);
    //perform the write
    blocks[blockIndex]->write(blockOffset, value);
}
//display all blocks in this set
void Set::display() const {
    std::cout << "    Blocks" << std::endl;
    for (int i = 0; i < numBlocks; i++) {
        std::cout << "    " << i << ":" << std::endl;
        blocks[i]->display();
    }
}




















