// vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab:filetype=arduino

#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#include "config.h"


uint8_t tcnt2 = 130;
uint8_t led_state = 0;
uint8_t count = 0;
volatile uint8_t enable = 0;
volatile uint8_t step = 0;
volatile uint8_t step_pos = 0;

uint8_t steps[] = {0b0001, 0b0101, 0b0100, 0b0110, 0b0010, 0b1010, 0b1000,
                   0b1001};
uint8_t pins[] = {CONFIG_PIN_0, CONFIG_PIN_1, CONFIG_PIN_2, CONFIG_PIN_3};


void setup();
void loop();

void do_step();
void disable_outputs();
void enable_outputs();
void send_output(uint8_t mask);

#endif
