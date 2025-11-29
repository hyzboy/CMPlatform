#pragma once

#include<hgl/type/DataType.h>
namespace hgl
{
    enum class CpuArch
    {
        x86_64,
    
        ARMv8,      //32+64
        ARMv9,      //64
    };//

    struct CpuInfo
    {
        uint cpu_count;             ///<处理器数量
        uint core_count;            ///<处理器核心数量
        uint logical_core_count;    ///<逻辑处理器核心数量
    };//struct CpuInfo

    /**
     * 取得CPU信息
     */
    bool GetCpuInfo(CpuInfo *);
}//namespace hgl
