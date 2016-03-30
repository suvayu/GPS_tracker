<div id="table-of-contents">
<h2>Table of Contents</h2>
<div id="text-table-of-contents">
<ul>
<li><a href="#orgheadline1">1. Introduction build status</a></li>
<li><a href="#orgheadline12">2. Tasks</a>
<ul>
<li><a href="#orgheadline4">2.1. Hardware components <code>[1/2]</code></a>
<ul>
<li><a href="#orgheadline2">2.1.1. <span class="done DONE">DONE</span> Logging: Arduino ↔ SD card</a></li>
<li><a href="#orgheadline3">2.1.2. <span class="todo TODO">TODO</span> Location: Arduino ↔ GPS module</a></li>
</ul>
</li>
<li><a href="#orgheadline11">2.2. Software tasks <code>[3/6]</code></a>
<ul>
<li><a href="#orgheadline5">2.2.1. <span class="done DONE">DONE</span> Read/write to SD card</a></li>
<li><a href="#orgheadline6">2.2.2. <span class="done DONE">DONE</span> Read GPS data over serial connection</a></li>
<li><a href="#orgheadline7">2.2.3. <span class="todo TODO">TODO</span> Final assembly</a></li>
<li><a href="#orgheadline8">2.2.4. <span class="done DONE">DONE</span> Log in CSV format</a></li>
<li><a href="#orgheadline9">2.2.5. <span class="todo TODO">TODO</span> Add numeric keypad and LCD display (16x2)</a></li>
<li><a href="#orgheadline10">2.2.6. <span class="todo WInP">WInP</span> Reduce code size (74% now)</a></li>
</ul>
</li>
</ul>
</li>
</ul>
</div>
</div>


# Introduction [![Build Status](https://travis-ci.org/suvayu/GPS_tracker.svg?branch=master)](https://travis-ci.org/suvayu/GPS_tracker)<a id="orgheadline1"></a>

This is the source code for a simple GPS tracker built using

-   an [Arduino](https://www.arduino.cc/en/Main/ArduinoBoardUno),
-   the [SD card shield from seeedstudio](http://www.seeedstudio.com/wiki/SD_Card_shield_V4.0), and
-   the [Ultimate GPS module from Adafruit](https://www.adafruit.com/products/746).

It uses the following libraries

-   SD & SPI library from the Arduino IDE distribution
-   Adafruit GPS library

We use `Make` to build the project, thanks to the Arduino-Makefile
project.

# Tasks<a id="orgheadline12"></a>

## Hardware components <code>[1/2]</code><a id="orgheadline4"></a>

### DONE Logging: Arduino ↔ SD card<a id="orgheadline2"></a>

Pins used:

-   [X] CS: 4 (not sure what this is)
-   [X] In: 11
-   [X] Out: 12
-   [X] Clock: 13

### TODO Location: Arduino ↔ GPS module<a id="orgheadline3"></a>

Understand how to connect the board in a circuit with the Arduino
(<https://learn.adafruit.com/adafruit-ultimate-gps>)

-   [X] Send instructions: PIN 3?
-   [X] Read/log data: PIN 2?
-   [X] How do we know when we have a GPS fix? `GPS.fix`
-   [ ] Solder button battery (CR1220) backup
-   [X] Design a simple circuit based on above understanding.
-   [ ] Add circuit diagram

## Software tasks <code>[3/6]</code><a id="orgheadline11"></a>

### DONE Read/write to SD card<a id="orgheadline5"></a>

Example program can be found in the `test` branch.

### DONE Read GPS data over serial connection<a id="orgheadline6"></a>

Example `echo`-ing program from the Adafruit library can be found on
the `test` branch.

### TODO Final assembly<a id="orgheadline7"></a>

-   [X] SD+GPS: how to combine the logic in the setup()+loop() scheme?
-   [ ] On power loss, revert to logging to GPS chip (under button
    battery power backup).  When power is back, retrieve logs, and
    resume logging as before.

### DONE Log in CSV format<a id="orgheadline8"></a>

### TODO Add numeric keypad and LCD display (16x2)<a id="orgheadline9"></a>

-   [ ] Take input with correction
-   [ ] Show as you type, confirm pass/fail (use smileys?)

### WInP Reduce code size (74% now)<a id="orgheadline10"></a>

-   [ ] Profile code for size: how?
    -   No easy way, move constants to Flash memory (see: `PROGMEM`, `F(..)`)
