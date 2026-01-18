#ifndef BLOCK_H
#define BLOCK_H 
 
#include "Memory.h"
#include <chrono>

//This class represents a single cache line that holds a block of data
class Block{

    private:
        int blockSize; //size of this block in bytes
        unsigned char* data; //array holding the cached data bytes
        Memory* memory; //pointer to main memory for load/save operations
        unsigned long tag; //tag identifying which memory block is stored here
        bool valid; //whether the block contains valid data (starts empty)
        bool dirty; //whether the data has been modified since loading (write-back policy)
        long timestamp; //when this block was last accessed
        std::chrono::high_resolution_clock m_clock; //clock for timestamps

    public:
        Block(int blockSize, Memory* memory); //constructor - create a cache block of specified size
        ~Block(); //destructor

        unsigned char read(int blockOffset); //read a byte from within this block at the specified offset
        void write(int blockOffset, unsigned char value); //write a byte to this block at the specified offset
        void loadFromMemory(unsigned long blockAddress); //load a block of data from main memory into this cache block
        void saveToMemory(unsigned long blockAddress); //save this block's data back to main memory (for dirty blocks)

        //getter and setter methods
        unsigned long getTag() const;
        void setTag(unsigned long newTag);
        bool isValid() const;
        void setValid(bool valid);
        bool isDirty() const;
        void setDirty(bool dirty);
        long getTimestamp() const;

        void updateTimestamp(); //update timestamp to current time (called on each access for LRU)
        void display() const; //display block contents and metadata
};

#endif