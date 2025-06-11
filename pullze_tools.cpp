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

    cct_cls();
    cct_setcolor();

    cout << "========== ��֯��Ϸ ==========" << endl;
    cout << "1. �ı�ģʽ - ��ʼ�����󲢴�ӡ" << endl;
    cout << "2. �ı�ģʽ - ������/����ʾ������ӡ" << endl;
    cout << "3. �ı�ģʽ - ������Ϸ" << endl;
    cout << "4. ͼ��ģʽ(�޷ָ���) - ��ʼ״̬" << endl;
    cout << "5. ͼ��ģʽ(�޷ָ���) - ����ʾ��" << endl;
    cout << "6. ͼ��ģʽ(�޷ָ���) - ����ƶ�" << endl;
    cout << "7. ͼ��ģʽ(�޷ָ���) - ������Ϸ" << endl;
    cout << "8. ͼ��ģʽ(�зָ���) - ��ʼ״̬" << endl;
    cout << "9. ͼ��ģʽ(�зָ���) - ����ʾ��" << endl;
    cout << "10. ͼ��ģʽ(�зָ���) - ����ƶ�" << endl;
    cout << "11. ͼ��ģʽ(�зָ���) - ������Ϸ" << endl;
    cout << "0. �˳�" << endl;
    cout << "��ѡ��: ";

    while (!(cin >> choice) || choice < 0 || choice > 11)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "�������������ѡ��: ";
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

    cout << "���������� (5-" << MAX_MATRIX_SIZE << "): ";
    while (!(cin >> params.rows) || params.rows < 5 || params.rows > MAX_MATRIX_SIZE)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "��������������������� (5-" << MAX_MATRIX_SIZE << "): ";
    }

    cout << "���������� (5-" << MAX_MATRIX_SIZE << "): ";
    while (!(cin >> params.cols) || params.cols < 5 || params.cols > MAX_MATRIX_SIZE)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "��������������������� (5-" << MAX_MATRIX_SIZE << "): ";
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
        display_hints_text(matrix, params);

        // ��ʾ��ǰ״̬
        for (int i = 0; i < params.rows; i++)
        {
            cout << (char)('A' + i) << ": ";
            for (int j = 0; j < params.cols; j++)
            {
                if (matrix.cells[i][j] == EMPTY)
                {
                    cout << ". ";
                }
                else if (matrix.cells[i][j] == MARKED)
                {
                    cout << "0 ";
                }
                else if (matrix.cells[i][j] == MARKED_WRONG)
                {
                    cout << "X ";
                }
                else if (matrix.cells[i][j] == MARKED_NOT)
                {
                    cout << "�� ";
                }

                if (params.cheat_mode && matrix.solution[i][j] && matrix.cells[i][j] == EMPTY)
                {
                    cout << "0 ";
                }
            }
            cout << endl;
        }

        // �û�����
        cout << "\n��������(��A1)������λ�ã�����Q�˳�������C�ύ: ";
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
                cout << "�����󣬵�һ������λ�ã�" << (char)('A' + error_row) << (error_col + 1)
                     << endl;
                system("pause");
            }
        }
        else if (input[0] >= 'A' && input[0] <= 'A' + params.rows - 1 && input[1] >= '1' &&
                 input[1] <= '9')
        {
            // ��������
            int row = input[0] - 'A';
            int col = atoi(input + 1) - 1;

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