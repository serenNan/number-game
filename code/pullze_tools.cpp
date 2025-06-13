#include "pullze.h"
#include <Windows.h>
#include <cstdio>
#include <cstring>
#include <iostream>

/***************************************************************************
  �������ƣ�print_repeated_char
  ��    �ܣ���ӡ�ظ����ַ�
  ���������char ch - Ҫ�ظ����ַ�
            int count - �ظ�����
  �� �� ֵ����
  ˵    ������� string(count, ch) �Ĺ���
***************************************************************************/
void print_repeated_char(char ch, int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << ch;
    }
}

/***************************************************************************
  �������ƣ�show_menu
  ��    �ܣ���ʾ��Ϸ�˵�����ȡ�û�ѡ��
  �����������
  �� �� ֵ��int - �û�ѡ��Ĳ˵���
  ˵    ������ʾ�˵��������û�ѡ��
***************************************************************************/
int show_menu()
{
    int choice = 0;
    char ch;

    cct_cls();
    cct_setcolor();

    cout << "---------------------------------------------------------" << endl;
    cout << " A.�ڲ����飬ԭ�����" << endl;
    cout << " B.�ڲ����飬������ʾ���в����" << endl;
    cout << " C.�ڲ����飬��Ϸ��" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " D.n*n�Ŀ��(�޷ָ���)��ԭ�����" << endl;
    cout << " E.n*n�Ŀ��(�޷ָ���)������ʾ����" << endl;
    cout << " F.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬������ƶ�����ʾ����" << endl;
    cout << " G.cmdͼ�ν���������(�޷ָ���)" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " H.n*n�Ŀ��(�зָ���)��ԭ�����" << endl;
    cout << " I.n*n�Ŀ��(�зָ���)������ʾ����" << endl;
    cout << " J.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬������ƶ�����ʾ����" << endl;
    cout << " K.cmdͼ�ν���������(�зָ���)" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " Q.�˳�" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "[��ѡ��:]  ";

    while (1)
    {
        ch = _getch();

        if (ch >= 'a' && ch <= 'k')
            ch = ch - 'a' + 'A';

        if (ch == 'A')
            choice = 1;
        else if (ch == 'B')
            choice = 2;
        else if (ch == 'C')
            choice = 3;
        else if (ch == 'D')
            choice = 4;
        else if (ch == 'E')
            choice = 5;
        else if (ch == 'F')
            choice = 6;
        else if (ch == 'G')
            choice = 7;
        else if (ch == 'H')
            choice = 8;
        else if (ch == 'I')
            choice = 9;
        else if (ch == 'J')
            choice = 10;
        else if (ch == 'K')
            choice = 11;
        else if (ch == 'Q' || ch == 'q')
            choice = 0;
        else
            continue;

        cout << ch << endl;
        break;
    }

    return choice;
}

/***************************************************************************
  �������ƣ�get_game_params
  ��    �ܣ���ȡ��Ϸ����
  �����������
  �� �� ֵ��bool - �Ƿ�ɹ���ȡ����
  ˵    ������ȡ�û��������Ϸ����
***************************************************************************/
bool get_game_params()
{
    cct_cls();
    int choice = 0;
    char ch;

    cout << "��ѡ����Ϸ��С��" << endl;
    cout << "1. 5��5" << endl;
    cout << "2. 10��10" << endl;
    cout << "3. 15��15" << endl;
    cout << "��ѡ��[1-3]��";

    while (1)
    {
        ch = _getch();

        if (ch >= '1' && ch <= '3')
        {
            choice = ch - '0';
            cout << ch << endl;
            break;
        }
    }

    switch (choice)
    {
    case 1:
        g_rows = g_cols = 5;
        break;
    case 2:
        g_rows = g_cols = 10;
        break;
    case 3:
        g_rows = g_cols = 15;
        break;
    }

    return true;
}

