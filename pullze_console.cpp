#include "pullze.h"

/***************************************************************************
  �������ƣ�display_matrix_text
  ��    �ܣ��ı�ģʽ����ʾ����
  ���������const GameMatrix& matrix - ��Ϸ����
            const GameParams& params - ��Ϸ����
  �� �� ֵ����
  ˵    ������ʾ���б�ʶ�;�������
***************************************************************************/
void display_matrix_text(const GameMatrix &matrix, const GameParams &params)
{
    // ����
    cct_cls();

    cout << "��ʼ���飺" << endl;

    // ����ʾ��ʾ��Ϣ��ֱ����ʾ����
    // ��ʾ�����߿���б���
    cout << "+-+";
    for (int j = 0; j < params.cols; j++)
    {
        cout << "-";
        if ((j + 1) % 5 == 0 && j < params.cols - 1)
        {
            cout << "-";
        }
    }
    cout << "-----------+" << endl;

    cout << "| |";
    for (int j = 0; j < params.cols; j++)
    {
        cout << " " << (char)('a' + j);
        if ((j + 1) % 5 == 0 && j < params.cols - 1)
        {
            cout << " |";
        }
    }
    cout << " |" << endl;

    cout << "+-+";
    for (int j = 0; j < params.cols; j++)
    {
        cout << "-";
        if ((j + 1) % 5 == 0 && j < params.cols - 1)
        {
            cout << "-";
        }
    }
    cout << "-----------+" << endl;

    // ��ʾ��������
    for (int i = 0; i < params.rows; i++)
    {
        // ��ʾ�б��⣨A,B,C,...��
        cout << "|" << (char)('A' + i) << "|";

        for (int j = 0; j < params.cols; j++)
        {
            // ��������ģʽ��ʾ��Ԫ������
            if (params.cheat_mode && matrix.solution[i][j])
            {
                cout << " O";
            }
            else
            {
                cout << "  ";
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
            cout << "+-+";
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
    cout << "+-+";
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

/***************************************************************************
  �������ƣ�display_hints_text
  ��    �ܣ��ı�ģʽ����ʾ��ʾ��
  ���������const GameMatrix& matrix - ��Ϸ����
            const GameParams& params - ��Ϸ����
  �� �� ֵ����
  ˵    ������ʾ������ʾ
***************************************************************************/
void display_hints_text(const GameMatrix &matrix, const GameParams &params)
{
    // ����
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
                // ��������ģʽ��ʾ��Ԫ������
                if (params.cheat_mode && matrix.solution[i][j])
                {
                    cout << " O";
                }
                else
                {
                    cout << "  ";
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
                // ��������ģʽ��ʾ��Ԫ������
                if (params.cheat_mode && matrix.solution[i][j])
                {
                    cout << " O";
                }
                else
                {
                    cout << "  ";
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
        cct_showstr(screen_x, screen_y, "0", COLOR_BLACK, COLOR_WHITE);
        break;

    case MARKED:
        // ��ʾ0��ʾ�����̵׺���
        cct_setcolor(COLOR_BLACK, COLOR_HGREEN);
        cct_showstr(screen_x, screen_y, "0", COLOR_BLACK, COLOR_HGREEN);
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

/***************************************************************************
  �������ƣ�display_matrix_graphic
  ��    �ܣ�ͼ��ģʽ����ʾ����
  ���������const GameMatrix& matrix - ��Ϸ����
            const GameParams& params - ��Ϸ����
  �� �� ֵ����
  ˵    ����ͼ��ģʽ����ʾ���б�ʶ�;�������
***************************************************************************/
void display_matrix_graphic(const GameMatrix &matrix, const GameParams &params)
{
    // ����
    cct_cls();

    // ���õ�Ԫ���С
    int cell_width = 2; // ÿ����Ԫ��ռ2��

    // ��������С
    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.rows + 2; // ���±߿��ռ1�У��м���������

    // ���Ʊ߿�
    draw_frame(5, 3, matrix_width, matrix_height, false);

    // ��ʾ�б��⣨1,2,3,...��
    for (int j = 0; j < params.cols; j++)
    {
        int x = 6 + j * cell_width;
        cct_showint(x, 2, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ�б��⣨A,B,C,...��
    for (int i = 0; i < params.rows; i++)
    {
        int y = 4 + i;
        cct_showch(3, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ��������
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            int x = 6 + j * cell_width;
            int y = 4 + i;

            if (params.cheat_mode && matrix.solution[i][j])
            {
                display_cell(x, y, FILLED, false);
            }
            else
            {
                display_cell(x, y, EMPTY, false);
            }
        }
    }

    // ������ƶ���ͼ���·�������"�밴���������..."��ʾ��ͼ���м�
    cct_gotoxy(0, 3 + matrix_height + 2);
}

/***************************************************************************
  �������ƣ�display_game_graphic
  ��    �ܣ�ͼ��ģʽ����ʾ������Ϸ����
  ���������const GameMatrix& matrix - ��Ϸ����
            const GameParams& params - ��Ϸ����
  �� �� ֵ����
  ˵    ����ͼ��ģʽ����ʾ���б�ʶ���������ݺ���ʾ��
***************************************************************************/
void display_game_graphic(const GameMatrix &matrix, const GameParams &params)
{
    // ����
    cct_cls();

    // ���õ�Ԫ���С
    int cell_width = 2; // ÿ����Ԫ��ռ2��

    // ��������С��λ��
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;

    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.rows + 2; // ���±߿��ռ1�У��м���������

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
    draw_frame(matrix_x, matrix_y, matrix_width, matrix_height, false);

    // ��ʾ�б��⣨1,2,3,...��
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + 1 + j * cell_width;
        cct_showint(x, matrix_y - 1, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ�б��⣨A,B,C,...��
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + 1 + i;
        cct_showch(matrix_x - 2, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ��������
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            int x = matrix_x + 1 + j * cell_width;
            int y = matrix_y + 1 + i;

            if (params.cheat_mode && matrix.solution[i][j])
            {
                display_cell(x, y, FILLED, false);
            }
            else
            {
                display_cell(x, y, EMPTY, false);
            }
        }
    }

    // ��ʾ����ʾ
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + 1 + i;
        int hint_x = row_hint_x + 1; // ������ʾ���ڲ���ʼ

        // �Ҷ�����ʾ
        for (int h = 0; h < matrix.row_hint_count[i]; h++)
        {
            int x = hint_x + (matrix.hint_width - matrix.row_hint_count[i] + h) * 2;
            cct_showint(x, y, matrix.row_hints[i][h], COLOR_BLACK, COLOR_WHITE);
        }
    }

    // ��ʾ����ʾ
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + 1 + j * cell_width;
        int hint_y = col_hint_y + 1; // ������ʾ���ڲ���ʼ

        // �¶�����ʾ
        for (int h = 0; h < matrix.col_hint_count[j]; h++)
        {
            int y = hint_y + (matrix.hint_height - matrix.col_hint_count[j] + h);
            cct_showint(x, y, matrix.col_hints[j][h], COLOR_BLACK, COLOR_WHITE);
        }
    }

    // ������ƶ���ͼ���·�������"�밴���������..."��ʾ��ͼ���м�
    cct_gotoxy(0, matrix_y + matrix_height + 2);
}

/***************************************************************************
  �������ƣ�display_mouse_position
  ��    �ܣ���ʾ���λ��
  ���������int mx - ���X����
            int my - ���Y����
            const GameParams& params - ��Ϸ����
  �� �� ֵ����
  ˵    ������״̬����ʾ���λ��
***************************************************************************/
void display_mouse_position(int mx, int my, const GameParams &params)
{
    cct_setcolor();
    cct_gotoxy(0, 30);
    cout << "���λ��: " << mx << "," << my << "                ";
}

/***************************************************************************
  �������ƣ�convert_mouse_to_cell
  ��    �ܣ����������ת��Ϊ����Ԫ������
  ���������int mx - ���X����
            int my - ���Y����
            int& row - ����������
            int& col - ����������
            const GameParams& params - ��Ϸ����
            const GameMatrix& matrix - ��Ϸ����
            bool& is_valid - �����Ƿ���Ч
  �� �� ֵ����
  ˵    �����������Ƿ�����Ч�ľ��������ڣ���ת������
***************************************************************************/
void convert_mouse_to_cell(int mx, int my, int &row, int &col, const GameParams &params,
                           const GameMatrix &matrix, bool &is_valid)
{
    // ���õ�Ԫ���С
    int cell_width = 2; // ÿ����Ԫ��ռ2��

    // ��������С��λ��
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;

    // �������Ƿ��ھ���������
    if (mx >= matrix_x + 1 && mx < matrix_x + params.cols * cell_width + 1 && my >= matrix_y + 1 &&
        my < matrix_y + params.rows + 1)
    {
        // ������������
        col = (mx - matrix_x - 1) / cell_width;
        row = (my - matrix_y - 1);

        // ��������Ƿ�����Ч��Χ��
        if (row >= 0 && row < params.rows && col >= 0 && col < params.cols)
        {
            is_valid = true;
            return;
        }
    }

    is_valid = false;
}