#include <stdio.h>
#include <stdlib.h>
#include "timestamp.h"
#include <math.h>
#include <glib.h>
#include <pthread.h>
int main()
{
   system("clear");
   time_t timestamp = get_pxe_server_timestamp();

   GDateTime *utc_current_time = g_date_time_new_now_utc();
   gint64 seconds_utc_current_time_from_lib = g_date_time_to_unix(utc_current_time);
   gint64 seconds_utc_current_time_from_server = timestamp;
   printf("Timestamp from glib: %li\n",(long int) seconds_utc_current_time_from_lib);
   printf("Time-Date: %s\n",ctime(&seconds_utc_current_time_from_lib));
   printf("Timestamp from server: %li\n",(long int) seconds_utc_current_time_from_server);
   printf("time-Date: %s\n",ctime(&seconds_utc_current_time_from_server));
   GDateTime *gdate = g_date_time_new_from_unix_local(timestamp);
   gint64 seconds_utc_current_time = g_date_time_to_unix(gdate);
   printf("converted gdate to long: %li\n",seconds_utc_current_time);
   
   
   printf("fin de programa....");
   return 0;
}







  
