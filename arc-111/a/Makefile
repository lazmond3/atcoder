.PHONY: clean ojtest

main: main2.cpp
	g++ -std=c++17 main2.cpp -o main
debug: main2.cpp
	g++ -std=c++17 main2.cpp -o debug
test: main2.cpp main2_test.cpp main2.hpp
	g++ -DTEST -std=c++17 main2.cpp  main2_test.cpp -o test-out
	./test-out

oj:
	if [ ! -e main ]; then make main; fi
	oj test -c ./main

clean:
	if [ -e test-out ]; then rm test-out; fi
	if [ -e a.out ]; then rm a.out; fi
	if [ -e main ]; then rm main; fi
	if [ -e debug ]; then rm debug; fi