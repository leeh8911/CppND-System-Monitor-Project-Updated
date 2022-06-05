/* Copyright */
#ifndef INCLUDE_LINUX_PARSER_H_
#define INCLUDE_LINUX_PARSER_H_

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
float MemoryUtilization();
int32_t UpTime();
std::vector<int> Pids();
int16_t TotalProcesses();
int16_t RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
std::vector<std::string> CpuUtilization();
int16_t Jiffies();
int16_t ActiveJiffies();
int16_t ActiveJiffies(int16_t pid);
int16_t IdleJiffies();

// Processes
std::string Command(int16_t pid);
std::string Ram(int16_t pid);
std::string Uid(int16_t pid);
std::string User(int16_t pid);
int16_t UpTime(int16_t pid);
};  // namespace LinuxParser

#endif //INCLUDE_LINUX_PARSER_H_