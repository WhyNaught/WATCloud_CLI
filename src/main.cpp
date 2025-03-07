#include <iostream>
#include "status.h"
#include "daemon.h"
#include "quota.h"

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) { // we only have three very specific commands (for now)
        std::cerr << "Usage: watcloud <command> <optional: specifier>\n"; 
        return 1; 
    }
    std::string command = argv[1]; 
    std::string specifier = ""; 
    if (argc == 3) { // ensures that we don't access unavailable memory
        specifier = argv[2]; 
    }
    if (command == "status") {
        checkClusterStatus(); // imported from status.h
    } else if (command == "daemon" && specifier == "status") {
        checkDaemonStatus(); // imported from daemon.h
    } else if (command == "quota" && specifier == "status") {
        checkQuotaStatus(); // imported from quota.h
    } else {
        std::cerr << "Unknown command: " << command << "\n";
        return 1; 
    }
    return 0; 
}