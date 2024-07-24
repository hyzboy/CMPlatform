#include<hgl/CodePage.h>

#include<windows.h>

namespace hgl
{
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
    
    AnsiString ToAnsiString(const CharSet &cs,const UTF16String &str)
    {
        int len;
        char *ansi_str;

        len=utf16_to(cs,&ansi_str,str.c_str(),str.Length());

        return AnsiString::newOf(ansi_str,len);
    }
}//namespace hgl


