#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{

    int sockfd, n;
    int bytesReceived = 0;
    struct sockaddr_in serv_addr;
    unsigned char recvBuff[8000000];
    
    if (argc < 2) {
      fprintf(stderr,"Ingresar el puerto ip");
      exit(-1);
    }
    if (argc < 3) {
       fprintf(stderr,"Ingresar el puerto");
       exit(-1);
    }
    if (argc < 4) {
       fprintf(stderr,"Ingresar el path de la imagen");
       exit(-1);
    }
    if (argc < 5) {
       fprintf(stderr,"Ingresar la salida de la imagen");
       exit(-1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
  	serv_addr.sin_port = htons(atoi(argv[2]));
  	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
        // error("ERROR connecting");
    }

    //se crea archivo nuevo
    FILE *fp = fopen(argv[4],"ab");
    
    n = write(sockfd,argv[3],strlen(argv[3]));
    
    if (n < 0)
         error("ERROR writing to socket");
    
    bytesReceived = read(sockfd, recvBuff, sizeof(recvBuff));

    if(bytesReceived==0){
      printf("Archivo no encontrado\n");
    }

    //Se procesa información y se escribe en archivo conforme llega del servidor.
    while(bytesReceived > 0) {
      fwrite(recvBuff, 1,bytesReceived,fp);
      bzero(recvBuff,sizeof(recvBuff));
      bytesReceived = read(sockfd, recvBuff, sizeof(recvBuff));
      if(bytesReceived==0){
        fclose(fp);
        printf("Archivo guardado\n");
      }
    }
    
    return 0;
}
