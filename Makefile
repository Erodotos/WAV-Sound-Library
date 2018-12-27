###############################################
# Makefile for compiling the program skeleton
# 'make' build executable file 'PROJ'
# 'make doxy' build project manual in doxygen
# 'make all' build project + manual
# 'make clean' removes all .o, executable and doxy log
###############################################
###############################################
# Makefile for compiling the program skeleton
# 'make' build executable file 'PROJ'
# 'make doxy' build project manual in doxygen
# 'make all' build project + manual
# 'make clean' removes all .o, executable and doxy log
###############################################
PROJ = wavengine # the name of the project
CC = gcc # name of compiler
DOXYGEN = doxygen # name of doxygen binary
# define any compile-time flags
CFLAGS = -std=c99 -Wall -O -Wuninitialized -Wunreachable-code -pedantic # there is a space at the end of this
LFLAGS = -lm
LIB = ar -cvq wavLib.a 
EXE = wavengine wavengine.c wavLib.a
###############################################
# You don't need to edit anything below this line
###############################################
# list of object files
# The following includes all of them!
O_FILES := chop.o decrypt.o encrypt.o list.o mixer.o mono.o reverse.o similarity.o wave.o speedup.o delay.o
C_FILES := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(C_FILES))
# To create the executable file we need the individual
# object files
$(PROJ): $(OBJS)
	$(CC) $(LFLAGS) -o $(PROJ) $(OBJS)
$(LIB): $(LIB) $(OBJS)
# To create each individual object file we need to
# compile these files using the following general
# purpose macro
.c.o:
	$(CC) $(CFLAGS) -c $<
# there is a TAB for each identation.
# To make all (program + manual) "make all"
# make
# ar -cvq wavLib.a wavEngine.o wavLib.o wavProcessing.o
# gcc -std=c99 -o -lm wavengine wavEngine.c wavLib.a 
# ar -t wavLib.a
lib :    
	make clean
	$(CC) -c $(CFLAGS) $(LFLAGS) $(C_FILES)
	$(LIB) $(O_FILES)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(EXE)
	rm -rf *.o
all :
	make
	make doxy
# To make all (program + manual) "make doxy"
doxy :
	$(DOXYGEN) doxygen.conf &> doxygen.log
# To clean .o files: "make clean"
clean:
	rm -rf *.o doxygen.log html wavLib.a wavengine
