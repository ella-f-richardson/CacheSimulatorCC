#include "AddressDecoder.h"  
#include <cmath>

//constructor - calculate how many bits are needed for each address component
AddressDecoder::AddressDecoder(int cacheSize, int blockSize, int associativity) : blockSize(blockSize){
    int numBlocks = cacheSize / blockSize;
    numSets = numBlocks / associativity;

    blockOffsetBits = (int)log2(blockSize);
    setIndexBits = (int)log2(numSets);
    tagBits = 32 - blockOffsetBits - setIndexBits; //for 32 bit addresses
}

//extract tag from address by shifting away set index and block offset bits
unsigned long AddressDecoder::getTag(unsigned long address) const {
    return address >> (blockOffsetBits + setIndexBits);
}

//extract set index by shifting away block offset bits and masking upper bits
unsigned long AddressDecoder::getSetIndex(unsigned long address) const {
    unsigned long mask = (1UL << setIndexBits) - 1;
    return (address >> blockOffsetBits) & mask;
}

//extract block offset by masking away upper bits
unsigned long AddressDecoder::getBlockOffset(unsigned long address) const{
    unsigned long mask = (1UL << blockOffsetBits) - 1;
    return address & mask;
}

//get block-aligned address by clearning the block offset bits
//(gives the starting address of the memory block containing this address)
unsigned long AddressDecoder::getBlockAddress(unsigned long address) const {
    //return addres with block offset bits cleared (start of block)
    return address & ~((1UL << blockOffsetBits) - 1);
}

//Reconstruct address from tag and set index (with block offset = 0)
unsigned long AddressDecoder::reconstructAddress(unsigned long tag, unsigned long setIndex) const {
    return (tag << (blockOffsetBits + setIndexBits)) | (setIndex << blockOffsetBits);
}