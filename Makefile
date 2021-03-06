##
# Copyright (C) 2015 Jolla Ltd.
# Contact: Matti Kosola <matti.kosola@jolla.com>
# License: GPLv2
##

CC = gcc
CFLAGS = -g -Wall -Werror
REBOOTTOOL = reboot-tool
INSTALL = install -c
INSTALLDIR = install -d

# The directory to install tools
sbindir = /usr/sbin

.PHONY: all
all: $(REBOOTTOOL)

$(REBOOTTOOL): $(REBOOTTOOL).c
	$(CC) $(CFLAGS) -o $(REBOOTTOOL) $(REBOOTTOOL).c

.PHONY: install
install:
	$(INSTALLDIR) $(DESTDIR)$(sbindir)
	$(INSTALL) $(REBOOTTOOL) $(DESTDIR)$(sbindir)/$(REBOOTTOOL)

.PHONY: clean
clean:
	$(RM) $(REBOOTTOOL)
