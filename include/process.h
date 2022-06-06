/* Copyright */
#ifndef INCLUDE_PROCESS_H_
#define INCLUDE_PROCESS_H_

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int16_t pid);

  int16_t Pid() const;
  std::string User();
  std::string Command();
  float CpuUtilization() const;
  std::string Ram();
  int32_t UpTime();
  bool operator<(Process const& a) const;

 private:
  int16_t pid_;
};

#endif  // INCLUDE_PROCESS_H_
