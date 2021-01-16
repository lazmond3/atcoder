debug: main.cpp
	g++ -std=c++17 -fsanitize=address main.cpp
	DEBUG=1 ./a.out
slim: slim.cpp
	g++ -std=c++17 -fsanitize=address slim.cpp
	DEBUG=1 ./a.out
run: main.cpp
	g++ -std=c++17 -fsanitize=address main.cpp
	./a.out 
ojtest: main.cpp
	g++ -DTEST -std=c++17 -fsanitize=address main.cpp test.cpp
	oj test -d $(ARGS) --compare-mode double-match
slimtest: slim.cpp
	g++ -DTEST -std=c++17 -fsanitize=address slim.cpp test.cpp
	oj test -d $(ARGS) --compare-mode double-match
