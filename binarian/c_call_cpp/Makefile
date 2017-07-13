TARGET := c_call_cpp
OBJS := main.o
LIB_USER := libadd.a 
LIB_USER_OBJS := add.o
OPTIONS := -g
CFLAGS := $(OPTIONS)
CXXFLAGS := $(OPTIONS)
CC := gcc
CXX := g++
all	: $(TARGET) $(LIB_USER)
$(TARGET): $(OBJS) $(LIB_USER)
	@$(CC) -o $@ $(OBJS) $(LIB_USER)
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
	@echo -e "\033[0;34m Removed all targets and objects\033[0m"
execute:
	./$(TARGET) 1 2
