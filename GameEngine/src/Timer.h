#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include <thread>
#include <iostream>
#include <string>

#include "Logging.h"
#include "SysStats.h"

// TODO Add only 1 global variable to keep the starting time 
// and compute the other timers using that?
// would need one variable per timer instead of this whole class?
// test performance

class Timer {
private:
    std::chrono::high_resolution_clock::time_point time_from_start;
    std::chrono::high_resolution_clock::time_point time_loop;
    double loop_time;
    int frame_count;
    int FPS;
    SysStats ss;

public:
    Timer() 
      : time_from_start(std::chrono::high_resolution_clock::now()), 
      time_loop(std::chrono::high_resolution_clock::now()), loop_time(0.0), 
      frame_count(0), FPS(0) {

        LOG(MESSAGE) << "Timer module initialized.";
    };
    
    ~Timer() {};

    inline void start() {
        this->time_loop = std::chrono::high_resolution_clock::now();
    }

    inline void resetLoop() {
        this->time_loop = std::chrono::high_resolution_clock::now();
    }

    inline void resetBeginning() {
        this->time_from_start = std::chrono::high_resolution_clock::now();
    }

    // Milliseconds
    inline double getElapsedTimeLoop() {
        return std::chrono::duration<double, std::milli>(
          std::chrono::high_resolution_clock::now() - this->time_loop).count();

    }
        // Milliseconds
    inline double getElapsedTimeStart() {
        return std::chrono::duration<double, std::milli>(
          std::chrono::high_resolution_clock::now() - this->time_from_start).count();

    }

    // Compute game loop, time and fps
    inline void computeLoop() {
        this->loop_time += this->getElapsedTimeLoop();
        this->frame_count++;
        if (this->loop_time >= 1000) {
            LOG_NO_INFO(SYSTEM) << "FPS: " << this->frame_count << 
              " - LOOP TIME: " <<  this->getElapsedTimeLoop() << "ms";
            
            //std::cout << "FPS: " << this->frame_count << " - LOOP TIME: " <<  this->getElapsedTimeLoop() << "\n";
            this->FPS = this->frame_count;
            this->frame_count = 0;
            this->loop_time = 0.0;
            ss.myAllStatsPrint();
        }
        this->resetLoop();
    }

    inline int getFPS() {
        return this->FPS;
    }

    inline double getLastLoopTime() {
        return this->loop_time;
    }

    inline void nap(unsigned int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(
          (long)(ms - this->getElapsedTimeLoop())));
    }
};
#endif // !BENCHMARK_H