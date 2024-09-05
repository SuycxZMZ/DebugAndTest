#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {

    int server_fd, client_fd;
    
    // 创建
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == server_fd) {
        std::cerr << "server socket create err" << std::endl;
        return -1;
    }

    // 绑定
    sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))) {
        std::cerr << "server bind err" << std::endl;
        close(server_fd);
        return -1;
    }


    // 监听
    if (listen(server_fd, 500) == -1) {
        std::cerr << "server listen err" << std::endl;
        close(server_fd);
        return -1;
    }

    std::cout << "start listen at port 8080 ......" << std::endl;
    socklen_t client_addr_len = 0;
    char recv_buf[BUFFER_SIZE] = {0};
    while (1)
    {
        // 死循环，accept --> recv --> send
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len)) == -1)
        {
            std::cerr << "accept error: " << errno << std::endl;
            continue;
        }

        // 连接了, 打印客户端信息
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        std::cout << "accept connection from : " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl;

        // echo 循环
        ssize_t bytes_recv = 0;
        while (((bytes_recv = recv(client_fd, recv_buf, BUFFER_SIZE, 0)) > 0)) {
            send(client_fd, recv_buf, bytes_recv, 0);
        }
        std::cout << "connection close by client ..." << std::endl;
        close(client_fd);
    }

    // 跑出循环了
    close(server_fd);
    return 0;
}
