#include "types.hh"

// template <typename Writer>
void Address::serialize(Writer& writer) const {
    writer.StartObject();

    writer.String("country");
    writer.String(country.c_str(), static_cast<rapidjson::SizeType>(country.length()));

    writer.String("city");
    writer.String(city.c_str(), static_cast<rapidjson::SizeType>(city.length()));

    writer.String("street");
    writer.String(street.c_str(), static_cast<rapidjson::SizeType>(street.length()));

    writer.String("neighbors");
    writer.StartArray();
    for (auto &person : neighbors)
        person.serialize(writer);
    writer.EndArray();

    writer.EndObject();
}

    // std::string name;
    // int age;
    // Address address;
    // std::vector<Friend> friends;
    // my_traits::Any secret;

// template <typename Writer>
void Person::serialize(Writer& writer) const {
    writer.StartObject();

    writer.String("name");
    writer.String(name.c_str(), static_cast<rapidjson::SizeType>(name.length()));

    writer.String("age");
    writer.Int(age);

    writer.String("address");
    address.serialize(writer);

    writer.String("friends");
    writer.StartArray();
    for (auto &f : friends)
        f.serialize(writer);
    writer.EndArray();

    writer.String("secret");
    secret.serialize(writer);

    writer.EndObject();
}

    // std::string relation;
    // my_traits::Any secret;
// template <typename Writer>
void Friend::serialize(Writer& writer) const {
   writer.StartObject();

    writer.String("relation");
    writer.String(relation.c_str(), static_cast<rapidjson::SizeType>(relation.length()));

    writer.String("secret");
    secret.serialize(writer);

    writer.EndObject();
}

    // std::string type;
    // int age;
// template <typename Writer>
void Singer::serialize(Writer& writer) const {
    writer.StartObject();

    writer.String("type");
    writer.String(type.c_str(), static_cast<rapidjson::SizeType>(type.length()));

    writer.String("age");
    writer.Int(age);

    writer.EndObject();
}

