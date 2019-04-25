CFLAGS = -Wall -O2
LDLIBS = -lpthread

TARGET := msgqtest 
SRCS = src/main.cpp
INC_DIR = ./inc
OBJ_DIR = ./

TEMOBJS := $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJ_DIR), $(TEMOBJS))

.PHONY : clean all


all: $(TARGET)


$(TARGET): 
	gcc -g $(SRCS) -I$(INC_DIR)  -o $@ -Wall

clean:
	@rm -f $(TARGET) src/*.o

