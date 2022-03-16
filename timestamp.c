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

#define NTP_TIMESTAMP_DELTA 2208988800ull

#define LI(packet)   (uint8_t) ((packet.li_vn_mode & 0xC0) >> 6) 
#define VN(packet)   (uint8_t) ((packet.li_vn_mode & 0x38) >> 3) 
#define MODE(packet) (uint8_t) ((packet.li_vn_mode & 0x07) >> 0) 

long int timestamp;

  typedef struct
  {
    uint8_t li_vn_mode;      
    uint8_t stratum;         
    uint8_t poll;            
    uint8_t precision;       
    uint32_t rootDelay;      
    uint32_t rootDispersion; 
    uint32_t refId;          
    uint32_t refTm_s;        
    uint32_t refTm_f;        
    uint32_t origTm_s;       
    uint32_t origTm_f;       
    uint32_t rxTm_s;         
    uint32_t rxTm_f;         
    uint32_t txTm_s;         
    uint32_t txTm_f;         

  } ntp_packet;             


void error( char* msg )
{
    perror( msg );
    exit( 0 ); 
}


void *timeout_server()
{
  int sockfd, n; // Socket file descriptor and the n return result from writing/reading from the socket.

  int portno = 123; // NTP UDP port number.

  //char* host_name = "pxe.server"; // NTP server host-name.
  char* host_name = "pxes.server"; // NTP server host-name.
  
  ntp_packet packet = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  memset( &packet, 0, sizeof( ntp_packet ) );
  *( ( char * ) &packet + 0 ) = 0x1b;
  struct sockaddr_in serv_addr; 
  struct hostent *server;      

  sockfd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ); // Create a UDP socket.
  printf("conextando al server %s\n",host_name );

  server = gethostbyname( host_name ); // Convert URL to IP.
  if(!server){
    printf("fa");
  }

  /*
  if(server = NULL){
    timestamp = 99;
  }*/

  bzero( ( char* ) &serv_addr, sizeof( serv_addr ) );
  serv_addr.sin_family = AF_INET;
  bcopy( ( char* )server->h_addr, ( char* ) &serv_addr.sin_addr.s_addr, server->h_length );
  serv_addr.sin_port = htons( portno );
  n = write( sockfd, ( char* ) &packet, sizeof( ntp_packet ) );
  n = read( sockfd, ( char* ) &packet, sizeof( ntp_packet ) );
  packet.txTm_s = ntohl( packet.txTm_s ); // Time-stamp seconds.

  timestamp = ( time_t ) ( packet.txTm_s - NTP_TIMESTAMP_DELTA );
  
}
  

time_t get_pxe_server_timestamp(){

  timestamp = time(0);
    pthread_t thread_id;

    pthread_create(&thread_id,NULL,*timeout_server,NULL);
    //pthread_join(thread_id,NULL);
  sleep(3);
  
  return timestamp;

}


