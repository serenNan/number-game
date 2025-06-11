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

    // ѯ������ģʽ������˵�ѡ��û��Ԥ�裩
    if (!params.cheat_mode)
    {
        char cheat;
        cout << "�Ƿ���������ģʽ(Y/N)? ";
        cin >> cheat;
        params.cheat_mode = (cheat == 'Y' || cheat == 'y');
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

    while (!game_over)
    {
        // ��ʾ��Ϸ����
        cct_cls();

        cout << "��ʼ���飺" << endl;

        // ��ʾ����ʾ
        cout << "-------+";
        for (int j = 0; j < params.cols; j++)
        {
            cout << "-";
            if ((j + 1) % 5 == 0 && j < params.cols - 1)
            {
                cout << "-";
            }
        }
        cout << "-----------+" << endl;

        cout << "       |";
        for (int j = 0; j < params.cols; j++)
        {
            if (matrix.col_hint_count[j] > 0)
            {
                cout << " " << matrix.col_hints[j][0];
            }
            else
            {
                cout << "  ";
            }
            if ((j + 1) % 5 == 0 && j < params.cols - 1)
            {
                cout << " |";
            }
        }
        cout << " |" << endl;

        cout << "       |";
        for (int j = 0; j < params.cols; j++)
        {
            if (matrix.col_hint_count[j] > 1)
            {
                cout << " " << matrix.col_hints[j][1];
            }
            else
            {
                cout << "  ";
            }
            if ((j + 1) % 5 == 0 && j < params.cols - 1)
            {
                cout << " |";
            }
        }
        cout << " |" << endl;

        cout << "-------+";
        for (int j = 0; j < params.cols; j++)
        {
            cout << "-";
            if ((j + 1) % 5 == 0 && j < params.cols - 1)
            {
                cout << "-";
            }
        }
        cout << "-----------+" << endl;

        cout << "       |";
        for (int j = 0; j < params.cols; j++)
        {
            cout << " " << (char)('a' + j);
            if ((j + 1) % 5 == 0 && j < params.cols - 1)
            {
                cout << " |";
            }
        }
        cout << " |" << endl;

        cout << "-----+-+";
        for (int j = 0; j < params.cols; j++)
        {
            cout << "-";
            if ((j + 1) % 5 == 0 && j < params.cols - 1)
            {
                cout << "-";
            }
        }
        cout << "-----------+" << endl;

        // ��ʾ�������ݺ�����ʾ
        for (int i = 0; i < params.rows; i++)
        {
            // ��ʾ����ʾ
            if (matrix.row_hint_count[i] == 1)
            {
                cout << "   " << matrix.row_hints[i][0] << " |";
            }
            else if (matrix.row_hint_count[i] == 2)
            {
                cout << " " << matrix.row_hints[i][0] << " " << matrix.row_hints[i][1] << " |";
            }
            else if (matrix.row_hint_count[i] == 3)
            {
                cout << matrix.row_hints[i][0] << " " << matrix.row_hints[i][1] << " "
                     << matrix.row_hints[i][2] << " |";
            }
            else
            {
                cout << "     |";
            }

            // ��ʾ�б��⣨A,B,C,...��
            cout << (char)('A' + i) << "|";

            for (int j = 0; j < params.cols; j++)
            {
                if (matrix.cells[i][j] == EMPTY)
                {
                    if (params.cheat_mode && matrix.solution[i][j])
                        cout << " O";
                    else
                        cout << "  ";
                }
                else if (matrix.cells[i][j] == MARKED)
                {
                    cout << " O";
                }
                else if (matrix.cells[i][j] == MARKED_WRONG)
                {
                    cout << " X";
                }
                else if (matrix.cells[i][j] == MARKED_NOT)
                {
                    cout << " ��";
                }

                // ÿ5�����һ���ָ���
                if ((j + 1) % 5 == 0 && j < params.cols - 1)
                {
                    cout << " |";
                }
            }
            cout << " |" << endl;

            // ÿ5�����һ���ָ���
            if ((i + 1) % 5 == 0 && i < params.rows - 1)
            {
                cout << "-----+-+";
                for (int j = 0; j < params.cols; j++)
                {
                    cout << "-";
                    if ((j + 1) % 5 == 0 && j < params.cols - 1)
                    {
                        cout << "-";
                    }
                }
                cout << "-----------+" << endl;
            }
        }

        // ��ʾ�ײ��߿�
        cout << "-----+-+";
        for (int j = 0; j < params.cols; j++)
        {
            cout << "-";
            if ((j + 1) % 5 == 0 && j < params.cols - 1)
            {
                cout << "-";
            }
        }
        cout << "-----------+" << endl;

        // �û�����
        cout << "\n��������(��Aa)������λ�ã�����Q�˳�������C�ύ: ";
        char input[10];
        cin >> input;

        // �������
        if (input[0] == 'Q' || input[0] == 'q')
        {
            game_over = true;
        }
        else if (input[0] == 'C' || input[0] == 'c')
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
    bool game_over = false;

    // �������
    cct_enable_mouse();

    // ���Ƴ�ʼ��Ϸ����
    display_game_graphic(matrix, params);

    // ��ʾ������ʾ
    cct_setcolor();
    cct_gotoxy(0, 25);
    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳�" << endl;

    while (!game_over)
    {
        int mx, my, maction, keycode1, keycode2;
        int ret = cct_read_keyboard_and_mouse(mx, my, maction, keycode1, keycode2);

        if (ret == CCT_MOUSE_EVENT)
        {
            // ����¼�
            display_mouse_position(mx, my, params);

            if (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_RIGHT_BUTTON_CLICK)
            {
                int row, col;
                bool is_valid;

                convert_mouse_to_cell(mx, my, row, col, params, is_valid);

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
                    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳�"
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
                    int cell_width = params.has_separators ? 3 : 2;
                    int cell_height = params.has_separators ? 2 : 1;
                    int hint_width = matrix.hint_width * 3;
                    int hint_height = matrix.hint_height * 2;
                    int matrix_x = 5 + hint_width;
                    int matrix_y = 3 + hint_height;

                    // ��˸��ʾ����λ��
                    for (int i = 0; i < 3; i++)
                    {
                        cct_gotoxy(matrix_x + error_col * cell_width + 1,
                                   matrix_y + error_row * cell_height + 1);
                        cct_setcolor(COLOR_BLACK, COLOR_HRED);
                        cout << "X";
                        Sleep(300);

                        cct_gotoxy(matrix_x + error_col * cell_width + 1,
                                   matrix_y + error_row * cell_height + 1);
                        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                        cout << " ";
                        Sleep(300);
                    }

                    // �ָ���ʾ
                    display_game_graphic(matrix, params);

                    // ��ʾ������ʾ
                    cct_setcolor();
                    cct_gotoxy(0, 25);
                    cout << "����˵��������������ڣ��Ҽ�����򲻴��ڣ�Enter���ύ��Q���˳�"
                         << endl;
                }
            }
        }
    }

    // �������
    cct_disable_mouse();
}