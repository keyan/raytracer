G++ = g++ -g -std=c++11 -Werror

all: clean build run

clean:
	rm -rf .*swp *.out *.dSYM/ *.ppm .DS_Store

format:
	clang-format -i *.cc include/*.h

build:
	$(G++) main.cc -o main.out -I include

run:
	./main.out >> image.ppm
	open image.ppm
