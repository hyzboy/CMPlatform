﻿#ifndef HGL_QT_STRING_INCLUDE
#define HGL_QT_STRING_INCLUDE

#include<hgl/type/String.h>
#include<hgl/CodePage.h>
#include<QString>

#if HGL_OS == HGL_OS_Windows
    inline QString ToQString(const hgl::WideString &ws)
    {
        return QString::fromWCharArray(ws.c_str(),ws.Length());
    }

    inline QString ToQString(const wchar_t *str,int size){return QString::fromWCharArray(str,size);}

    inline hgl::UTF8String ToUTF8String(const QString &str)
    {
        QByteArray u8str=str.toUtf8();

        return hgl::UTF8String((hgl::u8char *)u8str.data(),u8str.size());
    }

    inline hgl::WideString ToOSString(const QString &str)
    {
        return hgl::WideString((wchar_t *)str.utf16(),str.length());
    }
#else
    template<int WS> QString WCharToQString(const wchar_t *,int);

    template<> inline QString WCharToQString<2>(const wchar_t *str,int size){return QString::fromUtf16((ushort *)str,size);}
    template<> inline QString WCharToQString<4>(const wchar_t *str,int size){return QString::fromUcs4((uint *)str,size);}

    inline QString ToQString(const wchar_t *str,int size)
    {
        return WCharToQString<sizeof(wchar_t)>(str,size);
    }

    inline QString ToQString(const u16char *str,int size){return QString::fromUtf16((ushort *)str,size);}
    inline QString ToQString(const char32_t *str,int size){return QString::fromUcs4((uint *)str,size);}

    inline QString ToQString(const hgl::UTF16String &str)
    {
        return QString::fromUtf16((ushort *)str.c_str(), str.Length());
    }

    inline hgl::UTF8String ToUTF8String(const QString &str)
    {
        QByteArray u8str=str.toUtf8();

        return hgl::UTF8String(u8str.data(),u8str.size());
    }

    inline hgl::UTF8String ToOSString(const QString &str)
    {
        return ToUTF8String(str);
    }
#endif//HGL_OS == HGL_OS_Windows

inline QString ToQString(const hgl::UTF8String &str)
{
    return QString::fromUtf8((char *)str.c_str(),str.Length());
}

inline hgl::UTF16String ToUTF16String(const QString &str)
{
    return hgl::UTF16String((u16char *)str.utf16(),str.length());
}

// inline QString toQString(const hgl::UTF32String &str)
// {
//  return QString::fromUcs4((uint *)str.c_str(),str.Length());
// }
#endif//HGL_QT_STRING_INCLUDE
