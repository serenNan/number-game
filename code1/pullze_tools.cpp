#include "pullze.h"
#include <Windows.h>
#include <iostream>

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
  ���������GameParams& params - ��Ϸ����
  �� �� ֵ��bool - �Ƿ�ɹ���ȡ����
  ˵    ������ȡ�û��������Ϸ����
***************************************************************************/
bool get_game_params(GameParams &params)
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
        params.rows = params.cols = 5;
        break;
    case 2:
        params.rows = params.cols = 10;
        break;
    case 3:
        params.rows = params.cols = 15;
        break;
    }

    return true;
}

/***************************************************************************
  �������ƣ�play_game_text_mode
  ��    �ܣ��ı�ģʽ�µ���Ϸ��ѭ��
  ���������GameMatrix& matrix - ��Ϸ����
            GameParams& params - ��Ϸ����
  �� �� ֵ����
  ˵    �����ı�ģʽ�µ�������Ϸ����
***************************************************************************/
void play_game_text_mode(GameMatrix &matrix, GameParams &params)
{
    bool game_over = false;

    // Ĭ�Ϲر�����ģʽ
    params.cheat_mode = false;

    // ������ʾ�û���ǵ���ʱ����
    int marked[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = {0};

    while (!game_over)
    {
        // ��ʾ��Ϸ����
        cct_cls();

        cout << "��Ϸ������..." << endl;

        // ��������ʾ�������
        int maxRowHintWidth = 0;
        char tempStr[MAX_MATRIX_SIZE * 4] = "";
        for (int i = 0; i < params.rows; i++)
        {
            char hint_str[MAX_MATRIX_SIZE * 4] = "";
            char temp[8];
            for (int h = 0; h < matrix.row_hint_count[i]; h++)
            {
                if (h > 0)
                    strcat(hint_str, " ");
                sprintf(temp, "%d", matrix.row_hints[i][h]);
                strcat(hint_str, temp);
            }
            maxRowHintWidth = max(maxRowHintWidth, (int)strlen(hint_str));
        }

        // ��������ʾ�����߶�
        int maxColHintHeight = 0;
        for (int j = 0; j < params.cols; j++)
        {
            maxColHintHeight = max(maxColHintHeight, matrix.col_hint_count[j]);
        }

        // ��ӡ�����߿�
        for (int i = 0; i < maxRowHintWidth + 2; ++i)
        {
            cout << '-';
        }
        cout << "--+"; // ��������ʼ�߿�
        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << "-+"; // ÿ5�зָ���
            cout << "--";     // ����
        }
        cout << "-+" << endl; // �Ҳ�����߿�

        // ��ӡ����ʾ�����¶��룩
        for (int h = 0; h < maxColHintHeight; h++)
        {
            // ����ʾ����������
            cout << setw(maxRowHintWidth + 5) << "  |";

            // ��ӡ����ʾ���¶��룩
            for (int j = 0; j < params.cols; j++)
            {
                if (j > 0 && j % 5 == 0)
                    cout << " |"; // ÿ5�зָ���
                int index = matrix.col_hint_count[j] - maxColHintHeight + h;
                if (index >= 0 && index < matrix.col_hint_count[j])
                {
                    cout << setw(2) << matrix.col_hints[j][index];
                }
                else
                {
                    cout << "  ";
                }
            }
            cout << " |" << endl;
        }

        // ��ӡ���񶥲��߿�
        for (int i = 0; i < maxRowHintWidth + 2; ++i)
        {
            cout << '-';
        }
        cout << "--+";
        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << "-+";
            cout << "--";
        }
        cout << "-+" << endl;

        // ��ӡ�б�ǩ��
        cout << setw(maxRowHintWidth + 2) << " " << "  |";
        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << " |";
            cout << " " << static_cast<char>('a' + j);
        }
        cout << " |" << endl;

        // ��ӡ�б�ǩ�µķָ���
        for (int i = 0; i < maxRowHintWidth + 2; ++i)
        {
            cout << '-';
        }
        cout << "+-+";
        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << "-+";
            cout << "--";
        }
        cout << "-+" << endl;

        // ��ʾ�������ݺ�����ʾ
        for (int i = 0; i < params.rows; i++)
        {
            // ��������ʾ�ַ���
            char row_hint_str[MAX_MATRIX_SIZE * 4] = "";
            char temp[8];
            for (int h = 0; h < matrix.row_hint_count[i]; h++)
            {
                if (h > 0)
                    strcat(row_hint_str, " ");
                sprintf(temp, "%d", matrix.row_hints[i][h]);
                strcat(row_hint_str, temp);
            }

            // ��ʾ����ʾ���Ҷ���
            cout << " " << setw(maxRowHintWidth) << row_hint_str << " |"
                 << static_cast<char>('A' + i) << "|";

            // ��ʾ����
            for (int j = 0; j < params.cols; j++)
            {
                if (j > 0 && j % 5 == 0)
                    cout << " |";

                // ���ݵ�Ԫ��״̬��ʾ����
                if (matrix.cells[i][j] == EMPTY)
                {
                    if (params.cheat_mode && matrix.solution[i][j])
                    {
                        // ����ģʽ����ʾ�����λ��
                        cct_setcolor(COLOR_HBLACK, COLOR_BLACK);
                        cout << " O";
                        cct_setcolor(); // �ָ�Ĭ����ɫ
                    }
                    else
                    {
                        cout << "  "; // �հ�
                    }
                }
                else if (matrix.cells[i][j] == MARKED)
                {
                    // �û����Ϊ����
                    if (params.cheat_mode)
                    {
                        if (matrix.solution[i][j])
                        {
                            // �����ȷ
                            cct_setcolor(COLOR_BLUE, COLOR_WHITE);
                            cout << " O";
                        }
                        else
                        {
                            // ��Ǵ���
                            cct_setcolor(COLOR_RED, COLOR_WHITE);
                            cout << " O";
                        }
                    }
                    else
                    {
                        // ��ͨģʽ�µı��
                        cct_setcolor(COLOR_BLUE, COLOR_WHITE);
                        cout << " O";
                    }
                    cct_setcolor(); // �ָ�Ĭ����ɫ
                }
                else if (matrix.cells[i][j] == MARKED_NOT)
                {
                    // �û����Ϊ����
                    if (params.cheat_mode)
                    {
                        if (!matrix.solution[i][j])
                        {
                            // �����ȷ
                            cct_setcolor(COLOR_RED, COLOR_WHITE);
                            cout << " X";
                        }
                        else
                        {
                            // ��Ǵ���
                            cct_setcolor(COLOR_BLUE, COLOR_WHITE);
                            cout << " X";
                        }
                    }
                    else
                    {
                        // ��ͨģʽ�µı��
                        cct_setcolor(COLOR_RED, COLOR_WHITE);
                        cout << " X";
                    }
                    cct_setcolor(); // �ָ�Ĭ����ɫ
                }
            }
            cout << " |" << endl;

            // ÿ5�����һ���ָ���
            if ((i + 1) % 5 == 0 && i < params.rows - 1)
            {
                for (int i = 0; i < maxRowHintWidth + 2; ++i)
                {
                    cout << '-';
                }
                cout << "+-+";
                for (int j = 0; j < params.cols; j++)
                {
                    if (j > 0 && j % 5 == 0)
                        cout << "-+";
                    cout << "--";
                }
                cout << "-+" << endl;
            }
        }

        // ��ʾ�ײ��߿�
        for (int i = 0; i < maxRowHintWidth + 2; ++i)
        {
            cout << '-';
        }
        cout << "+-+";
        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << "-+";
            cout << "--";
        }
        cout << "-+" << endl;

        // ��ʾ��ǰ����ģʽ״̬�Ͳ���˵��
        cout << "��ǰ" << (params.cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ" << endl << endl;
        cout << "����˵����" << endl;
        cout << "  Aa  - ���λ��(A��a��)Ϊ�����ٴ�������ͬλ����ȡ�����" << endl;
        cout << "  Aa# - ���λ��(A��a��)Ϊ�����ٴ�������ͬλ����ȡ�����" << endl;
        cout << "  X/x - �˳���Ϸ" << endl;
        cout << "  Y/y - �ύ��" << endl;
        cout << "  Z/z - �л�����ģʽ" << endl;

        // �û�����
        cout << "\n���������";
        char cmd[64];
        cin.getline(cmd, 64);

        // ������������
        if (strlen(cmd) == 0)
        {
            continue; // ���������
        }
        else if (strlen(cmd) == 1)
        {
            char c = toupper(cmd[0]);
            if (c == 'X')
            {
                game_over = true; // �˳�
                continue;
            }
            else if (c == 'Y')
            {
                // �ύ��
                int error_row, error_col;
                if (validate_solution(matrix, params, error_row, error_col))
                {
                    cout << "\n��ϲ����Ľ����ȷ��" << endl;
                    game_over = true;
                    system("pause");
                    continue;
                }
                else
                {
                    cout << "\n�����󣬵�һ������λ�ã�" << (char)('A' + error_row)
                         << (char)('a' + error_col) << " (" << error_row + 1 << "," << error_col + 1
                         << ")" << endl;
                    system("pause");
                    continue;
                }
            }
            else if (c == 'Z')
            {
                // �л�����ģʽ
                params.cheat_mode = !params.cheat_mode;
                cout << "\n��" << (params.cheat_mode ? "����" : "�ر�") << "����ģʽ" << endl;
                system("pause");
                continue;
            }
        }
        else if (strlen(cmd) >= 2)
        {
            // ������������
            char row_char = cmd[0];
            char col_char = cmd[1];

            // ����Ƿ�Ϊ��Ч�����б�ʶ
            if (row_char >= 'A' && row_char < 'A' + params.rows && col_char >= 'a' &&
                col_char < 'a' + params.cols)
            {
                int row = row_char - 'A';
                int col = col_char - 'a';

                // ����Ƿ�Ϊ�����������
                bool mark_empty = (strlen(cmd) > 2 && cmd[2] == '#');

                // ���±��
                if (mark_empty)
                {
                    // ���Ϊ�����ȡ�����
                    if (matrix.cells[row][col] == MARKED_NOT)
                        matrix.cells[row][col] = EMPTY; // ȡ�����
                    else
                        matrix.cells[row][col] = MARKED_NOT; // ���Ϊ����
                }
                else
                {
                    // ���Ϊ�����ȡ�����
                    if (matrix.cells[row][col] == MARKED)
                        matrix.cells[row][col] = EMPTY; // ȡ�����
                    else if (matrix.cells[row][col] == EMPTY ||
                             matrix.cells[row][col] == MARKED_NOT)
                        matrix.cells[row][col] = MARKED; // ���Ϊ����
                }

                continue;
            }
        }

        // ��Ч����
        cout << "\n��Ч���������" << endl;
        system("pause");
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
void play_game_graphic_mode(GameMatrix &matrix, GameParams &params)
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
    params.cheat_mode = false;

    // �������
    cct_enable_mouse();

    // ���Ƴ�ʼ��Ϸ����
    display_game_graphic(matrix, params);

    // ������ײ�λ��
    int cell_width = params.has_separators ? 5 : 2;
    int cell_height = params.has_separators ? 3 : 1;
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;
    int matrix_height = params.has_separators ? params.rows * 3 + 1 : params.rows + 2;
    int matrix_y = 3 + hint_height;
    int bottom_y = matrix_y + matrix_height + 2;

    // ��ʾ������ʾ
    cct_setcolor();
    cct_gotoxy(0, bottom_y);
    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���Z���л�����ģʽ"
         << endl;
    cct_gotoxy(0, bottom_y + 1);
    cout << "��ǰ" << (params.cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ" << endl;

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

                // ��ʾ���λ����Ϣ
                display_mouse_position(mx, my, params);

                // ת���������Ϊ����Ԫ������
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

                // ��ʾ��Ԫ����Ϣ
                cct_gotoxy(0, bottom_y + 2);
                if (is_valid)
                {
                    cout << "��ǰ��Ԫ��: " << (char)('A' + row) << (char)('a' + col) << " ("
                         << row + 1 << "," << col + 1 << ")           ";
                }
                else
                {
                    cout << "��ǰλ��: ������Ч��Ԫ����                     ";
                }
            }

            // ����������¼�
            if (btn != 0)
            {
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

                if (is_valid)
                {
                    // ������Ϊ�����Ҽ����Ϊ����
                    if (btn & FROM_LEFT_1ST_BUTTON_PRESSED)
                    {
                        // ������ - ���Ϊ����
                        if (matrix.cells[row][col] == EMPTY || matrix.cells[row][col] == MARKED_NOT)
                        {
                            matrix.cells[row][col] = MARKED;
                        }
                        else if (matrix.cells[row][col] == MARKED)
                        {
                            // ����Ѿ���ǣ���ȡ�����
                            matrix.cells[row][col] = EMPTY;
                        }
                    }
                    else if (btn & RIGHTMOST_BUTTON_PRESSED)
                    {
                        // �Ҽ���� - ���Ϊ����
                        if (matrix.cells[row][col] == EMPTY || matrix.cells[row][col] == MARKED ||
                            matrix.cells[row][col] == MARKED_WRONG)
                        {
                            matrix.cells[row][col] = MARKED_NOT;
                        }
                        else if (matrix.cells[row][col] == MARKED_NOT)
                        {
                            // ����Ѿ����Ϊ������ȡ�����
                            matrix.cells[row][col] = EMPTY;
                        }
                    }

                    // ˢ����Ϸ����
                    display_game_graphic(matrix, params);

                    // ������ʾ������ʾ
                    cct_setcolor();
                    cct_gotoxy(0, bottom_y);
                    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���Z��"
                            "�л�����ģʽ"
                         << endl;
                    cct_gotoxy(0, bottom_y + 1);
                    cout << "��ǰ" << (params.cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ"
                         << endl;
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
                    // �л�����ģʽ
                    params.cheat_mode = !params.cheat_mode;

                    // ˢ����Ϸ����
                    display_game_graphic(matrix, params);

                    // ��ʾģʽ�л���ʾ
                    cct_setcolor();
                    cct_gotoxy(0, bottom_y);
                    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���Z��"
                            "�л�����ģʽ"
                         << endl;
                    cct_gotoxy(0, bottom_y + 1);
                    cout << "��ǰ" << (params.cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ"
                         << endl;
                    cct_gotoxy(0, bottom_y + 2);
                    cout << (params.cheat_mode ? "�ѿ���" : "�ѹر�")
                         << "����ģʽ                   " << endl;
                    Sleep(500);
                }
                else if (keycode1 == '\r')
                {
                    // ��֤���
                    int error_row, error_col;
                    if (validate_solution(matrix, params, error_row, error_col))
                    {
                        // �����ȷ
                        cct_gotoxy(0, bottom_y + 3);
                        cout << "��ϲ����Ľ����ȷ��" << endl;
                        game_over = true;
                        system("pause");
                    }
                    else
                    {
                        // �����󣬸�����ʾ����λ��
                        cct_gotoxy(0, bottom_y + 3);
                        cout << "�����󣬵�һ������λ�ã�" << (char)('A' + error_row)
                             << (char)('a' + error_col) << " (" << error_row + 1 << ","
                             << error_col + 1 << ")      " << endl;

                        // �������λ�õ���Ļ����
                        int matrix_x = 5 + hint_width;
                        int matrix_y = 3 + hint_height;

                        // ��˸��ʾ����λ��
                        for (int i = 0; i < 3; i++)
                        {
                            int x = matrix_x + error_col * cell_width;
                            int y = matrix_y + error_row * cell_height;

                            // ��������Ԫ������λ��
                            if (params.has_separators)
                            {
                                x += 2; // ��Ԫ������
                                y += 1; // ��Ԫ������
                            }
                            else
                            {
                                x += 1; // ��Ԫ������
                                y += 0; // ��Ԫ������
                            }

                            // ��˸��ʾ������
                            cct_gotoxy(x, y);
                            cct_setcolor(COLOR_WHITE, COLOR_RED);
                            cout << "X";
                            Sleep(300);
                            cct_gotoxy(x, y);
                            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                            cout << " ";
                            Sleep(300);
                        }

                        // �ָ���Ϸ����
                        display_game_graphic(matrix, params);
                        cct_setcolor();
                        cct_gotoxy(0, bottom_y);
                        cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���"
                                "Z���л�����ģʽ"
                             << endl;
                        cct_gotoxy(0, bottom_y + 1);
                        cout << "��ǰ" << (params.cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ"
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
void show_mouse_position_mode(GameMatrix &matrix, GameParams &params)
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
    params.cheat_mode = true;

    // �������
    cct_enable_mouse();

    // ���Ƴ�ʼ��Ϸ����
    display_game_graphic(matrix, params);

    // ������ײ�λ��
    int cell_width = params.has_separators ? 5 : 2;
    int cell_height = params.has_separators ? 3 : 1;
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;
    int matrix_height = params.has_separators ? params.rows * 3 + 1 : params.rows + 2;
    int matrix_y = 3 + hint_height;
    int bottom_y = matrix_y + matrix_height + 2;

    // ��ʾ������ʾ
    cct_setcolor();
    cct_gotoxy(0, bottom_y);
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

            // ֻ������仯ʱˢ����ʾ��������˸
            if (mx != last_mx || my != last_my)
            {
                last_mx = mx;
                last_my = my;

                // ��ʾ���λ����Ϣ
                display_mouse_position(mx, my, params);

                // ת���������Ϊ����Ԫ������
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

                // ��ʾ��Ԫ����Ϣ
                cct_gotoxy(0, bottom_y + 2);
                if (is_valid)
                {
                    cout << "��ǰ��Ԫ��: " << (char)('A' + row) << (char)('a' + col) << " ("
                         << row + 1 << "," << col + 1 << ")           ";

                    // ��ʾ��Ԫ��������Ϣ
                    cout << " | ����: ";
                    if (matrix.solution[row][col])
                    {
                        cout << "����";
                    }
                    else
                    {
                        cout << "����";
                    }
                }
                else
                {
                    cout << "��ǰλ��: ������Ч��Ԫ����                     ";
                }
            }

            // ����������¼�
            if (btn != 0)
            {
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

                if (is_valid)
                {
                    cct_gotoxy(0, bottom_y + 3);
                    cout << "��⵽���: λ��=" << (char)('A' + row) << (char)('a' + col)
                         << " ����=" << (matrix.solution[row][col] ? "����" : "����") << "      ";
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
