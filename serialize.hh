
#pragma once

#include <ostream>
#include <stdexcept>
#include <iostream>
#include <type_traits>

#include "my_traits.hh"
// #include "types.hh"

#include "rapidjson/rapidjson.h"
#include "rapidjson/prettywriter.h"

using Writer = rapidjson::PrettyWriter<rapidjson::StringBuffer>;

namespace serialize {

template <MyTypeCheck T>
std::string dump_json(const T& t) {
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    t.serialize(writer);
    return sb.GetString();
}

template <typename T>
void serialize(Writer& writer, const T &d) {
    throw std::logic_error(std::string("not impl serial type: ") + typeid(T).name());
}

template <MyTypeCheck T>
void serialize(Writer& writer, const T &d) {
    d.serialize(writer);
}

} // namespace serialize

template<MyTypeCheck T>
// requires std::is_same<T, Person>::value || std::is_same<T, Address>::value || std::is_same<T, Friend>::value || std::is_same<T, Singer>::value
std::ostream& operator << (std::ostream &out, const T &p) {
    out << serialize::dump_json(p);
    return out;
}