vpath %.h  $(DIR_INCLUDE)
DIR_SUB = $(shell ls)
PPFLAGS += -I $(DIR_INCLUDE)
export PPFLAGS
.PHONY: all $(DIR_SUB) 
all: $(DIR_SUB)
main:	
	make -C $@
algraph:
	make -C $@
squeue:
	make -C $@
.PHONY: clean
clean:
	-rm  ../obj/*.o
