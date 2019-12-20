CXX=clang++ -O3
HALIDE_DISTRIB=~/Halide/build/distrib
CXX_FLAGS=-fno-rtti -std=c++11 -I $(HALIDE_DISTRIB)/include/ -I $(HALIDE_DISTRIB)/tools -L $(HALIDE_DISTRIB)/bin/
CXX_LIBS=-L $(HALIDE_DISTRIB)/bin/ -lHalide -ltinfo -lpthread -ldl
CXX_MM_LIBS=-L $(HALIDE_DISTRIB)/bin/ -lpthread -ldl -ljpeg -lpng

all: mm mm_int

mm: mm.cpp aot/halide_mm.a aot/halide_mm.h
	$(CXX) $(CXX_FLAGS) -I aot -o mm mm.cpp aot/halide_mm.a  $(CXX_MM_LIBS)

mm_int: mm_int.cpp aot_int/halide_mm.a aot_int/halide_mm.h
	$(CXX) $(CXX_FLAGS) -I aot_int -o mm_int mm_int.cpp aot_int/halide_mm.a  $(CXX_MM_LIBS)

aot/halide_mm.a: mm_generator
	LD_LIBRARY_PATH=$(HALIDE_DISTRIB)/bin/ ./mm_generator -g halide_mm -o ./aot MA.type=float32 MB.type=float32 output.type=float32 auto_schedule=true target=host	
	LD_LIBRARY_PATH=$(HALIDE_DISTRIB)/bin/ ./mm_generator -g halide_mm -o ./aot_int MA.type=uint8 MB.type=uint8 output.type=uint32 auto_schedule=true target=host
	LD_LIBRARY_PATH=$(HALIDE_DISTRIB)/bin/ ./mm_generator -g halide_mm -o ./aot_ndk_arm MA.type=float32 MB.type=float32 output.type=float32 auto_schedule=true target=arm-64-android
	LD_LIBRARY_PATH=$(HALIDE_DISTRIB)/bin/ ./mm_generator -g halide_mm -o ./aot_ndk_arm_int MA.type=uint8 MB.type=uint8 output.type=uint32 auto_schedule=true target=arm-64-android

mm_generator: mm_generator.cpp
	$(CXX) $(CXX_FLAGS) -o mm_generator mm_generator.cpp $(HALIDE_DISTRIB)/tools/GenGen.cpp $(CXX_LIBS)

clean:
	rm -f mm_generator mm mm_int aot/* aot_int/* aot_ndk_arm/*
