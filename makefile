
CC 		= g++
FLGS	= -Wall -c

INCLUDE	= -I lib/
SRC		= $(wildcard *.cpp)
LIB 	= $(patsubst(%.cpp, %.hpp, $(SRC))
OBJ		= $(patsubst(%.cpp, %.o, $(SRC))

info	= "\
Makefile usage: make [option]\n\
Options:\n\
1. stitch : used to stitch 2 images\n\
2. panorama : used to stitch all images in a folder\n\
3. clear : used to remove all object files\
"

stitch: $(OBJ)
	$(CC) $(OBJ) -o $@

panorama: stitch
	./panorama.sh

compile: $(SRC)
	$(CC) $(FLGS)

%.o: %.cpp
	$(CC) $(FLGS) $? -o $@

clear:
	$(RM) $(OBJ)

info:
	@echo $(info)
