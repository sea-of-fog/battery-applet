#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "unistd.h"
#include "libnotify/notify.h"

static char* BATTERY_PATH = "/sys/class/power_supply/BAT0/capacity";
uint8_t NOTIFY_THRESHOLD = 20;

void read_capacity(uint8_t* capacity){
    FILE *battery_capacity_fptr = fopen(BATTERY_PATH, "r");

    if(battery_capacity_fptr == NULL){
        printf("Error reading file\n");
        exit(1);
    }

    fscanf(battery_capacity_fptr,
           "%u",
           capacity);
    fclose(battery_capacity_fptr);

    return; 
}

int main(){

    uint8_t capacity;

    do {
        read_capacity(&capacity);
        printf("Current battery capacity: %u\n", capacity);
        if(capacity < NOTIFY_THRESHOLD){
            notify_init ("Battery control applet");
            NotifyNotification *low_battery = notify_notification_new ("Low battery", "Battery below 20%", "dialog-information");
            notify_notification_show (Hello, NULL);
            g_object_unref(G_OBJECT(Hello));
            notify_uninit();
        }
        sleep(1);
    } while(true);

    return 0;

}
