#include "protocol.h"
#include "../ps5-payload-sdk/include/network.h"

// هذه الدوال معتمدة من الـ SDK المرفق في مشروعك
void notify(const char *message) {
    // التعديل هنا يعتمد على دالة الـ notify المتاحة في SDK الخاص بك
    // إذا لم تكن موجودة، اتركها فارغة أو استخدم sceLibcPrintf إن توفرت
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    
    // استخدام دالة الـ SDK للشبكات
    server_fd = sceNetSocket("server", AF_INET, SOCK_STREAM, 0);
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = 0; // INADDR_ANY
    address.sin_port = sceNetHtons(9090);

    sceNetBind(server_fd, (struct sockaddr *)&address, sizeof(address));
    sceNetListen(server_fd, 3);
    
    while(1) {
        int client_socket = sceNetAccept(server_fd, NULL, NULL);
        if (client_socket < 0) continue;

        char buffer[1024];
        sceNetRecv(client_socket, buffer, 1024, 0);

        if (buffer[0] == 's') { // اختصار لـ shutdown
            sceKernelShutdownSystem();
        } else if (buffer[0] == 'r') { // اختصار لـ reboot
            sceKernelReboot();
        }

        sceNetClose(client_socket);
    }
    return 0;
}
