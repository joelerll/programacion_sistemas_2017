#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h> // exit()
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
void dostuff(int sockfd);

void error(char *msg)
{
    perror(msg);
    exit(-1);
}

int status = 0;
pid_t pmaster = 0;
void senal(int senal) {
    printf(ANSI_COLOR_RED "Parado el servidor con socketid %d" ANSI_COLOR_RESET "\n",pmaster);
    wait(NULL);
    close(pmaster);
    // kill(pmaster, SIGKILL);
    // printf("El id de la senal fue %d\n", senal);
    // exit(0);
}

void terminado(int senal) {
  printf("Servidor stop %d\n", senal);
}

int main(int argc, char *argv[])
{
  // definicion de las variables
  int sockfd, newsockfd = 0;
  struct sockaddr_in serv_addr;
  int pid;
  // comprobación de argumentos de entrada
  if (argc < 2) {
    fprintf(stderr,"ERROR, la direccion no esta ingresada\n");
    exit(-1);
  }
  if (argc < 3) {
    fprintf(stderr,"ERROR, el puerto no esta especificado\n");
    exit(-1);
  }

  // inicializacion del socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR al iniciar el socket");

  // set el puerto y los datos necesarios para inicializar el server
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    error("ERROR en bind socket");
  
  //100000 solicitudes pueden ser escuchadas
  listen(sockfd,100000);
  signal(SIGINT, SIG_IGN); 
  signal(SIGTSTP, senal);
  // signal(SIGINT, terminado);
  while (1) {
        // pmaster = getpid();
        pmaster = sockfd;
        //  printf("El parent %d\n", (int) getpid());
        if (sockfd > 0) {
         newsockfd = accept(sockfd,NULL,NULL);
        }
         if (newsockfd < 0) {
           exit(0);
           error("ERROR on accept");
         } 
         pid = fork();

         if (pid < 0) {
            error("ERROR on fork");
         }
         if (pid == 0)  { // childs process
             close(sockfd);
             dostuff(newsockfd);
            //  if (waitpid(pid, &status, WNOHANG) == pid) died = 1;
            //  if (!died) kill(pid, SIGKILL);
             exit(0);
         }
         else { // parent process
           wait(NULL);
           close(newsockfd);
         }
     } 

  return 0;
}

void dostuff(int newsockfd){
  // printf("hijo %d", pid);
  char buffNombreArchivo[256];
  unsigned char buffInfo[8000000]={0};
  int n;

  bzero(buffNombreArchivo,sizeof(buffNombreArchivo));
  bzero(buffInfo,sizeof(buffInfo));

  n = read(newsockfd, buffNombreArchivo, sizeof(buffNombreArchivo));

  if (n < 0) 
    error("ERROR al leer el socket");

  //Se abre archivo que contiene información solicitada por el cliente
  FILE *fp = fopen(buffNombreArchivo,"rb");

  if(fp==NULL) {
    printf("El archivo no existe\n");
    close(newsockfd);

  } else {

    int nread;
    //Se divide la información y se le envía el cliente en "pedazos"
    while((nread = fread(buffInfo,1,sizeof(buffInfo),fp))>0){
      write(newsockfd,buffInfo,nread);
      bzero(buffInfo,sizeof(buffInfo));

      if (feof(fp)){
        printf("Terminado de copiar el archivo. Comando ejecutado: get %s\n",buffNombreArchivo);
        write(newsockfd,"",0);
      }
    }
    fclose(fp);
    close(newsockfd);
    // kill(pid, SIGKILL);
    printf("------------------------------------------------------------\n");

  }

}