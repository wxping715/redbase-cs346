#include "rm.h"
#include <cstring>

RM_Record::RM_Record()
{
    pData = NULL;
}

RM_Record::~RM_Record() 
{
    if (pData != NULL) {
        delete[] pData;
    }
}

RC RM_Record::SetData(const char *data, size_t size) 
{
    // release the memory of original data
    if (pData != NULL) {
        delete[] pData;
    }

    pData = new char[size];
    memcpy(pData, data, size);
}

RC RM_Record::GetData(char *&pData) const
{
    pData = this->pData;
    return 0;
}

RC RM_Record::GetRid(RID &rid) const
{
    rid = this->rid;
    return 0;
}