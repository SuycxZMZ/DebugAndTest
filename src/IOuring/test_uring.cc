#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <liburing.h>
 
int main(int argc, char *argv[]) {
    struct io_uring ring;
    int ret;
 
    if (argc != 2) {
        printf("Usage: %s [file]\n", argv[0]);
        return 1;
    }
 
    ret = io_uring_queue_init(8, &ring, 0);
    if (ret) {
        fprintf(stderr, "Unable to setup io_uring: %s\n", strerror(-ret));
        return 1;
    }
 
    printf("I/O uring setup successfully\n");
    io_uring_queue_exit(&ring);
 
    return 0;
}