#include "pullze.h"
#include <Windows.h>

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

    while (!game_over)
    {
        // ��ʾ��Ϸ����
        cct_cls();

        cout << "��ʼ���飺" << endl;

        // ��������ʾ���������
        int max_row_hints = 0;
        for (int i = 0; i < params.rows; i++)
        {
            if (matrix.row_hint_count[i] > max_row_hints)
            {
                max_row_hints = matrix.row_hint_count[i];
            }
        }

        // ����ÿ������ʾռ�õĿ�ȣ�ÿ������2���ַ�������+�ո�
        int hint_width = max_row_hints * 2;

        // ��ʾ�����߿�
        cout << string(hint_width + 1, '-') << "+-----------+-----------+" << endl;

        // ��������ʾ�����߶�
        int max_col_hints = 0;
        for (int j = 0; j < params.cols; j++)
        {
            if (matrix.col_hint_count[j] > max_col_hints)
            {
                max_col_hints = matrix.col_hint_count[j];
            }
        }

        // ��ʾ����ʾ���������£�
        for (int h = 0; h < max_col_hints; h++)
        {
            cout << string(hint_width + 1, ' ') << "|";

            // ��һ��5��
            for (int j = 0; j < 5; j++)
            {
                if (j < params.cols && h < matrix.col_hint_count[j])
                {
                    cout << " " << matrix.col_hints[j][h];
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
                if (j < params.cols && h < matrix.col_hint_count[j])
                {
                    cout << " " << matrix.col_hints[j][h];
                }
                else
                {
                    cout << "  ";
                }
            }

            cout << " |" << endl;
        }

        // ��ʾ�ָ���
        cout << string(hint_width + 1, '-') << "+-----------+-----------+" << endl;

        // ��ʾ�б���
        cout << string(hint_width + 1, ' ') << "|";

        // ��һ��5��
        for (int j = 0; j < 5; j++)
        {
            if (j < params.cols)
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
            if (j < params.cols)
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
        for (int i = 0; i < params.rows; i++)
        {
            // ��ʾ����ʾ���Ҷ���
            string row_hint_str = "";
            for (int h = 0; h < matrix.row_hint_count[i]; h++)
            {
                row_hint_str += to_string(matrix.row_hints[i][h]) + " ";
            }

            // ȷ������ʾ������һ��
            cout << setw(hint_width) << right << row_hint_str << " |";

            // ��ʾ�б��⣨A,B,C,...��
            cout << (char)('A' + i) << "|";

            // ��һ��5��
            for (int j = 0; j < 5; j++)
            {
                if (j < params.cols)
                {
                    if (matrix.cells[i][j] == EMPTY)
                    {
                        if (params.cheat_mode && matrix.solution[i][j])
                        {
                            cout << " O"; // ����ģʽ��ʾ��ͨ��O
                        }
                        else
                            cout << "  ";
                    }
                    else if (matrix.cells[i][j] == MARKED)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HGREEN); // �û����Ϊ��ɫ����
                        cout << " O";
                        cct_setcolor(); // �ָ�Ĭ����ɫ
                    }
                    else if (matrix.cells[i][j] == MARKED_WRONG)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HRED); // ������Ϊ��ɫ����
                        cout << " X";
                        cct_setcolor(); // �ָ�Ĭ����ɫ
                    }
                    else if (matrix.cells[i][j] == MARKED_NOT)
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
                if (j < params.cols)
                {
                    if (matrix.cells[i][j] == EMPTY)
                    {
                        if (params.cheat_mode && matrix.solution[i][j])
                        {
                            cout << " O"; // ����ģʽ��ʾ��ͨ��O
                        }
                        else
                            cout << "  ";
                    }
                    else if (matrix.cells[i][j] == MARKED)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HGREEN); // �û����Ϊ��ɫ����
                        cout << " O";
                        cct_setcolor(); // �ָ�Ĭ����ɫ
                    }
                    else if (matrix.cells[i][j] == MARKED_WRONG)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HRED); // ������Ϊ��ɫ����
                        cout << " X";
                        cct_setcolor(); // �ָ�Ĭ����ɫ
                    }
                    else if (matrix.cells[i][j] == MARKED_NOT)
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
            if ((i + 1) % 5 == 0 && i < params.rows - 1)
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
        cout << "��ǰ" << (params.cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ" << endl;

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
            if (validate_solution(matrix, params, error_row, error_col))
            {
                cout << "��ϲ����Ľ����ȷ��" << endl;
                game_over = true;
                system("pause");
            }
            else
            {
                cout << "�����󣬵�һ������λ�ã�" << (char)('A' + error_row)
                     << (char)('a' + error_col) << endl;
                system("pause");
            }
        }
        else if ((input[0] == 'Z' || input[0] == 'z') && input[1] == '\0')
        {
            // �л�����ģʽ
            params.cheat_mode = !params.cheat_mode;
            cout << (params.cheat_mode ? "�ѿ���" : "�ѹر�") << "����ģʽ" << endl;
            system("pause");
        }
        else if (input[0] >= 'A' && input[0] <= 'A' + params.rows - 1 && input[1] >= 'a' &&
                 input[1] <= 'a' + params.cols - 1)
        {
            // ��������
            int row = input[0] - 'A';
            int col = input[1] - 'a';

            // ���������Ч��
            if (row >= 0 && row < params.rows && col >= 0 && col < params.cols)
            {
                // ��ǻ�ȡ�����
                mark_cell(matrix, params, row, col, 1);
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

    // Ĭ�Ϲر�����ģʽ
    params.cheat_mode = false;

    // �������
    cct_enable_mouse();

    // ���Ƴ�ʼ��Ϸ����
    display_game_graphic(matrix, params);

    // ��ʾ������ʾ
    cct_setcolor();
    cct_gotoxy(0, 25);
    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���Z���л�����ģʽ"
         << endl;
    cct_gotoxy(0, 26);
    cout << "��ǰ" << (params.cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ" << endl;

    while (!game_over)
    {
        int mx, my, maction, keycode1, keycode2;
        int ret = cct_read_keyboard_and_mouse(mx, my, maction, keycode1, keycode2);

        if (ret == CCT_MOUSE_EVENT)
        {
            // ����¼�
            display_mouse_position(mx, my, params);

            // �������������ʾ�������ƶ��¼���
            int row, col;
            bool is_valid;
            convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

            if (is_valid)
            {
                // ��ʾ��ǰ��Ԫ������
                cct_gotoxy(0, 27);
                cout << "��ǰ��Ԫ��: " << (char)('A' + row) << (col + 1) << "                ";
            }
            else
            {
                // �����Ԫ��������ʾ
                cct_gotoxy(0, 27);
                cout << "                                  ";
            }

            if (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_RIGHT_BUTTON_CLICK)
            {
                if (is_valid)
                {
                    // �������Ҽ���ͬ�ı�Ƿ�ʽ
                    if (maction == MOUSE_LEFT_BUTTON_CLICK)
                    {
                        mark_cell(matrix, params, row, col, 1);
                    }
                    else if (maction == MOUSE_RIGHT_BUTTON_CLICK)
                    {
                        mark_cell(matrix, params, row, col, 2);
                    }

                    // �ػ���Ϸ����
                    display_game_graphic(matrix, params);

                    // ��ʾ������ʾ
                    cct_setcolor();
                    cct_gotoxy(0, 25);
                    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���Z��"
                            "�л�����ģʽ"
                         << endl;
                    cct_gotoxy(0, 26);
                    cout << "��ǰ" << (params.cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ"
                         << endl;
                }
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT)
        {
            // �����¼�
            if (keycode1 == 'q' || keycode1 == 'Q')
            {
                game_over = true;
            }
            else if (keycode1 == 'z' || keycode1 == 'Z')
            {
                // �л�����ģʽ
                params.cheat_mode = !params.cheat_mode;

                // �ػ���Ϸ����
                display_game_graphic(matrix, params);

                // ��ʾ������ʾ
                cct_setcolor();
                cct_gotoxy(0, 25);
                cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���Z���л�"
                        "����ģʽ"
                     << endl;
                cct_gotoxy(0, 26);
                cout << "��ǰ" << (params.cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ" << endl;
                cct_gotoxy(0, 27);
                cout << (params.cheat_mode ? "�ѿ���" : "�ѹر�") << "����ģʽ                   "
                     << endl;
                Sleep(500); // ��ʾһ���л���ʾ
            }
            else if (keycode1 == '\r')
            {
                // ��֤���
                int error_row, error_col;
                if (validate_solution(matrix, params, error_row, error_col))
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

                    // ��Ǵ���λ��
                    int cell_width = params.has_separators ? 5 : 2;
                    int cell_height = params.has_separators ? 3 : 1;
                    int hint_width = matrix.hint_width * 2;
                    int hint_height = matrix.hint_height;
                    int matrix_x = 5 + hint_width;
                    int matrix_y = 3 + hint_height;

                    // ��˸��ʾ����λ��
                    for (int i = 0; i < 3; i++)
                    {
                        int x = matrix_x + error_col * cell_width;
                        int y = matrix_y + error_row * cell_height;

                        if (params.has_separators)
                        {
                            x += 2; // �ڵ�Ԫ������λ��
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

                    // �ָ���ʾ
                    display_game_graphic(matrix, params);

                    // ��ʾ������ʾ
                    cct_setcolor();
                    cct_gotoxy(0, 25);
                    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳���Z��"
                            "�л�����ģʽ"
                         << endl;
                    cct_gotoxy(0, 26);
                    cout << "��ǰ" << (params.cheat_mode ? "�ѿ���" : "δ����") << "����ģʽ"
                         << endl;
                }
            }
        }
    }

    // �������
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

    // Ĭ�Ͽ�������ģʽ����ʾ���
    params.cheat_mode = true;

    // �������
    cct_enable_mouse();

    // ���Ƴ�ʼ��Ϸ����
    display_game_graphic(matrix, params);

    // ��ʾ������ʾ
    cct_setcolor();
    cct_gotoxy(0, 25);
    cout << "����˵�����ƶ������ʾ���꣬Q���˳�" << endl;

    while (!quit)
    {
        int mx, my, maction, keycode1, keycode2;
        int ret = cct_read_keyboard_and_mouse(mx, my, maction, keycode1, keycode2);

        if (ret == CCT_MOUSE_EVENT)
        {
            // ����¼�
            display_mouse_position(mx, my, params);

            // �������������ʾ�������ƶ��¼���
            int row, col;
            bool is_valid;
            convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

            if (is_valid)
            {
                // ��ʾ��ǰ��Ԫ������
                cct_gotoxy(0, 27);
                cout << "��ǰ��Ԫ��: " << (char)('A' + row) << (col + 1) << "                ";
            }
            else
            {
                // �����Ԫ��������ʾ
                cct_gotoxy(0, 27);
                cout << "                                  ";
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT)
        {
            // �����¼�
            if (keycode1 == 'q' || keycode1 == 'Q')
            {
                quit = true;
            }
        }
    }

    // �������
    cct_disable_mouse();
}
