#pragma once

struct Person;
struct Address;
struct Friend;
struct Singer;

template<typename T>
concept MyTypeCheck = std::is_same_v<T, Person> ||
                      std::is_same_v<T, Address> ||
                      std::is_same_v<T, Friend> ||
                      std::is_same_v<T, Singer>;

// template<typename T>
// concept MySerializeType = std::is_same_v<T, Person> ||
//                           std::is_same_v<T, Address> ||
//                           std::is_same_v<T, Friend> ||
//                           std::is_same_v<T, Singer>;

