# Fedora specific: due to ccache
OVERRIDE_EXECUTABLES = 1
CC      = /usr/lib64/ccache/$(CC_NAME)
CXX     = /usr/lib64/ccache/$(CXX_NAME)
AS      = /usr/bin/$(AS_NAME)
OBJCOPY = /usr/bin/$(OBJCOPY_NAME)
OBJDUMP = /usr/bin/$(OBJDUMP_NAME)
AR      = /usr/bin/$(AR_NAME)
SIZE    = /usr/bin/$(SIZE_NAME)
NM      = /usr/bin/$(NM_NAME)
AVRDUDE = /usr/bin/avrdude

# alternate serial monitor (default: screen)
# MONITOR_CMD	= minicom

# hardware
BOARD_TAG	= uno
MONITOR_PORT	= /dev/ttyACM0

# when using Waveshare UNO PLUS
# MONITOR_PORT	= /dev/ttyUSB0

# master Makefile
PROJECT		= ${PWD}
include ${PROJECT}/mk/Arduino.mk
