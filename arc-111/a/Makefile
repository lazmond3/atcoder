.PHONY: clean ojtest

clean:
	if [ -e test-out ]; then rm test-out; fi
	if [ -e a.out ]; then rm a.out; fi
	if [ -e main ]; then rm main; fi

test: main2.cpp main2_test.cpp main2.hpp
	g++ -DTEST -std=c++17 main2.cpp  main2_test.cpp -o test-out
	./test-out

oj:
	oj test