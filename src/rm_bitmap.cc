#include "rm_internal.h"
#include <cstring>

RM_Bitmap::RM_Bitmap(const RMByte* bitmap, const unsigned int capacity) {
    unsigned int bytes = (capacity >> 3) + 1;

    this->bitmap = new RMByte[bytes];
    std::memcpy(this->bitmap, bitmap, bytes);
}

RC RM_Bitmap::Get(int pos, bool& ret) const {
    ret = (this->bitmap[pos >> 3] >> (pos & 0x7)) & 1;
    return OK_RC;
}

RC RM_Bitmap::Set(int pos, bool val) {
    if (val) {
        this->bitmap[pos >> 3] |= (1 << (pos & 0x7));
    } else {
        this->bitmap[pos >> 3] &= (1 << (pos & 0x7));
    }
    return OK_RC;
}

RM_Bitmap::~RM_Bitmap() {
    delete[] this->bitmap;
}