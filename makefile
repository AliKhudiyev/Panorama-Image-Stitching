
CC 		= g++
FLGS	= -Wall -c

INCLUDE	= -I lib/
SRC		= $(wildcard *.cpp)
LIB 	= $(patsubst(%.cpp, %.hpp, $(SRC))
OBJ		= main.o bmp.o bmp_info.o pixel.o

info	= "\
Makefile usage: make [option]\n\
Options:\n\
1. stitch : used to stitch 2 images\n\
2. panorama : used to prepare cropped images in a folder\n\
3. clear : used to remove all object files\
"

program: $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.cpp
	$(CC) $(FLGS) $? -o $@

clear:
	$(RM) $(OBJ)

info:
	@echo $(info)
