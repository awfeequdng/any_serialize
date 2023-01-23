#include "hash.hh"

namespace my_hash {

template <>
void update_hash<int>(SipHash &hash, const int &d) {
    hash.update(d);
}

template <>
void update_hash<std::string>(SipHash &hash, const std::string &d) {
    hash.update(d);
}

} // namespace my_hash