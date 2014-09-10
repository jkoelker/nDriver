// vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab:filetype=arduino

#include "main.h"


void setup() {
    pinMode(CONFIG_LED_PIN, OUTPUT);
    attachInterrupt(CONFIG_ENABLE_INT, tool_enable, CHANGE);
    servo.attach(CONFIG_SERVO_PIN);
    tool_off();
}


void loop() {
    position = servo.read();

    if (on) {
        tool_on();

    } else if (!on) {
        tool_off();
    }
}


void tool_enable() {
    if (on) {
        on = 0;
    } else {
        on = 1;
    }
}


void tool_off() {
    digitalWrite(CONFIG_LED_PIN, LOW);

    if (position > CONFIG_SERVO_MIN) {
        servo.write(CONFIG_SERVO_MIN);
   }
}

void tool_on() {
    digitalWrite(CONFIG_LED_PIN, HIGH);

    if (position < CONFIG_SERVO_MAX) {
        servo.write(CONFIG_SERVO_MAX);
    }
}
