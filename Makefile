CC = g++
CFLAGS = -g -std=c++11 -Wall -Wextra -O3 -march=native -flto
LDFLAGS = -larmadillo

TARGET = ./bin/main
MAIN_CPP = ./src/main.cpp
OBJS = ./obj/poly.o ./obj/utils.o ./obj/basis.o ./obj/nuclear.o ./obj/exporter.o

TEST_TARGET = ./bin/tests
TEST_INC = ./tests/testTest.h ./tests/testUtils.h ./tests/testPoly.h ./tests/testBasis.h
TEST_CXX_CPP = ./tests/tests.cpp

VISU_POVRAY_SCENE = visu/visu.pov # If the 'visu' folder is changed, pay attention to change the path of files in the visu.pov as well !
VISU_POVRAY_RENDER = povray.png

WEBSERVER_ADDRESS = 0.0.0.0:8000

ASTYLE_OPTIONS = \
		 --style=linux -s4 \
		 --pad-oper --pad-header --pad-comma \
		 --align-pointer=name --align-reference=name \
		 --break-one-line-headers \
		 --remove-braces \
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
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

./obj/%.o: ./src/%.cpp ./headers/%.h
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(OBJS)
	cxxtestgen --error-printer -o $(TEST_CXX_CPP) $(TEST_INC)
	$(CC) $(CFLAGS) $(TEST_CXX_CPP) $^ -o $(TEST_TARGET) $(LDFLAGS)

povray:
	povray -D +A0.0001 -W800 -H600 +P +Q11 $(VISU_POVRAY_SCENE) +o$(VISU_POVRAY_RENDER)

pres:
	php -S $(WEBSERVER_ADDRESS) -t pres/

doc:
	doxygen

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
	rm -f $(TEST_TARGET)
	rm -f $(TEST_CXX_CPP)
	find . -name '*.orig' -exec rm {} \;
