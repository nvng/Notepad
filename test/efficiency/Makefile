ifneq ($(rtags), y)
	CCACHE = ccache
endif

CC	= $(CCACHE) g++

ifeq ($(release),y)
	CC_FLAG	= -DNDEBUG -std=c++11 -Wall -Werror -O2
else
	CC_FLAG	= -g -std=c++11 -Wall -Werror -O2
endif

INC	= -I../../share \
	  -I../

LINK	= -lpthread

SRC_CC	= $(wildcard ./*.cc)

TARGETS	= $(patsubst %.cc, %, $(SRC_CC))

PCH	  = ../pre_compiled.h
ifneq ($(PCH),)
	INC    += -include $(PCH)
	PCH_OBJ = $(foreach f, $(PCH), $(addsuffix .gch, $(basename $(f))))
endif

all	: $(PCH_OBJ) $(TARGETS)

%	: %.cc
	$(CC) $(CC_FLAG) $(INC) -o $@ $< $(LINK)

%.gch : %.h $(ADDED_DEPS)
	$(CC) $(CC_FLAG) $(INC) -x c++-header -o $@ $<

release :
	@make clean; \
	make release=y;

rtags :
	@make clean; \
	echo $(INC) > .clang_complete; \
	bear make rtags=y; \
	rc -J ./compile_commands.json

clean	:
	-rm -f $(TARGETS) $(PCH_OBJ) *.o .*~ .clang_complete .compile_commands.json
