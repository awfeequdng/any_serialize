
#pragma once

#include <ostream>
#include <stdexcept>
#include <iostream>
#include <type_traits>

#include "types.hh"

namespace my_json {

template <typename T>
std::string dump_json(const T& t) {
    throw std::logic_error(std::string("dump_json type failed: invalid type: ") +
                               typeid(T).name());
}

template <>
std::string dump_json<my_traits::Any>(const my_traits::Any& any);

template <>
std::string dump_json<Person>(const Person &p);

template <>
std::string dump_json<Friend>(const Friend &f);

template <>
std::string dump_json<Address>(const Address &addr);

// std::ostream &operator << (std::ostream &out, const Person &p);
// std::ostream &operator << (std::ostream &out, const Friend &p);
// std::ostream &operator << (std::ostream &out, const Address &p);
// std::ostream &operator << (std::ostream &out, const Singer &p);

} // namespace my_json

template<typename T>
requires std::is_same<T, Person>::value || std::is_same<T, Address>::value || std::is_same<T, Friend>::value || std::is_same<T, Singer>::value
std::ostream& operator << (std::ostream &out, const T &p) {
    out << my_json::dump_json(p);
    return out;
}