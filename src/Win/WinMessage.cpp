#include"WinWindow.h"
#include<hgl/platform/InputDevice.h>
#include<Windows.h>

#ifdef _DEBUG
#include<hgl/log/LogInfo.h>
#endif//_DEBUG

namespace hgl
{
    namespace
    {
        #define PROP_DPIISOLATION          L"PROP_ISOLATION"

        static KeyboardButton KeyConvert[256];
        static void (*WMProc[2048])(WinWindow *,uint32,uint32);                 //消息处理队列

        uint32 GetMouseKeyFlags(uint32 wflags)
        {
            uint32 flag=0;

            if(wflags&MK_LBUTTON)flag|=mbLeft;
            if(wflags&MK_RBUTTON)flag|=mbRight;
            if(wflags&MK_MBUTTON)flag|=mbMid;

            if(wflags&MK_XBUTTON1)flag|=mbX1;
            if(wflags&MK_XBUTTON2)flag|=mbX2;

            if(wflags&MK_SHIFT  )flag|=mbShift;
            if(wflags&MK_CONTROL)flag|=mbCtrl;

            return(flag);
        }

        void InitKeyConvert()
        {
            int i;

            memset(KeyConvert,0,sizeof(KeyConvert));

            KeyConvert[VK_ESCAPE    ]=KeyboardButton::Esc;
            for(i=VK_F1;i<=VK_F12;i++)KeyConvert[i]=(KeyboardButton)(int(KeyboardButton::F1)+i-VK_F1);

            KeyConvert['`'          ]=KeyboardButton::Grave;
            for(i='0';i<='9';i++)KeyConvert[i]=KeyboardButton(int(KeyboardButton::_0)+i-'0');
            KeyConvert['-'          ]=KeyboardButton::Minus;
            KeyConvert['='          ]=KeyboardButton::Equals;
            KeyConvert['\\'         ]=KeyboardButton::BackSlash;
            KeyConvert[VK_BACK      ]=KeyboardButton::BackSpace;

            KeyConvert[VK_TAB       ]=KeyboardButton::Tab;
            KeyConvert['Q'          ]=KeyboardButton::Q;
            KeyConvert['W'          ]=KeyboardButton::W;
            KeyConvert['E'          ]=KeyboardButton::E;
            KeyConvert['R'          ]=KeyboardButton::R;
            KeyConvert['T'          ]=KeyboardButton::T;
            KeyConvert['Y'          ]=KeyboardButton::Y;
            KeyConvert['U'          ]=KeyboardButton::U;
            KeyConvert['I'          ]=KeyboardButton::I;
            KeyConvert['O'          ]=KeyboardButton::O;
            KeyConvert['P'          ]=KeyboardButton::P;
            KeyConvert['['          ]=KeyboardButton::LeftBracket;
            KeyConvert[']'          ]=KeyboardButton::RightBracket;

            KeyConvert[VK_CAPITAL   ]=KeyboardButton::CapsLock;
            KeyConvert['A'          ]=KeyboardButton::A;
            KeyConvert['S'          ]=KeyboardButton::S;
            KeyConvert['D'          ]=KeyboardButton::D;
            KeyConvert['F'          ]=KeyboardButton::F;
            KeyConvert['G'          ]=KeyboardButton::G;
            KeyConvert['H'          ]=KeyboardButton::H;
            KeyConvert['J'          ]=KeyboardButton::J;
            KeyConvert['K'          ]=KeyboardButton::K;
            KeyConvert['L'          ]=KeyboardButton::L;
            KeyConvert[';'          ]=KeyboardButton::Semicolon;
            KeyConvert['\''         ]=KeyboardButton::Apostrophe;
            KeyConvert[VK_RETURN    ]=KeyboardButton::Enter;

            KeyConvert[VK_LSHIFT    ]=KeyboardButton::LeftShift;
            KeyConvert['Z'          ]=KeyboardButton::Z;
            KeyConvert['X'          ]=KeyboardButton::X;
            KeyConvert['C'          ]=KeyboardButton::C;
            KeyConvert['V'          ]=KeyboardButton::V;
            KeyConvert['B'          ]=KeyboardButton::B;
            KeyConvert['N'          ]=KeyboardButton::N;
            KeyConvert['M'          ]=KeyboardButton::M;
            KeyConvert[','          ]=KeyboardButton::Comma;
            KeyConvert['.'          ]=KeyboardButton::Period;
            KeyConvert['/'          ]=KeyboardButton::Slash;
            KeyConvert[VK_RSHIFT    ]=KeyboardButton::RightShift;

            KeyConvert[VK_LCONTROL  ]=KeyboardButton::LeftCtrl;
            KeyConvert[VK_LWIN      ]=KeyboardButton::LeftOS;
            KeyConvert[VK_LMENU     ]=KeyboardButton::LeftAlt;
            KeyConvert[VK_SPACE     ]=KeyboardButton::Space;
            KeyConvert[VK_RMENU     ]=KeyboardButton::RightAlt;
            KeyConvert[VK_RWIN      ]=KeyboardButton::RightOS;
            KeyConvert[VK_RCONTROL  ]=KeyboardButton::RightCtrl;

            KeyConvert[VK_PAUSE     ]=KeyboardButton::Pause;
        //        KeyConvert[VK_CLEAR     ]=KeyboardButton::Clear;

            KeyConvert[VK_NUMPAD0   ]=KeyboardButton::Num0;
            KeyConvert[VK_NUMPAD1   ]=KeyboardButton::Num1;
            KeyConvert[VK_NUMPAD2   ]=KeyboardButton::Num2;
            KeyConvert[VK_NUMPAD3   ]=KeyboardButton::Num3;
            KeyConvert[VK_NUMPAD4   ]=KeyboardButton::Num4;
            KeyConvert[VK_NUMPAD5   ]=KeyboardButton::Num5;
            KeyConvert[VK_NUMPAD6   ]=KeyboardButton::Num6;
            KeyConvert[VK_NUMPAD7   ]=KeyboardButton::Num7;
            KeyConvert[VK_NUMPAD8   ]=KeyboardButton::Num8;
            KeyConvert[VK_NUMPAD9   ]=KeyboardButton::Num9;

            KeyConvert[VK_DECIMAL   ]=KeyboardButton::NumDecimal;
            KeyConvert[VK_DIVIDE    ]=KeyboardButton::NumDivide;
            KeyConvert[VK_MULTIPLY  ]=KeyboardButton::NumMultiply;
            KeyConvert[VK_SUBTRACT  ]=KeyboardButton::NumSubtract;
            KeyConvert[VK_ADD       ]=KeyboardButton::NumAdd;

            KeyConvert[VK_UP        ]=KeyboardButton::Up;
            KeyConvert[VK_DOWN      ]=KeyboardButton::Down;
            KeyConvert[VK_LEFT      ]=KeyboardButton::Left;
            KeyConvert[VK_RIGHT     ]=KeyboardButton::Right;

            KeyConvert[VK_INSERT    ]=KeyboardButton::Insert;
            KeyConvert[VK_DELETE    ]=KeyboardButton::Delete;
            KeyConvert[VK_HOME      ]=KeyboardButton::Home;
            KeyConvert[VK_END       ]=KeyboardButton::End;
            KeyConvert[VK_PRIOR     ]=KeyboardButton::PageUp;
            KeyConvert[VK_NEXT      ]=KeyboardButton::PageDown;

            KeyConvert[VK_NUMLOCK   ]=KeyboardButton::NumLock;
            KeyConvert[VK_SCROLL    ]=KeyboardButton::ScrollLock;

            //KeyConvert[VK_SHIFT       ]=kbLeftShift;
            //KeyConvert[VK_CONTROL ]=kbLeftCtrl;
            //KeyConvert[VK_MENU        ]=kbLeftAlt;

            KeyConvert[VK_OEM_1     ]=KeyboardButton::Semicolon;
            KeyConvert[VK_OEM_PLUS  ]=KeyboardButton::Equals;
            KeyConvert[VK_OEM_COMMA ]=KeyboardButton::Comma;
            KeyConvert[VK_OEM_MINUS ]=KeyboardButton::Minus;
            KeyConvert[VK_OEM_PERIOD]=KeyboardButton::Period;
            KeyConvert[VK_OEM_2     ]=KeyboardButton::Slash;
            KeyConvert[VK_OEM_3     ]=KeyboardButton::Grave;
            KeyConvert[VK_OEM_4     ]=KeyboardButton::LeftBracket;
            KeyConvert[VK_OEM_5     ]=KeyboardButton::BackSlash;
            KeyConvert[VK_OEM_6     ]=KeyboardButton::RightBracket;
            KeyConvert[VK_OEM_7     ]=KeyboardButton::Apostrophe;
        }

