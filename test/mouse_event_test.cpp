#include <iostream>
#include <windows.h>

int main()
{
    // 获取标准输入句柄
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hInput, &mode);

    // 关闭快速编辑模式，启用鼠标输入和扩展标志
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hInput, mode);

    std::cout << "请在cmd窗口内移动鼠标或点击，按ESC键退出。" << std::endl;

    INPUT_RECORD ir;
    DWORD read;
    while (true)
    {
        ReadConsoleInput(hInput, &ir, 1, &read);
        if (ir.EventType == MOUSE_EVENT)
        {
            auto &me = ir.Event.MouseEvent;
            // 鼠标移动
            if (me.dwEventFlags == MOUSE_MOVED)
            {
                std::cout << "鼠标移动到: X=" << me.dwMousePosition.X
                          << " Y=" << me.dwMousePosition.Y << std::endl;
            }
            // 鼠标按下
            if (me.dwButtonState != 0)
            {
                std::cout << "鼠标点击: X=" << me.dwMousePosition.X << " Y=" << me.dwMousePosition.Y
                          << std::endl;
            }
        }
        else if (ir.EventType == KEY_EVENT)
        {
            // 按下ESC键退出
            if (ir.Event.KeyEvent.bKeyDown && ir.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
            {
                std::cout << "检测到ESC，程序退出。" << std::endl;
                break;
            }
        }
        else
        {
            // 其他事件类型调试输出
            std::cout << "捕获到其他事件: " << ir.EventType << std::endl;
        }
    }
    return 0;
}