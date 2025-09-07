#include<hgl/Charset.h>

#include<windows.h>

namespace hgl
{
    namespace
    {
        /**
        * Windows代码页枚举
        * 全部Windows所支持代码页请参见 http://msdn.microsoft.com/en-us/library/dd317756
        *                            https://docs.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
        */
        enum class CharCodePage:uint16                  ///代码页枚举
        {
            NONE=0,                                     ///<起始定义，无意义

            IBM437                  =437,               ///<OEM United States (dos)

            //中文
            GBK                     =936,               ///<中国GBK标准中文
            Big5                    =950,               ///<中国台湾Big5标准繁体中文
            GB2312                  =20936,             ///<中国GB2312标准简体中文
            GB18030                 =54936,             ///<中国GB18030-2000标准中文

            //日文
            ShiftJIS                =932,               ///<日文ShiftJIS
            EUC_JP                  =20932,             ///<日文JIS 0208-1990 and 0212-1990
            ISO2022JP               =50220,             ///<ISO 2022 Japanese with no halfwidth Katakana; Japanese (JIS)
            csISO2022JP             =50221,             ///<ISO 2022 Japanese with halfwidth Katakana; Japanese (JIS-Allow 1 byte Kana)
            JISX                    =50222,             ///<日文JIS X/ISO 2022

            //韩文
            Korean                  =949,               ///<韩文

            //苹果编码
            MacJanpan               =10001,             ///<日文
            MacTraditionalChinese   =10002,             ///<繁体中文
            MacSimplifiedChinese    =10008,             ///<简体中文

            //ISO
            ISO_8859_1              =28591,             ///<ISO 8859-1 Latin 1; Western European                    西欧语系(阿尔巴尼亚语,西班牙加泰罗尼亚语,丹麦语,荷兰语,英语,Faeroese语,芬兰语,法语,德语,加里西亚语,爱尔兰语,冰岛语,意大利语,挪威语,葡萄牙语,瑞士语.)这同时适用于美国英语. 
            ISO_8859_2              =28592,             ///<ISO 8859-2 Central European; Central European (ISO)     斯拉夫/中欧语系(捷克语,德语,匈牙利语,波兰语,罗马尼亚语,克罗地亚语,斯洛伐克语,斯洛文尼亚语) 
            ISO_8859_3              =28593,             ///<ISO 8859-3 Latin 3                                      世界语,加里西亚语,马耳他语,土耳其语
            ISO_8859_4              =28594,             ///<ISO 8859-4 Baltic                                       爱莎尼亚语,拉脱维亚语,立陶宛语
            ISO_8859_5              =28595,             ///<ISO 8859-5 Cyrillic                                     斯拉夫语系(保加利亚语,Byelorussian语,马其顿语,俄语,塞尔维亚语,乌克兰语)
            ISO_8859_6              =28596,             ///<ISO 8859-6 Arabic                                       阿拉伯语
            ISO_8859_7              =28597,             ///<ISO 8859-7 Greek                                        现代希腊语
            ISO_8859_8              =28598,             ///<ISO 8859-8 Hebrew; Hebrew (ISO-Visual)                  希伯来语
            ISO_8859_9              =28599,             ///<ISO 8859-9 Turkish                                      Latin 5 字符集, (去掉了 Latin 1中不经常使用的一些冰岛语字符而代以土耳其语字符) 
            ISO_8859_13             =28603,             ///<ISO 8859-13 Estonian
            ISO_8859_15             =28605,             ///<ISO 8859-15 Latin 9                                     Latin 9 字符集, 是Latin 1字符集的更新版本,去掉一些不常用的字符,增加了对爱莎尼亚语的支持,修正了法语和芬兰语部份,增加了欧元字符) 

            //unicode
            UTF7                    =65000,             ///<utf-7
            UTF8                    =65001,             ///<utf-8

            UTF16LE                 =1200,
            UTF16BE                 =1201,
            UTF32LE                 =12000,
            UTF32BE                 =12001,

            END                                         ///<结束定义，无意义
        };//enum CharCodePage

        struct CodePageAndCharSet
        {
            uint16 codepage;
            CharSetName charset;
        };

    #define HGL_CODE_PAGE_AND_CHAR_SET(codepage,charset) {uint16(CharCodePage::codepage),charset}

