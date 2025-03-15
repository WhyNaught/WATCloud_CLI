#include <iostream>
#include <sstream>
#include <regex>

void checkDaemonStatus() {
    std::cout << "Checking Docker daemon status..."; 
    char* startCommand = "systemctl --user status docker-rootless"; 
    FILE* pipe = popen(startCommand, "r");
    if (!pipe) {
        std::cerr << "Error opening pipe"; 
        return; 
    }

    std::ostringstream result; 
    char buffer[256]; 
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result << buffer; 
    }
    pclose(pipe);
    std::string message = result.str(); 
    std::smatch match; 

    std::regex active(R"(Active:\s+(\w+))"); 
    std::regex pid(R"(Main PID:\s+(\d+))");
    std::regex tasks(R"(Tasks:\s+(\d+))");
    std::regex memory(R"(Memory:\s+(\d+))");
    std::regex cpuUsage(R"(CPU:\s+(\d+))");

    std::string as; 
    std::string pd; 
    std::string tsks; 
    std::string mem; 
    std::string cpu; 

    if (!std::regex_search(message, match, active)) {
        std::cerr << "Something went wrong with the regex matching"; 
        return; 
    } else if (std::regex_search(message, match, active)) {
        as = match[1]; 
    }

    std::cout << "Docker Rootless Status:\n"; 
    std::cout << ; 
}