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
   gint64 seconds_utc_current_time_from_server = timestamp;

   switch (timestamp)
   {
   case 0:
      printf("\nNTP SERVER NOT INSTALLED\n");
      break;
   case 1:
      printf("\nSERVER NOT FOUND\n");
      break;
   default:
      printf("\nTimestamp from server: %li\n", (long int)seconds_utc_current_time_from_server);
      printf("time-Date: %s\n", ctime(&seconds_utc_current_time_from_server));
      return 0;
   }
}
