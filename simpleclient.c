#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
 int sockfd;
 int len;
 struct sockaddr_in address;
 int result;
 char buf[1024] = {0};

 /** �������ݻ��� */
 char get[1024] = {0};

 if (argc < 2)
 {
    fprintf(stderr,"\n\033[31musage:\033[34m%s\033[32m %s|%s|%s|%s\033[0m\t\n\n",argv[0], "get", "post", "head", "options");
    exit(1);
 }

 if (strcmp(argv[1], "get") == 0) {
          char get_buf[1024] = "GET / HTTP/1.1\n\n\n";
          strcpy(buf, get_buf);
 }else if (strcmp(argv[1], "post") == 0) {
          char post_buf[1024] = "POST / HTTP/1.1\nContent-Length: 12 \n\n ";
          strcpy(buf, post_buf);
 }else if (strcmp(argv[1], "head") == 0) {
          char head_buf[1024] = "HEAD / HTTP/1.1\n\n\n";
          strcpy(buf, head_buf);
 }else if (strcmp(argv[1], "options") == 0) {
          char options_buf[1024] = "OPTIONS / HTTP/1.1\n\n\n";
          strcpy(buf, options_buf);
 }else
 {
    fprintf(stderr, "\n\033[31m%s is not legal command or has not implemented yet.\033[0m\n\n", argv[1]);
    exit(1);
 }
  
 /** ����tcp���� */
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 address.sin_family = AF_INET;
 address.sin_addr.s_addr = inet_addr("127.0.0.1");/** ����IP��ַ*/
 address.sin_port = htons(11000);/** tinyhttpd�Ķ˿� */
 len = sizeof(address);

 /** �������� */
 result = connect(sockfd, (struct sockaddr *)&address, len);
 if (result == -1)
 {
  perror("oops:client:");
  _exit(1);
 }
 
 /** ����http���� */
 write(sockfd,buf, sizeof(buf)); 
 /** ���ܻ�Ӧ */
 read(sockfd, get, sizeof(get));

 /**��ӡ�������� */
 printf("-----------------------------show buffer -----------------------------\n");
 printf("%s",get);
 printf("----------------------------------------------------------------------\n");
 /** �Ͽ����� */
 close(sockfd);
 _exit(0);
}
