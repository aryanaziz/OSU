#include <cassert>
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sa_dst;
    memset(&sa_dst, 0, sizeof(struct sockaddr_in));
    sa_dst.sin_family = AF_INET;
    sa_dst.sin_port = htons(1234);
    sa_dst.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = connect(fd, (struct sockaddr *)&sa_dst, sizeof(struct sockaddr));
    assert(ret != -1);

    std::ofstream file;
    file.open("filename", std::ios::out | std::ios::binary);
    assert(file.is_open());
    char buffer[255];
    while (1) {
        std::cout << "..";
        ssize_t p = read(fd, buffer, sizeof(buffer));
        assert(p != -1);
        if (p == 0)
            break;
        file.write(buffer, p);
    }
    file.close();
}