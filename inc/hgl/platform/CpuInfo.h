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

    /**
     * X86处理器特性标志
     */
    struct CpuX86Features
    {
        // 基本信息
        char vendor[13];               ///< CPU厂商字符串 (12字节 + null终止符)
        char brand[49];                ///< CPU品牌字符串 (48字节 + null终止符)
        uint32 family;                 ///< CPU家族
        uint32 model;                  ///< CPU型号
        uint32 stepping;               ///< CPU步进

        // 指令集支持
        bool has_mmx      : 1;         ///< 支持MMX
        bool has_sse      : 1;         ///< 支持SSE
        bool has_sse2     : 1;         ///< 支持SSE2
        bool has_sse3     : 1;         ///< 支持SSE3
        bool has_ssse3    : 1;         ///< 支持SSSE3
        bool has_sse4_1   : 1;         ///< 支持SSE4.1
        bool has_sse4_2   : 1;         ///< 支持SSE4.2
        bool has_avx      : 1;         ///< 支持AVX
        bool has_avx2     : 1;         ///< 支持AVX2
        bool has_avx512_f : 1;         ///< 支持AVX-512 Foundation
        bool has_avx512_dq: 1;         ///< 支持AVX-512 Doubleword and Quadword
        bool has_avx512_ifma: 1;       ///< 支持AVX-512 Integer FMA
        bool has_avx512_pf: 1;         ///< 支持AVX-512 Prefetch
        bool has_avx512_er: 1;         ///< 支持AVX-512 Exponential and Reciprocal
        bool has_avx512_cd: 1;         ///< 支持AVX-512 Conflict Detection
        bool has_avx512_bw: 1;         ///< 支持AVX-512 Byte and Word
        bool has_avx512_vl: 1;         ///< 支持AVX-512 Vector Length

        // 其他特性
        bool has_fma3     : 1;         ///< 支持FMA3
        bool has_fma4     : 1;         ///< 支持FMA4
        bool has_aes      : 1;         ///< 支持AES
        bool has_sha      : 1;         ///< 支持SHA
        bool has_pclmulqdq: 1;         ///< 支持PCLMULQDQ
        bool has_rdrand   : 1;         ///< 支持RDRAND
        bool has_rdseed   : 1;         ///< 支持RDSEED
        bool has_adx      : 1;         ///< 支持ADX
        bool has_bmi1     : 1;         ///< 支持BMI1
        bool has_bmi2     : 1;         ///< 支持BMI2
        bool has_popcnt   : 1;         ///< 支持POPCNT
        bool has_lzcnt    : 1;         ///< 支持LZCNT
        bool has_prefetchw: 1;         ///< 支持PREFETCHW

        // 缓存信息
        uint32 l1_data_cache_size;     ///< L1数据缓存大小(KB)
        uint32 l1_inst_cache_size;     ///< L1指令缓存大小(KB)
        uint32 l2_cache_size;          ///< L2缓存大小(KB)
        uint32 l3_cache_size;          ///< L3缓存大小(KB)

        // 频率信息
        uint32 base_frequency;         ///< 基础频率(MHz)
        uint32 max_frequency;          ///< 最大频率(MHz)
        uint32 bus_frequency;          ///< 总线频率(MHz)
    };//struct CpuX86Features

    struct CpuInfo
    {
        uint cpu_count;             ///<处理器数量
        uint core_count;            ///<处理器核心数量
        uint logical_core_count;    ///<逻辑处理器核心数量

        CpuArch arch;               ///<处理器架构

        union
        {
            CpuX86Features x86;     ///< X86处理器特性 (当arch为x86_64时有效)
            // 可以在这里添加其他架构的特性结构
            // ARMFeatures arm;      ///< ARM处理器特性 (当arch为ARMv8/ARMv9时有效)
        };
    };//struct CpuInfo

    /**
     * 取得CPU信息
     */
    bool GetCpuInfo(CpuInfo *);
}//namespace hgl
