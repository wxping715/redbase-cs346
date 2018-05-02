#include "rm_rid.h"

RID::RID()
{
    this->pageNum = 0;
    this->slotNum = 0;
}

RID::RID(PageNum pageNum, SlotNum slotNum)
{
    this->pageNum = pageNum;
    this->slotNum = slotNum;
}

~RID::RID()
{
    // do nothing
}

RC GetPageNum(PageNum &pageNum) const
{
    pageNum = this->pageNum;
    return 0;
}

RC GetSlotNum(SlotNum &slotNum) const
{
    slotNum = this->pageNum;
    return 0;
}

