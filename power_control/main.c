#include "../include/network.h"
#include "../include/kernel.h"



int main() {
    int server_fd = sceNetSocket("server", AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = 0;
    address.sin_port = sceNetHtons(9090);

    sceNetBind(server_fd, (struct sockaddr *)&address, sizeof(address));
    sceNetListen(server_fd, 3);
    
    while(1) {
        int client_socket = sceNetAccept(server_fd, NULL, NULL);
        if (client_socket < 0) continue;

        char buffer[1024];
        sceNetRecv(client_socket, buffer, 1024, 0);

        if (buffer[0] == 's') {
            sceKernelShutdownSystem();
        } else if (buffer[0] == 'r') {
            sceKernelReboot();
        }

        sceNetClose(client_socket);
    }
    return 0;
}
