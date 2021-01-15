debug: main.cpp
	g++ -std=c++17 main.cpp
	DEBUG=1 ./a.out
run: main.cpp
	./a.out 
ojtest: main.cpp
	g++ -DTEST -std=c++17 main.cpp test.cpp
	oj test -d $(ARGS)
