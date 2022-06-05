/* Copyright */
#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "./process.h"
#include "./processor.h"

class System {
 public:
  Processor& Cpu();                   // TODO(@sangwon): See src/system.cpp
  std::vector<Process>& Processes();  // TODO(@sangwon): See src/system.cpp
  float MemoryUtilization();          // TODO(@sangwon): See src/system.cpp
  int16_t UpTime();                      // TODO(@sangwon): See src/system.cpp
  int16_t TotalProcesses();               // TODO(@sangwon): See src/system.cpp
  int16_t RunningProcesses();             // TODO(@sangwon): See src/system.cpp
  std::string Kernel();               // TODO(@sangwon): See src/system.cpp
  std::string OperatingSystem();      // TODO(@sangwon): See src/system.cpp

  System();
  // TODO(@sangwon): Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif