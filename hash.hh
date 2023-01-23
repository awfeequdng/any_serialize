#pragma once
#include "SipHash.hh"
#include "my_traits.hh"

namespace my_hash {

template <typename T>
void update_hash(SipHash &hash, const T& d) {
    throw std::logic_error(std::string("not impl hash for type: ") + typeid(T).name());
}

template <MyTypeCheck T>
void update_hash(SipHash &hash, const T& d) {
    d.update_hash(hash);
}

} // namespace my_hash