        KeyboardButton ConvertOSKey(uint key)
        {
            if(key>=256)return(KeyboardButton::NONE);
            if(KeyConvert[key]==KeyboardButton::NONE)return(KeyboardButton::NONE);

            if(key==VK_SHIFT)
            {
                if((GetAsyncKeyState(VK_LSHIFT)>>15)&1)
                    return KeyboardButton::LeftShift;
                else
                    return KeyboardButton::RightShift;
            }
            else
            if(key==VK_CONTROL)
            {
                if((GetAsyncKeyState(VK_LCONTROL)>>15)&1)
                    return KeyboardButton::LeftCtrl;
                else
                    return KeyboardButton::RightCtrl;
            }
            if(key==VK_MENU)
            {
                if((GetAsyncKeyState(VK_LMENU)>>15)&1)
                    return KeyboardButton::LeftAlt;
                else
                    return KeyboardButton::RightAlt;
            }

    #ifdef _DEBUG
            if(KeyConvert[key]==KeyboardButton::NONE)
            {
                wchar_t name[64];

                ::GetKeyNameTextW(key,name,64);

                LOG_INFO(WideString(L"Unknow Key: " )+WideString::valueOf(key)
                        +WideString(L" ,name: "     )+WideString(name));
            }
    #endif _DEBUG

            return KeyConvert[key];
        }