/***************************************************************************
  �������ƣ�play_game_text_mode
  ��    �ܣ��ı�ģʽ�µ���Ϸ��ѭ��
  �����������
  �� �� ֵ����
  ˵    �����ı�ģʽ�µ�������Ϸ����
***************************************************************************/
void play_game_text_mode()
{
    bool game_over = false;

    // Ĭ�Ϲر�����ģʽ
    g_cheat_mode = false;

    while (!game_over)
    {
        // ��ʾ��Ϸ����
        cct_cls();

        cout << "��ʼ���飺" << endl;

        // ��������ʾ���������
        int max_row_hints = 0;
        for (int i = 0; i < g_rows; i++)
        {
            if (g_row_hint_count[i] > max_row_hints)
            {
                max_row_hints = g_row_hint_count[i];
            }
        }

        // ����ÿ������ʾռ�õĿ�ȣ�ÿ������2���ַ�������+�ո�
        int hint_width = max_row_hints * 2;

        // ��ʾ�����߿�
        print_repeated_char('-', hint_width + 1);
        cout << "+-----------+-----------+" << endl;

        // ��������ʾ�����߶�
        int max_col_hints = 0;
        for (int j = 0; j < g_cols; j++)
        {
            if (g_col_hint_count[j] > max_col_hints)
            {
                max_col_hints = g_col_hint_count[j];
            }
        }

        // ��ʾ����ʾ���������£�
        for (int h = 0; h < max_col_hints; h++)
        {
            print_repeated_char(' ', hint_width + 1);
            cout << "|";

            // ��һ��5��
            for (int j = 0; j < 5; j++)
            {
                if (j < g_cols && h < g_col_hint_count[j])
                {
                    cout << " " << g_col_hints[j][h];
                }
                else
                {
                    cout << "  ";
                }
            }

            cout << " |";

            // �ڶ���5��
            for (int j = 5; j < 10; j++)
            {
                if (j < g_cols && h < g_col_hint_count[j])
                {
                    cout << " " << g_col_hints[j][h];
                }
                else
                {
                    cout << "  ";
                }
            }

            cout << " |" << endl;
        }

        // ��ʾ�ָ���
        print_repeated_char('-', hint_width + 1);
        cout << "+-----------+-----------+" << endl;

        // ��ʾ�б���
        print_repeated_char(' ', hint_width + 1);
        cout << "|";

        // ��һ��5��
        for (int j = 0; j < 5; j++)
        {
            if (j < g_cols)
            {
                cout << " " << (char)('a' + j);
            }
            else
            {
                cout << "  ";
            }
        }

        cout << " |";

        // �ڶ���5��
        for (int j = 5; j < 10; j++)
        {
            if (j < g_cols)
            {
                cout << " " << (char)('a' + j);
            }
            else
            {
                cout << "  ";
            }
        }

        cout << " |" << endl;

        // ��ʾ����ʾ����;���ķָ���
        for (int i = 0; i < hint_width - 1; i++)
        {
            cout << "-";
        }
        cout << "---+-+-----------+-----------+" << endl;

        // ��ʾ�������ݺ�����ʾ
        for (int i = 0; i < g_rows; i++)
        {
            // ��ʾ����ʾ���Ҷ���
            char row_hint_str[MAX_STR_LEN] = "";
            int pos = 0;
            for (int h = 0; h < g_row_hint_count[i]; h++)
            {
                // ������ת��Ϊ�ַ�������ӵ�row_hint_str
                char num_str[10];
                sprintf(num_str, "%d ", g_row_hints[i][h]);
                strcat(row_hint_str, num_str);
            }

            // ȷ������ʾ������һ��
            int hint_len = strlen(row_hint_str);
            int spaces = hint_width - hint_len;
            if (spaces > 0)
            {
                print_repeated_char(' ', spaces);
            }
            cout << row_hint_str << " |";

            // ��ʾ�б��⣨A,B,C,...��
            cout << (char)('A' + i) << "|";

            // ��һ��5��
            for (int j = 0; j < 5; j++)
            {
                if (j < g_cols)
                {
                    if (g_cells[i][j] == EMPTY)
                    {
                        if (g_cheat_mode && g_solution[i][j])
                        {
                            cout << " O"; // ����ģʽ��ʾ��ͨ��O
                        }
                        else
                            cout << "  ";
                    }
                    else if (g_cells[i][j] == MARKED)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HGREEN); // �û����Ϊ��ɫ����
                        cout << " O";
                        cct_setcolor(); // �ָ�Ĭ����ɫ
                    }
                    else if (g_cells[i][j] == MARKED_WRONG)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HRED); // ������Ϊ��ɫ����
                        cout << " X";
                        cct_setcolor(); // �ָ�Ĭ����ɫ
                    }
                    else if (g_cells[i][j] == MARKED_NOT)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HBLUE); // ���Ϊ������Ϊ��ɫ����
                        cout << " ��";
                        cct_setcolor(); // �ָ�Ĭ����ɫ
                    }
                }
                else
                {
                    cout << "  ";
                }
            }

            cout << " |";

            // �ڶ���5��
            for (int j = 5; j < 10; j++)
            {
                if (j < g_cols)
                {
                    if (g_cells[i][j] == EMPTY)
                    {
                        if (g_cheat_mode && g_solution[i][j])
                        {
                            cout << " O"; // ����ģʽ��ʾ��ͨ��O
                        }
                        else
                            cout << "  ";
                    }
                    else if (g_cells[i][j] == MARKED)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HGREEN); // �û����Ϊ��ɫ����
                        cout << " O";
                        cct_setcolor(); // �ָ�Ĭ����ɫ
                    }
                    else if (g_cells[i][j] == MARKED_WRONG)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HRED); // ������Ϊ��ɫ����
                        cout << " X";
                        cct_setcolor(); // �ָ�Ĭ����ɫ
                    }
                    else if (g_cells[i][j] == MARKED_NOT)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HBLUE); // ���Ϊ������Ϊ��ɫ����
                        cout << " ��";
                        cct_setcolor(); // �ָ�Ĭ����ɫ
                    }
                }
                else
                {
                    cout << "  ";
                }
            }

            cout << " |" << endl;

            // ÿ5�����һ���ָ���
            if ((i + 1) % 5 == 0 && i < g_rows - 1)
            {
                for (int k = 0; k < hint_width - 1; k++)
                {
                    cout << "-";
                }
                cout << "---+-+-----------+-----------+" << endl;
            }
        }

        // ��ʾ�ײ��߿�
        for (int i = 0; i < hint_width - 1; i++)
        {
            cout << "-";
        }
        cout << "---+-+-----------+-----------+" << endl;

        // ��ʾ��ǰ����ģʽ״̬
        cout << "��ǰ" << (g_cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ" << endl;

        // �û�����
        cout << "\n������ʽ��Aa=�ȼ���ͼ����Ϸ��������ѡ��Aaλ(���ִ�Сд)" << endl;
        cout << "         ����Ҫ֧��ͼ�ν�����Ҽ���棬�ٴ�����Aa�൱�����" << endl;
        cout << "         X/x=�˳�(���н���X/x�����ִ�Сд)" << endl;
        cout << "         Y/y=�ύ(���н���Y/y�����ִ�Сд)" << endl;
        cout << "         Z/z=����(���н���Z/z�����ִ�Сд)" << endl;
        cout << "�������";
        char input[10];
        cin >> input;

        // �������
        if ((input[0] == 'X' || input[0] == 'x') && input[1] == '\0')
        {
            game_over = true;
        }
        else if ((input[0] == 'Y' || input[0] == 'y') && input[1] == '\0')
        {
            // ��֤���
            int error_row, error_col;
            if (validate_solution(error_row, error_col))
            {
                cout << "��ϲ����Ľ����ȷ��" << endl;
                game_over = true;
            }
            else
            {
                // ��ʾ����λ��
                cout << "�����󣡵�һ������λ���ڣ�" << (char)('A' + error_row)
                     << (char)('a' + error_col) << endl;
                system("pause");
            }
        }
        else if ((input[0] == 'Z' || input[0] == 'z') && input[1] == '\0')
        {
            // �л�����ģʽ
            g_cheat_mode = !g_cheat_mode;
            cout << (g_cheat_mode ? "�ѿ���" : "�ѹر�") << "����ģʽ" << endl;
            system("pause");
        }
        else if (input[0] >= 'A' && input[0] <= 'A' + g_rows - 1 && input[1] >= 'a' &&
                 input[1] <= 'a' + g_cols - 1)
        {
            // ��������
            int row = input[0] - 'A';
            int col = input[1] - 'a';

            // ���������Ч��
            if (row >= 0 && row < g_rows && col >= 0 && col < g_cols)
            {
                // ��ǻ�ȡ�����
                mark_cell(row, col, 1);
            }
        }
    }
}

