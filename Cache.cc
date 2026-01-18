#include "Cache.h" 
#include <iostream> 

//constructor - initialize the cache system with specified parameters
Cache::Cache(Memory* memory, int cacheSize, int blockSize, int associativity) 
: memory(memory), cacheSize(cacheSize), blockSize(blockSize), associativity(associativity) {
    int numBlocks = cacheSize / blockSize;
    numSets = numBlocks / associativity;

    decoder = new AddressDecoder(cacheSize, blockSize, associativity);
    perfCounter = new PerformanceCounter();

    sets = new Set*[numSets]; //EXPLAIN
    for(int i = 0; i < numSets; i++) {
        sets[i] = new Set(associativity, blockSize, memory, decoder, perfCounter);
    }

}

//destructor
Cache::~Cache(){
    for(int i = 0; i < numSets; i++){
        delete sets[i];
    }

    delete[] sets;
    delete decoder;
    delete perfCounter;
}

//get a byte from cache or load from memory if needed
unsigned char Cache::read(unsigned long address){
    unsigned long setIndex = decoder->getSetIndex(address);
    return sets[setIndex]->read(address);
}

//write a byte to cache using write-allocate, write-back policy
void Cache::write(unsigned long address, unsigned char value){
    unsigned long setIndex = decoder->getSetIndex(address);
    sets[setIndex]->write(address, value);
}

//display the entire cache state
void Cache::display() const {
    std::cout << "CACHE:" << std::endl;
    for(int i = 0; i < numSets; i++){
        std::cout << "  Set " << i << std::endl;
        sets[i]->display();
        std::cout << std::endl;
    }
    std::cout << std::endl;
    perfCounter->display();
}

//provide access to performance statistics
PerformanceCounter* Cache::getPerformanceCounter() const {
    return perfCounter;
}