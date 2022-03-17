#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <glib.h>
#include <arpa/inet.h>

#include "timestamp.h"


#define NTP_TIMESTAMP_DELTA 2208988800ull
#define PXE_SERVER_ADRESS "pxe.server"

#define LI(packet)   (uint8_t) ((packet.li_vn_mode & 0xC0) >> 6) 
#define VN(packet)   (uint8_t) ((packet.li_vn_mode & 0x38) >> 3) 
#define MODE(packet) (uint8_t) ((packet.li_vn_mode & 0x07) >> 0) 

long int timestamp;
ntp_server_t timestam;
ntp_packet packet = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int sockfd, n; 
int portno = 123; 
struct hostent *server;   
struct sockaddr_in serv_addr;

void *timeout_server()
{
  void init_server(ntp_server_t * server_stats);

  memset( &packet, 0, sizeof( ntp_packet ) );
  *( ( char * ) &packet + 0 ) = 0x1b;

  printf("creando soket...\n");
  sockfd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ); // Create a UDP socket.
  if (sockfd < 0)
        printf("error al crear el soket\n");

  printf("conectando al server %s\n",PXE_SERVER_ADRESS );
  char *IPbuffer;
  IPbuffer = inet_ntoa(*((struct in_addr*)
                           server->h_addr_list[0]));
  printf("direccion %s\n",IPbuffer);

  bzero( ( char* ) &serv_addr, sizeof( serv_addr ) );
  serv_addr.sin_family = AF_INET;
  bcopy( ( char* )server->h_addr, ( char* ) &serv_addr.sin_addr.s_addr, server->h_length );

  serv_addr.sin_port = htons( portno );

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      printf("error al conectar");

  printf("enviando paquete...\n");
  n = write( sockfd, ( char* ) &packet, sizeof( ntp_packet ) );
  printf("Paquete enviado...%i\n",n);

  n = read( sockfd, ( char* ) &packet, sizeof( ntp_packet ) );

  printf("paquete recivido...\n");
  packet.txTm_s = ntohl( packet.txTm_s ); // Time-stamp seconds.

  timestamp = ( time_t ) ( packet.txTm_s - NTP_TIMESTAMP_DELTA );

  printf("asjdkhasjdh %li\n",timestamp);

}
  

time_t get_pxe_server_timestamp(){
  
  server = gethostbyname(PXE_SERVER_ADRESS);
  if(server == NULL)
    return EXIT_FAILURE;
  
  pthread_t thread_id;
  pthread_create(&thread_id,NULL,*timeout_server,NULL);  
  sleep(3);
  pthread_cancel(thread_id);
  return timestamp;
}


void init_server(ntp_server_t * const server){
    server->adress[0] = '\0';
    server->portn = 0U;
    server->timestamp = 0UL; 
}
