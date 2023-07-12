#pragma once

#include<hgl/TypeFunc.h>

namespace hgl
{
    enum class SOCVendor
    {
        Unknow=0,

        Qualcomm,       ///<高通
        Hisilicon,      ///<海思
        Samsung,        ///<三星
        MediaTek,       ///<联发科
        //Rockchip,       ///<瑞芯微
        //Intel,          ///<英特尔
        Unisoc,         ///<展锐
        Spreadtrum,     ///<展讯
        JLQ,            ///<瓴盛
        //TI,             ///<德州仪器

        ENUM_CLASS_RANGE(Unknow,JLQ)
    };

    struct SOCInfo
    {
        SOCVendor       vendor;
        char            model[16];
    };

    /**
     * 根据收集到的SOC信息，解晰具体的SOC厂商和主要型号
     */
    bool ParseSOCInfo(SOCInfo &,const char *);
}//namespace hgl
