ifneq ($(rtags), y)
	CCACHE = ccache
endif

CC = $(CCACHE) g++

ifeq ($(release), y)
	CC_FLAG = -DNDEBUG -std=c++11 -Wall -Werror -O2
else
	CC_FLAG = -g -std=c++11 -Wall -Werror
endif

# {{{ project info
SRC_DIR   = ./src \
	    ./src/net \
	    ../../share

TARGET	= server.out

SRC_EXTS = .c .cc .cpp
HDR_EXTS = .h .hpp

SRC	= $(foreach d, $(SRC_DIR), $(wildcard $(addprefix $(d)/*, $(SRC_EXTS))))
# HEADERS = $(foreach d, $(SRC_DIR), $(wildcard $(addprefix $(d)/*, $(HDR_EXTS))))

INC	+= $(addprefix -I, $(SRC_DIR)) # 等价于下面一行
# INC	= $(foreach d, $(SRC_DIR), $(addsuffix $(d), -I))

# OBJS    += $(addprefix $(basename $(SRC)), .o) # 只给最后一个加，前面的都没加 why???
OBJS	+= $(foreach s, $(SRC), $(addprefix $(basename $s), .o))
DEPS	+= $(foreach s, $(SRC), $(addprefix $(basename $(s)), .d))

RM	+= $(OBJS) $(TARGET)
RM_ALL += $(DEPS)
# }}}

# {{{ dependency includes and libs
EXT_DIR =
EXT_LIB = protobuf

LIB_DIR = $(foreach d, $(EXT_DIR), $(addsuffix $(d)/lib, -L))
INC	+= $(foreach d, $(EXT_DIR), $(addprefix -I, $(d)/include))
LIB	+= $(addprefix -l, $(EXT_LIB))
# }}}

#{{{ precompiled headers
PCH	  = ./src/PreCompiled.h
ifneq ($(PCH),)
	INC    += -include $(PCH)
	PCH_OBJ = $(foreach f, $(PCH), $(addsuffix .gch, $(basename $(f))))

	# 这里可以认为是生成.d时，需要*.gch，所以就会生成相应的文件
	# DEPS    += $(PCH_OBJ:.gch=.d)
	
	RM_ALL += $(PCH_OBJ)
endif
#}}}

#{{{ protobuf
PROTO_DIR = ./src/proto
ifneq ($(PROTO_DIR),)
	PROTO_PROTO = $(foreach d, $(PROTO_DIR), $(wildcard $(addprefix $(d)/*, .proto)))
	PROTO_CC = $(PROTO_PROTO:.proto=.pb.cc)
	PROTO_H  = $(PROTO_PROTO:.proto=.pb.h)
	OBJS	+= $(PROTO_PROTO:.proto=.pb.o)
	INC	+= $(addsuffix $(PROTO_DIR), -I)

	RM_ALL += $(PROTO_CC) $(PROTO_H)
	
	ADDED_DEPS += $(PROTO_CC)
endif
#}}}

#{{{ compile rules
COMPILE_CMD = $(CC) $(CC_FLAG) $(INC)

.PHONY	: all show clean cleanall rtags release

# 虽然生成依赖的时候就生成了 PROTO_CC，而如果这里不写，删除之前生成的。
# 然后根据 TARGET 的依赖 OBJS 生成 PROTO_CC
all : $(PROTO_CC) $(PCH_OBJ) $(TARGET)

$(TARGET) : $(OBJS)
	$(COMPILE_CMD) -o $(TARGET) $(OBJS) $(LIB_DIR) $(LIB)

MAKE_OBJ_CMD = $(COMPILE_CMD) -o $@ -c $<
MAKE_DEP_CMD = @echo create dependency $@; \
	       set -e; \
	       $(COMPILE_CMD) -MM $< | sed 's,\($(notdir $*)\)\.o[ :]*,$*.o $*.d : ,g' > $@

%.o : %.cpp $(ADDED_DEPS) ; $(MAKE_OBJ_CMD)
%.o : %.cc  $(ADDED_DEPS) ; $(MAKE_OBJ_CMD)
%.o : %.c   $(ADDED_DEPS) ; $(MAKE_OBJ_CMD)

%.d : %.cpp $(ADDED_DEPS) ; $(MAKE_DEP_CMD)
%.d : %.cc  $(ADDED_DEPS) ; $(MAKE_DEP_CMD)
%.d : %.c   $(ADDED_DEPS) ; $(MAKE_DEP_CMD)

# for protobuf
%.pb.cc : %.proto
	protoc -I=$(PROTO_DIR) --cpp_out=$(PROTO_DIR) $<

%.pb.d : %.pb.cc
	$(MAKE_DEP_CMD)

# for precompiled header
%.gch : %.h $(ADDED_DEPS)
	$(COMPILE_CMD) -x c++-header -o $@ $<

%.d : %.gch
	@echo create dependency $@; \
	set -e; \
	$(COMPILE_CMD) -MM $*.h | sed 's,\($(notdir $*)\)\.o[ :]*,$*.gch $*.d : ,g' > $@

# include src/proto/Makefile # 在最后执行
sinclude $(DEPS) # 在最先执行

rtags :
	@make clean; \
	echo $(INC) > .clang_complete; \
	bear make rtags=y; \
	rc -J ./compile_commands.json

release :
	@make clean; \
	make release=y;

show :
	@echo "TARGET	:" $(TARGET)
	@echo "SRC_DIR	:" $(SRC_DIR)
	@echo "EXT_DIR	:" $(EXT_DIR)
	@echo "PROTO_DIR :" $(PROTO_DIR)

cleanall : clean
	-rm -f $(RM_ALL) compile_commands.json .clang_complete

clean :
	-rm -f $(RM)

#}}}

#{{{ help note

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
# }}}
