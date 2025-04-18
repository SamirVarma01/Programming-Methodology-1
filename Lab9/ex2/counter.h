#ifndef COUNTER_H
#define COUNTER_H

class Counter {
private:
    int value;
    static int total_counters; 

public:
    Counter();
    Counter(int initial_value);
    ~Counter();

    void increment();
    void decrement();
    int getValue() const;

    static int getTotalCounters();
};

#endif