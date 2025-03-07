#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <sstream>

void checkClusterStatus() {
    std::cout << "Fetching cluster status...\n"; 

    const char* command = "sinfo";
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        std::cerr << "Error: Unable to fetch cluster status\n"; 
        return; 
    } 

    std::ostringstream result;
    char buffer[256]; 

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result << buffer; 
    }

    pclose(pipe); 
    std::istringstream inp; 
}