        void WMProcNCCreate(WinWindow *win,uint32 wParam,uint32 lParam)
        {
            auto createStruct = reinterpret_cast<const CREATESTRUCTW *>(lParam);
            auto createParams = static_cast<const WindowCreateExteraParams *>(createStruct->lpCreateParams);

            if (createParams->bEnableNonClientDpiScaling)
            {
                EnableNonClientDpiScaling(win->GetWnd());
            }

            // Store a flag on the window to note that it'll run its child in a different awareness
            if (createParams->bChildWindowDpiIsolation)
            {
                SetPropW(win->GetWnd(), PROP_DPIISOLATION, (HANDLE)TRUE);
            }
        }

        void WMProcCreate(WinWindow *win,uint32 wParam,uint32 lParam)
        {
            HWND hWnd=win->GetWnd();
            RECT rcWindow = {};
            UINT uDpi = 96;
            DPI_AWARENESS dpiAwareness = GetAwarenessFromDpiAwarenessContext(GetThreadDpiAwarenessContext());

            switch (dpiAwareness)
            {
                // Scale the window to the system DPI
            case DPI_AWARENESS_SYSTEM_AWARE:
                uDpi = GetDpiForSystem();
                break;

                // Scale the window to the monitor DPI
            case DPI_AWARENESS_PER_MONITOR_AWARE:
                uDpi = GetDpiForWindow(hWnd);
                break;
            }

            GetWindowRect(hWnd, &rcWindow);
            rcWindow.right = rcWindow.left + MulDiv(win->GetWidth(), uDpi, 96);
            rcWindow.bottom = rcWindow.top + MulDiv(win->GetHeight(), uDpi, 96);
            SetWindowPos(hWnd, nullptr, rcWindow.right, rcWindow.top, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top, SWP_NOZORDER | SWP_NOACTIVATE);

            BOOL bDpiIsolation = PtrToInt(GetPropW(hWnd, PROP_DPIISOLATION));

            DPI_AWARENESS_CONTEXT previousDpiContext = {};
            DPI_HOSTING_BEHAVIOR previousDpiHostingBehavior = {};

            if (bDpiIsolation)
            {
                previousDpiHostingBehavior = SetThreadDpiHostingBehavior(DPI_HOSTING_BEHAVIOR_MIXED);

                // For this example, we'll have the external content run with System-DPI awareness
                previousDpiContext = SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

                SetThreadDpiAwarenessContext(previousDpiContext);
                SetThreadDpiHostingBehavior(previousDpiHostingBehavior);
            }
        }

        void WMProcDestroy(WinWindow *win,uint32,uint32)
        {
            win->ProcClose();
            PostQuitMessage(0);
        }

        #define WMEF_MOUSE(button,action)   void WMProcMouse##button##action(WinWindow *win,uint32 wParam,uint32 lParam)    \
            {   \
                const int x=LOWORD(lParam); \
                const int y=HIWORD(lParam); \
                \
                win->ProcMouseMove(x,y);  \
                win->ProcMouse##action(x,y,mb##button|GetMouseKeyFlags(wParam));   \
            }

            WMEF_MOUSE(Left,Pressed);
            WMEF_MOUSE(Left,Released);
            WMEF_MOUSE(Left,DblClicked);

            WMEF_MOUSE(Mid,Pressed);
            WMEF_MOUSE(Mid,Released);
            WMEF_MOUSE(Mid,DblClicked);

            WMEF_MOUSE(Right,Pressed);
            WMEF_MOUSE(Right,Released);
            WMEF_MOUSE(Right,DblClicked);

