Servo nDriver - Convert Tool enable/disable to servo position
=============================================================

The Servo driver code will react to GRBL tool enable/disable when connected to
the GRBL controller's Tool pin to the driver's pin 2 (Interrupt 0).

For example using a spare Arduino Nano:

.. code-block::

     +------------+
    -|D13      D12|-
    -|3V3      D11|-
    -|REF      D10|-
    -|A0        D9|-----> Servo Control PIN
    -|A1        D8|-
    -|A2        D7|-
    -|A3        D6|-
    -|A4        D5|-
    -|A5        D4|-
    -|A6        D3|-
    -|A7        D2|-----> Spindle Enable
    -|5V       GND|-
    -|RST      RST|-
    -|GND       RX|-
    -|VIN       TX|-
     +------------+
        nDriver


The firmware can be compiled with `Ino Tool <http://inotool.org>`_. Changing
pin, Servo positions, or Interrupt can be done either in config.h or using
``Defines`` to the preprocessor for example to set ``CONFIG_SERVO_MIN`` to 40:

.. code-block:: bash

    ino build --cppflags="-ffunction-sections -fdata-sections -g -Os -w -DCONFIG_SERVO_MIN=40"

Where ``-ffunction-sections -fdata-sections -g -Os -w`` is the default specified in ino.ini.
