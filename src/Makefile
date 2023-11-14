TRASH= *.out ../build* ../3DViewer2.tar.gz
APP_DIR = ../app
BUILD_DIR= ../build
MANUAL = Manual
APP_NAME=3DViewer2.app
ifeq ($(UNAME), Linux)
    APP_NAME=3DViewer2
endif

all: run

run: install
	@sleep 1
	open $(APP_DIR)/$(APP_NAME)

build:
	cmake -DCMAKE_PREFIX_PATH=$(QT_INSTALL_PREFIX) -B $(BUILD_DIR)
	make -C $(BUILD_DIR)

install: build
	mkdir -p $(APP_DIR)
	cp -rf $(BUILD_DIR)/$(APP_NAME) $(APP_DIR)

uninstall:
	rm -rf $(APP_DIR)

build_tests:
	cmake -S tests -B ../build_tests -DCMAKE_CXX_COMPILER=g++

create_tests: build_tests
	make -C ../build_tests 3DViewer2_tests

tests: create_tests
	./../build_tests/3DViewer2_tests

leaks: tests
	leaks --atExit -- ./../build_tests/3DViewer2_tests

dist: clean
	cd .. && tar -zcvf 3DViewer2.tar.gz src

clean:
	rm -rf $(TRASH)

style:
	clang-format --style=google -verbose -n model/*.cc model/*.h 3DViewer2/*.cc 3DViewer2/*.h tests/*.cc

dvi:
	mkdir -p $(APP_DIR)
	texi2pdf $(MANUAL).texi
	texi2html $(MANUAL).texi
	cp -r $(MANUAL).pdf $(APP_DIR)
	cp -r $(MANUAL).html $(APP_DIR)
	rm -rf $(MANUAL).aux $(MANUAL).log $(MANUAL).toc $(MANUAL).pdf $(MANUAL).html