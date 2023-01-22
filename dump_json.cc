#include "dump_json.hh"
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <types.hh>

namespace my_json {

template <>
std::string dump_json<std::string>(const std::string &s) {
    std::string ret = "s:" + s;
    return ret;
}

template <>
std::string dump_json<Singer>(const Singer &singer) {
    std::string ret;
    std::stringstream ss;
    ss << "{\n\"type\":\"" << singer.type << "\",";
    ss << "\n\"age\":" << singer.age;
    ss << "\n}";
    ret = ss.str();
    return ret;
}

template <>
std::string dump_json<Address>(const Address &addr) {
    std::string ret;
    std::stringstream ss;
    ss << "{\n\"country\":\"" << addr.country << "\",";
    ss << "\n\"city\":\"" << addr.city << "\",";
    ss << "\n\"street\":\"" << addr.street << "\",";
    ss << "\n\"neighbors\":[";
    int size = addr.neighbors.size();
    for (int i = 0; i < size; i++) {
        auto &neighbor = addr.neighbors[i];
        ss << dump_json(neighbor);
        if (i < size - 1) {
            ss << ",";
        }
    }
    ss << "]";
    ss << "\n}";

    ret = ss.str();
    return ret;
}

template <>
std::string dump_json<Friend>(const Friend &f) {
    std::string ret;
    std::stringstream ss;
    ss << "{\n\"relation\":\"" << f.relation << "\",";
    ss << "\n\"secret\":" << dump_json(f.secret) << "";
    ss << "\n}";
    ret = ss.str();
    return ret;
}

template <>
std::string dump_json<Person>(const Person &p) {
    std::string ret;
    std::stringstream ss;
    ss << "{\n\"name\":\"" << p.name << "\",";
    ss << "\n\"age\":" << std::to_string(p.age) << ",";
    ss << "\n\"address\":" << dump_json(p.address) << ",";
    ss << "\n\"friends\": [";
    int size = p.friends.size();
    for (int i = 0; i < size; i++) {
        auto &f = p.friends[i];
        ss << dump_json(f);
        if (i < size - 1) {
            ss << ",";
        }
    }
    ss << "],";
    ss << "\n\"secret\":" << dump_json(p.secret);
    ss << "\n}";

    ret = ss.str();
    return ret;
}

template <>
std::string dump_json<my_traits::Any>(const my_traits::Any& any) {
    std::string ret;
    ret += "{\n";
    const std::string &tn = any.get_typename();
    if (tn == "i") {
        auto &value = any.get<int>();
        ret += "\"int\":";
        ret += std::to_string(value);
    } else if (tn == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
        auto &value = any.get<std::string>();
        ret += "\"string\":\"";
        ret += value + "\"";
    } else if (tn == "") {
        // empty type
    } else if (tn == "6Singer") {
        auto &value = any.get<Singer>();
        ret += "\"Singer\":";
        ret += dump_json(value);
    } else if (tn == "PKc") {
        auto &value = any.get<const char *>();
        ret += "\"string\":\"";
        ret += std::string(value) + "\"";
    } else if (tn == "6Person") {
        auto &value = any.get<Person>();
        ret += "\"Person\":";
        ret += dump_json(value);
    } else if (tn == "7Address") {
        auto &value = any.get<Address>();
        ret += "\"Address\":";
        ret += dump_json(value);
    }
    else {
        throw std::logic_error(std::string("unknow type in class Any: ") + tn);
    }
    return ret + "\n}";
}

} // namespace my_json