/***************************************************************************
  �������ƣ�play_game_graphic_mode
  ��    �ܣ�ͼ��ģʽ�µ���Ϸ��ѭ��
  ���������GameMatrix& matrix - ��Ϸ����
            GameParams& params - ��Ϸ����
  �� �� ֵ����
  ˵    ����ͼ��ģʽ�µ�������Ϸ����
***************************************************************************/
void play_game_graphic_mode()
{
    // ����Win11��ȷ������¼��ܱ�����
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hInput, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hInput, mode);

    bool game_over = false;
    int last_mx = -1, last_my = -1;

    // Ĭ�Ϲر�����ģʽ
    g_cheat_mode = false;

    // �������
    cct_enable_mouse();

    // ���Ƴ�ʼ��Ϸ����
    display_game_graphic();

    // ��ʾ������ʾ
    cct_setcolor();
    cct_gotoxy(0, 25);
    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���Z���л�����ģʽ"
         << endl;
    cct_gotoxy(0, 26);
    cout << "��ǰ" << (g_cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ" << endl;

    INPUT_RECORD ir;
    DWORD read;
    while (!game_over)
    {
        ReadConsoleInput(hInput, &ir, 1, &read);
        if (ir.EventType == MOUSE_EVENT)
        {
            auto &me = ir.Event.MouseEvent;
            int mx = me.dwMousePosition.X;
            int my = me.dwMousePosition.Y;
            DWORD btn = me.dwButtonState;
            DWORD evt = me.dwEventFlags;

            // ֻ������仯ʱˢ����ʾ��������˸
            if (mx != last_mx || my != last_my)
            {
                last_mx = mx;
                last_my = my;
                cct_gotoxy(0, 29);
                cout << "[DEBUG] mx=" << mx << " my=" << my << " btn=" << btn << " evt=" << evt
                     << "      ";
                display_mouse_position(mx, my);

                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, is_valid);

                if (is_valid)
                {
                    cct_gotoxy(0, 27);
                    cout << "��ǰ��Ԫ��: " << (char)('A' + row) << (col + 1) << "                ";
                }
                else
                {
                    cct_gotoxy(0, 27);
                    cout << "                                  ";
                }
            }
            // ֻҪ�а�ť���¾ʹ���Ϊ���
            if (btn != 0)
            {
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, is_valid);
                cct_gotoxy(0, 28);
                cout << "[DEBUG] btn=" << btn << " evt=" << evt << " mx=" << mx << " my=" << my
                     << " row=" << row << " col=" << col << " is_valid=" << is_valid << "      ";
                if (is_valid)
                {
                    int markType = (btn & FROM_LEFT_1ST_BUTTON_PRESSED) ? 1 : 2;
                    // ������ʾ���λ�ã���������������Ϊ�ո�
                    int cell_width = g_has_separators ? 5 : 2;
                    int cell_height = g_has_separators ? 3 : 1;
                    int hint_width = g_hint_width * 2;
                    int hint_height = g_hint_height;
                    int matrix_x = 5 + hint_width;
                    int matrix_y = 3 + hint_height;
                    int x = matrix_x + col * cell_width;
                    int y = matrix_y + row * cell_height;
                    if (g_has_separators)
                    {
                        x += 2;
                        y += 1;
                    }
                    else
                    {
                        x += 1;
                        y += 1;
                    }
                    cct_gotoxy(x, y);
                    if (btn & FROM_LEFT_1ST_BUTTON_PRESSED)
                    {
                        cct_setcolor(COLOR_HGREEN, COLOR_BLACK);
                        cout << " ";
                    }
                    else if (btn & RIGHTMOST_BUTTON_PRESSED)
                    {
                        cct_setcolor(COLOR_HRED, COLOR_BLACK);
                        cout << " ";
                    }
                    else
                    {
                        cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
                        cout << " ";
                    }
                    cct_setcolor();
                    Sleep(120);

                    // �޸ģ������ǣ��Ҽ�ֱ�����
                    if (markType == 1 && g_cells[row][col] == MARKED)
                    {
                        // �Ѿ����ΪO�������κβ���
                    }
                    else if (markType == 1)
                    {
                        mark_cell(row, col, 1);
                    }
                    else if (markType == 2)
                    {
                        g_cells[row][col] = EMPTY;
                    }

                    // ֻˢ�µ�ǰ��Ԫ����ʾ����������ģʽ����ͨģʽO����ɫ
                    cct_gotoxy(x, y);
                    if (g_cells[row][col] == MARKED && !g_cheat_mode)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HGREEN);
                        cout << "O";
                        cct_setcolor();
                    }
                    else if (g_cells[row][col] == MARKED && g_cheat_mode)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                        cout << "O";
                        cct_setcolor();
                    }
                    else
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                        cout << " ";
                        cct_setcolor();
                    }

                    cct_setcolor();
                    cct_gotoxy(0, 25);
                    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���Z��"
                            "�л�����ģʽ"
                         << endl;
                    cct_gotoxy(0, 26);
                    cout << "��ǰ" << (g_cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ" << endl;
                }
            }
        }
        else if (ir.EventType == KEY_EVENT)
        {
            if (ir.Event.KeyEvent.bKeyDown)
            {
                int keycode1 = ir.Event.KeyEvent.uChar.AsciiChar;
                if (keycode1 == 'q' || keycode1 == 'Q')
                {
                    game_over = true;
                }
                else if (keycode1 == 'z' || keycode1 == 'Z')
                {
                    g_cheat_mode = !g_cheat_mode;
                    display_game_graphic();
                    cct_setcolor();
                    cct_gotoxy(0, 25);
                    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���Z��"
                            "�л�����ģʽ"
                         << endl;
                    cct_gotoxy(0, 26);
                    cout << "��ǰ" << (g_cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ" << endl;
                    cct_gotoxy(0, 27);
                    cout << (g_cheat_mode ? "�ѿ���" : "�ѹر�") << "����ģʽ                   "
                         << endl;
                    Sleep(500);
                }
                else if (keycode1 == '\r')
                {
                    int error_row, error_col;
                    if (validate_solution(error_row, error_col))
                    {
                        cct_gotoxy(0, 28);
                        cout << "��ϲ����Ľ����ȷ��" << endl;
                        game_over = true;
                        system("pause");
                    }
                    else
                    {
                        cct_gotoxy(0, 28);
                        cout << "�����󣬵�һ������λ�ã�" << (char)('A' + error_row)
                             << (error_col + 1) << "      " << endl;
                        int cell_width = g_has_separators ? 5 : 2;
                        int cell_height = g_has_separators ? 3 : 1;
                        int hint_width = g_hint_width * 2;
                        int hint_height = g_hint_height;
                        int matrix_x = 5 + hint_width;
                        int matrix_y = 3 + hint_height;
                        for (int i = 0; i < 3; i++)
                        {
                            int x = matrix_x + error_col * cell_width;
                            int y = matrix_y + error_row * cell_height;
                            if (g_has_separators)
                            {
                                x += 2;
                                y += 1;
                            }
                            else
                            {
                                x += 1;
                                y += 1;
                            }
                            cct_gotoxy(x, y);
                            cct_setcolor(COLOR_BLACK, COLOR_HRED);
                            cout << "X";
                            Sleep(300);
                            cct_gotoxy(x, y);
                            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                            cout << " ";
                            Sleep(300);
                        }
                        display_game_graphic();
                        cct_setcolor();
                        cct_gotoxy(0, 25);
                        cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���"
                                "Z���л�����ģʽ"
                             << endl;
                        cct_gotoxy(0, 26);
                        cout << "��ǰ" << (g_cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ"
                             << endl;
                    }
                }
            }
        }
    }
    cct_disable_mouse();
}

