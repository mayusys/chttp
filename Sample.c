#include <sys/fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void){
    int rsock, wsock;
    socklen_t len;
    struct sockaddr_in reader_addr, writer_addr;

    // socket生成
    rsock = socket(AF_INET, SOCK_STREAM, 0);

    // socket setting
    reader_addr.sin_family = AF_INET;
    reader_addr.sin_port = htons(8080);
    reader_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // socket binding
    if(bind(rsock, (struct sockaddr *)&reader_addr, sizeof(reader_addr)) < 0) {
        perror("reader: bind");
        exit(1);
    }

    // listen socket
    if (listen(rsock, 5) < 0) {
        perror("reader: listen");
        close(rsock);
        exit(1);
    }

    // accept TCP connection
    wsock = accept(rsock, (struct sockaddr *)&writer_addr, &len);
    if(wsock < 0) {
        perror("reader: accept");
        exit(1);
    }

    write(wsock, "HTTP1.1 200 OK", 14);

    close(rsock);
    close(wsock);

    return 0;
}
