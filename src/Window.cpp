#include<hgl/platform/Window.h>

namespace hgl
{
    void Window::ProcKeyDown(KeyboardButton kb)
    {
        if(key_push[kb])
            ProcKeyPress(kb);
        else
            key_push[kb]=true;

       SafeCallEvent(OnKeyDown,(kb));
    }

    void Window::ProcKeyUp(KeyboardButton kb)
    {
        key_push[kb]=false;

        SafeCallEvent(OnKeyUp,(kb));
    }

    void Window::ProcResize(uint w,uint h)
    {
        if(w==width&&height==h)
            return;

        width=w;
        height=h;

        if(w==0||h==0)
        {
            is_min=true;
        }
        else
        {
            is_min=false;
        }

        SafeCallEvent(OnResize,(w,h));
    }

    void Window::ProcActive(bool a)
    {
        active=a; 
        SafeCallEvent(OnActive,(a));
    }

    void Window::ProcClose()
    { 
        is_close=true; 
        SafeCallEvent(OnClose,());
    }

    bool Window::Update()
    {
        while(MessageProc());

        if(is_close)
            return(false);

//        if(!active||is_min)
        if(is_min)
            this->WaitMessage();

        return(true);
    }
}//namespace hgl
