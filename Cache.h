#ifndef CACHE_H
#define CACHE_H 

#include "Set.h"
#include "Memory.h"
#include "AddressDecoder.h"
#include "PerformanceCounter.h"

//This class is a top-level coordinator that ties all cache parts together
class Cache {

    private:
        Memory* memory; //pointer to the main memory
        int cacheSize; //total cache size in bytes
        int blockSize; //size of each cache block in bytes
        int associativity; //number of blocks per set
        int numSets; //total sets in the cache
        AddressDecoder* decoder; //shared address decoder for all sets
        PerformanceCounter* perfCounter; //shared performance tracking
        Set** sets; //array of pointers
        
        

    public:
        Cache(Memory* memory, int cacheSize, int blockSize, int associativity); //constructor - create a cache with specified parameters
        ~Cache(); //destructor

        unsigned char read(unsigned long address); //read a byte from the cache at the specified memory address
        void write(unsigned long address, unsigned char value); //write a byte to the cache at the specified memory address
        void display() const; //display entire cache contents, including all sets and blocks

        PerformanceCounter* getPerformanceCounter() const; //get access to the performance counter stats

};

#endif