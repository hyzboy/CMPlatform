#if !defined(_WIN32)
#error "mmap_win.cpp should only be built on Windows"
#endif

#include <hgl/io/MMapFile.h>
#include <windows.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <vector>

namespace hgl
{
    class MMapFileImpl
    {
    public:
        HANDLE hFile=INVALID_HANDLE_VALUE;
        HANDLE hMap=nullptr;
    };

    MMapFile::MMapFile(const OSString &filename,size_t size,bool readOnly)
        : data_(nullptr),size_(size)
    {
        DWORD access=readOnly?GENERIC_READ:(GENERIC_READ|GENERIC_WRITE);
        DWORD protect=readOnly?PAGE_READONLY:PAGE_READWRITE;
        DWORD mapAccess=readOnly?FILE_MAP_READ:FILE_MAP_WRITE;

        MMapFileImpl *impl=new MMapFileImpl();

        impl_=impl;

        impl->hFile=CreateFileW(filename.c_str(),access,0,nullptr,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);

        if(impl->hFile==INVALID_HANDLE_VALUE)
            throw std::runtime_error("Failed to open file");

        LARGE_INTEGER fileSize;

        if(!GetFileSizeEx(impl->hFile,&fileSize)||fileSize.QuadPart<(LONGLONG)size)
        {
            fileSize.QuadPart=size;
            if(!SetFilePointerEx(impl->hFile,fileSize,nullptr,FILE_BEGIN)||!SetEndOfFile(impl->hFile))
                throw std::runtime_error("Failed to set file size");
        }

        impl->hMap=CreateFileMappingW(impl->hFile,nullptr,protect,0,(DWORD)size,nullptr);

        if(!impl->hMap)
            throw std::runtime_error("Failed to create file mapping");

        data_=MapViewOfFile(impl->hMap,mapAccess,0,0,size);

        if(!data_)
            throw std::runtime_error("Failed to map view of file");
    }

    MMapFile::~MMapFile()
    {
        MMapFileImpl *impl=reinterpret_cast<MMapFileImpl *>(impl_);

        if(data_)
            UnmapViewOfFile(data_);

        if(impl)
        {
            if(impl->hMap) CloseHandle(impl->hMap);
            if(impl->hFile!=INVALID_HANDLE_VALUE) CloseHandle(impl->hFile);
            delete impl;
        }
    }

    void *MMapFile::data() { return data_; }
    size_t MMapFile::size() const { return size_; }
}//namespace hgl
