#include "rm.h"

#ifndef RM_INTERNAL_H
#define RM_INTERNAL_H

struct RM_PageHdr {
    SlotNum firstFreeSlot;
    RM_Bitmap* bitmap;
};

struct RM_FileHdr {
    RecordNum recordSize;
    RecordNum RecordsPerPage;
};

class RM_Bitmap {
public:
    // build bitmap from a memory block
    // bitmap: the memory block
    // len: the capacity of bitmap
    RM_Bitmap(const RMByte* bitmap, const unsigned int capacity);
    RM_Bitmap(const RM_Bitmap& bitmap) = delete;
    RM_Bitmap operator=(const RM_Bitmap& bitmap) = delete;
    //  get the value from bitmap
    RC Get(int pos, bool& ret) const;
    // set the value in bit map
    RC Set(int pos, bool val);
    ~RM_Bitmap();

private:
    RMByte* bitmap;
};

#endif

1:09:56