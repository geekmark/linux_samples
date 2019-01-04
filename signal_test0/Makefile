#CC	= aarch64-linux-gnu-gcc
#LD	= aarch64-linux-gnu-gcc
#AR	= aarch64-linux-gnu-ar

CC	= g++
LD	= g++
AR	= ar

INC_DIR :=
LIB_DIR :=
COMMON_INC=-I/usr/src/linux-headers-4.15.0-32-generic/include
COMMON_SRC=
OBJ_DIR=

CFLAGS = -g -O2 -Wall $(INC_DIR) $(COMMON_INC) $(LIB_DIR) -lpthread

TARGET=signaletest0
SRCS = main.cpp                 \


TEMOBJS := $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(TEMOBJS))


all:$(TARGET)

$(TARGET):$(OBJS)
	$(LD) $(OBJS) $(CFLAGS) $(LIB_DIR)  $(LIB) $(LDFLAGS) -o $@ 
	chmod a+x $@
$(OBJ_DIR)%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf  $(TARGET) 

