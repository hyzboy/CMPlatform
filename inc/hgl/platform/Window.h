#ifndef HGL_GRAPH_WINDOW_INCLUDE
#define HGL_GRAPH_WINDOW_INCLUDE

#include<hgl/type/String.h>
#include<hgl/platform/InputDevice.h>

namespace hgl
{
    class Window
    {
    protected:

        uint width,height;
        bool full_screen;

        OSString win_name;

        bool active;
        bool is_close;
        bool is_min;

        bool key_push[kbRangeSize];

    protected:

        virtual bool MessageProc()=0;
        virtual bool WaitMessage()=0;

    public:

        virtual void ProcMouseMove      (int x,int y)               {SafeCallEvent(OnMouseMove,     (x,y));}
        virtual void ProcMouseWheel     (int v,int h,uint mb)       {SafeCallEvent(OnMouseWheel,    (v,h,mb));}
        virtual void ProcMousePressed   (int x,int y,uint mb)       {SafeCallEvent(OnMousePressed,  (x,y,mb));}
        virtual void ProcMouseReleased  (int x,int y,uint mb)       {SafeCallEvent(OnMouseReleased, (x,y,mb));}
        virtual void ProcMouseDblClicked(int x,int y,uint mb)       {SafeCallEvent(OnMouseDblClicked, (x,y,mb));}

        //virtual void ProcJoystickPressed (uint);
        //virtual void ProcJoystickRepeat  (uint);
        //virtual void ProcJoystickReleased(uint);

        virtual void ProcKeyPressed (KeyboardButton);
        virtual void ProcKeyRepeat  (KeyboardButton kb){SafeCallEvent(OnKeyRepeat,(kb));}
        virtual void ProcKeyReleased(KeyboardButton);

        virtual void ProcChar       (os_char ch){SafeCallEvent(OnChar,(ch));}

        virtual void ProcResize     (uint,uint);

        virtual void ProcActive     (bool);
        virtual void ProcClose      ();

    public:

        uint GetWidth()const{return width;}
        uint GetHeight()const{return height;}

    public:

        DefEvent(void,OnMouseMove,      (int,int));
        DefEvent(void,OnMouseWheel,     (int,int,uint));
        DefEvent(void,OnMousePressed,   (int,int,uint));
        DefEvent(void,OnMouseReleased,  (int,int,uint));
        DefEvent(void,OnMouseDblClicked,(int,int,uint));

        //DefEvent(void,OnJoystickDown    ,(uint));
        //DefEvent(void,OnJoystickPress ,(uint));
        //DefEvent(void,OnJoystickUp    ,(uint));

        DefEvent(void,OnKeyPressed, (KeyboardButton));
        DefEvent(void,OnKeyRepeat,  (KeyboardButton));
        DefEvent(void,OnKeyReleased,(KeyboardButton));

        DefEvent(void,OnChar    ,(os_char));

        DefEvent(void,OnResize  ,(uint,uint));

        DefEvent(void,OnActive  ,(bool));
        DefEvent(void,OnClose   ,());

    public:

        Window(const OSString &wn)
        {
            width=height=0;
            full_screen=false;
            win_name=wn;
            active=false;
            is_close=true;
            is_min=false;
            hgl_zero(key_push);
        }
        virtual ~Window()=default;

        virtual bool Create(uint,uint)=0;
        virtual bool Create(uint,uint,uint)=0;
        virtual void Close()=0;

                bool IsMin()const{return is_min;}
                bool IsClose()const{return is_close;}
                bool IsVisible()const{return (!is_close)&&width&&height;}

        virtual void SetCaption(const OSString &)=0;

        virtual void Show()=0;
        virtual void Hide()=0;

        virtual void ToMinWindow()=0;
        virtual void ToMaxWindow()=0;

        virtual void SetSystemCursor(bool){}

        virtual bool Update();
    };//class Window

    Window *CreateRenderWindow(const OSString &win_name);

    void InitNativeWindowSystem();
}//namespace hgl
#endif//HGL_GRAPH_WINDOW_INCLUDE
