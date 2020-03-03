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