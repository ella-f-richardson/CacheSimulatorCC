#pragma once 

//This class breaks down memory addresses into cache-relevant components
//  Tag | Set Index | Block Offset
class AddressDecoder {

    private:
        int blockOffsetBits;
        int setIndexBits;
        int tagBits;
        int blockSize; //size of each cache block in bytes
        int numSets; //number of sets in the cache

    public:
        AddressDecoder(int cacheSize, int blockSize, int associativity); //constructor - calculate bit field sizes based on cache parameters

        unsigned long getTag(unsigned long address) const; //extract tag portion of memory address
        unsigned long getSetIndex(unsigned long address) const; //extract set index portion of memory address
        unsigned long getBlockOffset(unsigned long address) const; //extract block offset portion of memory address
        unsigned long getBlockAddress(unsigned long address) const; //get starting address of the memory block containing the address
        
        //Reconstruct address from tag and set index
        unsigned long reconstructAddress(unsigned long tag, unsigned long setIndex) const;
};