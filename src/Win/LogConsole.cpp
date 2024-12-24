﻿#include<hgl/log/Logger.h>
#include<hgl/CodePage.h>
#include<windows.h>

namespace hgl
{
    namespace logger
    {
        constexpr uint LOG_BUF_SIZE=4096;

        class LogWinConsole:public Logger
        {
        private:

            DWORD result=0;

            void *console_handle=nullptr;

            u16char buf[LOG_BUF_SIZE]{};

        public:

            LogWinConsole(LogLevel ll):Logger(ll)
            {
                console_handle=GetStdHandle(STD_OUTPUT_HANDLE);
            }

            bool Create(const U16String &)
            {
                return(true);
            }

            ~LogWinConsole()
            {
                Close();
            }

            void Close()
            {
                CloseHandle(console_handle);
            }

            void Write(const u16char *str,int size)
            {
                WriteConsoleW(console_handle,str,size,&result,nullptr);
                WriteConsoleW(console_handle,L"\n", 1, &result, nullptr);
            }

            void Write(const u8char *str,int size)
            {
                const int len=u8_to_u16(buf,LOG_BUF_SIZE,str,size);

                if(len<=0)return;

                buf[len]=L'\n';

                WriteConsoleW(console_handle,buf,len+1,&result,nullptr);
            }
        };//class LogWinConsole

        Logger *CreateLoggerConsole(LogLevel ll)
        {
            return(new LogWinConsole(ll));
        }
    }//namespace logger
}//namespace hgl
