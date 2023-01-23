#pragma once
#include <rapidjson/rapidjson.h>
#include <vector>
#include <string>

#include "any.hh"
#include "rapidjson/prettywriter.h"
#include "SipHash.hh"
#include "my_traits.hh"
#include "serialize.hh"

struct Person;

using Writer = rapidjson::PrettyWriter<rapidjson::StringBuffer>;

struct Singer {
    std::string type;
    int age;

    // template <typename Writer>
    void serialize(Writer& writer) const;

    uint64_t hash() const;
    void update(SipHash& hash) const;
};

struct Address {
    std::string country;
    std::string city;
    std::string street;
    std::vector<Person> neighbors;

    // template <typename Writer>
    void serialize(Writer& writer) const;
    uint64_t hash() const;
    void update(SipHash& hash) const;
};

struct Friend {
    std::string relation;
    my_traits::Any secret;

    // template <typename Writer>
    void serialize(Writer& writer) const;
    uint64_t hash() const;
    void update(SipHash& hash) const;
};
struct Person {
    std::string name;
    int age;
    Address address;
    std::vector<Friend> friends;
    my_traits::Any secret;

    // template <typename Writer>
    void serialize(Writer& writer) const;
    uint64_t hash() const;
    void update(SipHash& hash) const;
};

template<MyTypeCheck T>
bool operator==(const T &a, const T& b) {
    auto hash_a = a.hash();
    auto hash_b = b.hash();
    return hash_a == hash_b;
    // std::cout << "hash_a = " << hash_a << std::endl;
    // std::cout << "hash_b = " << hash_b << std::endl;
    // auto json_a = serialize::dump_json(a);
    // std::cout << "json_a : " << json_a << std::endl;
    // auto json_b = serialize::dump_json(b);
    // std::cout << "json_b : " << json_b << std::endl;
    // assert(json_a == json_b);

    // return json_a == json_b;
}

