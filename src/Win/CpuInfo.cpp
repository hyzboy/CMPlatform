#include<hgl/platform/CpuInfo.h>
#include<hgl/type/StrChar.h>
#include<sysinfoapi.h>
#include<string.h>
#include<iostream>

namespace hgl
{
    namespace
    {
        DWORD CountSetBits(ULONG_PTR bitMask)
        {
            DWORD LSHIFT = sizeof(ULONG_PTR)*8 - 1;
            DWORD bitSetCount = 0;
            ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;    
            DWORD i;
    
            for (i = 0; i <= LSHIFT; ++i)
            {
                bitSetCount += ((bitMask & bitTest)?1:0);
                bitTest/=2;
            }
 
            return bitSetCount;
        }
    }//namespace

    bool GetCpuInfo(CpuInfo *ci)
    {
        if(!ci)return(false);

        AutoFree<SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX> buf;
        DWORD length=0;

        GetLogicalProcessorInformationEx(RelationAll,nullptr,&length);

        if(GetLastError()!=ERROR_INSUFFICIENT_BUFFER)
            return(false);

        buf=(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *)malloc(length);

        if(!GetLogicalProcessorInformationEx(RelationAll,buf,&length))
            return(false);

        char *sp=(char *)(buf.data());
        SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *p;

        memset(ci,0,sizeof(CpuInfo));

        while(length>0)
        {
            p=(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *)sp;
            
            if(p->Relationship==RelationProcessorPackage)
                ++ci->cpu_count;
            else
            if(p->Relationship==RelationProcessorCore)
            {
                ++ci->core_count;

                ci->logical_core_count+=CountSetBits(p->Processor.GroupMask[0].Mask);
            }

            sp+=p->Size;
            length-=p->Size;
        }

        return(true);
    }
}//namespace hgl
