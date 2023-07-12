#pragma once

namespace hgl
{
    struct AndroidVersion
    {
        unsigned int major;
        unsigned int minor;
        unsigned int patch;

        char postfix;
    };

    /**
    * 根据版本号取得Android的APILevel,如若出错返回-1
    */
    const int GetAndroidAPILevel(const AndroidVersion &);
}//namespace hgl
