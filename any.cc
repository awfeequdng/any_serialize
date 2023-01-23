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
    update_hash(hash);
    return hash.get64();
}

void Any::update_hash(SipHash& hash) const {
    if (wrapper_) {
        wrapper_->update_hash(hash);
    }
}

} // namespace my_traits