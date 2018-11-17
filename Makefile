G++ = g++ -g -std=c++11 -Werror

all: clean format build run

clean:
	rm -rf .*swp
	rm -rf *.out
	rm -rf *.dSYM/

format:
	clang-format -i *.cc
	clang-format -i *.h

build:
	$(G++) main.cc -o main.out

run:
	./main.out
