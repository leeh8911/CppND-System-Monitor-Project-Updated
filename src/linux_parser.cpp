/* Copyright */
#include "include/linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <limits>
#include <string>
#include <vector>

using std::numeric_limits;
using std::stof;
using std::stoul;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  string unit;

  float mem_free = -1.f;
  float mem_total = -1.f;
  float mem_buffers = -1.f;
  float mem_cached = -1.f;
  float mem_sreclaimable = -1.f;
  float mem_shmem = -1.f;

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value >> unit) {
        if (key == "MemTotal") {
          mem_total = stof(value);
        } else if (key == "MemFree") {
          mem_free = stof(value);
        } else if (key == "Buffers") {
          mem_buffers = stof(value);
        } else if (key == "Cached") {
          mem_cached = stof(value);
        } else if (key == "SReclaimable") {
          mem_sreclaimable = stof(value);
        } else if (key == "mem_shmem") {
          mem_shmem = stof(value);
        } else {
          // Do Nothing
        }
      }
    }
  }

  return (mem_total - (mem_free + mem_buffers + mem_cached + mem_shmem +
                       mem_sreclaimable)) /
         mem_total;
}

int32_t LinuxParser::UpTime() {
  string uptime, idle_uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idle_uptime;
  }

  uint32_t uptime_buffer = stoul(uptime);
  uptime_buffer =
      uptime_buffer < static_cast<uint32_t>(numeric_limits<int32_t>::max())
          ? uptime_buffer
          : std::numeric_limits<int16_t>::max();
  return static_cast<int32_t>(uptime_buffer);
}

// TODO(@sangwon): Read and return the number of jiffies for the system
int16_t LinuxParser::Jiffies() { return 0; }

// TODO(@sangwon): Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
int16_t LinuxParser::ActiveJiffies(int16_t pid [[maybe_unused]]) { return 0; }

// TODO(@sangwon): Read and return the number of active jiffies for the system
int16_t LinuxParser::ActiveJiffies() { return 0; }

// TODO(@sangwon): Read and return the number of idle jiffies for the system
int16_t LinuxParser::IdleJiffies() { return 0; }

// TODO(@sangwon): Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> res;
  string line;
  string key;
  string value;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
    }
  }
  return res;
}

int16_t LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return stof(value);
        } else {
          // Do Nothing
        }
      }
    }
  }

  return 0;
}

int16_t LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return stof(value);
        } else {
          // Do Nothing
        }
      }
    }
  }

  return 0;
}

// TODO(@sangwon): Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int16_t pid [[maybe_unused]]) { return string(); }

// TODO(@sangwon): Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int16_t pid [[maybe_unused]]) { return string(); }

// TODO(@sangwon): Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int16_t pid [[maybe_unused]]) { return string(); }

// TODO(@sangwon): Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int16_t pid [[maybe_unused]]) { return string(); }

// TODO(@sangwon): Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
int16_t LinuxParser::UpTime(int16_t pid [[maybe_unused]]) { return 0; }
