CC            = g++
CFLAGS64      = -c -Wall -m64 -O2 -DNDEBUG
# -D__HAS_AVX512__
CFLAGS32      = -c -Wall -m32 -O2 -DNDEBUG
# -D__HAS_AVX512__
CFLAGSSE2     = -msse2
CFLAGAVX      = -mavx
CFLAGXOP      = -mavx -mxop -DPARALLEL__AVX_XOP__
CFLAGAVX2     = -mavx2 -DPARALLEL__AVX2__
CFLAGXOP2     = -mavx2 -mxop -DPARALLEL__AVX2_XOP__
CFLAGAVX512DQ = 
#-mavx512dq -DPARALLEL__AVX512__
LFLAGS64      = -m64
LFLAGS32      = -m32

all: parallel64 parallel32
	

# 64 bit
parallel64: main64.o common64.o hashfactory64.o parallelsha25664.o parallelsha256avx64.o parallelsha256xop64.o parallelsha256avx264.o parallelsha256xop264.o parallelsha256avx51264.o
	$(CC) $(LFLAGS64) -o parallel64 main64.o common64.o hashfactory64.o parallelsha25664.o parallelsha256avx64.o parallelsha256xop64.o parallelsha256avx264.o parallelsha256xop264.o parallelsha256avx51264.o

main64.o: main.cpp hashfactory.h hash.h common.h architecture.h
	$(CC) $(CFLAGS64) -o main64.o main.cpp

common64.o: common.cpp common.h architecture.h
	$(CC) $(CFLAGS64) -o common64.o common.cpp

hashfactory64.o: hashfactory.cpp hashfactory.h hash.h common.h architecture.h
	$(CC) $(CFLAGS64) -o hashfactory64.o hashfactory.cpp

parallelsha25664.o: parallelsha256.cpp parallelsha256.h parallelsha256help.h hashfactory.h hash.h common.h architecture.h
	$(CC) $(CFLAGS64) $(CFLAGSSE2) -o parallelsha25664.o parallelsha256.cpp

parallelsha256avx64.o: parallelsha256avx.cpp parallelsha256.h parallelsha256help.h common.h architecture.h
	$(CC) $(CFLAGS64) $(CFLAGAVX) -o parallelsha256avx64.o parallelsha256avx.cpp

parallelsha256xop64.o: parallelsha256xop.cpp parallelsha256.h parallelsha256help.h common.h architecture.h
	$(CC) $(CFLAGS64) $(CFLAGXOP) -o parallelsha256xop64.o parallelsha256xop.cpp

parallelsha256avx264.o: parallelsha256avx2.cpp parallelsha256.h parallelsha256help.h common.h architecture.h
	$(CC) $(CFLAGS64) $(CFLAGAVX2) -o parallelsha256avx264.o parallelsha256avx2.cpp

parallelsha256xop264.o: parallelsha256xop2.cpp parallelsha256.h parallelsha256help.h common.h architecture.h
	$(CC) $(CFLAGS64) $(CFLAGXOP2) -o parallelsha256xop264.o parallelsha256xop2.cpp

parallelsha256avx51264.o: parallelsha256avx512.cpp parallelsha256.h parallelsha256help.h common.h architecture.h
	$(CC) $(CFLAGS64) $(CFLAGAVX512DQ) -o parallelsha256avx51264.o parallelsha256avx512.cpp


# 32 bit
parallel32: main32.o common32.o hashfactory32.o parallelsha25632.o parallelsha256avx32.o parallelsha256xop32.o parallelsha256avx232.o parallelsha256xop232.o parallelsha256avx51232.o
	$(CC) $(LFLAGS32) -o parallel32 main32.o 

main32.o: main.cpp hashfactory.h hash.h common.h architecture.h
	$(CC) $(CFLAGS32) -o main32.o main.cpp

common32.o: common.cpp common.h architecture.h
	$(CC) $(CFLAGS32) -o common32.o common.cpp

hashfactory32.o: hashfactory.cpp hashfactory.h hash.h common.h architecture.h
	$(CC) $(CFLAGS32) -o hashfactory32.o hashfactory.cpp

parallelsha25632.o: parallelsha256.cpp parallelsha256.h parallelsha256help.h hashfactory.h hash.h common.h architecture.h
	$(CC) $(CFLAGS32) $(CFLAGSSE2) -o parallelsha25632.o parallelsha256.cpp

parallelsha256avx32.o: parallelsha256avx.cpp parallelsha256.h parallelsha256help.h common.h architecture.h
	$(CC) $(CFLAGS32) $(CFLAGAVX) -o parallelsha256avx32.o parallelsha256avx.cpp

parallelsha256xop32.o: parallelsha256xop.cpp parallelsha256.h parallelsha256help.h common.h architecture.h
	$(CC) $(CFLAGS32) $(CFLAGXOP) -o parallelsha256xop32.o parallelsha256xop.cpp

parallelsha256avx232.o: parallelsha256avx2.cpp parallelsha256.h parallelsha256help.h common.h architecture.h
	$(CC) $(CFLAGS32) $(CFLAGAVX2) -o parallelsha256avx232.o parallelsha256avx2.cpp

parallelsha256xop232.o: parallelsha256xop2.cpp parallelsha256.h parallelsha256help.h common.h architecture.h
	$(CC) $(CFLAGS32) $(CFLAGXOP2) -o parallelsha256xop232.o parallelsha256xop2.cpp

parallelsha256avx51232.o: parallelsha256avx512.cpp parallelsha256.h parallelsha256help.h common.h architecture.h
	$(CC) $(CFLAGS32) $(CFLAGAVX512DQ) -o parallelsha256avx51232.o parallelsha256avx512.cpp


clean:
	-rm *.o parallel64 parallel32
