
all: main.cc serialize/parse_json.cc traits/any.cc types.cc serialize/serialize.cc hash/hash.cc
	clang++ $^ -o any -std=c++20 -I rapidjson/include -I.

clean:
	rm -rf any *.o