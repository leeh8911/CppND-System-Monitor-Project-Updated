/* Copyright */
#include "include/system.h"

#include <unistd.h>

#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "include/linux_parser.h"
#include "include/process.h"
#include "include/processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() {
  vector<int16_t> pids = LinuxParser::Pids();
  processes_ = {};

  for (auto pid : pids) {
    processes_.emplace_back(Process(pid));
  }

  std::sort(processes_.begin(), processes_.end());

  return processes_;
}

std::string System::Kernel() { return LinuxParser::Kernel(); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int16_t System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int16_t System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

int32_t System::UpTime() { return LinuxParser::UpTime(); }
