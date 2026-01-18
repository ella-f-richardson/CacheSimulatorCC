#ifndef PERFORMANCE_COUNTER_H 
#define PERFORMANCE_COUNTER_H 

//This class tracks cache performance statistics
class PerformanceCounter {

    private:
        int hits; //data found in cache
        int misses; //data not in cache, must fetch from memory
        int writebacks; //dirty block evicted, must write to memory

    public:
        PerformanceCounter(); //constructor

        //increment values
        void incrementHits();
        void incrementMisses();
        void incrementWritebacks();

        //getters
        int getHits() const;
        int getMisses() const;
        int getWritebacks() const;
        int getTotalAccesses() const;

        double getMissPercentage() const; //calculate miss percentage
        double getWritebackPercentage() const; //calculate writeback percentage

        void display() const; //display all performance statistics
};

#endif