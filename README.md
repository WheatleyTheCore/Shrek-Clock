# Shrek Clock

## A brief explanation

The units of time that we use (e.g. minutes, seconds) are completely arbitrary. So, I decided to make a clock that, instead of using those units, uses the length of the origional Shrek movie as it's unit of time. Every 95 minutes is one Shrek, and the time resets every day at midnight. 

## What this project uses

This project uses some super cheap ESP32 modules I found on Amazon. I did a quick proof-of-concept using the Arduino IDE, but afterwards rewrote/ported it to Embedded C using the ESP's ESP-IDF. I used the SNTP example to build this off of, and really only changed the main.c file. The example code can be found here: https://github.com/espressif/esp-idf/tree/master/examples/protocols/sntp.

