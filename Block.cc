#include "Block.h" 
#include <iostream> 
#include <iomanip>

//constructor - initialize a cache block
Block::Block(int blockSize, Memory* memory) 
    : blockSize(blockSize), memory(memory), tag(0), valid(false), dirty(false), timestamp(0) {
    data = new unsigned char[blockSize];    
    for(int i = 0; i < blockSize; i++){
        data[i] = 0;
    }
}

//destructor - free the data array
Block::~Block(){
    delete[] data;
}

//read a byte from this block at the specified offset
unsigned char Block::read(int blockOffset){
    updateTimestamp();
    return data[blockOffset];
}

//write a byte to this block at the specified offset
void Block::write(int blockOffset, unsigned char value){
    updateTimestamp();
    data[blockOffset] = value;
    dirty = true;
}

//load a complete block of data from main memory
void Block::loadFromMemory(unsigned long blockAddress){
    for(int i = 0; i < blockSize; i++){
        data[i] = memory->getByte(blockAddress+i);
    }
    valid = true;
    dirty = false;
    updateTimestamp();
}

//save this block's data back to main memory (for write-back policy)
void Block::saveToMemory(unsigned long blockAddress){
    for(int i = 0; i < blockSize; i++){
        memory->setByte(blockAddress + i, data[i]);
    }
    dirty = false;
}

//get tag
unsigned long Block::getTag() const{
    return tag;
}

//set the tag
void Block::setTag(unsigned long newTag){
    tag = newTag;
}

//check if block contains valid data
bool Block::isValid() const {
    return valid;
}

//set valid flag (true when block contains data, false when empty)
void Block::setValid(bool newValid){
    valid = newValid;
}

//check if block has been modified since loading from memory
bool Block::isDirty() const{
    return dirty;
}

//set dirty flag (true when block differs from memory)
void Block::setDirty(bool newDirty){
    dirty = newDirty;
}

//get timestampt of last access (used for LRU replacement)
long Block::getTimestamp() const{
    return timestamp;
}

//update timestamp to current time (called on every access)
void Block::updateTimestamp() {
    timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(
        m_clock.now().time_since_epoch()).count();
}

//display block metadata
void Block::display() const {
    std::cout << "      valid: " << (valid ? 1 : 0) 
              << "    tag: " << tag 
              << "    dirty: " << (dirty ? 1 : 0) 
              << "    timestamp: " << timestamp << std::endl;
    std::cout << "      ";
    for (int i = 0; i < blockSize; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) 
                  << static_cast<int>(data[i]) << "  ";
    }
    std::cout << std::endl;
}