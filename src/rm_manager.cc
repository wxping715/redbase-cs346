#include "rm.h"

RM_Manager::RM_Manager(PF_Manager &pfm)
{
    this->pfManager = pfm; 
}

~RM_Manager::RM_Manager()
{

}

RC RM_Manager::CreateFile(const char *fileName, int recordSize)
{

}

RC RM_Manager::Destroy(const char *fileName)
{
    RC rc = this->pfManager->DestroyFile(fileName);
    return rc;
}

RC RM_Manager::OpenFile(const char *fileName, RM_FileHandle &fileHandle)
{
    
}

RC RM_Manager::CloseFile(RM_FileHandle &fileHandle)
{
    RC rc = this->pfManager->CloseFile(fileHandle);
    return rc;
}