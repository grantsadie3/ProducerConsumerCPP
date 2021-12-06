

// PROBLEM:
//  - Producer will produce and consumer will consume with synchronisation
//     of common buffer.
//  - Will continue intil producer thread does not produce any data for the consumer
//  - Threads will use a condition variable to notify each other
//  - Mutex needs to be used because the CV waits on the Mutex


#include <iostream>
#include <chrono>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mu;
condition_variable cond;
deque<int> buffer;
const unsigned int maxBufferSize = 50;
bool producer_alive = true;

void producer(int val)
{
    while(val)
    {
        unique_lock<mutex> locker(mu);
        cond.wait(locker, [](){return buffer.size() < maxBufferSize;});
        buffer.push_back(val);
        cout << "Produced: " << val << endl;
        val--;
        locker.unlock();
        cond.notify_one();
    }
    cout << "Proucer has ended." << endl;
    producer_alive = false;
}

void consumer()
{
    while(producer_alive == true || buffer.size() > 0)
    {
        unique_lock<mutex> locker(mu);
        cond.wait(locker, [](){return buffer.size() > 0;});
        int val = buffer.back();
        buffer.pop_back();
        cout << "Consumed: " << val << endl;
        locker.unlock();
        cond.notify_one();
    }
    cout << "Consumer has ended." << endl;
}

int main()
{
    thread t1(producer, 100);
    thread t2(consumer);
    
    t1.join();
    t2.join();

    cout << "Program has ended." << endl;
    return 0;
}
