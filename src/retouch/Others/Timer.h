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
        double duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now() - start).count() / 1000.;
        std::cout << "The operation took " << duration << " seconds\n";
    }
};


#endif
