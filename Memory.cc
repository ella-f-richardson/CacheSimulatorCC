#include "Memory.h"  
#include <iostream>
#include <iomanip>

//constructor - allocate memory and initialize
Memory::Memory(int size) : memorySize(size){
    bytes = new unsigned char[size];

    //initialize memory with i%255 for testing
    for(int i = 0; i < size; i++){
        bytes[i] = i%255;
    }
}

//destructor
Memory::~Memory(){
    delete[] bytes;
}

//read a single byte from the specified memory address
unsigned char Memory::getByte(unsigned long address){
    return bytes[address];
}

//write a single byte to the specified memory address
void Memory::setByte(unsigned long address, unsigned char value){
    bytes[address] = value;
}

//return total size of memory
int Memory::getSize() const{
    return memorySize;
}

//display all memory contents in hex format
void Memory::display() const{
    std::cout << "MAIN MEMORY:" << std::endl;
    for(int i = 0; i < memorySize; i++){
        std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(bytes[i]) << " ";
        
        //print newline after every 16 bytes
        if((i+1) % 16 == 0){
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}