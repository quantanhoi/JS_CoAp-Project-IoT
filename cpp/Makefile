# Makefile for libcoap minimal examples
#
# Copyright (C) 2018-2023 Olaf Bergmann <bergmann@tzi.org>
#

LIBCOAP?=libcoap-3
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
pkgconfig=$(shell pkg-config $(1) $(2))
CPPFLAGS=-Wall -Wextra $(call pkgconfig,--cflags,$(LIBCOAP))
LDLIBS=$(call pkgconfig,--libs,$(LIBCOAP))
LINK.o=$(LINK.cc)

CXXFLAGS=-std=c++14

all: client server

client:: client.o common.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) client.o common.o $(LDLIBS) -lncurses -o client

server:: server.o common.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) server.o common.o $(LDLIBS) -o server

clean:
	rm -f *.o client server
