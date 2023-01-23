#pragma once

/** SipHash is a fast cryptographic hash function for short strings.
  * Taken from here: https://www.131002.net/siphash/
  *
  * This is SipHash 2-4 variant.
  *
  * Two changes are made:
  * - returns also 128 bits, not only 64;
  * - done streaming (can be calculated in parts).
  *
  * On short strings (URL, search phrases) more than 3 times faster than MD5 from OpenSSL.
  * (~ 700 MB/sec, 15 million strings per second)
  */
#include <iostream>
#include <string.h>
#include <cstdint>
#include <string>
#include <type_traits>

template <typename T>
inline T unalignedLoad(const void * address)
{
    T res {};
    memcpy(&res, address, sizeof(res));
    return res;
}

/// We've had troubles before with wrong store size due to integral promotions
/// (e.g., unalignedStore(dest, uint16_t + uint16_t) stores an uint32_t).
/// To prevent this, make the caller specify the stored type explicitly.
/// To disable deduction of T, wrap the argument type with std::enable_if.
template <typename T>
inline void unalignedStore(void * address,
                           const typename std::enable_if<true, T>::type & src)
{
    static_assert(std::is_trivially_copyable_v<T>);
    memcpy(address, &src, sizeof(src));
}


#define ROTL(x, b) static_cast<uint64_t>(((x) << (b)) | ((x) >> (64 - (b))))

#define SIPROUND                                                  \
    do                                                            \
    {                                                             \
        v0 += v1; v1 = ROTL(v1, 13); v1 ^= v0; v0 = ROTL(v0, 32); \
        v2 += v3; v3 = ROTL(v3, 16); v3 ^= v2;                    \
        v0 += v3; v3 = ROTL(v3, 21); v3 ^= v0;                    \
        v2 += v1; v1 = ROTL(v1, 17); v1 ^= v2; v2 = ROTL(v2, 32); \
    } while(0)


class SipHash
{
private:
    /// State.
    uint64_t v0;
    uint64_t v1;
    uint64_t v2;
    uint64_t v3;

    /// How many bytes have been processed.
    uint64_t cnt;

    /// The current 8 bytes of input data.
    union
    {
        uint64_t current_word;
        uint8_t current_bytes[8];
    };

    inline void finalize()
    {
        /// In the last free byte, we write the remainder of the division by 256.
        current_bytes[7] = cnt;

        v3 ^= current_word;
        SIPROUND;
        SIPROUND;
        v0 ^= current_word;

        v2 ^= 0xff;
        SIPROUND;
        SIPROUND;
        SIPROUND;
        SIPROUND;
    }

public:
    /// Arguments - seed.
    SipHash(uint64_t k0 = 0, uint64_t k1 = 0)
    {
        /// Initialize the state with some random bytes and seed.
        v0 = 0x736f6d6570736575ULL ^ k0;
        v1 = 0x646f72616e646f6dULL ^ k1;
        v2 = 0x6c7967656e657261ULL ^ k0;
        v3 = 0x7465646279746573ULL ^ k1;

        cnt = 0;
        current_word = 0;
    }

    void update(const char * data, uint64_t size)
    {
        const char * end = data + size;

        /// We'll finish to process the remainder of the previous update, if any.
        if (cnt & 7)
        {
            while (cnt & 7 && data < end)
            {
                current_bytes[cnt & 7] = *data;
                ++data;
                ++cnt;
            }

            /// If we still do not have enough bytes to an 8-byte word.
            if (cnt & 7)
                return;

            v3 ^= current_word;
            SIPROUND;
            SIPROUND;
            v0 ^= current_word;
        }

        cnt += end - data;

        while (data + 8 <= end)
        {
            current_word = unalignedLoad<uint64_t>(data);

            v3 ^= current_word;
            SIPROUND;
            SIPROUND;
            v0 ^= current_word;

            data += 8;
        }

        /// Pad the remainder, which is missing up to an 8-byte word.
        current_word = 0;
        switch (end - data)
        {
            case 7: current_bytes[6] = data[6]; [[fallthrough]];
            case 6: current_bytes[5] = data[5]; [[fallthrough]];
            case 5: current_bytes[4] = data[4]; [[fallthrough]];
            case 4: current_bytes[3] = data[3]; [[fallthrough]];
            case 3: current_bytes[2] = data[2]; [[fallthrough]];
            case 2: current_bytes[1] = data[1]; [[fallthrough]];
            case 1: current_bytes[0] = data[0]; [[fallthrough]];
            case 0: break;
        }
    }

    template <typename T>
    void update(const T & x)
    {
        update(reinterpret_cast<const char *>(&x), sizeof(x));
    }

    void update(const std::string & x)
    {
        update(x.data(), x.length());
    }

    /// Get the result in some form. This can only be done once!

    void get128(char * out)
    {
        finalize();
        unalignedStore<uint64_t>(out, v0 ^ v1);
        unalignedStore<uint64_t>(out + 8, v2 ^ v3);
    }

    template <typename T>
    inline void get128(T & lo, T & hi)
    {
        static_assert(sizeof(T) == 8);
        finalize();
        lo = v0 ^ v1;
        hi = v2 ^ v3;
    }

    template <typename T>
    inline void get128(T & dst)
    {
        static_assert(sizeof(T) == 16);
        get128(reinterpret_cast<char *>(&dst));
    }

    uint64_t get64()
    {
        finalize();
        return v0 ^ v1 ^ v2 ^ v3;
    }
};


#undef ROTL
#undef SIPROUND

#include <cstddef>

// inline void sipHash128(const char * data, const size_t size, char * out)
// {
//     SipHash hash;
//     hash.update(data, size);
//     hash.get128(out);
// }

// inline UInt128 sipHash128(const char * data, const size_t size)
// {
//     SipHash hash;
//     hash.update(data, size);
//     UInt128 res;
//     hash.get128(res);
//     return res;
// }

inline uint64_t sipHash64(const char * data, const size_t size)
{
    SipHash hash;
    hash.update(data, size);
    return hash.get64();
}

template <typename T>
uint64_t sipHash64(const T & x)
{
    SipHash hash;
    hash.update(x);
    return hash.get64();
}

inline uint64_t sipHash64(const std::string & s)
{
    return sipHash64(s.data(), s.size());
}
