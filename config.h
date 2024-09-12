#include "stdint.h"

const uint8_t LOW_NOTIFY_THRESHOLD  = 20;
const uint8_t HIGH_NOTIFY_THRESHOLD = 80;

// sleep time in seconds
const uint8_t REFRESH_TIME = 1;

// path to battery capacity file
const char* BATTERY_PATH = "/sys/class/power_supply/BAT0/capacity";
