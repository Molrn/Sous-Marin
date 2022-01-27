CC=g++
CFLAGS=-O0 -g3 -Wall -c -fmessage-length=0
HEAD_DIR="header\\"
SRC_DIR=src
EXEC=main

OBJ_FILES=$(SRC_DIR)\main.o $(SRC_DIR)\Scheduler.o $(SRC_DIR)\Server.o

all: $(OBJ_FILES) $(EXEC)

$(EXEC): 
	$(CC) -o $@ $(OBJ_FILES)


%.o: %.cpp
	$(CC) -I$(HEAD_DIR) $(CFLAGS) -o $@ -c $<
