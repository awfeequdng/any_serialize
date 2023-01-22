#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "any.hh"
#include "types.hh"
#include "dump_json.hh"
#include "parse_json.hh"

void test_set() {
    my_traits::Any any;
    any.set(20);
    std::cout << any.get<int>() << std::endl;
    std::cout << any.get_typename() << std::endl;
    any.set("200");
    std::cout << any.get_typename() << std::endl;
    any.set(std::string("hello world"));
    std::cout << "std::string type: " << any.get_typename() << std::endl;
    std::vector<int> vec(2, 9);
    any.set(vec);
    std::cout << any.get_typename() << std::endl;

    any.set(2.0);
    std::cout << any.get_typename() << std::endl;


}

void test_get() {
    my_traits::Any any;
    any.set(30);
    try {
        auto v = any.get<float>();
        std::cout << v << std::endl;
    }
    catch (std::logic_error e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "get any failed" << std::endl;
    }
}

void test_dump() {
    std::cout << "test_dump -------" << std::endl;

    Friend f1{"my best friend", Singer{"rocker", 18}};
    Friend f2{"new friend", "little girl"};
    Friend f3{"third friend", 3};
    Person p2{"p2", 3, Address{"china", "shanghai", "putuo"}};
    Address addr1{"china", "beijing", "wangjing", {p2}};
    Person p1{"p1", 4, addr1, {f1, f2, f3}, "the kind!"};

    // my_traits::Any any(p1);
    // std::cout << "person type: " << any.get_typename() << std::endl;
    // any.set(addr1);
    // std::cout << "address type: " << any.get_typename() << std::endl;

    auto json_p1 = my_json::dump_json(p1);
    // std::cout << p1 << std::endl;
    auto pp = my_json::parse_json<Person>(json_p1);
    auto json_pp = my_json::dump_json(pp);
    // if (json_p1 == json_pp) {
    //     std::cout << "json_p1 == json_pp" << std::endl;
    // } else {
    //     std::cout << "json_p1 != json_pp" << std::endl;
    // }
    assert(json_p1 == json_pp);
}

int main() {
    test_set();
    test_get();

    test_dump();

    return 0;
}
