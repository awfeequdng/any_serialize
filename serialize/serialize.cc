#include <rapidjson/rapidjson.h>
#include "serialize/serialize.hh"

namespace serialize {

template <>
void serialize<int>(Writer& writer, const int &d) {
    writer.Int(d);
}

template <>
void serialize<std::string>(Writer& writer, const std::string &d) {
    writer.String(d.c_str(), static_cast<rapidjson::SizeType>(d.length()));
}


}