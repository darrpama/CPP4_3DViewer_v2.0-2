CC = g++
CCFLAGS = -g -std=c++17 -Wall -Werror -Wextra
LDFLAGS = -lgtest -fprofile-arcs -ftest-coverage
PROJECTDIR = $(CURDIR)
BUILDDIR = $(PROJECTDIR)/build
EXECUTABLE = test.out
STATICLIB = 3DViewer.a
DISTDIR = ../distributive

HEADERS = \
	$(PROJECTDIR)/models/object.h \
	$(PROJECTDIR)/models/matrix4x4.h \
	$(PROJECTDIR)/models/settings.h \
	$(PROJECTDIR)/models/transform.h \
	$(PROJECTDIR)/models/type.h \
	$(PROJECTDIR)/models/obj_parser.h

SOURCES = \
	$(PROJECTDIR)/models/object.cc \
	$(PROJECTDIR)/models/transform.cc \
	$(PROJECTDIR)/models/matrix4x4.cc \
	$(PROJECTDIR)/models/settings.cc \
	$(PROJECTDIR)/models/obj_parser.cc \
	$(PROJECTDIR)/tests/settings_test.cc \
	$(PROJECTDIR)/tests/transform_test.cc \
	$(PROJECTDIR)/tests/run_all_tests.cc \
	$(PROJECTDIR)/tests/parser_test.cc

OTHERS = \
	$(PROJECTDIR)/models/model_facade.h \
	$(PROJECTDIR)/models/model_facade.cc \
	$(PROJECTDIR)/models/renderer.h \
	$(PROJECTDIR)/models/renderer.cc \
	$(PROJECTDIR)/models/screenshot_strategy.h \
	$(PROJECTDIR)/models/screenshot_strategy.cc \
	$(PROJECTDIR)/controllers/controller_singleton.h \
	$(PROJECTDIR)/controllers/controller_singleton.cc

OBJECTS = $(SOURCES:.cc=.o)
GCDA = $(SOURCES:.cc=.gcda)
GCNO = $(SOURCES:.cc=.gcno)

all: install

tests: $(SOURCES) $(EXECUTABLE)

dvi:
	open ./README.pdf

build:
	cd $(PROJECTDIR) && ls -la && mkdir $(BUILDDIR) && cd $(BUILDDIR) && cmake .. && make

install:
	@read -p "Enter path to install: " path; \
	if [ -z "$$path" ]; then \
        path="./"; \
    fi; \
	cd $$path && ls -la && mkdir $(BUILDDIR) && cd $(BUILDDIR) && cmake .. && make
	$(BUILDDIR)/3DViewer_2_0.app/Contents/MacOS/3DViewer_2_0

uninstall: clean

dist: build
	rm -rf $(DISTDIR)
	mkdir $(DISTDIR)
	cp -r $(PROJECTDIR) $(DISTDIR)
	cd .. && tar -czvf distributive.tgz distributive
	rm -rf $(DISTDIR)

check:
	clang-format -i --style="Google" $(SOURCES) $(HEADERS) $(OTHERS)
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=unusedStructMember --suppress=unusedFunction --suppress=missingInclude $(SOURCES) $(OTHERS) $(HEADERS)

leaks: $(EXECUTABLE)
	leaks -atExit -- ./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(INCLUDE) -o $@ $(LDFLAGS)
	./$(EXECUTABLE) 

%.o: %.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -o $@ -c $< $(LDFLAGS)

$(STATICLIB): $(OBJECTS)
	ar rcs $(STATICLIB) $^

gcov_report: $(EXECUTABLE)
	./$(EXECUTABLE)
	lcov -t "./test.out" -o test.info --no-external -c -d . --ignore-errors mismatch
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
	rm -rf *.tgz ../*.tgz
