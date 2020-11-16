#ifndef PRACTICE_PHILOSOPHER_H
#define PRACTICE_PHILOSOPHER_H

#include <random>
#include "iostream"
using namespace std;

random_device rd;
mt19937 mt(rd());

enum states
{
    EATING,
    HUNGRY,
    THINKING
};

class Philosopher
{
public:
    states state;
    int id;

    explicit Philosopher(int i)
    {
        state = THINKING;
        id = i;
        uniform_int_distribution<int> distribution(2, 5);
    }

    void thinking(int mn = 99, int mx = 99)
    {
        uniform_int_distribution<int> distribution(mn, mx);
        int x = distribution(mt);
        // cout << id << ":Thinking Start\n";
        for (int i = 0; i < x; i++)
            ;
        // cout << id << ":Thinking End\n";
    }
    void eating(int mn = 99, int mx = 99)
    {
        uniform_int_distribution<int> distribution(mn, mx);
        int x = distribution(mt);
        // cout << id << ":Eating Start\n";
        for (int i = 0; i < x; i++)
            ;
        // cout << id << ":Eating End\n";
    }
};

#endif