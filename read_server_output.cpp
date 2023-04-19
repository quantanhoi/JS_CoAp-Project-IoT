#include <iostream>
#include <cstdio>
#include <cstring>

int main() {
    const char* command = "node coap_server.js";
    char buffer[128];
    FILE* pipe = popen(command, "r");

    if (!pipe) {
        std::cerr << "Could not open pipe" << std::endl;
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::cout << "C++ program received: " << buffer;
    }

    pclose(pipe);
    return 0;
}