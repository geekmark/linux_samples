#CC	= aarch64-linux-gnu-gcc
#LD	= aarch64-linux-gnu-gcc
#AR	= aarch64-linux-gnu-ar

CC	= gcc
LD	= gcc
AR	= ar

INC_DIR := 
LIB_DIR := 
COMMON_INC =      
COMMON_SRC = 
OBJ_DIR   = 

CFLAGS = -g -O2 -Wall -I$(INC_DIR) -I$(COMMON_INC) -I$(LIB_DIR) -lpthread

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

