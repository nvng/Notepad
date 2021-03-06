ifneq ($(rtags), y)
	CCACHE = ccache
endif

CC	= $(CCACHE) g++

# ifeq ($(debug),y)
# 	CC_FLAG	= -g -std=c++11 -Wall -Werror -finstrument-functions -O0
# else
# 	CC_FLAG	= -DNDEBUG -std=c++11 -Wall -Werror -finstrument-functions -O2
# endif

ifeq ($(debug),y)
	CC_FLAG	= -g -std=c++11 -Wall -Werror -O0
else
	CC_FLAG	= -DNDEBUG -std=c++11 -Wall -Werror -O2
endif

INC	= -I../../share \
	  -I../

LINK	= -lpthread \
	  -levent

SRC_CC	= $(wildcard ./*.cc)

TARGETS	= $(patsubst %.cc, %.out, $(SRC_CC))

PCH	  = ../pre_compiled.h
ifneq ($(PCH),)
	INC    += -include $(PCH)
	PCH_OBJ = $(foreach f, $(PCH), $(addsuffix .gch, $(basename $(f))))
endif

all	: $(PCH_OBJ) $(TARGETS)

%.out	: %.cc
	$(CC) $(CC_FLAG) $(INC) -o $@ $< $(LINK)

%.gch : %.h $(ADDED_DEPS)
	$(CC) $(CC_FLAG) $(INC) -x c++-header -o $@ $<

debug :
	@make -j4 debug=y;

rtags :
	@make clean; \
	echo $(INC) > .clang_complete; \
	bear make -j4 rtags=y; \
	rc -J ./compile_commands.json

clean	:
	-rm -f $(TARGETS) $(PCH_OBJ) *.o .*~ .clang_complete .compile_commands.json *.dot *.png
