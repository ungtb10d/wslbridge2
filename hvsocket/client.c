/* 
* This file is part of hvtool project
* Licensed under the GNU General Public License version 3
*/

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/vm_sockets.h>

#ifndef AF_VSOCK
#define AF_VSOCK 40
#endif

#define PORT_NUM 5000
#define BUFF_SIZE 400

int main(void)
{
    int sockfd = socket(AF_VSOCK, SOCK_STREAM, 0);
    if (sockfd < 0)
        printf("socket error: %s\n", strerror(errno));

    struct sockaddr_vm addr;
    memset(&addr, 0, sizeof addr);

    addr.svm_family = AF_VSOCK;
    addr.svm_port = PORT_NUM;
    addr.svm_cid = VMADDR_CID_HOST;
    int ret = connect(sockfd, (struct sockaddr*)&addr, sizeof addr);
    if (ret < 0)
        printf("connect error: %s\n", strerror(errno));

    char msg[BUFF_SIZE];

    while (1)
    {
        memset(msg, 0, sizeof msg);
        printf("Enter message: ");
        scanf("%s", msg);
        ret = send(sockfd, msg, strlen(msg), 0);
        if (ret < 0)
        {
            printf("send error: %s\n", strerror(errno));
            break;
        }
    }

/* cleanup */
    if (sockfd > 0)
        close(sockfd);
    return 0;
}
