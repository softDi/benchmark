target := avx 
sources := main.cpp
include_path := -I/usr/lib/gcc/x86_64-redhat-linux/4.8.5/include/
cxxflags := $(include_path)
cxxflags += -g -mavx -O3 
CXX := g++

$(target) : $(sources)
	$(CXX) $(cxxflags) -o $@ $^ 
clean:
	rm $(target) *.o	
