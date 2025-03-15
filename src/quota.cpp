#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <regex>
#include <string> 

void checkQuotaStatus() {
    std::cout << "Checking quota usage...\n";
    const char* command = "getfattr -n ceph.dir.rbytes \"$HOME\""; // checks quota usage of the home directory according to SLURM docs
    FILE* pipe = popen(command, "r"); 
    if (!pipe) {
        std::cerr << "Unable to open pipe from terminal input\n";
        return; 
    }

    std::ostringstream result1; 
    char buffer[256]; 
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result1 << buffer; 
    }
    pclose(pipe); 

    const char* command2 = "getfattr -n ceph.dir.rfiles \"$HOME\""; 
    FILE* pipe2 = popen(command, "r"); 
    if (!pipe2) {
        std::cerr << "Unable to open pipe from terminal input\n";
        return; 
    }
    
    std::ostringstream result2; 
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result2 << buffer;
    }
    pclose(pipe2); 

    // we use regular expression matching to get the byte usage from result1 and the file usage from result2
    std::string bytesOutput = result1.str(); 
    std::string filesOutput = result2.str(); 

    std::regex pattern("\"(\\d+)\""); 
    std::smatch matches; 
    std::string bytesUsage; 
    std::string filesUsage; 
    double gigabyteUsage; 
    if (std::regex_search(bytesOutput, matches, pattern)) {
        bytesUsage = matches[1]; 
        std::uint64_t byteUsage = std::stoull(bytesUsage);
        gigabyteUsage = byteUsage / (1024.0 * 1024.0 * 1024.0);
    } else {
        std::cerr << "Bytes output could not be retrieved from pipe";
        return; 
    }

    if (std::regex_search(filesOutput, matches, pattern)) {
        filesUsage = matches[1]; 
    } else {
        std::cerr << "Files output could not be retrived from pipe";
        return;  
    }

    std::cout << "You are using " << gigabyteUsage << "GiB out of 20 GiB and " << filesUsage << " files.\n"; 
}