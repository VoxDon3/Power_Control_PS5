#include "protocol.h"

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef long unsigned int size_t;
typedef long ssize_t;
typedef int socklen_t;

struct in_addr {
    uint32_t s_addr;
};

struct sockaddr_in {
    unsigned char sin_len;
    unsigned char sin_family;
    uint16_t sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};

struct sockaddr {
    unsigned char sa_len;
    unsigned char sa_family;
    char sa_data[14];
};

#define AF_INET 2
#define SOCK_STREAM 1
#define SOL_SOCKET 0xffff
#define SO_REUSEADDR 0x0004
#define INADDR_ANY 0
#define CUSTOM_HTONS(n) (uint16_t)((((n) & 0xFF) << 8) | (((n) & 0xFF00) >> 8))

int socket(int domain, int type, int protocol);
int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
int bind(int s, const struct sockaddr *addr, socklen_t addrlen);
int listen(int s, int backlog);
int accept(int s, struct sockaddr *addr, socklen_t *addrlen);
ssize_t read(int fd, void *buf, size_t nbytes);
int close(int fd);

void custom_memset(void *ptr, int value, size_t num) {
    unsigned char *p = (unsigned char *)ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
}

int custom_strncmp(const char *s1, const char *s2, size_t n) {
    while (n > 0 && *s1 && (*s1 == *s2)) {
        s1++;
        s2++;
        n--;
    }
    if (n == 0) return 0;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        return 1;
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    custom_memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = CUSTOM_HTONS(9090);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        return 1;
    }

    while(1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            continue;
        }

        custom_memset(buffer, 0, 1024);
        read(client_socket, buffer, 1023);

        if (custom_strncmp(buffer, "shutdown", 8) == 0) {
            sceKernelShutdownSystem();
        } else if (custom_strncmp(buffer, "reboot", 6) == 0 || custom_strncmp(buffer, "restart", 7) == 0) {
            sceKernelReboot();
        } else if (custom_strncmp(buffer, "rest", 4) == 0) {
            sceKernelSuspendSystem();
        }

        close(client_socket);
    }

    return 0;
}
