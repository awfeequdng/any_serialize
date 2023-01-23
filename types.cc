#include "types.hh"
#include "SipHash.hh"

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

uint64_t Address::hash() const {
    SipHash hash;
    update(hash);
    return hash.get64();
}

void Address::update(SipHash& hash) const {
    hash.update(country);
    hash.update(city);
    hash.update(street);
    for (auto &neighbor : neighbors) {
        neighbor.update(hash);
    }
}

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

uint64_t Person::hash() const {
    SipHash hash;
    update(hash);
    return hash.get64();
}

void Person::update(SipHash& hash) const {
    hash.update(name);
    hash.update(age);
    address.update(hash);
    for (auto &f : friends) {
        f.update(hash);
    }
    secret.update(hash);
}

// template <typename Writer>
void Friend::serialize(Writer& writer) const {
   writer.StartObject();

    writer.String("relation");
    writer.String(relation.c_str(), static_cast<rapidjson::SizeType>(relation.length()));

    writer.String("secret");
    secret.serialize(writer);

    writer.EndObject();
}
uint64_t Friend::hash() const {
    SipHash hash;
    update(hash);
    return hash.get64();
}

void Friend::update(SipHash& hash) const {
    hash.update(relation);
    secret.update(hash);
}

// template <typename Writer>
void Singer::serialize(Writer& writer) const {
    writer.StartObject();

    writer.String("type");
    writer.String(type.c_str(), static_cast<rapidjson::SizeType>(type.length()));

    writer.String("age");
    writer.Int(age);

    writer.EndObject();
}

uint64_t Singer::hash() const {
    SipHash hash;
    update(hash);
    return hash.get64();
}

void Singer::update(SipHash& hash) const {
    hash.update(type);
    hash.update(age);
}