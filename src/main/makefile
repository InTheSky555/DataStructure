vpath %.h $(DIR_INCLUDE) 
.PHONY: all
all: main.o  
main.o:main.cpp algraph.h squeue.h
	cc -c $(PPFLAGS) $< -o $(DIR_OBJ)/$@
.PHONY: clean
clean:
	-rm $(DIR_OBJ)/*.o
