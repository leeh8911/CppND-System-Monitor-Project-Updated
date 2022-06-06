/* Copyright */
#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int16_t pid) : pid_(pid){};
  int16_t Pid() const;
  std::string User();      // TODO(@sangwon): See src/process.cpp
  std::string Command();   // TODO(@sangwon): See src/process.cpp
  float CpuUtilization();  // TODO(@sangwon): See src/process.cpp
  std::string Ram();       // TODO(@sangwon): See src/process.cpp
  long int UpTime();       // TODO(@sangwon): See src/process.cpp
  bool operator<(
      Process const& a) const;  // TODO(@sangwon): See src/process.cpp

  // TODO(@sangwon): Declare any necessary private members
 private:
  int16_t pid_;
};

#endif