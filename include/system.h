/* Copyright */
#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "./process.h"
#include "./processor.h"

class System {
 public:
  Processor& Cpu();
  std::vector<Process>& Processes();
  float MemoryUtilization();
  int32_t UpTime();
  int16_t TotalProcesses();
  int16_t RunningProcesses();
  std::string Kernel();
  std::string OperatingSystem();

 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif