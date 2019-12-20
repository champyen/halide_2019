CXX=g++
HALIDE_DISTRIB=~/Halide/build/distrib
INC=-I $(HALIDE_DISTRIB)/include -I $(HALIDE_DISTRIB)/tools
LIBS=-L $(HALIDE_DISTRIB)/bin -lHalide `libpng-config --cflags --ldflags` -ljpeg -lpthread -ldl

image_jit: image_jit.cpp
	$(CXX) image_jit.cpp -o image_jit -std=c++11 $(INC) $(LIBS)

clean:
	rm -f image_jit