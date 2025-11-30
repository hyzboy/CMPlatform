#pragma once

#include <hgl/type/DataType.h>

namespace hgl
 {
    /**
     * ARM处理器特性标志
     */
    struct CpuFeatures
    {
        // 基本信息
        char implementer[3];           ///< 实现商 (2字节 + null终止符)
        uint32 part_number;            ///< 部件号
        uint32 variant;                ///< 变体
        uint32 revision;               ///< 修订版

        // 指令集支持
        bool has_neon     : 1;         ///< 支持NEON
        bool has_vfp      : 1;         ///< 支持VFP
        bool has_vfpv3    : 1;         ///< 支持VFPv3
        bool has_vfpv4    : 1;         ///< 支持VFPv4
        bool has_aes      : 1;         ///< 支持AES
        bool has_sha1     : 1;         ///< 支持SHA1
        bool has_sha2     : 1;         ///< 支持SHA2
        bool has_crc32    : 1;         ///< 支持CRC32
        bool has_pmull    : 1;         ///< 支持PMULL
        bool has_fp16     : 1;         ///< 支持半精度浮点
        bool has_dotprod  : 1;         ///< 支持点积指令
        bool has_i8mm     : 1;         ///< 支持8-bit整数矩阵乘法
        bool has_bf16     : 1;         ///< 支持BF16
        bool has_sve      : 1;         ///< 支持SVE (Scalable Vector Extension)

        // 大小核信息
        bool has_big_little : 1;       ///< 是否为大小核架构
        uint32 big_core_count;         ///< 大核数量
        uint32 little_core_count;      ///< 小核数量
        uint32 big_core_max_freq;      ///< 大核最大频率(MHz)
        uint32 little_core_max_freq;   ///< 小核最大频率(MHz)

        // 缓存信息 (每个核簇可能不同)
        uint32 l1_data_cache_size;     ///< L1数据缓存大小(KB)
        uint32 l1_inst_cache_size;     ///< L1指令缓存大小(KB)
        uint32 l2_cache_size;          ///< L2缓存大小(KB)
        uint32 l3_cache_size;          ///< L3缓存大小(KB)
    };
} // namespace hgl
