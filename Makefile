##
# escapec
# tool to quickly escape input for use in C / C++ as string literals.
#
# @file
# @version 0.1

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -O2
TARGET = escapec
SRC = escapec.c

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

# Lets not install anything yet

# install: $(TARGET)
# 	install -d $(DESTDIR)/usr/local/bin
# 	install -m 755 $(TARGET) $(DESTDIR)/usr/local/bin
#
# uninstall:
# 	rm -f $(DESTDIR)/usr/local/bin/$(TARGET)

# end
