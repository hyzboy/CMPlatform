﻿#include<hgl/platform/ExternalModule.h>
#include<hgl/platform/Platform.h>
#include<hgl/log/LogInfo.h>

namespace hgl
{
    ExternalModule *LoadExternalModule(const os_char *filename)
    {
        ExternalModulePointer fp=LoadLibraryW(filename);

        if(!fp)
        {
            uint dw=GetLastError();
            os_char *str=nullptr;

            FormatMessageW( FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,nullptr,dw,
                            MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),str,0,nullptr);

            LOG_ERROR(OS_TEXT("LoadModule <")+OSString(filename)+OS_TEXT("> error! os info: ")+OSString::numberOf(dw)+OSString::charOf(',')+str);

            return(nullptr);
        }

        return(new ExternalModule(fp));
    }

    /**
    * 加载一个外部模块
    * @param name 模块文件名称
    * @return 是否加载成功
    */
    bool ExternalModule::Load(const os_char *name)
    {
        Clear();

        fp=LoadLibraryW(name);

        if(!fp)
        {
            const uint dw=GetLastError();
            u16char *str=nullptr;

            FormatMessageW( FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,nullptr,dw,
                            MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),str,0,nullptr);

            LOG_ERROR(L"LoadModule <"+UTF16String(name)+L"> error! os info: "+UTF16String::numberOf(dw)+UTF16String::charOf(L',')+str);

            return(false);
        }

        return(true);
    }
}//namespace hgl

