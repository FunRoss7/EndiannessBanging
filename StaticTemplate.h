#pragma once

#include <stdint.h>
#include <vector>
#include <algorithm>

#pragma pack(1) // Important so bytes appear in memory as they do in the struct

using ByteVector = std::vector<uint8_t>;

template<typename Fields> union StaticStructure {
    public:
    StaticStructure() = default;
    StaticStructure(const ByteVector& data) {
        #if __ORDER_LITTLE_ENDIAN__
        std::reverse_copy(data.begin(), data.end(), punnedBytes);
        #elif __ORDER_BIG_ENDIAN__
        std::copy(data.begin(), data.end(), punnedBytes);
        #endif
    }
    
    ByteVector encode() const {
        #if __ORDER_LITTLE_ENDIAN__
        return ByteVector(std::make_reverse_iterator(punnedBytes + sizeof(Fields)), 
        std::make_reverse_iterator(punnedBytes));
        #elif __ORDER_BIG_ENDIAN__
        return ByteVector(punnedBytes, punnedBytes + sizeof(Fields));
        #endif
    }

    static ByteVector encode(const StaticStructure& foo) {
        return foo.encode();
    }
    static StaticStructure decode(const ByteVector& foo) {
        return StaticStructure(foo);
    }

    Fields fields;

    private:
    uint8_t punnedBytes[sizeof(Fields)];
};