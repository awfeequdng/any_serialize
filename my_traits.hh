#pragma once
// #include "types.hh"

struct Person;
struct Address;
struct Friend;
struct Singer;

template<typename T>
concept MyTypeCheck = std::is_same<T, Person>::value || std::is_same<T, Address>::value || std::is_same<T, Friend>::value || std::is_same<T, Singer>::value;

