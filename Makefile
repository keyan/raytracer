G++ = g++ -g -std=c++11 -Werror

all: clean format build run

clean:
	rm -rf .*swp *.out *.dSYM/ *.ppm .DS_Store

format:
	clang-format -i *.cc *.h

build:
	$(G++) main.cc -o main.out

run:
	./main.out >> image.ppm
	open image.ppm
