
all: main.cc parse_json.cc any.cc types.cc
	clang++ $^ -o any -std=c++20 -I rapidjson/include

clean:
	rm -rf any *.o