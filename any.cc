#include "any.hh"
#include "types.hh"
#include <cstring>
#include "serialize.hh"

namespace my_traits {

void Any::serialize(Writer& writer) const {
    if (wrapper_) {
        wrapper_->serialize(writer);
    } else {
        writer.Null();
    }
}

uint64_t Any::hash() const {
    SipHash hash;
    update(hash);
    return hash.get64();
}

void Any::update(SipHash& hash) const {
    auto &tn = typename_;
    if (tn == "i") {
        auto &value = get<int>();
        hash.update(value);
    } else if (tn == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
        auto &value = get<std::string>();
        hash.update(value);
    } else if (tn == "") {
    } else if (tn == "6Singer") {
        auto &value = get<Singer>();
        value.update(hash);
    }
    // else if (tn == "PKc") {
    //     auto &value = get<const char *>();
    //     hash.update(value);
    // }
    else if (tn == "6Person") {
        auto &value = get<Person>();
        value.update(hash);
    } else if (tn == "7Address") {
        auto &value = get<Address>();
        value.update(hash);
    }
    else {
        throw std::logic_error(std::string("unknow type in class Any: ") + tn);
    }
}

} // namespace my_traits