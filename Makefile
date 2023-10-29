rg-cpp: src/main.cpp 
	g++ -Ofast -o rg-cpp src/main.cpp -o rg-cpp
install: rg-cpp
	cp rg-cpp /usr/bin/
clean: rg-cpp
	rm -rf rg-cpp
all: src/main.cpp
	g++ -Ofast src/main.cpp -o rg-cpp
	cp rg-cpp /usr/bin/