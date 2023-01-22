#pragma once
#include <vector>
#include <string>

#include "any.hh"

struct Person;
struct Singer {
    std::string type;
    int age;
};
struct Address {
    std::string country;
    std::string city;
    std::string street;
    std::vector<Person> neighbors;
};

struct Friend {
    std::string relation;
    my_traits::Any secret;
};
struct Person {
    std::string name;
    int age;
    Address address;
    std::vector<Friend> friends;
    my_traits::Any secret;
};
