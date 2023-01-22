#include "types.hh"
#include "rapidjson/document.h"

namespace my_json {

template <typename T>
T parse_json(std::string json) {
    throw std::logic_error(std::string("parse_json type failed: invalid type: ") +
                               typeid(T).name());
}
template <>
Person parse_json<Person>(std::string json);

template <typename T>
T parse(rapidjson::Document &doc) {
    throw std::logic_error(std::string("parse rapidjson::Document type failed: invalid type: ") +
                               typeid(T).name());
}
template <>
Person parse<Person>(rapidjson::Document &doc);


template<typename T>
T parse(rapidjson::GenericValue<rapidjson::UTF8<>> &value) {
    throw std::logic_error(std::string("parse rapidjson::GenericValue type failed: invalid type: ") +
                               typeid(T).name());
}
template<>
Singer parse<Singer>(rapidjson::GenericValue<rapidjson::UTF8<>> &value);
template<>
Address parse<Address>(rapidjson::GenericValue<rapidjson::UTF8<>> &value);
template<>
std::vector<Friend> parse<std::vector<Friend>>(rapidjson::GenericValue<rapidjson::UTF8<>> &value);
template<>
Friend parse<Friend>(rapidjson::GenericValue<rapidjson::UTF8<>> &value);
template<>
Person parse<Person>(rapidjson::GenericValue<rapidjson::UTF8<>> &value);
template<>
std::vector<Person> parse<std::vector<Person>>(rapidjson::GenericValue<rapidjson::UTF8<>> &value);
template<>
my_traits::Any parse<my_traits::Any>(rapidjson::GenericValue<rapidjson::UTF8<>> &value);

} // namespace my_json