#include <iostream>

void checkQuotaStatus() {
    std::cout << "Checking quota usage...\n";
    const char* command = "getfattr -n ceph.quota \"$HOME\""; // checks quota usage of the home directory according to SLURM docs
    FILE* pipe = popen(command, "r"); 
    if (!pipe) {
        std::cerr << "Unable to open pipe from terminal input\n";
    }
    
}