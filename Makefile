G++ = g++ -g -std=c++11 -Werror

all: clean format build run

clean:
	rm -rf .*swp *.out *.dSYM/ *.ppm

format:
	clang-format -i *.cc *.h

build:
	$(G++) main.cc -o main.out

run:
	./main.out >> image.ppm
	open image.ppm
