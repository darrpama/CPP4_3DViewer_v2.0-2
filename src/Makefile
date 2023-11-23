CC = g++
CCFLAGS = -g -std=c++17 -Wall -Werror -Wextra
LDFLAGS = -lgtest -fprofile-arcs -ftest-coverage
PROJECTDIR = $(CURDIR)
BUILDDIR = $(PROJECTDIR)/build
INSTALLDIR = $(PROJECTDIR)
EXECUTABLE = test.out
STATICLIB = 3DViewer.a
DISTDIR = ../distributive

HEADERS = \
    $(PROJECTDIR)/models/transform.h
    # $(PROJECTDIR)/models/obj_parser.h \
    $(PROJECTDIR)/models/settings.h
    # $(PROJECTDIR)/models/renderer.h \
    # $(PROJECTDIR)/models/type.h
    # $(PROJECTDIR)/models/model.h \

SOURCES = \
    $(PROJECTDIR)/models/transform.cc \
    $(PROJECTDIR)/tests/transform_test.cc
    # $(PROJECTDIR)/models/obj_parser.cc \
    # $(PROJECTDIR)/tests/parser_test.cc \
    # $(PROJECTDIR)/models/renderer.cc \
    # $(PROJECTDIR)/models/settings.cc \
    # $(PROJECTDIR)/models/model.cc \
    # $(PROJECTDIR)/tests/run_all_tests.cc
    # $(PROJECTDIR)/main.cc \

OBJECTS = $(SOURCES:.cc=.o)
GCDA = $(SOURCES:.cc=.gcda)
GCNO = $(SOURCES:.cc=.gcno)

all: install

tests: $(SOURCES) $(EXECUTABLE)

dvi:
	open ./README.pdf

build:
	cd $(PROJECTDIR) && ls -la && mkdir $(BUILDDIR) && cd $(BUILDDIR) && cmake .. && make

open:
	cd $(INSTALLDIR) && $(INSTALLDIR)/3DViewer_2_0.app/Contents/MacOS/3DViewer_2_0

install: build
	cd $(INSTALLDIR) && ls -la && cp -r $(BUILDDIR)/3DViewer_2_0.app .

uninstall:
	cd $(INSTALLDIR) && rm -rf 3DViewer_2_0.app

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
	$(CC) $(OBJECTS) $(HEADERS) $(INCLUDE) -o $@ $(LDFLAGS)
	./$(EXECUTABLE) 

%.o: %.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -o $@ -c $<

$(STATICLIB): $(OBJECTS)
	ar rcs $(STATICLIB) $^

gcov_report: $(EXECUTABLE)
	./$(EXECUTABLE)
	lcov -t "./test.out" -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

.PHONY: clean test dvi dist check leaks gcov_report
clean:
	rm -rf $(OBJECTS)
	rm -rf $(EXECUTABLE)
	rm -rf $(STATICLIB)
	rm -rf $(BUILDDIR)
	rm -rf *.gcno $(GCDA) $(GCNO) *.info
	rm -rf report
	rm -rf *.tgz

