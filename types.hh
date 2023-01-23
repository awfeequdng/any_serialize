#pragma once
#include <rapidjson/rapidjson.h>
#include <vector>
#include <string>

#include "any.hh"
#include "rapidjson/prettywriter.h"

struct Person;

using Writer = rapidjson::PrettyWriter<rapidjson::StringBuffer>;

struct Singer {
    std::string type;
    int age;

    // template <typename Writer>
    void serialize(Writer& writer) const;
};

struct Address {
    std::string country;
    std::string city;
    std::string street;
    std::vector<Person> neighbors;

    // template <typename Writer>
    void serialize(Writer& writer) const;
};

struct Friend {
    std::string relation;
    my_traits::Any secret;

    // template <typename Writer>
    void serialize(Writer& writer) const;
};
struct Person {
    std::string name;
    int age;
    Address address;
    std::vector<Friend> friends;
    my_traits::Any secret;

    // template <typename Writer>
    void serialize(Writer& writer) const;
};
