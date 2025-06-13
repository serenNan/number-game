#include "pullze.h"
#include <cstdio>  // ���sprintf������ͷ�ļ�
#include <cstring> // ����ַ�����������ͷ�ļ�

/***************************************************************************
  �������ƣ�display_matrix_text
  ��    �ܣ��ı�ģʽ����ʾ����
  �����������
  �� �� ֵ����
  ˵    ������ʾ���б�ʶ�;�������
***************************************************************************/
void display_matrix_text()
{
    // ����
    cct_cls();

    cout << "��ʼ���飺" << endl;

    // ����ʾ��ʾ��Ϣ��ֱ����ʾ����
    // ��ʾ�����߿���б���
    cout << "+-+";
    for (int j = 0; j < g_cols; j++)
    {
        cout << "-";
        if ((j + 1) % 5 == 0 && j < g_cols - 1)
        {
            cout << "-";
        }
    }
    cout << "-----------+" << endl;

    cout << "| |";
    for (int j = 0; j < g_cols; j++)
    {
        cout << " " << (char)('a' + j);
        if ((j + 1) % 5 == 0 && j < g_cols - 1)
        {
            cout << " |";
        }
    }
    cout << " |" << endl;

    cout << "+-+";
    for (int j = 0; j < g_cols; j++)
    {
        cout << "-";
        if ((j + 1) % 5 == 0 && j < g_cols - 1)
        {
            cout << "-";
        }
    }
    cout << "-----------+" << endl;

    // ��ʾ��������
    for (int i = 0; i < g_rows; i++)
    {
        // ��ʾ�б��⣨A,B,C,...��
        cout << "|" << (char)('A' + i) << "|";

        for (int j = 0; j < g_cols; j++)
        {
            // ��������ģʽ��ʾ��Ԫ������
            if (g_cheat_mode && g_solution[i][j])
            {
                cout << " O";
            }
            else
            {
                cout << "  ";
            }

            // ÿ5�����һ���ָ���
            if ((j + 1) % 5 == 0 && j < g_cols - 1)
            {
                cout << " |";
            }
        }
        cout << " |" << endl;

        // ÿ5�����һ���ָ���
        if ((i + 1) % 5 == 0 && i < g_rows - 1)
        {
            cout << "+-+";
            for (int j = 0; j < g_cols; j++)
            {
                cout << "-";
                if ((j + 1) % 5 == 0 && j < g_cols - 1)
                {
                    cout << "-";
                }
            }
            cout << "-----------+" << endl;
        }
    }

    // ��ʾ�ײ��߿�
    cout << "+-+";
    for (int j = 0; j < g_cols; j++)
    {
        cout << "-";
        if ((j + 1) % 5 == 0 && j < g_cols - 1)
        {
            cout << "-";
        }
    }
    cout << "-----------+" << endl;
}

