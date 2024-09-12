#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "unistd.h"
#include "libnotify/notify.h"

#include "config.h"

// TODO: add error wrappers
void read_capacity(uint8_t* capacity){
    FILE *battery_capacity_fptr = fopen(BATTERY_PATH, "r");

    if(battery_capacity_fptr == NULL){
        printf("Error reading battery file\n");
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
    notify_init ("Battery control applet");

    do {
        read_capacity(&capacity);
        if(capacity <= LOW_NOTIFY_THRESHOLD){
            NotifyNotification *low_battery = notify_notification_new ("Low battery", "Battery below 20%", "dialog-information");
            notify_notification_show (low_battery, NULL);
            g_object_unref(G_OBJECT(low_battery));
        }
        if(capacity >= HIGH_NOTIFY_THRESHOLD){
            NotifyNotification *high_battery = notify_notification_new ("High battery", "Battery now above 80%", "dialog-information");
            notify_notification_show (high_battery, NULL);
            g_object_unref(G_OBJECT(high_battery));
        }
        sleep(REFRESH_TIME);
    } while(true);

    notify_uninit();
    return 0;

}
