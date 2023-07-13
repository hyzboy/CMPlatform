#pragma once

#include<hgl/TypeFunc.h>
#include<hgl/CompOperator.h>

namespace hgl
{
    enum class SOCVendor
    {
        Unknow=0,

        Qualcomm,       ///<高通
        Hisilicon,      ///<海思
        Samsung,        ///<三星
        MediaTek,       ///<联发科
        Unisoc,         ///<展锐
        Spreadtrum,     ///<展讯
        JLQ,            ///<瓴盛

        //Maxvell,        ///<马维尔
        //Broadcom,       ///<博通
        //TI,             ///<德州仪器
        //Rockchip,       ///<瑞芯微
        //Intel,          ///<英特尔
        //nVidia,         ///<英伟达
        //AMD,            ///<AMD
        //Google,         ///<谷歌

        ENUM_CLASS_RANGE(Unknow,JLQ)
    };

    struct SOCInfo
    {
        SOCVendor       vendor;
        char            model[32];

    public:

        CompOperatorMemcmp(const SOCInfo &);
    };

    /**
     * 根据收集到的SOC信息，解晰具体的SOC厂商和主要型号
     */
    bool ParseSOCInfo(SOCInfo &,const char *);
}//namespace hgl
