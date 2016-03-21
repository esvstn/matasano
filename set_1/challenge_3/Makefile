CC=gcc
PWD=$(shell pwd)
INCLUDE_DIR=$(PWD)/../../include
CFLAGS= -I$(INCLUDE_DIR) 

hex2base:
	$(CC) *.c -o hack_singlebyte_xor $(CFLAGS)
clean:
	rm ./hack_singlebyte_xor
