CXXFLAGS          := -O3 -g
BIN =NeuralNet3

CUDA_INSTALL_PATH ?= /opt/cuda

CPPCOMPILER = g++
NVCC ?= $(CUDA_INSTALL_PATH)/bin/nvcc
INCD = -I"$(CUDA_INSTALL_PATH)/include" -I"$(CUDA_INSTALL_PATH)/include/thrust" -I"../src"
LIBS = -lcuda -L"$(CUDA_INSTALL_PATH)/lib64" -lcudart 

#NVCCFLAGS := -G -g -O0 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_20,code=sm_21 -M
#NVCCFLAGS := -G -g -O0 --compile -x c++
NVCCFLAGS := --compile -G -O0 -ccbin g++ -g -gencode arch=compute_20,code=compute_20 -gencode arch=compute_20,code=sm_21  -x cu
CPPFLAGS := -c -g -std=c++11 -I/opt/cuda/include
NVCCLINKERFLAGS := --cudart static -link

# files
CPP_SOURCES       := $(wildcard ../src/*.cpp) $(wildcard ../src/*/*.cpp)
CU_SOURCES        := $(wildcard ../src/*.cu) $(wildcard ../src/*/*.cu)
HEADERS           := $(wildcard ../src/*.h) $(wildcard ../src*/*.h)
CPP_OBJS          := $(patsubst %.cpp, %.o, $(CPP_SOURCES))
CU_OBJS           := $(patsubst %.cu, %.o, $(CU_SOURCES))
#CU_OBJS           := $(patsubst %.cu, %.d, $(CU_SOURCES))



all: $(CPP_OBJS) $(CU_OBJS)
	$(NVCC) $(NVCCLINKERFLAGS) -o $(BIN) $(CU_OBJS) $(CPP_OBJS) $(LDFLAGS) $(LIBS)
#	$(NVCC) $(NVCCLINKERFLAGS) -o $(BIN) $(CU_OBJS) $(CPP_OBJS) $(LDFLAGS) $(INCD) $(LIBS)
#	$(CPPCOMPILER) -o $(BIN) $(CU_OBJS) $(CPP_OBJS) $(LDFLAGS) $(INCD) $(LIBS)

debug: all
	rm -f debug.log
	./$(BIN)>> debug.log

#%.d : %.cu
#	$(NVCC) $(NVCCFLAGS) $(INCD) -o $@ $<

%.o: %.cpp
	$(CPPCOMPILER) $(CPPFLAGS) $(INCD) -o $@ $<

%.o: %.cu
	$(NVCC) $(NVCCFLAGS) -o $@ $<
#	$(NVCC) $(NVCCFLAGS) $(INCD) -o $@ $<


clean:
#	rm -f $(BIN) ../src/*.o ../src/*.cu_o ../src/*/*.o ../src/*/*.cu_o
	rm -f $(BIN) OutPut.csv debug.log ../src/*.o ../src/*.d ../src/*/*.o ../src/*/*.d