        constexpr struct CodePageAndCharSet CodePage2CharSet[]=
        {
            HGL_CODE_PAGE_AND_CHAR_SET(NONE,                    "us-ascii"  ),
            HGL_CODE_PAGE_AND_CHAR_SET(IBM437,                  "IBM437"    ),

            HGL_CODE_PAGE_AND_CHAR_SET(GBK,                     "gbk"       ),
            HGL_CODE_PAGE_AND_CHAR_SET(Big5,                    "big5"      ),
            HGL_CODE_PAGE_AND_CHAR_SET(GB2312,                  "gb2312"    ),
            HGL_CODE_PAGE_AND_CHAR_SET(GB18030,                 "gb18030"   ),

            HGL_CODE_PAGE_AND_CHAR_SET(ShiftJIS,                "shift-jis"     ),
            HGL_CODE_PAGE_AND_CHAR_SET(EUC_JP,                  "EUC-JP"        ),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO2022JP,               "iso-2022-jp"   ),
            HGL_CODE_PAGE_AND_CHAR_SET(csISO2022JP,             "csISO2022JP"   ),
            HGL_CODE_PAGE_AND_CHAR_SET(JISX,                    "iso-2022-jp"   ),

            HGL_CODE_PAGE_AND_CHAR_SET(Korean,                  "ks_c_5601-1987"),

            HGL_CODE_PAGE_AND_CHAR_SET(MacJanpan,               "x-mac-japanese"    ),
            HGL_CODE_PAGE_AND_CHAR_SET(MacTraditionalChinese,   "x-mac-chinesetrad" ),
            HGL_CODE_PAGE_AND_CHAR_SET(MacSimplifiedChinese,    "x-mac-chinesesimp" ),

            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_1,         "iso-8859-1"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_2,         "iso-8859-2"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_3,         "iso-8859-3"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_4,         "iso-8859-4"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_5,         "iso-8859-5"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_6,         "iso-8859-6"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_7,         "iso-8859-7"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_8,         "iso-8859-8"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_9,         "iso-8859-9"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_13,        "iso-8859-13"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_15,        "iso-8859-15"),

            HGL_CODE_PAGE_AND_CHAR_SET(UTF7,           "utf-7"     ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF8,           "utf-8"     ),

