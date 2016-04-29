ROOT = $(shell pwd)
DIR_INCLUDE = $(ROOT)/include
DIR_BIN = $(ROOT)/bin
DIR_OBJ = $(ROOT)/obj
DIR_SRC = $(ROOT)/src

export ROOT DIR_INCLUDE DIR_BIN DIR_OBJ DIR_SRC 
vpath %.o  $(ROOT)/obj
.PHONY:all clean  OBJ CUROBJ
all: OBJ CUROBJ 

OBJ:
	make -C $(DIR_SRC)
CUROBJ:
	make main
main:main.o algraph.o squeue.o
	cc -o $(DIR_BIN)/$@ $^

clean:
	-rm $(DIR_BIN)/main $(DIR_OBJ)/*.o
