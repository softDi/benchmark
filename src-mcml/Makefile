TARGET := mcml
$(TARGET) : *.c
	gcc -o $@ *.c -g -O3 -msse -lm
clean:
	rm $(TARGET) *.o 
