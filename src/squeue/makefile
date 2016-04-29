vpath %.h $(DIR_INCLUDE)
.PHONY: all
all: squeue.o  
squeue.o:squeue.cpp squeue.h
	cc -c $(PPFLAGS) $< -o $(DIR_OBJ)/$@
.PHONY: clean
clean:
	-rm $(DIR_OBJ)/*.o
