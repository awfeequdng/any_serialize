#pragma once

#include <exception>
#include <memory>
#include <cxxabi.h>
#include <stdexcept>
#include <iostream>

#include "hash/hash.hh"
#include "serialize/serialize.hh"

namespace my_traits {

class Any;

class WrapperBase {
public:
    virtual std::unique_ptr<WrapperBase> clone() = 0;
    virtual void serialize(Writer &writer) = 0;
    virtual void update_hash(SipHash &hash) = 0;
    virtual ~WrapperBase() {}
};

template<typename T>
class Wrapper : public WrapperBase {
public:
    Wrapper(T d) : data_(d) {}

    std::unique_ptr<WrapperBase> clone() override {
        return std::make_unique<Wrapper<T>>(data_);
    }
    void serialize(Writer &writer) override {
        serialize::serialize(writer, data_);
    }

    void update_hash(SipHash &hash) override {
        my_hash::update_hash(hash, data_);
    }
private:
    friend class Any;
    T data_;
};

class Any {
public:
    Any() {}

    inline void assign(const Any& any) {
        typename_ = any.typename_;
        if (any.wrapper_) {
            wrapper_ = any.wrapper_.get()->clone();
        }
    }
    Any(const Any &any) {
        assign(any);
    }

    Any& operator=(const Any &any) {
        assign(any);
        return *this;
    }

    template <typename T>
    Any(T d) {
        set(d);
    }

    template <typename T>
    requires std::is_same<T, const char *>::value
    void set(T d) {
        auto tn = typeid(std::string).name();
        typename_ = tn;
        // int status;
        // typename_ = abi::__cxa_demangle(tn, nullptr, nullptr, &status);
        wrapper_ = std::make_unique<Wrapper<std::string>>(std::string(d));
    }

    template<typename T>
    void set(T d) {
        auto tn = typeid(T).name();
        typename_ = tn;
        wrapper_ = std::make_unique<Wrapper<T>>(d);
    }

    template <typename T>
    const T& get() const {
        auto p = dynamic_cast<Wrapper<T>*>(wrapper_.get());
        if (p) {
            return p->data_;
        } else {
            throw std::logic_error(std::string("get value failed: invalid type: ") + typeid(T).name());
        }
    }

    const std::string& get_typename() const {
        return typename_;
    }

    void serialize(Writer& writer) const;
    uint64_t hash() const;
    void update_hash(SipHash& hash) const;

private:
    std::unique_ptr<WrapperBase> wrapper_;
    std::string typename_;
};

}
