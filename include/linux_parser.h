/* Copyright */
#ifndef INCLUDE_LINUX_PARSER_H_
#define INCLUDE_LINUX_PARSER_H_

#include <fstream>
#include <regex>
#include <string>
#include <vector>

namespace LinuxParser {
using std::vector;
using std::string;

// Paths
const string kProcDirectory{"/proc/"};
const string kCmdlineFilename{"/cmdline"};
const string kCpuinfoFilename{"/cpuinfo"};
const string kStatusFilename{"/status"};
const string kStatFilename{"/stat"};
const string kUptimeFilename{"/uptime"};
const string kMeminfoFilename{"/meminfo"};
const string kVersionFilename{"/version"};
const string kOSPath{"/etc/os-release"};
const string kPasswordPath{"/etc/passwd"};

// System
float MemoryUtilization();
int32_t UpTime();
vector<int> Pids();
int16_t TotalProcesses();
int16_t RunningProcesses();
string OperatingSystem();
string Kernel();

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
vector<string> CpuUtilization();
int16_t Jiffies();
int16_t ActiveJiffies();
int16_t ActiveJiffies(int16_t pid);
int16_t IdleJiffies();

// Processes
string Command(int16_t pid);
string Ram(int16_t pid);
string Uid(int16_t pid);
string User(int16_t pid);
int16_t UpTime(int16_t pid);
};  // namespace LinuxParser

#endif  // INCLUDE_LINUX_PARSER_H_