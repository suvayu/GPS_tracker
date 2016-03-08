<div id="table-of-contents">
<h2>Table of Contents</h2>
<div id="text-table-of-contents">
<ul>
<li><a href="#orgheadline1">1. Introduction</a></li>
<li><a href="#orgheadline9">2. Tasks</a>
<ul>
<li><a href="#orgheadline4">2.1. Hardware components <code>[1/2]</code></a>
<ul>
<li><a href="#orgheadline2">2.1.1. <span class="done nilDONE">DONE</span> Logging: Arduino ↔ SD card</a></li>
<li><a href="#orgheadline3">2.1.2. <span class="todo nilTODO">TODO</span> Location: Arduino ↔ GPS module</a></li>
</ul>
</li>
<li><a href="#orgheadline8">2.2. Software tasks <code>[2/4]</code></a>
<ul>
<li><a href="#orgheadline5">2.2.1. <span class="done nilDONE">DONE</span> Read/write to SD card</a></li>
<li><a href="#orgheadline6">2.2.2. <span class="todo nilTODO">TODO</span> Read GPS data over serial connection</a></li>
<li><a href="#orgheadline7">2.2.3. <span class="todo nilTODO">TODO</span> Final assembly</a></li>
</ul>
</li>
</ul>
</li>
</ul>
</div>
</div>


# Introduction<a id="orgheadline1"></a>

This is the source code for a simple GPS tracker built using

-   an [Arduino](https://www.arduino.cc/en/Main/ArduinoBoardUno),
-   the [SD card shield from seeedstudio](http://www.seeedstudio.com/wiki/SD_Card_shield_V4.0), and
-   the [Ultimate GPS module from Adafruit](https://www.adafruit.com/products/746).

It uses the following libraries

-   SD & SPI library from the Arduino IDE distribution
-   Adafruit GPS library

We use `Make` to build the project, thanks to the Arduino-Makefile
project.

# Tasks<a id="orgheadline9"></a>

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

-   [ ] Send instructions: PIN?
-   [ ] Read/log data: PIN?
-   [ ] How do we know when we have a GPS fix?
-   [ ] Solder button battery (CR1220) backup
-   [ ] Design a simple circuit based on above understanding.

## Software tasks <code>[2/4]</code><a id="orgheadline8"></a>

### DONE Read/write to SD card<a id="orgheadline5"></a>

Example program can be found in the `test` branch.

### TODO Read GPS data over serial connection<a id="orgheadline6"></a>

Example `echo`-ing program from the Adafruit library can be found on
the `test` branch.

### TODO Final assembly<a id="orgheadline7"></a>

-   [ ] SD+GPS: how to combine the logic in the setup()+loop() scheme?
-   [ ] On power loss, revert to logging to GPS chip (under button
    battery power backup).  When power is back, retrieve logs, and
    resume logging as before.
