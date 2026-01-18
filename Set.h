#ifndef SET_H
#define SET_H
 
#include "Block.h" 
#include "Memory.h"
#include "AddressDecoder.h"
#include "PerformanceCounter.h"

//This class manages of group of cache blocks that compete for the same cache location
class Set {

    private:
        int numBlocks; //number of blocks in this set
        int blockSize; //size of each block in bytes
        Block** blocks; //array of block pointers
        Memory* memory; //pointer to main memory
        AddressDecoder* decoder; //helper to decode addresses
        PerformanceCounter* perfCounter; //performance tracking

        int findBlock(unsigned long tag); //search for a block with the specified tag in this set
        int findEmptyBlock(); //find an empty (invalid) block in this set
        int findLRUBlock(); //find the least recently used block for replacement

    public:
        //constructor - create a set with specified number of blocks
        Set(int numbBlocks, int blockSize, Memory* memory, AddressDecoder* decoder, PerformanceCounter* perfCounter);
        ~Set(); //destructor

        unsigned char read(unsigned long address); //read a byte from the cache at the specified address 
        void write(unsigned long address, unsigned char value); //write a byte to the cache at the specified address
        void display() const; //display all blocks in this set with their data and metadata
};

#endif