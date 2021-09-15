#include<hgl/platform/Window.h>

namespace hgl
{
    void Window::ProcKeyPressed(KeyboardButton kb)
    {
        if(key_push[size_t(kb)])
            ProcKeyRepeat(kb);
        else
            key_push[size_t(kb)]=true;

       SafeCallEvent(OnKeyPressed,(kb));
    }

    void Window::ProcKeyReleased(KeyboardButton kb)
    {
        key_push[size_t(kb)]=false;

        SafeCallEvent(OnKeyReleased,(kb));
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
