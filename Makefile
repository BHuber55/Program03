AutomatedMakefile = am
CC = g++

FILES = RadixSortDriver.o
EXECUTABLE = RadixSortDriver.exe

PROJECT_PATH = $(PROJECT_DIR)
INC_DIRS = -I$(PROJECT_PATH)/CSC2110/
LIB_DIRS = -L$(PROJECT_PATH)/CSC2110/
LIBS = -lCSC2110

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

all: Project	

Project: 			$(FILES)
				$(LINK) $(EXECUTABLE) $(FILES) $(LIBS)
					
RadixSortDriver.o: 	RadixSort.h RadixSortDriver.cpp 
								$(COMPILE) RadixSortDriver.cpp