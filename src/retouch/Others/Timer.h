#ifndef LAPLACIAN_PYRAMID_TIMER_H
#define LAPLACIAN_PYRAMID_TIMER_H
#include <chrono>
#include <iostream>

class Timer
{
    std::chrono::system_clock::time_point start;
public:
    Timer()
    {
        start = std::chrono::system_clock::now();
    }
    ~Timer()
    {
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now() - start).count();
        std::cout << "The operation took " << duration << "seconds\n";
    }
};


#endif
