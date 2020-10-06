#
#  Trevon Harris & Michael Hamm
#  September 28th 2020
# 
#  Makefile used to auto compile and run main. "make" command to start the Makefile.
#
all: compile run
compile: main.c commandline.c Dispatch.c Queue.c Schedule.c
	gcc -pthread -o main main.c commandline.c Dispatch.c Queue.c Schedule.c
run: main
	./main
.PHONY: all compile run
