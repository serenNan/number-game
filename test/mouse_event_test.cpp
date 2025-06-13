#include <iostream>
#include <windows.h>

int main()
{
    // ��ȡ��׼������
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hInput, &mode);

    // �رտ��ٱ༭ģʽ����������������չ��־
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hInput, mode);

    std::cout << "����cmd�������ƶ�����������ESC���˳���" << std::endl;

    INPUT_RECORD ir;
    DWORD read;
    while (true)
    {
        ReadConsoleInput(hInput, &ir, 1, &read);
        if (ir.EventType == MOUSE_EVENT)
        {
            auto &me = ir.Event.MouseEvent;
            // ����ƶ�
            if (me.dwEventFlags == MOUSE_MOVED)
            {
                std::cout << "����ƶ���: X=" << me.dwMousePosition.X
                          << " Y=" << me.dwMousePosition.Y << std::endl;
            }
            // ��갴��
            if (me.dwButtonState != 0)
            {
                std::cout << "�����: X=" << me.dwMousePosition.X << " Y=" << me.dwMousePosition.Y
                          << std::endl;
            }
        }
        else if (ir.EventType == KEY_EVENT)
        {
            // ����ESC���˳�
            if (ir.Event.KeyEvent.bKeyDown && ir.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
            {
                std::cout << "��⵽ESC�������˳���" << std::endl;
                break;
            }
        }
        else
        {
            // �����¼����͵������
            std::cout << "���������¼�: " << ir.EventType << std::endl;
        }
    }
    return 0;
}