ifeq ($(rtags), y)
	CC = g++
else
	CC = ccache g++
endif

CC_FLAG = -g -std=c++11 -O2 -Wall -Werror

SRC_DIR   = . \
	    ../../../share

EXT_DIR = /usr/local

EXT_LIB = protobuf

PCH	  =
PROTO_DIR = ./proto
TARGET	  = test

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

.PHONY	: all show clean cleanall rtags proto

all : $(PCH_OBJ) $(PROTO_CC) $(TARGET)

# for precompiled header
$(PCH_OBJ) : $(PCH)
	$(CC) $(CC_FLAG) $(INC) -x c++-header -o $@ $<

$(TARGET) : $(OBJS)
	$(CC) $(CC_FLAG) $(INC) -o $(TARGET) $(OBJS) $(LIB_DIR) $(LIB)

%.d : %.cc
	@set -e; \
	$(CC) -MM $(CC_FLAG) $(INC) $< > $@; \
	sed -i 's,\($(notdir $*)\)\.o[ :]*,$*.o $*.d : ,g' $@;

%.o : %.cc
	$(CC) $(CC_FLAG) $(INC) -o $@ -c $<

%.pb.cc : %.proto
	protoc -I=$(PROTO_DIR) --cpp_out=$(PROTO_DIR) $<

sinclude $(DEPS)

proto : $(PROTO_CC)

rtags :
	@make clean; \
	bear make rtags=y; \
	rc -J ./compile_commands.json

show :
	@echo "TARGET	:" $(TARGET)
	@echo "OBJS	:" $(OBJS)
	@echo "SRC_DIR	:" $(SRC_DIR)
	@echo "EXT_DIR	:" $(EXT_DIR)
	@echo "PROTO_PROTO :" $(PROTO_PROTO)
	@echo "PCH_OBJ	:" $(PCH_OBJ)

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
