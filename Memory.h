#ifndef MEMORY_H  
#define MEMORY_H

//This class represents the main memory of the computer system
//where the data is stored when not in cache, and where cache fetches data from when there is a cache miss
class Memory {
    
    private:
        int memorySize; //total size of memory in bytes
        unsigned char* bytes; //pointer to actual memory storage array

    public:
        Memory(int size); //constructor - creates memory of specified size
        ~Memory(); //destructor

        unsigned char getByte(unsigned long address); //reads a single byte of memory at the given address
        void setByte(unsigned long address, unsigned char value); //writes a single byte to memory at the given address
        int getSize() const; //returns total size of memory
        void display() const; //display entire memory contents in hex format
};

#endif