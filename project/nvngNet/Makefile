ifeq ($(rtags), y)
	CC = g++
else
	CC = ccache g++
endif

ifeq ($(release), y)
	CC_FLAG = -std=c++11 -Wall -Werror -O2
else
	CC_FLAG = -g -std=c++11 -Wall -Werror
endif

SRC_DIR   = ./src \
	    ./src/net \
	    ../../share

EXT_DIR = /usr/local

EXT_LIB = protobuf

PCH	  = ./src/PreCompiled.h
PROTO_DIR = ./src/proto
TARGET	  = server

SRC_EXTS = .c .C .cc .cpp .CPP .c++ .cxx .cp
HDR_EXTS = .h .H .hh .hpp .HPP .h++ .hxx .hp

SRC	= $(foreach d, $(SRC_DIR), $(wildcard $(addprefix $(d)/*, $(SRC_EXTS))))
# HEADERS = $(foreach d, $(SRC_DIR), $(wildcard $(addprefix $(d)/*, $(HDR_EXTS))))

INC	= $(foreach d, $(SRC_DIR), $(addprefix -I, $(d)))
INC    += $(foreach d, $(EXT_DIR), $(addsuffix $(d)/include, -I))

LIB_DIR = $(foreach d, $(EXT_DIR), $(addsuffix $(d)/lib, -L))
LIB	= $(foreach l, $(EXT_LIB), $(addsuffix $(l), -l))

OBJS    = $(addsuffix .o, $(basename $(SRC)))

PCH_OBJ	= $(addsuffix .gch, $(basename $(PCH)))

ifneq ($(PROTO_DIR),)
	PROTO_PROTO = $(foreach d, $(PROTO_DIR), $(wildcard $(addprefix $(d)/*, .proto)))
	PROTO_CC = $(PROTO_PROTO:.proto=.pb.cc)
	PROTO_H  = $(PROTO_PROTO:.proto=.pb.h)
	OBJS	+= $(PROTO_PROTO:.proto=.pb.o)
	INC	+= $(addprefix -I, $(PROTO_DIR))
endif

DEPS    = $(SRC:.cc=.d)
DEPS    += $(PCH_OBJ:.gch=.d)

.PHONY	: all show clean cleanall rtags proto release

all : $(PROTO_CC) $(PCH_OBJ) $(TARGET)

%.pb.cc : %.proto
	protoc -I=$(PROTO_DIR) --cpp_out=$(PROTO_DIR) $<

# for precompiled header
$(PCH_OBJ) : $(PCH)
	$(CC) $(CC_FLAG) $(INC) -x c++-header -o $@ $<

# for precompiled header
%.d : %.gch $(PROTO_CC)
	@set -e; \
	$(CC) -MM $(CC_FLAG) $(INC) $*.h | sed 's,\($(notdir $*)\)\.o[ :]*,$*.gch $*.d : ,g' > $@

$(TARGET) : $(OBJS)
	$(CC) $(CC_FLAG) $(INC) -o $(TARGET) $(OBJS) $(LIB_DIR) $(LIB)

MAKE_DEP_CMD = @set -e; \
	$(CC) -MM $(CC_FLAG) $(INC) $< | sed 's,\($(notdir $*)\)\.o[ :]*,$*.o $*.d : ,g' > $@

%.d : %.cpp $(PROTO_CC) ; $(MAKE_DEP_CMD)
%.d : %.cc  $(PROTO_CC) ; $(MAKE_DEP_CMD)
%.d : %.c   $(PROTO_CC) ; $(MAKE_DEP_CMD)

MAKE_OBJ_CMD = $(CC) $(CC_FLAG) $(INC) -o $@ -c $<

%.o : %.cpp ; $(MAKE_OBJ_CMD)
%.o : %.cc  ; $(MAKE_OBJ_CMD)
%.o : %.c   ; $(MAKE_OBJ_CMD)

# include src/proto/Makefile # 在最后执行
sinclude $(DEPS) # 在最先执行

rtags :
	@make clean; \
	bear make rtags=y; \
	rc -J ./compile_commands.json

release :
	@make clean; \
	make release=y;

show :
	@echo "TARGET	:" $(TARGET)
	@echo "OBJS	:" $(OBJS)
	@echo "SRC_DIR	:" $(SRC_DIR)
	@echo "EXT_DIR	:" $(EXT_DIR)
	@echo "PROTO_PROTO :" $(PROTO_PROTO)
	@echo "PCH_OBJ	:" $(PCH_OBJ)
	@echo $(MAKE)

cleanall : clean
	-rm -f $(DEPS) $(PCH_OBJ) $(PROTO_CC) $(PROTO_H) compile_commands.json

clean :
	-rm -f $(OBJS) $(TARGET)

# .PHONY 定义伪目录
#
# -rm	表示也许某些文件出现问题，继续做后面的事
#
# =	是最基本的赋值
# :=	是覆盖之前的值
# ?=	是如果没有被赋值过就赋予等号后面的值
# +=	是添加等号后面的值
#
# $?	比目标的修改时间更晚的那些依赖模块表
# $@	当前目标的全路径名。可用于用户定义的目标名的相关行中
# $^	所有的依赖文件
# $<	比给定的目标文件时间标记更新的依赖文件名
# $*	去掉后缀的当前目标名。例如，若当前目标是pro.o，则$*表示pro
