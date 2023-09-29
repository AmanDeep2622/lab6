#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERV_PORT 6000
int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[512];
    char recvline[512];

 if (argc != 2) printf("usage tcpcli <ipaddress>\n");
sockfd = socket(AF_INET, SOCK_STREAM, 0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(6000);
servaddr.sin_addr.s_addr = inet_addr(argv[1]);
connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
fgets(sendline, 512, stdin);
int n = strlen(sendline);
write(sockfd, sendline, n);
n = read(sockfd, recvline, 512);
if (n < 0) printf("error reading\n");
recvline[n] = 0;
fputs(recvline, stdout);
exit(0);



}


//server


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERV_PORT 6000

int main(int argc, char **argv) {
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    char msg1[512];

listenfd = socket(AF_INET, SOCK_STREAM, 0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(SERV_PORT);
bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
listen(listenfd, 5);
for(;;) {
  clilen = sizeof(cliaddr);
  connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
  if ((childpid = fork()) == 0) {
    close(listenfd);
    int n1 = read(connfd, msg1, 512);
    write(connfd, msg1, 50);
    close(connfd);
exit(0);
}
  close(connfd);
}


}
