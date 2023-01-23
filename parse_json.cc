#include "parse_json.hh"
#include <rapidjson/encodings.h>
#include <stdexcept>
#include <vector>
namespace serialize {

template <>
Person parse_json<Person>(std::string json) {
    rapidjson::Document doc;
    doc.Parse(json.c_str());
    return parse<Person>(doc);
}

template<>
Address parse<Address>(rapidjson::GenericValue<rapidjson::UTF8<>> &value) {
    Address addr;
    addr.country = value["country"].GetString();
    addr.city = value["city"].GetString();
    addr.street = value["street"].GetString();
    addr.neighbors = parse<std::vector<Person>>(value["neighbors"]);
    return addr;
}

template<>
Person parse<Person>(rapidjson::GenericValue<rapidjson::UTF8<>> &value) {
    Person person;
    person.name = value["name"].GetString();
    person.age = value["age"].GetInt();
    person.address = parse<Address>(value["address"]);
    person.friends = parse<std::vector<Friend>>(value["friends"]);
    person.secret = parse<my_traits::Any>(value["secret"]);
    return person;
}

template<>
std::vector<Person> parse<std::vector<Person>>(rapidjson::GenericValue<rapidjson::UTF8<>> &value) {
    std::vector<Person> persons;
    for (int i = 0; i < value.Size(); i++) {
        auto p = parse<Person>(value[i]);
        persons.push_back(p);
    }
    return persons;
}

template<>
Friend parse<Friend>(rapidjson::GenericValue<rapidjson::UTF8<>> &value) {
    Friend f;
    f.relation = value["relation"].GetString();
    f.secret = parse<my_traits::Any>(value["secret"]);
    return f;
}

template<>
std::vector<Friend> parse<std::vector<Friend>>(rapidjson::GenericValue<rapidjson::UTF8<>> &value) {
    std::vector<Friend> friends;
    for (int i = 0; i < value.Size(); i++) {
        auto f = parse<Friend>(value[i]);
        friends.push_back(f);
    }
    return friends;
}

template<>
my_traits::Any parse<my_traits::Any>(rapidjson::GenericValue<rapidjson::UTF8<>> &value) {
    my_traits::Any any;
    if (value.IsString()) {
        any.set(value.GetString());
    } else if (value.IsInt()) {
        any.set(value.GetInt());
    } else if (value.IsObject()) {
        any.set(parse<Singer>(value));
    } else if (value.IsNull()) {
    } else {
        throw std::logic_error("not supported any type");
    }

    // if (value.HasMember("string")) {
    //     any.set(value["string"].GetString());
    // } else if (value.HasMember("int")) {
    //     any.set(value["int"].GetInt());
    // } else if (value.HasMember("Singer")) {
    //     any.set(parse<Singer>(value["Singer"]));
    // } else {
    //     throw std::logic_error("not supported any type");
    // }
    return any;
}
template<>
Singer parse<Singer>(rapidjson::GenericValue<rapidjson::UTF8<>> &value) {
    Singer singer;
    singer.age = value["age"].GetInt();
    singer.type = value["type"].GetString();
    return singer;
}

template <>
Person parse<Person>(rapidjson::Document &doc) {
    Person p;
    p.name = doc["name"].GetString();
    p.age = doc["age"].GetInt();
    p.address = parse<Address>(doc["address"]);
    p.friends = parse<std::vector<Friend>>(doc["friends"]);
    p.secret = parse<my_traits::Any>(doc["secret"]);
    return p;
}

} // namespace serialize
