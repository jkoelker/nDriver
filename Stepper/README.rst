Stepper nDriver - Emulate a stepper driver and drive each coil
==============================================================

To bridge between GRBL and a `28byj-48 + ULN2003 stepper "driver"
<http://42bots.com/tutorials/28byj-48-stepper-motor-with-uln2003-driver-and-arduino-uno>`_.
The driver code will react to GRBL stepper enable/disable and step/direction
pulses.

For example using a spare Arduino Nano:

.. code-block::

      "Stepper Drv"         ULN2003 Driver
     +-------------+       +--------------+
    -|D13       D12|-      |              |
    -|3V3       D11|-------|1N1           |
    -|REF       D10|-------|1N2           |
    -|A0         D9|-------|1N3           |
    -|A1         D8|-------|1N4           |
    -|A2         D7|-      |              |
    -|A3         D6|----   +--------------+
    -|A4         D5|-   \
    -|A5         D4|-    ----> Stepper Enable
    -|A6         D3|---------> Direction
    -|A7         D2|---------> Step Pulse
    -|5V        GND|-
    -|RST       RST|-
    -|GND        RX|-
    -|VIN        TX|-
     +-------------+
         nDriver


The firmware can be compiled with `Ino Tool <http://inotool.org>`_. Changing
pins, Step Delay, or Interrupt can be done either in config.h or using
``Defines`` to the preprocessor for example to set ``CONFIG_STEP_DELAY`` to 8:

.. code-block:: bash

    ino build --cppflags="-ffunction-sections -fdata-sections -g -Os -w -DCONFIG_STEP_DELAY=8"

Where ``-ffunction-sections -fdata-sections -g -Os -w`` is the default specified in ino.ini.
