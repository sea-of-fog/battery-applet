#!/bin/bash

gcc -o battery-applet `pkg-config --cflags --libs libnotify` main.c
