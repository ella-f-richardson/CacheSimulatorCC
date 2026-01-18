#include "PerformanceCounter.h"
#include <iostream> 
#include <iomanip> 

//constructor - initialize all performance counters to 0
PerformanceCounter::PerformanceCounter() : hits(0), misses(0), writebacks(0) {
}

//increment hit counter when data is found in cache
void PerformanceCounter::incrementHits() {
    hits++;
}

//increment mniss counter when data isn't found in cache
void PerformanceCounter::incrementMisses(){
    misses++;
}

//increment writeback counter when dirty block is written to memory
void PerformanceCounter::incrementWritebacks(){
    writebacks++;
}

//return number of hits
int PerformanceCounter::getHits() const {
    return hits;
}

//return number of misses
int PerformanceCounter::getMisses() const {
    return misses;
}

//return number of writebacks
int PerformanceCounter::getWritebacks() const {
    return writebacks;
}

//return total number of hits and misses
int PerformanceCounter::getTotalAccesses() const {
    return hits + misses;
}

//calculate miss rate as a percentage
double PerformanceCounter::getMissPercentage() const {
    int total = getTotalAccesses();
    if (total == 0){
        return 0.0;
    }
    else{
        return (double)misses / total*100.0;
    }
}

//calculate writeback rate as a percentage
double PerformanceCounter::getWritebackPercentage() const {
    int total = getTotalAccesses();
    if (total == 0){
        return 0.0;
    }
    else{
        return (double)writebacks / total*100.0;
    }
}

//display all performance statistics
void PerformanceCounter::display() const {
    std::cout << "Accesses:     " << getTotalAccesses() << std::endl;
    std::cout << "Hits:         " << hits << std::endl;
    std::cout << "Misses:         " << misses << std::endl;
    std::cout << "Writebacks:     " << writebacks << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Miss Perc:     " << getMissPercentage() << std::endl;
    std::cout << "Writeback Perc:     " << getWritebackPercentage() << std::endl;
}