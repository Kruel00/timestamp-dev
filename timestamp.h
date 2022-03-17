#include <time.h>
#include <netdb.h>
time_t get_pxe_server_timestamp();


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


  typedef struct ntp_server_s
{
    char adress[64];
    int portn;
    long int timestamp;
    struct hostent server_ip;
    int server_status;

} ntp_server_t;


enum server_status_code{
    SERVER_OK,
    CREATE_SOCKET_FAIL,
    CONNECTION_FAIL,
    SEND_PACKET_FAIL,
    RECIVE_PACKET_FAIL,
};