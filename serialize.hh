
#pragma once

#include <ostream>
#include <stdexcept>
#include <iostream>
#include <type_traits>

#include "my_traits.hh"
#include "types.hh"

namespace serialize {

template <MyTypeCheck T>
std::string dump_json(const T& t) {
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    t.serialize(writer);
    return sb.GetString();
}

} // namespace serialize


template<MyTypeCheck T>
// requires std::is_same<T, Person>::value || std::is_same<T, Address>::value || std::is_same<T, Friend>::value || std::is_same<T, Singer>::value
std::ostream& operator << (std::ostream &out, const T &p) {
    out << serialize::dump_json(p);
    return out;
}