/***************************************************************************
  �������ƣ�show_mouse_position_mode
  ��    �ܣ�ͼ��ģʽ��ֻ��ʾ���λ��
  ���������GameMatrix& matrix - ��Ϸ����
            GameParams& params - ��Ϸ����
  �� �� ֵ����
  ˵    ����Fѡ��ר�ã�ֻ��ʾ���λ�ã���������Ϸ
***************************************************************************/
void show_mouse_position_mode()
{
    // ����Win11��ȷ������¼��ܱ�����
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hInput, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hInput, mode);

    bool quit = false;
    int last_mx = -1, last_my = -1;

    // Ĭ�Ͽ�������ģʽ����ʾ���
    g_cheat_mode = true;

    // �������
    cct_enable_mouse();

    // ���Ƴ�ʼ��Ϸ����
    display_game_graphic();

    // ��ʾ������ʾ
    cct_setcolor();
    cct_gotoxy(0, 25);
    cout << "����˵�����ƶ������ʾ���꣬Q���˳�" << endl;

    INPUT_RECORD ir;
    DWORD read;
    while (!quit)
    {
        ReadConsoleInput(hInput, &ir, 1, &read);
        if (ir.EventType == MOUSE_EVENT)
        {
            auto &me = ir.Event.MouseEvent;
            int mx = me.dwMousePosition.X;
            int my = me.dwMousePosition.Y;
            DWORD btn = me.dwButtonState;
            DWORD evt = me.dwEventFlags;

            if (mx != last_mx || my != last_my)
            {
                last_mx = mx;
                last_my = my;
                cct_gotoxy(0, 29);
                cout << "[DEBUG] mx=" << mx << " my=" << my << " btn=" << btn << " evt=" << evt
                     << "      ";
                display_mouse_position(mx, my);
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, is_valid);
                if (is_valid)
                {
                    cct_gotoxy(0, 27);
                    cout << "��ǰ��Ԫ��: " << (char)('A' + row) << (col + 1) << "                ";
                }
                else
                {
                    cct_gotoxy(0, 27);
                    cout << "                                  ";
                }
            }
            // ֻҪ�а�ť���¾ʹ���Ϊ���
            if (btn != 0)
            {
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, is_valid);
                if (is_valid)
                {
                    cct_gotoxy(0, 28);
                    cout << "[DEBUG] ��⵽��� btn=" << btn << " evt=" << evt << "      ";
                }
            }
        }
        else if (ir.EventType == KEY_EVENT)
        {
            if (ir.Event.KeyEvent.bKeyDown)
            {
                int keycode1 = ir.Event.KeyEvent.uChar.AsciiChar;
                if (keycode1 == 'q' || keycode1 == 'Q')
                {
                    quit = true;
                }
            }
        }
    }
    cct_disable_mouse();
}

void debug_raw_mouse_event()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hInput, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hInput, mode);

    std::cout << "���ڴ������ƶ��������꣬��ESC�˳�\n";
    INPUT_RECORD ir;
    DWORD read;
    while (true)
    {
        ReadConsoleInput(hInput, &ir, 1, &read);
        if (ir.EventType == MOUSE_EVENT)
        {
            auto &me = ir.Event.MouseEvent;
            std::cout << "X=" << me.dwMousePosition.X << " Y=" << me.dwMousePosition.Y
                      << " ButtonState=" << me.dwButtonState << " EventFlags=" << me.dwEventFlags
                      << std::endl;
        }
        else if (ir.EventType == KEY_EVENT)
        {
            if (ir.Event.KeyEvent.bKeyDown && ir.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
            {
                std::cout << "ESC�˳�\n";
                break;
            }
        }
    }
}
