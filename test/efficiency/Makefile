CC	= ccache g++

CC_FLAG	= -g -std=c++11 -Wall -Werror -O2

INC	= -I../../share \
	  -I../

SRC_CC	= $(wildcard ./*.cc)

TARGETS	= $(patsubst %.cc, %.out, $(SRC_CC))

all	: $(TARGETS)

%.out	: %.cc
	$(CC) $(CC_FLAG) $(INC) -o $@ $<

clean	:
	-rm -f $(TARGETS) *.o .*~
