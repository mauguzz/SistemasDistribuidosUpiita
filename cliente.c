#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h> /* es necesaria por la estructura hostend */

#define PORT 3550   /*El puerto abierto delnodo remoto */
#define MAXDATASIZE 100 /*El número máximo de datos en bytes */

int main(int argc, char *argv[]){

          int fd, numbytes;   /*ficheros descriptores */
          char buf[MAXDATASIZE]; /*En donde se almacenará el texto recibido */
          struct hostent *he; /*estructura que recibirá información sobre el nodo remoto */
          struct sockaddr_in server; /*información sobre la dirección del servidor */
          
          if(argc !=3){
                    /*esto es porque nuestro programa solo necesitará un argumento (la IP) */
                    printf("Uso: %s <Dirección IP> <Puerto>\n",argv[0]);
                    exit(EXIT_FAILURE);
          }
          if((he=gethostbyname(argv[1]))==NULL){
                    /*llamada a gethostbyname() */
                    perror("gethostbyname() error\n");
                    exit(EXIT_FAILURE);
          }
          if((fd=socket(AF_INET, SOCK_STREAM,0))==-1){
                    /* llamada a socket() */
                    perror("socket() error\n");
                    exit(EXIT_FAILURE);
          }
          
          server.sin_family=AF_INET;
          server.sin_port=htons(atoi(argv[2])); //PORT /*htons() es necesaria nuevamente ;-o */
          server.sin_addr = *((struct in_addr *)he->h_addr); /**he->h_addr pasa lainformación de '*he' a 'h_addr' */
          
          bzero(&(server.sin_zero),8);
          if(connect(fd,(struct sockaddr *)&server,sizeof(struct sockaddr))==-1){
                    /* llamada a connect() */
                    perror("connect() error\n");
                    exit(EXIT_FAILURE);
          }

          send(fd, "15\n",3,0);   /*Cantidad de caracteres que enviará al cliente */
          sleep(1);
          send(fd, "Hola servidor.\n",15,0);   /*Que enviará elmensaje de bienvenida al cliente */
          
          if((numbytes=recv(fd,buf,MAXDATASIZE,0))==-1){
                    /*llamada a recv()*/
                    perror("Error en recv() \n");
                    exit(EXIT_FAILURE);
          }
          
          buf[numbytes]='\0';
          printf("Cantidad de caracteres del mensaje del servidor: %s\n",buf);         /*Muestrea elmensaje de bienvenida del servidor */
          if((numbytes=recv(fd,buf,MAXDATASIZE,0))==-1){
                    /*llamada a recv()*/
                    perror("Error en recv() \n");
                    exit(EXIT_FAILURE);
          }
          
          buf[numbytes]='\0';
          printf("Mensaje del servidor: %s\n",buf);         /*Muestrea elmensaje de bienvenida del servidor */
          close(fd);   /*cerramos fd */


}
