#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <sstream>

void checkClusterStatus() {
    std::cout << "Fetching cluster status...\n"; // faux loading lol

    const char* command = "sinfo"; // I am assuming that the cluster status is just an alias for sinfo
    FILE* pipe = popen(command, "r");
    if (!pipe) { // error in creating a pipe 
        std::cerr << "Error: Unable to fetch cluster status\n"; 
        return; 
    } 

    std::ostringstream result;
    char buffer[256]; // buffer for more efficient memory management 

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result << buffer; // pipe the data from the pipe into the result via the buffer, 256 chars at a time
    }

    pclose(pipe); // close the pipe 
    std::istringstream iss(result.str()); // convert result to stdin string stream 
    std::string line; 
    bool headerSkipped = false; 
    while (std::getline(iss, line)) { // output to standard output 
        if (line.empty()) {continue;}
        if (!headerSkipped) {headerSkipped = true; continue;}
        std::istringstream lineStream(line); 
        std::string partition, avail, timeLimit, nodes, state, nodeList; 
        lineStream >> partition >> avail >> timeLimit >> nodes >> state >> nodeList; 
        std::cout << "Partition: " << partition << "\n"; 
        std::cout << "Availability: " << avail << "\n"; 
        std::cout << "Time Limit: " << timeLimit << "\n"; 
        std::cout << "Nodes: " << nodes << "\n"; 
        std::cout << "State: " << state << "\n";  
        std::cout << "Node List: " << nodeList << "\n";  // prints the data more cleanly 
    } 
}