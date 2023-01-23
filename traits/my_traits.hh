#pragma once

struct Person;
struct Address;
struct Friend;
struct Singer;

template<typename T>
concept MyTypeCheck = std::is_same<T, Person>::value || std::is_same<T, Address>::value || std::is_same<T, Friend>::value || std::is_same<T, Singer>::value;

template<typename T>
concept MySerializeType = std::is_same<T, Person>::value ||
                          std::is_same<T, Address>::value ||
                          std::is_same<T, Friend>::value ||
                          std::is_same<T, Singer>::value; // ||
                        //   std::is_same<T, std::string>::value ||
                        //   std::is_same<T, int>::value;

