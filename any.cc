#include "any.hh"
#include "types.hh"
#include <cstring>

using namespace my_traits;

// template <typename Writer>
void Any::serialize(Writer& writer) const {
    auto &tn = typename_;
    if (tn == "i") {
        auto &value = get<int>();
        writer.Int(value);
    } else if (tn == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
        auto &value = get<std::string>();
        writer.String(value.c_str(), static_cast<rapidjson::SizeType>(value.length()));
    } else if (tn == "") {
        writer.Null();
    } else if (tn == "6Singer") {
        auto &value = get<Singer>();
        value.serialize(writer);
    } else if (tn == "PKc") {
        auto &value = get<const char *>();
        writer.String(value, static_cast<rapidjson::SizeType>(strlen(value)));
    } else if (tn == "6Person") {
        auto &value = get<Person>();
        value.serialize(writer);
    } else if (tn == "7Address") {
        auto &value = get<Address>();
        value.serialize(writer);
    }
    else {
        throw std::logic_error(std::string("unknow type in class Any: ") + tn);
    }
}

// // template <typename Writer>
// void Any::serialize(Writer& writer) const {
//     auto &tn = typename_;
//     // writer.StartObject();
//     if (tn == "i") {
//         auto &value = get<int>();
//         // writer.String("int");
//         writer.Int(value);
//     } else if (tn == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
//         auto &value = get<std::string>();
//         // writer.String("string");
//         writer.String(value.c_str(), static_cast<rapidjson::SizeType>(value.length()));
//     } else if (tn == "") {
//         writer.Null();
//     } else if (tn == "6Singer") {
//         auto &value = get<Singer>();
//         // writer.String("Singer");
//         value.serialize(writer);
//     } else if (tn == "PKc") {
//         auto &value = get<const char *>();
//         // writer.String("string");
//         writer.String(value, static_cast<rapidjson::SizeType>(strlen(value)));
//     } else if (tn == "6Person") {
//         auto &value = get<Person>();
//         // writer.String("Person");
//         value.serialize(writer);
//     } else if (tn == "7Address") {
//         auto &value = get<Address>();
//         // writer.String("Address");
//         value.serialize(writer);
//     }
//     else {
//         throw std::logic_error(std::string("unknow type in class Any: ") + tn);
//     }
//     // writer.EndObject();
// }