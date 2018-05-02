#include "rm.h"
#include "rm_internal.h"
#include <cstdio>
#include <cstring>

RM_FileHandle::RM_FileHandle()
{
    recordCount = recordsPerPage = recordSize = 0;
}

RM_FileHandle::~RM_FileHandle()
{

}

RC RM_FileHandle::GetRec(const RID &rid, RM_Record &rec) const {
    PageNum pageNum;
    SlotNum slot;
    PF_PageHandle pfPageHandle;
    char* data;

    CALL(FindRec(rid, pageNum, slot, pfPageHandle, data));
    // the offset of record data
    Offset offset = pageHdrSize + recordSize * slot;

    CALL(rec.SetRid(rid));
    CALL(rec.SetData(data + offset, size_t(recordSize)));
    
    // unpin the page
    CALL(pfFileHandle.UnpinPage(pageNum));
    return OK_RC;
}

RC RM_FileHandle::InsertRec(const char *pData, RID &rid) {
    
}

RC RM_FileHandle::DeleteRec(const RID &rid)
{
    PageNum pageNum;
    SlotNum slot;
    PF_PageHandle pfPageHandle;
    char* data;

    CALL(FindRec(rid, pageNum, slot, pfPageHandle, data));

    size_t offset = pageHdrSize + recordSize * slot;
    
    // covert record slot to size_t
    size_t* curSlot = (size_t *)(data + offset);
    // covert start data to pagehdr
    RM_PageHdr* pageHdr = (RM_PageHdr*)data;

    *curSlot = 
}

RC RM_FileHandle::UpdateRec(const RM_Record &rec)
{
    // check open status
    if (!openStatus) {
        return RM_FILENOTOPEND;
    }

    RID rid;
    CALL(rec.GetRid(rid));
    
    SlotNum slot;
    PageNum pageNum;
    CALL(rid.GetPageNum(pageNum));
    CALL(rid.GetSlotNum(slot));

    if (slot < INVALID_SLOT || slot >= recordsPerPage) {
        return RM_INVALIDRID;
    }

    // find the page
    PF_PageHandle pfPageHandle;
    CALL(FindRec(rid, pfPageHandle));

    char *data, *pData;
    CALL(pfPageHandle.GetData(data));
    CALL(rec.GetData(pData));

    // compute the offset
    int offset = pageHdrSize + recordSize * slot;
    memcpy(data + offset, pData, recordSize);

    // TODO: set bitmap

    CALL(pfFileHandle.MarkDirty(pageNum));
    CALL(pfFileHandle.UnpinPage(pageNum));

    return OK_RC;
} 

RC RM_FileHandle::ForcePages (PageNum pageNum = ALL_PAGES) {

}


RC RM_FileHandle::FindRec(const RID& rid, PageNum &pageNum, 
    SlotNum& slot, PF_PageHandle &pfPageHandle, char *& data) const {

    // ensure the fileHandle is opened correctly
    if (!openStatus) {
        return RM_FILENOTOPEND;
    }

    CALL(rid.GetPageNum(pageNum));
    CALL(rid.GetSlotNum(slot));

    if (slot < INVALID_SLOT || slot < recordsPerPage) {
        return RM_INVALIDRID;
    }

    CALL(pfFileHandle.GetThisPage(pageNum, pfPageHandle));
    CALL(pfPageHandle.GetData(data));

    return OK_RC;
}