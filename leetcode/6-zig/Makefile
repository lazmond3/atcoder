debug: main.cpp
	g++ -std=c++17 -fsanitize=address main.cpp
	DEBUG=1 ./a.out
run: main.cpp
	g++ -std=c++17 -fsanitize=address main.cpp
	./a.out 
ojtest: main.cpp
	g++ -DTEST -std=c++17 -fsanitize=address main.cpp test.cpp
	oj test -d $(ARGS)
