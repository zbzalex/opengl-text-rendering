all: compile

compile:
	cd build && cmake .. && make && ./test

do_clean:
	rm -rf build && mkdir build
clean: do_clean compile

