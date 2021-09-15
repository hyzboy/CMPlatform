#ifndef HGL_INPUT_DEVICE_INCLUDE
#define HGL_INPUT_DEVICE_INCLUDE

#include<hgl/TypeFunc.h>
namespace hgl
{
    /**
    * 鼠标状态枚举定义
    */
    enum MouseButton
    {
        mbMove              =0x00000001,    ///<鼠标移动了

        mbLeft              =0x00000002,    ///<鼠标左键处于按下状态
        mbMid               =0x00000004,    ///<鼠标中键处于按下状态
        mbRight             =0x00000008,    ///<鼠标右键处于按下状态

        mbX1                =0x00000010,
        mbX2                =0x00000020,

        mbShift             =0x10000000,    ///<Shift键处于按下状态
        mbCtrl              =0x20000000,    ///<Ctrl键处于按下状态
    };

    /**
    * 按键枚举定义
    */
    enum class KeyboardButton
    {
        NONE=0,
                            //主键盘区
        Esc,                ///<ESC

                            //F功能键
        F1,                 ///<F1
        F2,                 ///<F2
        F3,                 ///<F3
        F4,                 ///<F4
        F5,                 ///<F5
        F6,                 ///<F6
        F7,                 ///<F7
        F8,                 ///<F8
        F9,                 ///<F9
        F10,                ///<F10
        F11,                ///<F11
        F12,                ///<F12

        Grave,              //<`号(主键盘数字键1左边的按钮)

                            //10个数字
        _0,                 ///<数字键0
        _1,                 ///<数字键1
        _2,                 ///<数字键2
        _3,                 ///<数字键3
        _4,                 ///<数字键4
        _5,                 ///<数字键5
        _6,                 ///<数字键6
        _7,                 ///<数字键7
        _8,                 ///<数字键8
        _9,                 ///<数字键9

        Minus,              ///< - (减号)
        Equals,             ///< = (等号)
        BackSlash,          ///< \ (反斜杠)
        BackSpace,          ///< 退格键

        Tab,                ///<Tab键

        A,                  ///<A
        B,                  ///<B
        C,                  ///<C
        D,                  ///<D
        E,                  ///<E
        F,                  ///<F
        G,                  ///<G
        H,                  ///<H
        I,                  ///<I
        J,                  ///<J
        K,                  ///<K
        L,                  ///<L
        M,                  ///<M
        N,                  ///<N
        O,                  ///<O
        P,                  ///<P
        Q,                  ///<Q
        R,                  ///<R
        S,                  ///<S
        T,                  ///<T
        U,                  ///<U
        V,                  ///<V
        W,                  ///<W
        X,                  ///<X
        Y,                  ///<Y
        Z,                  ///<Z

        LeftBracket,        ///<[
        RightBracket,       ///<]

        CapsLock,           ///<大写锁定键

        Semicolon,          ///<; (分号)
        Apostrophe,         ///<' (单引号)
        Enter,              ///<回车键

        LeftShift,          ///<左边的Shift键

        Comma,              ///<, (逗号)
        Period,             ///<. (句号)
        Slash,              ///</ (除号)
        RightShift,         ///<右边的Shift键

        LeftCtrl,           ///<左边的Ctrl键
        LeftOS,             ///<左边的OS键(Win/Apple键)
        LeftAlt,            ///<左边的Alt键
        Space,              ///<空格键
        RightAlt,           ///<右边的Alt键
        RightOS,            ///<右边的OS键(Win/Apple键)
        RightMenu,          ///<右边的Menu键
        RightCtrl,          ///<右边的Ctrl键

                            //中键盘区
        PrintScreen,        ///<打印屏幕键
        ScrollLock,         ///<滚动锁定键
        Pause,              ///<暂停键

        Insert,             ///<插入键
        Delete,             ///<删除键
        Home,               ///<行首键
        End,                ///<行尾键
        PageUp,             ///<向前翻页键
        PageDown,           ///<向后翻页键

        Up,                 ///<↑光标键
        Down,               ///<↓光标键
        Left,               ///<←光标键
        Right,              ///<→光标键

                            //小键盘区
        NumLock,            ///<小键盘 数字锁定键

        NumAdd,             ///<小键盘 +
        NumSubtract,        ///<小键盘 -
        NumMultiply,        ///<小键盘 *
        NumDivide,          ///<小键盘 /

        Num0,               ///<小键盘 0
        Num1,               ///<小键盘 1
        Num2,               ///<小键盘 2
        Num3,               ///<小键盘 3
        Num4,               ///<小键盘 4
        Num5,               ///<小键盘 5
        Num6,               ///<小键盘 6
        Num7,               ///<小键盘 7
        Num8,               ///<小键盘 8
        Num9,               ///<小键盘 9

        NumDecimal,         ///<小键盘 . (小数点/删除键)
        NumEnter,           ///<小键盘 回车键

        ENUM_CLASS_RANGE(NONE,NumEnter)
    };//enum KeyboardButton

    /**
    * 手柄按键枚举
    */
    enum class JoystickButton
    {
        NONE=0,

        Up,
        Down,
        Left,
        Right,

        _0,        _1,        _2,        _3,        _4,        _5,        _6,        _7,
        _8,        _9,        _10,       _11,       _12,       _13,       _14,       _15,
        _16,       _17,       _18,       _19,       _20,       _21,       _22,       _23,
        _24,       _25,       _26,       _27,       _28,       _29,       _30,       _31,

        ENUM_CLASS_RANGE(NONE,_31)
    };

    enum class PlayStationButton
    {
        Up          =JoystickButton::Up,
        Down        =JoystickButton::Down,
        Left        =JoystickButton::Left,
        Right       =JoystickButton::Right,

        Fork        =JoystickButton::_0,           // 叉
        Circle      =JoystickButton::_1,           // 圆
        Square      =JoystickButton::_2,           // 方
        Triangle    =JoystickButton::_3,           // 三角

        L1          =JoystickButton::_6,       L2        =JoystickButton::_4,
        R1          =JoystickButton::_7,       R2        =JoystickButton::_5,
        Select      =JoystickButton::_8,       Start     =JoystickButton::_9,
    };

    //enum class XBoxButton
    //{
    //    //DreamCast/XBOX
    //    X=JoystickButton::_2,
    //    Y=JoystickButton::_3,
    //    A=JoystickButton::_0,
    //    B=JoystickButton::_1,
    //    L=JoystickButton::_4,
    //    R=JoystickButton::_5,

    //    //XBOX/XBOX360
    //    //XBOX,                     //西瓜键
    //};
}//namespace hgl
#endif//HGL_INPUT_DEVICE_INCLUDE
