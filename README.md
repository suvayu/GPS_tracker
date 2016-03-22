<div id="table-of-contents">
<h2>Table of Contents</h2>
<div id="text-table-of-contents">
<ul>
<li><a href="#org44977d1">1. Introduction</a></li>
<li><a href="#org535f83b">2. Tasks</a>
<ul>
<li><a href="#org23972c1">2.1. Hardware components <code>[1/2]</code></a>
<ul>
<li><a href="#org6963e75">2.1.1. <span class="done DONE">DONE</span> Logging: Arduino ↔ SD card</a></li>
<li><a href="#orgaa51fdd">2.1.2. <span class="todo TODO">TODO</span> Location: Arduino ↔ GPS module</a></li>
</ul>
</li>
<li><a href="#org8296fb0">2.2. Software tasks <code>[2/6]</code></a>
<ul>
<li><a href="#org2ad0564">2.2.1. <span class="done DONE">DONE</span> Read/write to SD card</a></li>
<li><a href="#org1d7be41">2.2.2. <span class="done DONE">DONE</span> Read GPS data over serial connection</a></li>
<li><a href="#org9a6b9e1">2.2.3. <span class="todo TODO">TODO</span> Final assembly</a></li>
<li><a href="#org2f04453">2.2.4. <span class="todo TODO">TODO</span> Log in CSV format</a></li>
<li><a href="#org6a3807a">2.2.5. <span class="todo TODO">TODO</span> Add numeric keypad and 7-segment display</a></li>
<li><a href="#orgbda2a66">2.2.6. <span class="todo TODO">TODO</span> Reduce code size (85% now)</a></li>
</ul>
</li>
</ul>
</li>
</ul>
</div>
</div>


# Introduction<a id="org44977d1"></a>

This is the source code for a simple GPS tracker built using

-   an [Arduino](https://www.arduino.cc/en/Main/ArduinoBoardUno),
-   the [SD card shield from seeedstudio](http://www.seeedstudio.com/wiki/SD_Card_shield_V4.0), and
-   the [Ultimate GPS module from Adafruit](https://www.adafruit.com/products/746).

It uses the following libraries

-   SD & SPI library from the Arduino IDE distribution
-   Adafruit GPS library

We use `Make` to build the project, thanks to the Arduino-Makefile
project.

# Tasks<a id="org535f83b"></a>

## Hardware components <code>[1/2]</code><a id="org23972c1"></a>

### DONE Logging: Arduino ↔ SD card<a id="org6963e75"></a>

Pins used:

-   [X] CS: 4 (not sure what this is)
-   [X] In: 11
-   [X] Out: 12
-   [X] Clock: 13

### TODO Location: Arduino ↔ GPS module<a id="orgaa51fdd"></a>

Understand how to connect the board in a circuit with the Arduino
(<https://learn.adafruit.com/adafruit-ultimate-gps>)

-   [X] Send instructions: PIN 3?
-   [X] Read/log data: PIN 2?
-   [X] How do we know when we have a GPS fix? `GPS.fix`
-   [ ] Solder button battery (CR1220) backup
-   [X] Design a simple circuit based on above understanding.
-   [ ] Add circuit diagram

## Software tasks <code>[2/6]</code><a id="org8296fb0"></a>

### DONE Read/write to SD card<a id="org2ad0564"></a>

Example program can be found in the `test` branch.

### DONE Read GPS data over serial connection<a id="org1d7be41"></a>

Example `echo`-ing program from the Adafruit library can be found on
the `test` branch.

### TODO Final assembly<a id="org9a6b9e1"></a>

-   [X] SD+GPS: how to combine the logic in the setup()+loop() scheme?
-   [ ] On power loss, revert to logging to GPS chip (under button
    battery power backup).  When power is back, retrieve logs, and
    resume logging as before.

### TODO Log in CSV format<a id="org2f04453"></a>

### TODO Add numeric keypad and 7-segment display<a id="org6a3807a"></a>

-   [ ] Take input with correction
-   [ ] Show as you type, confirm pass/fail (use smileys?)

### TODO Reduce code size (85% now)<a id="orgbda2a66"></a>

-   [ ] Profile code for size: how?
