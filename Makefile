# \
Copyright (c) 2020, Moonsik Park \
All rights reserved. \
\
Redistribution and use in source and binary forms, with or without \
modification, are permitted provided that the following conditions are met: \
    * Redistributions of source code must retain the above copyright \
      notice, this list of conditions and the following disclaimer. \
    * Redistributions in binary form must reproduce the above copyright \
      notice, this list of conditions and the following disclaimer in the \
      documentation and/or other materials provided with the distribution. \
    * Neither the name of the <organization> nor the \
      names of its contributors may be used to endorse or promote products \
      derived from this software without specific prior written permission. \
\
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND \
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED \
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE \
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY \
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES \
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; \
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND \
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT \
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS \
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. \

CC=gcc
DIR := ${CURDIR}
SOURCE_DIR=$(DIR)/src/bindings
BIN_DIR=$(DIR)/bin
CFLAGS=-Wall
LDLIBS=-lbrunslienc-c -lbrunslidec-c
DESTDIR=/usr/bin


OBJS=$(SOURCE_DIR)/brunsli_wrapper.o $(SOURCE_DIR)/common.o
TARGET=brunsli_wrapper

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(OBJS) $(LDLIBS)

$(SOURCE_DIR)/brunsli_wrapper.o: $(SOURCE_DIR)/brunsli_wrapper.c

$(SOURCE_DIR)/common.o: brunsli $(SOURCE_DIR)/common.h $(SOURCE_DIR)/common.c

git_update:
	cd $(DIR); git submodule update --init
	cd $(DIR)/src/brunsli; git submodule update --init

brunsli: git_update
	mkdir -p $(DIR)/src/brunsli/bin
	cd $(DIR)/src/brunsli/bin; cmake ..; make -j; make -j install


install: $(TARGET)
	cp $(BIN_DIR)/brunsli_wrapper $(DESTDIR)

clean:
	rm -rf $(BINDIR)
	rm -rf $(OBJS)