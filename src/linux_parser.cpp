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
using std::stoi;
using std::stol;
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

vector<int16_t> LinuxParser::Pids() {
    vector<int16_t> pids;
    DIR* directory = opendir(kProcDirectory.c_str());
    struct dirent* file;
    while ((file = readdir(directory)) != nullptr) {
        // Is this a directory?
        if (file->d_type == DT_DIR) {
            // Is every character of the name a digit?
            string filename(file->d_name);
            if (std::all_of(filename.begin(), filename.end(), isdigit)) {
                int16_t pid = stoi(filename);
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
                } else if (key == "Shmem") {
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

int16_t LinuxParser::Jiffies() { return 0; }

int16_t LinuxParser::ActiveJiffies(int16_t pid [[maybe_unused]]) { return 0; }

int16_t LinuxParser::ActiveJiffies() { return 0; }

int16_t LinuxParser::IdleJiffies() { return 0; }

vector<string> LinuxParser::CpuUtilization() {
    vector<string> jiffies;
    vector<int16_t> params;
    string line;
    string key;

    int16_t idle = 0;
    int16_t active = 0;
    float util = 0.f;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            linestream >> key;
            while (linestream >> key) {
                params.emplace_back(stoi(key));
            }
            idle = params[3] + params[4];
            active = params[0] + params[1] + params[4] + params[6] + params[7];
            util = active / static_cast<float>(idle + active);
            jiffies.emplace_back(to_string(util));
        }
    }
    return jiffies;
}

float LinuxParser::CpuUtilization(int16_t pid) {
    string line;
    vector<string> columns;
    string column;

    std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        while (linestream.good()) {
            columns.emplace_back(column);
        }
    }
    int total_process_ticks = 0;
    for (auto idx : {13, 14, 15, 16}) {
        if (idx < static_cast<int>(columns.size())) {
            total_process_ticks += stoi(columns[idx]);
        }
    }
    float total_process_time =
        total_process_ticks / static_cast<float>(sysconf(_SC_CLK_TCK));
    int16_t total_seconds = UpTime() + UpTime(pid);

    return total_seconds != 0
               ? (total_process_time / static_cast<float>(total_seconds))
               : 0.0;
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

string LinuxParser::Command(int16_t pid) {
    string line;
    std::ifstream filestream(kProcDirectory + to_string(pid) +
                             kCmdlineFilename);
    if (filestream.is_open()) {
        std::getline(filestream, line);
    }
    return line;
}

string LinuxParser::Ram(int16_t pid) {
    string line;
    string key;
    int32_t ram = 0;

    std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            linestream >> key;
            if (key == "VmSize:") {
                linestream >> ram;
                break;
            }
        }
    }
    return to_string(ram / 1024);
}

string LinuxParser::Uid(int16_t pid) {
    string line;
    string key;
    string uid = "";

    std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            linestream >> key;
            if (key == "Uid:") {
                linestream >> uid;
                break;
            }
        }
    }
    return uid;
}

string LinuxParser::User(int16_t pid) {
    string line;
    string user, pw, uid;
    std::ifstream filestream(kPasswordPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);

            while (linestream >> user >> pw >> uid) {
                if (uid == LinuxParser::Uid(pid)) {
                    break;
                }
            }
        }
    }
    return user;
}

int16_t LinuxParser::UpTime(int16_t pid) {
    string line;
    string value;
    vector<string> states;

    std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        while (linestream >> value) {
            states.emplace_back(value);
        }
    }

    return LinuxParser::UpTime() - stol(states[21]) / sysconf(_SC_CLK_TCK);
}
