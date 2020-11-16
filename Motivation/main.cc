#include "BST.h"
#include <bits/stdc++.h>

#define ops 1e6

using namespace std;

RBTree tree;
mutex mtx;

void func_mutex(int n, int id)
{
    for (int i = 0; i < n; i++)
    {
        mtx.lock();
        //Critical Section begin
        if (id == 1)
            tree.max_increment(1);
        if (id == 2)
            tree.remove_min();
        //Critical Section end
        mtx.unlock();
    }
}

void func_TM(int n, int id)
{
    for (int i = 0; i < n; i++)
    {
        //Critical Section begin
        if (id == 1)
            tree.max_increment(1);
        if (id == 2)
            tree.remove_min();
        //Critical Section end
    }
}

void mutex_call()
{
    clock_t start, end;
    start = clock();
    thread t1(func_mutex, ops, 1), t2(func_mutex, ops, 2);
    t1.join();
    t2.join();
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Lock-Based: " << time_taken << setprecision(5) << " sec" << endl;
}

void STM_call()
{
    clock_t start, end;
    start = clock();
    thread t1(func_TM, ops, 1), t2(func_TM, ops, 2);
    t1.join();
    t2.join();
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Lock-Free: " << time_taken << setprecision(5) << " sec" << endl;
}

void RBT_init()
{
    for (int i = 1; i <= 1e6; i++)
        tree.insert(i);
}

int main()
{
    RBT_init();
    mutex_call();
    tree.clear();
    RBT_init();
    STM_call();
    return 0;
}