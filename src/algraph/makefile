vpath %.h $(DIR_INCLUDE)
.PHONY: all
all: algraph.o  
algraph.o:algraph.cpp algraph.h squeue.h
	cc -c $(PPFLAGS) $< -o $(DIR_OBJ)/$@
.PHONY: clean
clean:
	-rm $(DIR_OBJ)/*.o
