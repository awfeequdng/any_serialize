#include "types.hh"

namespace my_json {


template <typename T>
T parse_json(std::string json) {
    throw std::logic_error(std::string("parse_json type failed: invalid type: ") +
                               typeid(T).name());
}

} // namespace my_json