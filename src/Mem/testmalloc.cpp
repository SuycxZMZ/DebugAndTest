#include <iostream>
#include <cstdlib> // for malloc, free
#include <unistd.h> // for sleep

int main() {
    const size_t blockSize = 1024 * 1024; // 1 MB
    size_t totalAllocated = 0;
    while (true) {
        void* block = malloc(blockSize);
        if (block == nullptr) {
            std::cerr << "Memory allocation failed after allocating " << totalAllocated / (1024 * 1024) << " MB" << std::endl;
            break;
        } else {
            totalAllocated += blockSize;
            std::cout << "Allocated " << totalAllocated / (1024 * 1024) << " MB" << std::endl;
            // Optionally, sleep for a short time to slow down the allocation process
            // sleep(1); // sleep for 1 second
        }
    }

    // Clean up the allocated memory (if you want to observe behavior after allocation failure)
    // while (true) {
    //     free(malloc(blockSize));
    // }

    return 0;
}
