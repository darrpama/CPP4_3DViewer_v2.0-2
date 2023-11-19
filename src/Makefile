CC = g++
CCFLAGS = -g -std=c++17 -pedantic -Wall -Werror -Wextra
LDFLAGS = -lstdc++ -lgtest -fprofile-arcs -ftest-coverage
PROJECTDIR = .
BUILDDIR = ./build
EXECUTABLE = test.out
STATICLIB = 3DViewer.a
DISTDIR = ../distributive

HEADERS = \
    $(PROJECTDIR)/models/model.h \
    $(PROJECTDIR)/models/obj_parser.h \
    $(PROJECTDIR)/models/object.h \
    $(PROJECTDIR)/models/renderer.h \
    $(PROJECTDIR)/models/settings.h \
    $(PROJECTDIR)/models/transform.h \
    $(PROJECTDIR)/models/type.h


SOURCES = \
    $(PROJECTDIR)/main.cc \
    $(PROJECTDIR)/models/model.cc \
    $(PROJECTDIR)/models/obj_parser.cc \
    $(PROJECTDIR)/models/object.cc \
    $(PROJECTDIR)/models/renderer.cc \
    $(PROJECTDIR)/models/settings.cc \
    $(PROJECTDIR)/models/transform.cc \
    $(PROJECTDIR)/tests/test_parser.cc \
    $(PROJECTDIR)/tests/transform_test.cc \
    $(PROJECTDIR)/tests/run_all_tests.cc

OBJECTS = $(SOURCES:.cc=.o)
GCDA = $(SOURCES:.cc=.gcda)
GCNO = $(SOURCES:.cc=.gcno)

# Makefile: !all, !install, !uninstall, !dvi, clean, dist, tests

all: install

tests: $(SOURCES) $(EXECUTABLE)

dvi:
	open ./README.pdf

build:
	cd $(PROJECTDIR) && ls -la && mkdir $(BUILDDIR) && cd $(BUILDDIR) && cmake .. && make

install:
	cd $(PROJECTDIR) && ls -la && mkdir $(BUILDDIR) && cd $(BUILDDIR) && cmake .. && make
	cd $(PROJECTDIR) && $(BUILDDIR)/Calculator.app/Contents/MacOS/Calculator

uninstall:
	cd $(PROJECTDIR) && rm -rf $(BUILDDIR)

dist:
	rm -rf $(DISTDIR)
	mkdir $(DISTDIR)
	mkdir $(DISTDIR)/src
	cp -r $(PROJECTDIR) README.md README.pdf Makefile $(DISTDIR)/src/
	tar cvzf distributive.tgz $(DISTDIR)
	rm -rf $(DISTDIR)

check:
	clang-format -n --style="Google" $(SOURCES) $(HEADERS)
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=unusedStructMember --suppress=missingInclude $(SOURCES) $(HEADERS)

leaks: $(EXECUTABLE)
	leaks -atExit -- ./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(HEADERS) -o $@ $(LDFLAGS)
	./$(EXECUTABLE) 

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $< $(LDFLAGS)

$(STATICLIB): $(OBJECTS)
	ar rcs $(STATICLIB) $^

gcov_report: $(EXECUTABLE)
	./$(EXECUTABLE)
	lcov -t "./test.out" -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

.PHONY: clean test dvi dist check leaks gcov_report
clean:
	@rm -rf $(OBJECTS)
	@rm -rf $(EXECUTABLE)
	@rm -rf $(STATICLIB)
	@rm -rf *.gcno $(GCDA) $(GCNO) *.info
	@rm -rf report
	@rm -rf *.tgz

