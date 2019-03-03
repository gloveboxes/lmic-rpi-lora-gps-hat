// gcc -o gps-test gps-test.cpp -lm -lgps
#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main() {

uint8_t coords[8];

int rc;
struct timeval tv;

struct gps_data_t gps_data;
if ((rc = gps_open("localhost", "2947", &gps_data)) == -1) {
    printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
    return EXIT_FAILURE;
}
gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

while (1) {
    /* wait for .5 seconds to receive data */
    if (gps_waiting (&gps_data, 500000)) {
        /* read data */
        if ((rc = gps_read(&gps_data)) == -1) {
            printf("error occured reading gps data. code: %d, reason: %s\n", rc, gps_errstr(rc));
        } else {
            /* Display data from the GPS receiver. */
            if ((gps_data.status == STATUS_FIX) && 
                (gps_data.fix.mode == MODE_2D || gps_data.fix.mode == MODE_3D) &&
                !isnan(gps_data.fix.latitude) && 
                !isnan(gps_data.fix.longitude)) {
                    printf("latitude: %f, longitude: %f, altitude: %f, hdop: %f, timestamp: %lf\n", gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.altitude, gps_data.dop.hdop, gps_data.fix.time); 
		int32_t lat = gps_data.fix.latitude * -10000;
int32_t lon = gps_data.fix.longitude * 10000;

// Pad 2 int32_t to 6 8uint_t, skipping the last byte (x >> 24)
coords[0] = lat;
coords[1] = lat >> 8;
coords[2] = lat >> 16;

coords[3] = lon;
coords[4] = lon >> 8;
coords[5] = lon >> 16;

coords[6] = floor(gps_data.fix.altitude);
coords[7] = gps_data.dop.hdop*100;
for (int i = 0; i < 8; i++)
{
    printf("%02X ", coords[i]);
}
                    printf("\nPKT latitude: %f, longitude: %f, altitude: %f, hdop: %f\n", 
				floor(gps_data.fix.latitude*1000000), floor(gps_data.fix.longitude*1000000), floor(gps_data.fix.altitude), floor(gps_data.dop.hdop*100)); 
            } else {
                printf("no GPS data available, hdop: %f\n", gps_data.dop.hdop);
            }
        }
    }

    sleep(3);
}

/* When you are done... */
gps_stream(&gps_data, WATCH_DISABLE, NULL);
gps_close (&gps_data);

return EXIT_SUCCESS;
}
