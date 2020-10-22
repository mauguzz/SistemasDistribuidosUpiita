#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 3550 /*Elpuerto que será abiertp */
#define BACKLOG 2 /*El número de conexiones permitidas */
#define MAXDATASIZE 100 /*El número máximo de datos en bytes */

int main (int argc, char *argv[]){
          
          int fd, fd2, numbytes; /*los ficheros descriptores */
          struct sockaddr_in server; /*para la información de la dirección del servidor */
          struct sockaddr_in client; /*para la información de la dirección del cliente */
          char buf[MAXDATASIZE]; /*En donde se almacenará el texto recibido */
          int sin_size;

          if(argc !=2){
                    /*esto es porque nuestro programa solo necesitará un argumento (la IP) */
                    printf("Uso: %s <Puerto>\n",argv[0]);
                    exit(EXIT_FAILURE);
          }
          
          /*A continuación la llamada a socket() */
          if((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){ perror("error en socket()\n"); exit(EXIT_FAILURE); }
          
          server.sin_family=AF_INET;
          server.sin_port=htons(atoi(argv[1])); //PORT
          server.sin_addr.s_addr=INADDR_ANY;      /*INADDR_ANY coloca nuestra dirección IP automáticamente */
          
          bzero(&(server.sin_zero),8);  /* Escribimos ceros en el resto de la estructura */
          
          /*A continuación la llamadaa bind() */
          if(bind(fd,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1){ perror("error en bind()\n"); exit(EXIT_FAILURE); }
          
          /* Llamada a listen() */
          if(listen(fd,BACKLOG)==-1){ perror("error en listen()\n"); exit(EXIT_FAILURE); }
          
          //while(1){
                    sin_size=sizeof(struct sockaddr_in);
                    /* A continuación la llamada a accept() */
                    if((fd2=accept(fd,(struct sockaddr*)&client,&sin_size))==-1) { perror("error en accept()\n"); exit(EXIT_FAILURE); }
                    //printf("Se obtuvo una conexión desde %s\n",inet_ntoa(client.sin_addr));         /* Que mostrará la IP del cliente */

                    if((numbytes=recv(fd2,buf,MAXDATASIZE,0))==-1){
                        /*llamada a recv()*/
                        perror("Error en recv() \n");
                        exit(EXIT_FAILURE);
                    }
                    buf[numbytes]='\0';
                    printf("Cantidad de caracteres, especificados por el cliente conectado: %s\n",buf);         /*Muestra el mensaje enviado por el cliente */
                    if((numbytes=recv(fd2,buf,MAXDATASIZE,0))==-1){
                        /*llamada a recv()*/
                        perror("Error en recv() \n");
                        exit(EXIT_FAILURE);
                    }
                    buf[numbytes]='\0';
                    printf("Mensaje recibido, enviado por el cliente conectado: %s\n",buf);         /*Muestra el mensaje enviado por el cliente */
                    
                    send(fd2, "14\0",3,0);   /*Cantidad de caracteres que enviará al cliente */
                    sleep(1);
                    send(fd2, "Hola cliente.\0",14,0);   /*Que enviará elmensaje de bienvenida al cliente */
                    close(fd2); /* cierra fd2*/
          //}

}