/***************************************************************************
  �������ƣ�display_hints_text
  ��    �ܣ��ı�ģʽ����ʾ��ʾ��
  �����������
  �� �� ֵ����
  ˵    ������ʾ������ʾ
***************************************************************************/
void display_hints_text()
{
    // ����
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

        // ��ʾ��������
        for (int j = 0; j < g_cols; j++)
        {
            // ��������ģʽ��ʾ��Ԫ������
            if (g_cheat_mode && g_solution[i][j])
            {
                cout << " O";
            }
            else
            {
                cout << "  ";
            }

            // ÿ5�����һ���ָ���
            if ((j + 1) % 5 == 0 && j < g_cols - 1)
            {
                cout << " |";
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
}

/***************************************************************************
  �������ƣ�display_cell
  ��    �ܣ���ָ��λ����ʾ��Ԫ��
  ���������int x - ������
            int y - ������
            CellStatus status - ��Ԫ��״̬
            bool has_separators - �Ƿ��зָ���
  �� �� ֵ����
  ˵    �������ݵ�Ԫ��״̬����ʽ��ʾ��ͬ����
***************************************************************************/
void display_cell(int x, int y, CellStatus status, bool has_separators)
{
    // ʹ�þ�������
    int screen_x = x;
    int screen_y = y;

    // ����зָ��ߣ���Ҫ������ʾλ�õ���Ԫ������
    if (has_separators)
    {
        // ��Ԫ���ڲ�������λ��
        screen_x += 2; // ��5��ĵ�Ԫ���У�������ʾ�ڵ�3��
        screen_y += 1; // ��3�ߵĵ�Ԫ���У�������ʾ�ڵ�2��
    }

    // ����״̬��������
    switch (status)
    {
    case EMPTY:
        // �ո񣬲���ʾ�κ�����
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, " ", COLOR_BLACK, COLOR_WHITE);
        break;

    case FILLED:
        // ��ʾ0��ʾ���򣬰׵׺���
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        if (has_separators)
        {
            cct_showstr(screen_x, screen_y, "��", COLOR_BLACK, COLOR_WHITE);
        }
        else
        {
            cct_showstr(screen_x, screen_y, "0", COLOR_BLACK, COLOR_WHITE);
        }
        break;

    case MARKED:
        // ��ʾ0��ʾ�����̵׺���
        cct_setcolor(COLOR_BLACK, COLOR_HGREEN);
        if (has_separators)
        {
            cct_showstr(screen_x, screen_y, "��", COLOR_BLACK, COLOR_HGREEN);
        }
        else
        {
            cct_showstr(screen_x, screen_y, "0", COLOR_BLACK, COLOR_HGREEN);
        }
        break;

    case MARKED_WRONG:
        // ��ʾX��ʾ�����ǣ���׺���
        cct_setcolor(COLOR_BLACK, COLOR_HRED);
        cct_showstr(screen_x, screen_y, "X", COLOR_BLACK, COLOR_HRED);
        break;

    case MARKED_NOT:
        // ��ʾ����ʾ���Ϊ�����ڣ����׺���
        cct_setcolor(COLOR_BLACK, COLOR_HBLUE);
        cct_showstr(screen_x, screen_y, "��", COLOR_BLACK, COLOR_HBLUE);
        break;
    }

    // �ָ�Ĭ����ɫ
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
  �������ƣ�draw_frame
  ��    �ܣ�������Ϸ�߿�
  ���������int x - ��ʼx����
            int y - ��ʼy����
            int width - ���
            int height - �߶�
            bool has_separators - �Ƿ��зָ���
  �� �� ֵ����
  ˵    ����ʹ�������Ʊ�����Ʊ߿�
***************************************************************************/
void draw_frame(int x, int y, int width, int height, bool has_separators)
{
    // ���Ԫ��
    const char *frame_elements[] = {"�X", "�^", "�[", "�a", "�T", "�U"};

    if (!has_separators)
    {
        // �򵥱߿�ģʽ
        // �����ϱ߿�
        cct_showstr(x, y, frame_elements[0], COLOR_BLACK, COLOR_WHITE); // ���Ͻ�
        for (int i = 1; i < width - 1; i++)
        {
            cct_showstr(x + i, y, frame_elements[4], COLOR_BLACK, COLOR_WHITE); // ����
        }
        cct_showstr(x + width - 1, y, frame_elements[2], COLOR_BLACK, COLOR_WHITE); // ���Ͻ�

        // �����м䲿��
        for (int j = 1; j < height - 1; j++)
        {
            // ���ұ߿�
            cct_showstr(x, y + j, frame_elements[5], COLOR_BLACK, COLOR_WHITE);             // ���
            cct_showstr(x + width - 1, y + j, frame_elements[5], COLOR_BLACK, COLOR_WHITE); // �ұ�
        }

        // �����±߿�
        cct_showstr(x, y + height - 1, frame_elements[1], COLOR_BLACK, COLOR_WHITE); // ���½�
        for (int i = 1; i < width - 1; i++)
        {
            cct_showstr(x + i, y + height - 1, frame_elements[4], COLOR_BLACK, COLOR_WHITE); // ����
        }
        cct_showstr(x + width - 1, y + height - 1, frame_elements[3], COLOR_BLACK,
                    COLOR_WHITE); // ���½�
    }
    else
    {
        // ���ӵ�Ԫ��ģʽ
        int cell_width = 5;  // ÿ����Ԫ����Ϊ5���ַ��������߿�
        int cell_height = 3; // ÿ����Ԫ��߶�Ϊ3�У������߿�
        int cols = (width - 1) / cell_width;
        int rows = (height - 1) / cell_height;

        // ���ƶ����߿�
        cct_showstr(x, y, "�X", COLOR_BLACK, COLOR_WHITE); // ���Ͻ�
        for (int j = 0; j < cols; j++)
        {
            for (int i = 0; i < cell_width - 1; i++)
            {
                cct_showstr(x + j * cell_width + i + 1, y, "�T", COLOR_BLACK, COLOR_WHITE);
            }
            if (j < cols - 1)
            {
                cct_showstr(x + (j + 1) * cell_width, y, "�j", COLOR_BLACK, COLOR_WHITE);
            }
        }
        cct_showstr(x + width - 1, y, "�[", COLOR_BLACK, COLOR_WHITE); // ���Ͻ�

        // �����м���
        for (int i = 0; i < rows; i++)
        {
            // ���Ƶ�Ԫ���ڲ�
            for (int k = 1; k < cell_height; k++)
            {
                for (int j = 0; j < cols; j++)
                {
                    cct_showstr(x, y + i * cell_height + k, "�U", COLOR_BLACK, COLOR_WHITE);
                    for (int l = 1; l < cell_width; l++)
                    {
                        cct_showstr(x + j * cell_width + l, y + i * cell_height + k, " ",
                                    COLOR_BLACK, COLOR_WHITE);
                    }
                    cct_showstr(x + (j + 1) * cell_width, y + i * cell_height + k, "�U", COLOR_BLACK,
                                COLOR_WHITE);
                }
            }

            // �����зָ���
            if (i < rows - 1)
            {
                cct_showstr(x, y + (i + 1) * cell_height, "�d", COLOR_BLACK, COLOR_WHITE);
                for (int j = 0; j < cols; j++)
                {
                    for (int l = 1; l < cell_width; l++)
                    {
                        cct_showstr(x + j * cell_width + l, y + (i + 1) * cell_height, "�T",
                                    COLOR_BLACK, COLOR_WHITE);
                    }
                    if (j < cols - 1)
                    {
                        cct_showstr(x + (j + 1) * cell_width, y + (i + 1) * cell_height, "�p",
                                    COLOR_BLACK, COLOR_WHITE);
                    }
                }
                cct_showstr(x + width - 1, y + (i + 1) * cell_height, "�g", COLOR_BLACK,
                            COLOR_WHITE);
            }
        }

        // ���Ƶײ��߿�
        cct_showstr(x, y + height - 1, "�^", COLOR_BLACK, COLOR_WHITE); // ���½�
        for (int j = 0; j < cols; j++)
        {
            for (int i = 0; i < cell_width - 1; i++)
            {
                cct_showstr(x + j * cell_width + i + 1, y + height - 1, "�T", COLOR_BLACK,
                            COLOR_WHITE);
            }
            if (j < cols - 1)
            {
                cct_showstr(x + (j + 1) * cell_width, y + height - 1, "�m", COLOR_BLACK,
                            COLOR_WHITE);
            }
        }
        cct_showstr(x + width - 1, y + height - 1, "�a", COLOR_BLACK, COLOR_WHITE); // ���½�
    }
}

/***************************************************************************
  �������ƣ�display_matrix_graphic
  ��    �ܣ�ͼ��ģʽ����ʾ����
  �����������
  �� �� ֵ����
  ˵    ������ʾ��������
***************************************************************************/
void display_matrix_graphic()
{
    // ����
    cct_cls();

    // ���õ�Ԫ���С
    int cell_width = g_has_separators ? 5 : 2; // �зָ���ʱÿ����Ԫ��ռ5�У�����ռ2��

    // ��������С
    int matrix_width = g_cols * cell_width + 1;
    int matrix_height =
        g_has_separators ? g_rows * 3 + 1 : g_rows + 2; // �зָ���ʱÿ��ռ3�У�����ռ1��

    // ���Ʊ߿�
    draw_frame(5, 3, matrix_width, matrix_height, g_has_separators);

    // ��ʾ�б��⣨1,2,3,...��
    for (int j = 0; j < g_cols; j++)
    {
        int x = 6 + j * cell_width;
        if (g_has_separators)
        {
            x = 5 + j * cell_width + cell_width / 2;
        }
        cct_showint(x, 2, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ�б��⣨A,B,C,...��
    for (int i = 0; i < g_rows; i++)
    {
        int y = 4 + i;
        if (g_has_separators)
        {
            y = 3 + i * 3 + 2; // ��ÿ����Ԫ����м�����ʾ
        }
        cct_showch(3, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ��������
    for (int i = 0; i < g_rows; i++)
    {
        for (int j = 0; j < g_cols; j++)
        {
            int x = 6 + j * cell_width;
            int y = 4 + i;

            if (g_has_separators)
            {
                x = 5 + j * cell_width + 1; // ��Ԫ�����Ͻ�
                y = 3 + i * 3 + 1;          // ��Ԫ�����Ͻ�
            }

            if (g_cheat_mode && g_solution[i][j] && g_cells[i][j] == EMPTY)
            {
                display_cell(x, y, FILLED, g_has_separators);
            }
            else
            {
                display_cell(x, y, g_cells[i][j], g_has_separators);
            }
        }
    }

    // ������ƶ���ͼ���·�������"�밴���������..."��ʾ��ͼ���м�
    cct_gotoxy(0, 3 + matrix_height + 2);
}

/***************************************************************************
  �������ƣ�display_game_graphic
  ��    �ܣ�ͼ��ģʽ����ʾ��Ϸ����
  �����������
  �� �� ֵ����
  ˵    ������ʾ��Ϸ���棬������ʾ���;���
***************************************************************************/
void display_game_graphic()
{
    // ����
    cct_cls();

    // ���õ�Ԫ���С
    int cell_width = g_has_separators ? 5 : 2; // �зָ���ʱÿ����Ԫ��ռ5�У�����ռ2��

    // ��������С��λ��
    int hint_width = g_hint_width * 2;
    int hint_height = g_hint_height;

    int matrix_width = g_cols * cell_width + 1;
    int matrix_height =
        g_has_separators ? g_rows * 3 + 1 : g_rows + 2; // �зָ���ʱÿ��ռ3�У�����ռ1��

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;

    // ��������ʾ�߿�
    int row_hint_x = matrix_x - hint_width - 2;
    int row_hint_y = matrix_y;
    int row_hint_width = hint_width;
    int row_hint_height = matrix_height;
    draw_frame(row_hint_x, row_hint_y, row_hint_width, row_hint_height, false);

    // ��������ʾ�߿�
    int col_hint_x = matrix_x;
    int col_hint_y = matrix_y - hint_height - 1;
    int col_hint_width = matrix_width;
    int col_hint_height = hint_height + 1;
    draw_frame(col_hint_x, col_hint_y, col_hint_width, col_hint_height, false);

    // ���ƾ���߿�
    draw_frame(matrix_x, matrix_y, matrix_width, matrix_height, g_has_separators);

    // ��ʾ�б��⣨1,2,3,...��
    for (int j = 0; j < g_cols; j++)
    {
        int x = matrix_x + 1 + j * cell_width;
        if (g_has_separators)
        {
            x = matrix_x + j * cell_width + cell_width / 2;
        }
        cct_showint(x, matrix_y - 1, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ�б��⣨A,B,C,...��
    for (int i = 0; i < g_rows; i++)
    {
        int y = matrix_y + 1 + i;
        if (g_has_separators)
        {
            y = matrix_y + i * 3 + 2; // ��ÿ����Ԫ����м�����ʾ
        }
        cct_showch(matrix_x - 2, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ��������
    for (int i = 0; i < g_rows; i++)
    {
        for (int j = 0; j < g_cols; j++)
        {
            int x = matrix_x + 1 + j * cell_width;
            int y = matrix_y + 1 + i;

            if (g_has_separators)
            {
                x = matrix_x + j * cell_width + 1; // ��Ԫ�����Ͻ�
                y = matrix_y + i * 3 + 1;          // ��Ԫ�����Ͻ�
            }

            if (g_cheat_mode && g_solution[i][j] && g_cells[i][j] == EMPTY)
            {
                display_cell(x, y, FILLED, g_has_separators);
            }
            else
            {
                display_cell(x, y, g_cells[i][j], g_has_separators);
            }
        }
    }

    // ��ʾ����ʾ
    for (int i = 0; i < g_rows; i++)
    {
        int y = matrix_y + 1 + i;
        if (g_has_separators)
        {
            y = matrix_y + i * 3 + 2; // ��ÿ����Ԫ����м�����ʾ
        }
        int hint_x = row_hint_x + 1; // ������ʾ���ڲ���ʼ

        // �Ҷ�����ʾ
        for (int h = 0; h < g_row_hint_count[i]; h++)
        {
            int x = hint_x + (g_hint_width - g_row_hint_count[i] + h) * 2;
            cct_showint(x, y, g_row_hints[i][h], COLOR_BLACK, COLOR_WHITE);
        }
    }

    // ��ʾ����ʾ
    for (int j = 0; j < g_cols; j++)
    {
        int x = matrix_x + 1 + j * cell_width;
        if (g_has_separators)
        {
            x = matrix_x + j * cell_width + cell_width / 2;
        }
        int hint_y = col_hint_y + 1; // ������ʾ���ڲ���ʼ

        // �¶�����ʾ
        for (int h = 0; h < g_col_hint_count[j]; h++)
        {
            int y = hint_y + (g_hint_height - g_col_hint_count[j] + h);
            cct_showint(x, y, g_col_hints[j][h], COLOR_BLACK, COLOR_WHITE);
        }
    }

    // ������ƶ���ͼ���·�������"�밴���������..."��ʾ��ͼ���м�
    cct_gotoxy(0, matrix_y + matrix_height + 2);
}

/***************************************************************************
  �������ƣ�display_mouse_position
  ��    �ܣ���ʾ���λ��
  ���������int mx - ���x����
            int my - ���y����
  �� �� ֵ����
  ˵    ������ʾ���λ��
***************************************************************************/
void display_mouse_position(int mx, int my)
{
    cct_setcolor();
    cct_gotoxy(0, 30);
    cout << "�������: X=" << setw(3) << mx << ", Y=" << setw(3) << my << "        ";
}

/***************************************************************************
  �������ƣ�convert_mouse_to_cell
  ��    �ܣ����������ת��Ϊ����Ԫ������
  ���������int mx - ���x����
            int my - ���y����
            int &row - ����������
            int &col - ����������
            bool &is_valid - ���������Ƿ���Ч
  �� �� ֵ����
  ˵    �������������ת��Ϊ����Ԫ������
***************************************************************************/
void convert_mouse_to_cell(int mx, int my, int &row, int &col, bool &is_valid)
{
    // ���õ�Ԫ���С
    int cell_width = g_has_separators ? 5 : 2;  // �зָ���ʱÿ����Ԫ��ռ5�У�����ռ2��
    int cell_height = g_has_separators ? 3 : 1; // �зָ���ʱÿ����Ԫ��ռ3�У�����ռ1��

    // ��������С��λ��
    int hint_width = g_hint_width * 2;
    int hint_height = g_hint_height;

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;

    // �������Ƿ��ھ���������
    if (g_has_separators)
    {
        if (mx >= matrix_x && mx < matrix_x + g_cols * cell_width + 1 && my >= matrix_y &&
            my < matrix_y + g_rows * cell_height + 1)
        {
            col = (mx - matrix_x) / cell_width;
            row = (my - matrix_y) / cell_height;
            if (row >= 0 && row < g_rows && col >= 0 && col < g_cols)
            {
                is_valid = true;
                return;
            }
        }
    }
    else
    {
        // �޷ָ���ģʽ�£�������ʾʱ��+1ƫ�ƣ�����ҲҪ����
        if (mx >= matrix_x + 1 && mx < matrix_x + 1 + g_cols * cell_width && my >= matrix_y + 1 &&
            my < matrix_y + 1 + g_rows * cell_height)
        {
            col = (mx - matrix_x - 1) / cell_width;
            row = (my - matrix_y - 1) / cell_height;
            if (row >= 0 && row < g_rows && col >= 0 && col < g_cols)
            {
                is_valid = true;
                return;
            }
        }
    }
    is_valid = false;
}