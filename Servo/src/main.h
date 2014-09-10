// vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab:filetype=arduino

#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <Servo.h>

#include "config.h"


uint8_t position = 0;
Servo servo;
volatile uint8_t on = 0;

void setup();
void loop();

void tool_enable();
void tool_off();
void tool_on();

#endif
