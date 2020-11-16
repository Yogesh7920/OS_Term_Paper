#include <bits/stdc++.h>
#include <semaphore.h>
#include "Philosopher.h"

#define N 10
#define loop_count 1000
#define output false

// int N = 10;
// int loop_count = 1000;
mutex mtx;
sem_t S[25];
vector<Philosopher> ps;

using namespace std;

void init()
{
    for (int i = 0; i < N; i++)
    {
        ps.emplace_back(i);
    }
}

Philosopher left(int i)
{
    if (i == 0)
        return ps[N - 1];
    else
        return ps[i];
}

Philosopher right(int i)
{
    if (i == N - 1)
        return ps[0];
    else
        return ps[i];
}

void test(int i)
{
    if (ps[i].state == HUNGRY && left(i).state != EATING && right(i).state != EATING)
    {
        ps[i].state = EATING;
        sem_post(&S[i]);
    }
}

void take_fork(int i)
{
    mtx.lock();
    ps[i].state = HUNGRY;
    test(i);
    mtx.unlock();
    sem_wait(&S[i]);
}

void put_fork(int i)
{
    mtx.lock();
    ps[i].state = THINKING;
    test(left(i).id);
    test(right(i).id);
    mtx.unlock();
}

void philosopher_lock(int i)
{
    for (int j = 0; j < loop_count; j++)
    {
        ps[i].thinking();
        take_fork(i);
        ps[i].eating();
        put_fork(i);
    }
}

void philosopher_TM(int i)
{
    for (int j = 0; j < loop_count; j++)
    {

        ps[i].thinking();
        if (output)
            cout << i << " Eating Start\n"; // * ostream can not be inside atomic as it is un-safe transaction function
        atomic_commit
        {
            if (left(i).state != EATING && right(i).state != EATING)
            {
                for (int k = 0; k < 100; k++) // * Eating method not used as it is a error, un-safe transcation function
                    ;
            }
        }
        if (output)
            cout << i << " Eating End\n";
    }
}

void lock_based()
{
    clock_t start, end;
    start = clock();
    for (auto s : S)
    {
        sem_init(&s, 0, 0);
    }
    thread threads[N];
    for (int i = 0; i < N; i++)
    {
        threads[i] = thread(philosopher_lock, i);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    for (auto s : S)
    {
        sem_destroy(&s);
    }
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Lock: " << time_taken << setprecision(5) << " sec" << endl;
}

void TM_based()
{
    clock_t start, end;
    start = clock();
    thread threads[N];
    for (int i = 0; i < N; i++)
    {
        threads[i] = thread(philosopher_TM, i);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "STM: " << time_taken << setprecision(5) << " sec" << endl;
}

int main()
{
    init();
    lock_based();
    ps.clear();
    init();
    TM_based();
    ps.clear();

    return 0;
}