            void WMProcMouseMove(WinWindow *win,uint32 wParam,uint32 lParam)
            {
                win->ProcMouseMove(LOWORD(lParam),HIWORD(lParam));
            }
        #undef WMEF_MOUSE

        #define WMEF2(name) void name(WinWindow *win,uint32 wParam,uint32 lParam)
            WMEF2(WMProcMouseWheel)
            {
                const int zDelta=GET_WHEEL_DELTA_WPARAM(wParam);
                const uint key=(uint)ConvertOSKey(GET_KEYSTATE_WPARAM(wParam));
                
                win->ProcMouseWheel(zDelta,0,key);
            }

            WMEF2(WMProcMouseHWheel)
            {
                const int zDelta=GET_WHEEL_DELTA_WPARAM(wParam);
                const uint key=(uint)ConvertOSKey(GET_KEYSTATE_WPARAM(wParam));
                
                win->ProcMouseWheel(0,zDelta,key);
            }

            WMEF2(WMProcSize)
            {
                win->ProcResize(LOWORD(lParam),HIWORD(lParam));
            }
        #undef WMEF2

        #define WMEF1(name) void name(WinWindow *win,uint32 wParam,uint32)
            WMEF1(WMProcKeyDown)
            {
                win->ProcKeyPressed(ConvertOSKey(wParam));
            }

            WMEF1(WMProcKeyUp)
            {
                win->ProcKeyReleased(ConvertOSKey(wParam));
            }

            WMEF1(WMProcChar)
            {
                win->ProcChar((wchar_t)wParam);
            }

            WMEF1(WMProcActive)
            {
                //if(JoyPlugIn)
                //    JoyInterface.SetInputActive(wParam);

                win->ProcActive(wParam);
            }
        #undef WMEF1
    }//namespace

    void InitMessageProc()
    {
        memset(WMProc,0,sizeof(WMProc));
        InitKeyConvert();

        //if(joy)
        //    LoadJoystick(win->hInstance,win->hWnd);

    #define WM_MAP(wm,func) WMProc[wm]=func;

        WM_MAP(WM_NCCREATE          ,WMProcNCCreate);
        WM_MAP(WM_CREATE            ,WMProcCreate);
        WM_MAP(WM_CLOSE             ,WMProcDestroy);
        WM_MAP(WM_LBUTTONDOWN       ,WMProcMouseLeftPressed);
        WM_MAP(WM_LBUTTONUP         ,WMProcMouseLeftReleased);
        WM_MAP(WM_LBUTTONDBLCLK     ,WMProcMouseLeftDblClicked);
        WM_MAP(WM_MBUTTONDOWN       ,WMProcMouseMidPressed);
        WM_MAP(WM_MBUTTONUP         ,WMProcMouseMidReleased);
        WM_MAP(WM_MBUTTONDBLCLK     ,WMProcMouseMidDblClicked);
        WM_MAP(WM_RBUTTONDOWN       ,WMProcMouseRightPressed);
        WM_MAP(WM_RBUTTONUP         ,WMProcMouseRightReleased);
        WM_MAP(WM_RBUTTONDBLCLK     ,WMProcMouseRightDblClicked);
        WM_MAP(WM_MOUSEWHEEL        ,WMProcMouseWheel);
        WM_MAP(WM_MOUSEHWHEEL       ,WMProcMouseHWheel);
        WM_MAP(WM_MOUSEMOVE         ,WMProcMouseMove);
        WM_MAP(WM_KEYDOWN           ,WMProcKeyDown);
        WM_MAP(WM_KEYUP             ,WMProcKeyUp);
        WM_MAP(WM_SYSKEYDOWN        ,WMProcKeyDown);
        WM_MAP(WM_SYSKEYUP          ,WMProcKeyUp);
        WM_MAP(WM_CHAR              ,WMProcChar);
        WM_MAP(WM_SYSCHAR           ,WMProcChar);
        WM_MAP(WM_ACTIVATE          ,WMProcActive);
        WM_MAP(WM_SIZE              ,WMProcSize);

    #undef WM_MAP
    }

    LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if(uMsg<2048)
            if(WMProc[uMsg])
            {
                WinWindow *win=(WinWindow *)GetWindowLongPtrW(hWnd,GWLP_USERDATA);

                if(win)
                    WMProc[uMsg](win,wParam,lParam);
            }

        return (DefWindowProcW(hWnd, uMsg, wParam, lParam));
    }

    void InitNativeWindowSystem()
    {
        InitMessageProc();
    }
}//namespace hgl
