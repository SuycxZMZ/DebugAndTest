//
// Created by yuan su on 24-5-11.
//
/**
 * @brief 共享内存线程通信
 * @details shm_open
 *          ftruncate
 *          mmap
 *          munmap
 *          close
 *          shm_unlink
 * */
#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstring>

const char* SHARED_MEMORY_NAME = "/my_shared_memory";
const int SHARED_MEMORY_SIZE = 1024;

void writerThread() {
    // 创建或打开共享内存对象
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to open shared memory" << std::endl;
        return;
    }

    // 调整共享内存对象的大小
    if (ftruncate(shm_fd, SHARED_MEMORY_SIZE) == -1) {
        std::cerr << "Failed to truncate shared memory" << std::endl;
        return;
    }

    // 将共享内存映射到进程的地址空间
    void* ptr = mmap(0, SHARED_MEMORY_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Failed to map shared memory" << std::endl;
        return;
    }

    // 写入数据到共享内存
    const char* message = "Hello from writer thread!";
    std::memcpy(ptr, message, strlen(message) + 1);

    // 解除映射并关闭共享内存对象
    munmap(ptr, SHARED_MEMORY_SIZE);
    close(shm_fd);
}

void readerThread() {
    // 打开共享内存对象
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to open shared memory" << std::endl;
        return;
    }

    // 将共享内存映射到进程的地址空间
    void* ptr = mmap(0, SHARED_MEMORY_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Failed to map shared memory" << std::endl;
        return;
    }

    // 读取共享内存中的数据
    std::cout << "Message read from shared memory: " << static_cast<const char*>(ptr) << std::endl;

    // 解除映射并关闭共享内存对象
    munmap(ptr, SHARED_MEMORY_SIZE);
    close(shm_fd);
}

int main() {
    // 创建一个写入者线程和一个读取者线程
    std::thread writer(writerThread);
    std::thread reader(readerThread);

    // 等待两个线程完成
    writer.join();
    reader.join();

    // 删除共享内存对象
    shm_unlink(SHARED_MEMORY_NAME);

    return 0;
}

