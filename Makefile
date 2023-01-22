
all: main.cc dump_json.cc parse_json.cc
	clang++ $^ -o any -std=c++20

clean:
	rm -rf any