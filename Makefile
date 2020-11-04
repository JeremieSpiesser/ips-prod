CC = g++
CFLAGS = -g -std=c++11 -Wall -Wextra
LDFLAGS = -larmadillo
TARGET = ./bin/main
TEST_TARGET = ./bin/tests
OBJS = ./obj/poly.o ./obj/phi.o ./obj/phiplotter.o 
TEST = ./tests/testTest.h ./tests/testPolgen.h ./tests/testPhi.h 

.PHONY: all tests pres

all: $(TARGET)

style:
	./astyle.sh

exec:
	$(TARGET)

$(TARGET): $(OBJS) ./src/main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

./obj/%.o: ./src/%.cpp ./headers/%.h
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(OBJS)
	cxxtestgen --error-printer -o ./tests/tests.cpp $(TEST)
	$(CC) $(CFLAGS) $(LDFLAGS) ./tests/tests.cpp $^ -o $(TEST_TARGET)
	./bin/tests

pres:
	php -S localhost:8000 -t pres/

docs:
	doxygen

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

