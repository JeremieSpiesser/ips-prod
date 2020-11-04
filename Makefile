CC = g++
CFLAGS = -g -std=c++11 -Wall -Wextra
LDFLAGS = -larmadillo

TARGET = ./bin/main
MAIN_CPP = ./src/main.cpp
OBJS = ./obj/poly.o

TEST_TARGET = ./bin/tests
TEST_INC = ./tests/testTest.h ./tests/testPoly.h
TEST_CXX_CPP = ./tests/tests.cpp

ASTYLE_OPTIONS = \
		 --style=linux -s4 \
		 --pad-oper --pad-header --pad-comma \
		 --align-pointer=name --align-reference=name \
		 --break-one-line-headers \
		 --remove-braces \
		 --break-return-type \
		 --convert-tabs \
		 --close-templates \
		 --max-code-length=101 \
		 --mode=c \
		 --lineend=linux \
		 --attach-inlines \
		 --indent-labels \
		 --indent-col1-comments \
		 --indent-preproc-block

.PHONY: all tests pres clean doc

all: $(TARGET)

style:
	astyle $(ASTYLE_OPTIONS) --recursive 'src/*.cpp'      || exit 1
	astyle $(ASTYLE_OPTIONS) --recursive 'headers/*.h'    || exit 1
	astyle $(ASTYLE_OPTIONS) --recursive 'tests/test*.h'  || exit 1
	exit 0

$(TARGET): $(OBJS) $(MAIN_CPP)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

./obj/%.o: ./src/%.cpp ./headers/%.h
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(OBJS)
	cxxtestgen --error-printer -o $(TEST_CXX_CPP) $(TEST_INC)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_CXX_CPP) $^ -o $(TEST_TARGET)

pres:
	php -S localhost:8000 -t pres/

doc:
	doxygen

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
	rm -f $(TEST_TARGET)
	rm -f $(TEST_CXX_CPP)
	find . -name '*.orig' -exec rm {} \;

