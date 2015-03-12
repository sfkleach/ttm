
CXXFLAGS=-std=c++11 -O

OBJS=main.o simplenetwork.o mishap.o

ttm: $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $(OBJS)

.PHONY: clean
clean:
	rm -f ttm
	rm -f *.o
