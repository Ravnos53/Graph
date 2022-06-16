.PHONY: all clean install uninstall 

CC = g++ -std=c++17
CFLAGS = -Wall -Werror -Wextra -MP -MMD -c
PROG = Graph.exe
FILESCPP = $(wildcard src/*.cpp)
OBJECTS = $(subst .cpp,.o,$(FILESCPP))

all: $(FILESCPP) $(PROG)

run:
	export LD_LIBRARY_PATH=lib && ./bin/$(PROG)

$(PROG): $(subst src/,build/src/,$(OBJECTS))
	$(CC) $^ -o bin/$@

build/src/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -Isrc/include -o $@

-include build/src/*.d

#tests
T_EXEC = test.exe
FILECPP_WITHOUT_MAIN = $(FILESCPP:src/main.cpp=)
TESTCPP = $(wildcard test/*.cpp)
T_OBJECTS = $(subst .cpp,.o,$(FILECPP_WITHOUT_MAIN))
TESTOBJ = $(subst .cpp,.o,$(TESTCPP))


test: $(FILECPP_WITHOUT_MAIN) $(TESTCPP) $(T_EXEC)

$(T_EXEC): $(subst src/,build/test/,$(T_OBJECTS)) $(subst test/,build/test/,$(TESTOBJ))
	$(CC) $(subst src/,build/test/,$(T_OBJECTS)) $(subst test/,build/test/,$(TESTOBJ)) -o bin/$@ 
	
build/test/%.o: src/%.cpp 	
	$(CC) $(CFLAGS) $< -Isrc/include -o $@

build/test/%.o: test/%.cpp	
	$(CC) $(CFLAGS) $< -Isrc/include -o $@


-include build/test/*.d

checktest:
	export LD_LIBRARY_PATH=lib && ./bin/test.exe

clean:  
	rm -rf build/test/*.o build/test/*.d  build/src/*.o build/src/*.d 
