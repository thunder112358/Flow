# Use C99 for C files and g++ for C++ files
CC = c99
CXX = g++
CFLAGS = -O3 -I../iio/
CXXFLAGS = -O3 -std=c++11 `pkg-config --cflags opencv4`
OMPFLAGS = -fopenmp
LDFLAGS = -ltiff -lpng -ljpeg -lm `pkg-config --libs opencv4`

# Targets
all: tvl1flow vqm

# Main executable for tvl1flow
tvl1flow: main.o opencv_wrapper.o tvl1flow_lib.o bicubic_interpolation.o mask.o zoom.o iio.o
	$(CC) $(CFLAGS) $(OMPFLAGS) -o tvl1flow main.o tvl1flow_lib.o bicubic_interpolation.o mask.o zoom.o iio.o opencv_wrapper.o $(LDFLAGS)

# Main executable for vqm
vqm: main_mesure.o opencv_wrapper.o tvl1flow_lib.o bicubic_interpolation.o mask.o zoom.o iio.o
	$(CC) $(CFLAGS) $(OMPFLAGS) -o vqm main_mesure.o tvl1flow_lib.o bicubic_interpolation.o mask.o zoom.o iio.o opencv_wrapper.o $(LDFLAGS)

# Compile the C++ wrapper
opencv_wrapper.o: opencv_wrapper.cpp
	$(CXX) $(CXXFLAGS) -c opencv_wrapper.cpp -o opencv_wrapper.o

# Compile individual C files
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

main_mesure.o: main_mesure.c
	$(CC) $(CFLAGS) -c main_mesure.c -o main_mesure.o

tvl1flow_lib.o: tvl1flow_lib.c
	$(CC) $(CFLAGS) -c tvl1flow_lib.c -o tvl1flow_lib.o

bicubic_interpolation.o: bicubic_interpolation.c
	$(CC) $(CFLAGS) -c bicubic_interpolation.c -o bicubic_interpolation.o

mask.o: mask.c
	$(CC) $(CFLAGS) -c mask.c -o mask.o

zoom.o: zoom.c
	$(CC) $(CFLAGS) -c zoom.c -o zoom.o

iio.o: ../iio/iio.c
	$(CC) $(CFLAGS) -DNDEBUG -D_GNU_SOURCE -c ../iio/iio.c -o iio.o

# Clean up
clean:
	rm -f *.o tvl1flow vqm
