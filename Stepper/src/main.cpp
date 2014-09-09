// vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab:filetype=arduino

#include "main.h"


void setup() {
    // Disable timer interrupt
    TIMSK2 &= ~(1<<TOIE2);

    // Pure counting mode
    TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
    TCCR2B &= ~(1<<WGM22);

    // Internal I/O clock
    ASSR &= ~(1<<AS2);

    // Disable COMPA
    TIMSK2 &= ~(1<<OCIE2A);

    // Prescaler = 128
    TCCR2B |= (1<<CS22)  | (1<<CS20);
    TCCR2B &= ~(1<<CS21);

    // Enable time interrupt
    TCNT2 = tcnt2;
    TIMSK2 |= (1<<TOIE2);

    pinMode(CONFIG_ENABLE_PIN, INPUT);
    pinMode(CONFIG_DIRECTION_PIN, INPUT);
    pinMode(CONFIG_LED_PIN, OUTPUT);
    enable_outputs();
    attachInterrupt(CONFIG_STEP_INT, do_step, FALLING);
}


void loop() {
    if (digitalRead(CONFIG_ENABLE_PIN) == LOW) {
        if (!enable) {
            enable_outputs();
        }

        enable = 1;

    } else {
        if (enable) {
            disable_outputs();
        }

        enable = 0;
    }

    if (step && !led_state) {
        led_state = 1;
        digitalWrite(CONFIG_LED_PIN, HIGH);
    } else if (!step & led_state) {
        led_state = 0;
        digitalWrite(CONFIG_LED_PIN, LOW);
    }
}


void do_step() {
    if (!enable) {
        return;
    }

    step = 1;

    if (digitalRead(CONFIG_DIRECTION_PIN) == HIGH) {
        if (step_pos == 7) {
            step_pos = 0;

        } else {
            step_pos += 1;
        }

    } else {
        if (step_pos == 0) {
            step_pos = 7;

        } else {
            step_pos -= 1;
        }
    }
}


void disable_outputs() {
    send_output(0);
}


void enable_outputs() {
    for (uint8_t i = 0; i < 4; i++) {
        pinMode(pins[i], OUTPUT);
    }
}


void send_output(uint8_t mask) {
    for (uint8_t i = 0; i < 4; i++) {
        digitalWrite(pins[i], (mask & (1 << i)) ? HIGH : LOW);
    }

}


ISR(TIMER2_OVF_vect) {
    count++;
    TCNT2 = tcnt2;

    if (count > CONFIG_STEP_DELAY) {
        count = 0;

        if (!step) {
            return;
        }

        send_output(steps[step_pos]);
        step = 0;
    }
}