            HGL_CODE_PAGE_AND_CHAR_SET(UTF16LE,        "utf-16le"  ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF16BE,        "utf-16be"  ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF32LE,        "utf-32le"  ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF32BE,        "utf-32be"  ),
        };//const struct

        constexpr int CharSetCount=sizeof(CodePage2CharSet)/sizeof(CodePageAndCharSet);

        constexpr struct CodePageAndCharSet CodeSet2CharPage[]=
        {
            HGL_CODE_PAGE_AND_CHAR_SET(NONE,                    "us-ascii"  ),
            HGL_CODE_PAGE_AND_CHAR_SET(IBM437,                  "IBM437"    ),

            HGL_CODE_PAGE_AND_CHAR_SET(GBK,                     "gbk"       ),

            HGL_CODE_PAGE_AND_CHAR_SET(Big5,                    "big5"      ),
            HGL_CODE_PAGE_AND_CHAR_SET(Big5,                    "bigfive"   ),

            HGL_CODE_PAGE_AND_CHAR_SET(GB2312,                  "gb2312"    ),
            HGL_CODE_PAGE_AND_CHAR_SET(GB18030,                 "gb18030"   ),

            HGL_CODE_PAGE_AND_CHAR_SET(ShiftJIS,                "shift_jis"     ),
            HGL_CODE_PAGE_AND_CHAR_SET(EUC_JP,                  "EUC-JP"        ),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO2022JP,               "iso-2022-jp"   ),
            HGL_CODE_PAGE_AND_CHAR_SET(csISO2022JP,             "csISO2022JP"   ),
            HGL_CODE_PAGE_AND_CHAR_SET(JISX,                    "iso-2022-jp"   ),

            HGL_CODE_PAGE_AND_CHAR_SET(Korean,                  "ks_c_5601-1987"),

            HGL_CODE_PAGE_AND_CHAR_SET(MacJanpan,               "x-mac-japanese"    ),
            HGL_CODE_PAGE_AND_CHAR_SET(MacTraditionalChinese,   "x-mac-chinesetrad" ),
            HGL_CODE_PAGE_AND_CHAR_SET(MacSimplifiedChinese,    "x-mac-chinesesimp" ),

            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_1,         "iso-8859-1"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_2,         "iso-8859-2"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_3,         "iso-8859-3"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_4,         "iso-8859-4"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_5,         "iso-8859-5"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_6,         "iso-8859-6"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_7,         "iso-8859-7"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_8,         "iso-8859-8"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_9,         "iso-8859-9"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_13,        "iso-8859-13"),
            HGL_CODE_PAGE_AND_CHAR_SET(ISO_8859_15,        "iso-8859-15"),

            HGL_CODE_PAGE_AND_CHAR_SET(UTF7,           "utf-7"      ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF8,           "utf-8"      ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF16LE,        "utf-16le"   ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF16BE,        "utf-16be"   ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF32LE,        "utf-32le"   ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF32BE,        "utf-32be"   ),

            HGL_CODE_PAGE_AND_CHAR_SET(UTF16LE,        "utf-16"     ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF16BE,        "unicodeFFFE"),

            HGL_CODE_PAGE_AND_CHAR_SET(UTF16LE,        "ucs-2le"    ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF16BE,        "ucs-2be"    ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF32LE,        "ucs-4le"    ),
            HGL_CODE_PAGE_AND_CHAR_SET(UTF32BE,        "ucs-4be"    )
        };//const struct CharSet Characters

        constexpr int CharPageCount=sizeof(CodeSet2CharPage)/sizeof(CodePageAndCharSet);
    }//namespace

    CharSet UTF8CharSet     ((uint16)CharCodePage::UTF8);
    CharSet UTF16LECharSet  ((uint16)CharCodePage::UTF16LE);
    CharSet UTF16BECharSet  ((uint16)CharCodePage::UTF16BE);

    const char *FindCharSet(const uint16 ccp)
    {
        for(int i=0;i<CharSetCount;i++)
            if(CodePage2CharSet[i].codepage==ccp)
                return CodePage2CharSet[i].charset;

        return 0;
    }

    inline uint16 FindCodePage(const u8char *char_set)
    {
        for(int i=0;i<CharPageCount;i++)
            if(!charset_cmp(CodePage2CharSet[i].charset,char_set))
                return CodePage2CharSet[i].codepage;

        return (uint16)CharCodePage::NONE;
    }

    int get_utf16_length(const CharSet &cs,const void *src,const int src_size)
    {
        const int src_str_size=(src_size==-1)?strlen((char *)src):src_size;

        const int len=MultiByteToWideChar((UINT)cs.codepage,0,(char *)src,src_str_size,0,0);

        if(len<=0)return(len);

        return len;
    }
    
    int to_utf16(const CharSet &cs,u16char **dst,const void *src,const int src_size)
    {
        const int src_str_size=(src_size==-1)?strlen((char *)src):src_size;

        const int len=MultiByteToWideChar((UINT)cs.codepage,0,(char *)src,src_str_size,0,0);

        if(len<=0)return(len);

        *dst=new u16char[len+1];

        MultiByteToWideChar((UINT)cs.codepage,0,(char *)src,src_str_size,*dst,len);
        (*dst)[len]=0;
        
        return len;
    }
    
    int to_utf16(const CharSet &cs,u16char *dst,const int dst_size,const void *src,const int src_size)
    {
        if(dst_size<=0)return dst_size;

        const int src_str_size=(src_size==-1)?strlen((char *)src):src_size;

        int len=MultiByteToWideChar((UINT)cs.codepage,0,(char *)src,src_str_size,dst,dst_size);

        if(len<dst_size)
            dst[len]=0;

        return len;
    }

    int to_utf8(const CharSet &cs,u8char **dst,const void *src,const int src_size)
    {
        u16char *u16str;
        int u16size=to_utf16(cs,&u16str,src,src_size);

        if(u16size<=0)return(u16size);

        int u8_size;
        *dst = u16_to_u8(u16str, u16size, u8_size);

        delete[] u16str;
        return u8_size;
    }

    int utf16_to(const CharSet &cs,char **dst,const u16char *src,const int src_size)
    {
        const int src_str_size=(src_size==-1)?strlen(src):src_size;

        const int len=WideCharToMultiByte((UINT)cs.codepage,0,src,src_str_size,0,0,0,0);

        if(len<=0)return(len);

        *dst=new char[len+1];

        WideCharToMultiByte((UINT)cs.codepage,0,src,src_str_size,*dst,len,0,0);
        
        (*dst)[len]=0;
        return len;
    }

    int utf8_to(const CharSet &cs,char **dst,const u8char *src,const int src_size)
    {
        int u16str_size;
        u16char *u16str=u8_to_u16(src,src_size,u16str_size);

        if(!u16str)return(0);

        int result=utf16_to(cs,dst,u16str,u16str_size);

        delete[] u16str;
        return(result);
    }
    
    AnsiString ToAnsiString(const CharSet &cs,const U16String &str)
    {
        int len;
        char *ansi_str;

        len=utf16_to(cs,&ansi_str,str.c_str(),str.Length());

        return AnsiString::newOf(ansi_str,len);
    }
}//namespace hgl


