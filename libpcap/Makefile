TARGET := pcapread
OBJS := main.o
LIB_USER :=  
LIB_USER_OBJS :=  
OPTIONS := -g
LDFLAGS := -lpcap
CFLAGS := $(OPTIONS)
CXXFLAGS := $(OPTIONS)
CC := gcc
CXX := g++
all	: $(TARGET) $(LIB_USER)
$(TARGET): $(OBJS) $(LIB_USER)
	@$(CXX) -o $@ $(OBJS) $(LIB_USER) $(LDFLAGS)
	@echo -e "\033[0;33m Generated	$@\033[0m"
$(LIB_USER):	$(LIB_USER_OBJS)
	@ar -rcs $@ $^
	@echo -e "\033[0;32m LINK	$@	by	$^\033[0m"
%.o	:	%.c
	@$(CC) -c -fPIC $(CFLAGS) $< -o $@
	@echo -e "\033[0;32m CC	$@\033[0m"
%.o	:	%.cpp
	@$(CXX) -c -fPIC $(CXXFLAGS) $< -o $@
	@echo -e "\033[0;32m CXX	$@\033[0m"
clean:
	@rm $(TARGET) $(LIB_USER) *.o
	@echo -e "\033[0;34m Removed all TARGET and objects\033[0m"


C_NONE=$(shell echo -e "\033[0m")
C_RED=$(shell echo -e "\033[31m")
C_GREEN=$(shell echo -e "\033[32m")
C_ORANGE=$(shell echo -e "\033[33m")
C_BLUE=$(shell echo -e "\033[34m")
C_PURPLE=$(shell echo -e "\033[35m")
C_CYAN=$(shell echo -e "\033[36m")
C_LIGHT_GRAY=$(shell echo -e "\033[37m")


