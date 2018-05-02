//
// rm.h
//
//   Record Manager component interface
//
// This file does not include the interface for the RID class.  This is
// found in rm_rid.h
//

#ifndef RM_H
#define RM_H

// Please DO NOT include any files other than redbase.h and pf.h in this
// file.  When you submit your code, the test program will be compiled
// with your rm.h and your redbase.h, along with the standard pf.h that
// was given to you.  Your rm.h, your redbase.h, and the standard pf.h
// should therefore be self-contained (i.e., should not depend upon
// declarations in any other file).

// Do not change the following includes
#include "redbase.h"
#include "rm_rid.h"
#include "pf.h"
#include <cstdio>
#include <cstring>

#define INVALID_SLOT 0

//
// RM_Record: RM Record interface
//
class RM_Record {
public:
    RM_Record ();
    RM_Record (char* pData, RID &rid);
    ~RM_Record();

    // Return the data corresponding to the record.  Sets *pData to the
    // record contents.
    RC GetData(char *&pData) const;

    // Return the RID associated with the record
    RC GetRid (RID &rid) const;

    // set the record data
    RC SetData(const char *pData, size_t size);

    // set the rid
    RC SetRid(const RID &rid);

private:
    char* pData;
    RID rid;
};

// a flag whether opened by rm manager
#define INVALID_OPEN_STATUS false

//
// RM_FileHandle: RM File interface
//
class RM_FileHandle {
public:
    RM_FileHandle ();
    ~RM_FileHandle();

    // Given a RID, return the record
    RC GetRec     (const RID &rid, RM_Record &rec) const;

    RC InsertRec  (const char *pData, RID &rid);       // Insert a new record

    RC DeleteRec  (const RID &rid);                    // Delete a record
    RC UpdateRec  (const RM_Record &rec);              // Update a record

    // Forces a page (along with any contents stored in this class)
    // from the buffer pool to disk.  Default value forces all pages.
    RC ForcePages (PageNum pageNum = ALL_PAGES);

private:
    PF_FileHandle &pfFileHandle;

    size_t recordSize; // the fixed size of a record
    size_t recordsPerPage; // the number of records per pages
    size_t recordCount; // total records
    size_t pageHdrSize; // the size of page header
    
    bool openStatus; // the status of file to decalre if opened

    RC FindRec(
        const RID& rid, // The given rid
        PageNum &pageNum, // the pageNum in rid
        SlotNum& slot, // the slotNum in rid
        PF_PageHandle &pfPageHandle, // the pageHandle of the page with rec
        char *& data // the data in the pageHandle
    ) const;
};

//
// RM_FileScan: condition-based scan of records in the file
//
class RM_FileScan {
public:
    RM_FileScan  ();
    ~RM_FileScan ();

    RC OpenScan  (const RM_FileHandle &fileHandle,
                  AttrType   attrType,
                  int        attrLength,
                  int        attrOffset,
                  CompOp     compOp,
                  void       *value,
                  ClientHint pinHint = NO_HINT); // Initialize a file scan
    RC GetNextRec(RM_Record &rec);               // Get next matching record
    RC CloseScan ();                             // Close the scan
};

//
// RM_Manager: provides RM file management
//
class RM_Manager {
public:
    RM_Manager    (PF_Manager &pfm);
    ~RM_Manager   ();

    RC CreateFile (const char *fileName, int recordSize);
    RC DestroyFile(const char *fileName);
    RC OpenFile   (const char *fileName, RM_FileHandle &fileHandle);

    RC CloseFile  (RM_FileHandle &fileHandle);
private:
    PF_Manager pfManager;
};

//
// Print-error function
//
void RM_PrintError(RC rc);

#define RM_FILENOTOPEND     (START_RM_WARN + 0) // the file handle doesn't refer a file
#define RM_INVALIDRID      (START_RM_WARN + 1) // invalid rid

#define PF_PAGEPINNED      (START_RM_ERR + 0) // page pinned in buffer

#endif
