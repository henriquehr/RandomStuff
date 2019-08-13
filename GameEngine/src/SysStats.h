#ifndef SYS_STATS_H
#define SYS_STATS_H

#include "Logging.h"

#if (unix)
#include <sys/sysinfo.h>
#include <sys/times.h>
#include <sys/vtimes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

class SysStats {
private:
    clock_t lastCPU;
    clock_t lastSysCPU;
    clock_t lastUserCPU;
    int numProcessors;

public:
    SysStats() { init(); }
    ~SysStats() {}

    // CPU usage of this process (%)
    inline float myCPUUsage() {
        return getCurrentValueCPU();
    }

    // Virtual memory of this process (MB)
    inline float myVirtualMemory() {
        return this->getValueVM();
    }

    // Physical memory of this process (MB)
    inline float myPhysicalMemory() {
        return this->getValuePM();
    }

    inline void myAllStatsPrint() {
        LOG_NO_INFO(SYSTEM) << "Cores:" << this->numProcessors << ". CPU Usage:" 
          << this->myCPUUsage() << "%. Memory:" << this->getValuePM() << "MB";

    }

    inline void myCPUUsagePrint() {
        LOG_NO_INFO(SYSTEM) << "Cores:" << this->numProcessors << ". CPU Usage:" 
          << this->myCPUUsage() << "%";

    }

    inline void myVirtualMemoryPrint() {
        LOG_NO_INFO(SYSTEM) << "Virtual Memory:" << this->getValueVM() << "MB";
    }

    inline void myPhysicalMemoryPrint() {
        LOG_NO_INFO(SYSTEM) << "Physical Memory:" << this->getValuePM() << "MB";
    }

private:
    inline void init(){
        FILE* file;
        struct tms timeSample;
        char line[128];
        this->lastCPU = times(&timeSample);
        this->lastSysCPU = timeSample.tms_stime;
        this->lastUserCPU = timeSample.tms_utime;
        file = fopen("/proc/cpuinfo", "r");
        numProcessors = 0;
        while(fgets(line, 128, file) != NULL){
            if (strncmp(line, "processor", 9) == 0) {
                numProcessors++;
            }
        }
        fclose(file);
    }

    inline float getCurrentValueCPU(){
        struct tms timeSample;
        clock_t now;
        float percent;
        now = times(&timeSample);
        if (now <= this->lastCPU || timeSample.tms_stime < this->lastSysCPU || 
          timeSample.tms_utime < this->lastUserCPU){

            //Overflow detection. Just skip this value.
            percent = -1.0f;
        } else {
            percent = (timeSample.tms_stime - this->lastSysCPU) + 
              (timeSample.tms_utime - this->lastUserCPU);

            percent /= (now - this->lastCPU);
            percent /= numProcessors;
            percent *= 100.0f;
        }
        this->lastCPU = now;
        this->lastSysCPU = timeSample.tms_stime;
        this->lastUserCPU = timeSample.tms_utime;
        return percent;
    }

    inline int parseLine(char* line){
        // This assumes that a digit will be found and the line ends in " Kb".
        int i = strlen(line);
        const char* p = line;
        while (*p <'0' || *p > '9') p++;
        line[i-3] = '\0';
        i = atoi(p);
        return i;
    }

    inline float getValueVM() {
        FILE* file = fopen("/proc/self/status", "r");
        int result = -1.0f;
        char line[128];
        while (fgets(line, 128, file) != NULL){
            if (strncmp(line, "VmSize:", 7) == 0){
                result = parseLine(line);
                break;
            }
        }
        fclose(file);
        return result / 1024.0f; // KB to MB
    }

    inline float getValuePM() {
        FILE* file = fopen("/proc/self/status", "r");
        int result = -1.0f;
        char line[128];
        while (fgets(line, 128, file) != NULL){
            if (strncmp(line, "VmRSS:", 6) == 0){
                result = parseLine(line);
                break;
            }
        }
        fclose(file);
        return result / 1024.0f; // KB to MB
    }
};
#endif // unix
#endif // !SYS_STATS_H