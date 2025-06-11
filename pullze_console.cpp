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
    // ���õ�Ԫ��Ŀ�Ⱥ͸߶�
    int cell_width = has_separators ? 3 : 2;
    int cell_height = has_separators ? 2 : 1;

    // ���㵥Ԫ�����Ļ����
    int screen_x = x * cell_width;
    int screen_y = y * cell_height;

    // ����״̬������ɫ������
    switch (status)
    {
    case EMPTY:
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        if (has_separators)
        {
            cct_showstr(screen_x, screen_y, "   ", COLOR_BLACK, COLOR_WHITE);
            cct_showstr(screen_x, screen_y + 1, "   ", COLOR_BLACK, COLOR_WHITE);
        }
        else
        {
            cct_showstr(screen_x, screen_y, "  ", COLOR_BLACK, COLOR_WHITE);
        }
        break;

    case FILLED:
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        if (has_separators)
        {
            cct_showstr(screen_x, screen_y, " 0 ", COLOR_BLACK, COLOR_WHITE);
            cct_showstr(screen_x, screen_y + 1, "   ", COLOR_BLACK, COLOR_WHITE);
        }
        else
        {
            cct_showstr(screen_x, screen_y, "0 ", COLOR_BLACK, COLOR_WHITE);
        }
        break;

    case MARKED:
        cct_setcolor(COLOR_BLACK, COLOR_HGREEN);
        if (has_separators)
        {
            cct_showstr(screen_x, screen_y, " 0 ", COLOR_BLACK, COLOR_HGREEN);
            cct_showstr(screen_x, screen_y + 1, "   ", COLOR_BLACK, COLOR_HGREEN);
        }
        else
        {
            cct_showstr(screen_x, screen_y, "0 ", COLOR_BLACK, COLOR_HGREEN);
        }
        break;

    case MARKED_WRONG:
        cct_setcolor(COLOR_BLACK, COLOR_HRED);
        if (has_separators)
        {
            cct_showstr(screen_x, screen_y, " X ", COLOR_BLACK, COLOR_HRED);
            cct_showstr(screen_x, screen_y + 1, "   ", COLOR_BLACK, COLOR_HRED);
        }
        else
        {
            cct_showstr(screen_x, screen_y, "X ", COLOR_BLACK, COLOR_HRED);
        }
        break;

    case MARKED_NOT:
        cct_setcolor(COLOR_BLACK, COLOR_HBLUE);
        if (has_separators)
        {
            cct_showstr(screen_x, screen_y, " �� ", COLOR_BLACK, COLOR_HBLUE);
            cct_showstr(screen_x, screen_y + 1, "   ", COLOR_BLACK, COLOR_HBLUE);
        }
        else
        {
            cct_showstr(screen_x, screen_y, "�� ", COLOR_BLACK, COLOR_HBLUE);
        }
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
    // ���Ԫ�أ�˫�߿�ܣ�
    const char *frame_elements[] = {"�X", "�^", "�[", "�a", "�T", "�U", "�j", "�m", "�d", "�g", "�p"};

    // �����ϱ߿�
    cct_showstr(x, y, frame_elements[0], COLOR_BLACK, COLOR_WHITE); // ���Ͻ�
    for (int i = 1; i < width - 1; i++)
    {
        if (has_separators && i % 3 == 0)
        {
            cct_showstr(x + i, y, frame_elements[6], COLOR_BLACK, COLOR_WHITE); // ��T��
        }
        else
        {
            cct_showstr(x + i, y, frame_elements[4], COLOR_BLACK, COLOR_WHITE); // ����
        }
    }
    cct_showstr(x + width - 1, y, frame_elements[2], COLOR_BLACK, COLOR_WHITE); // ���Ͻ�

    // �����м䲿��
    for (int j = 1; j < height - 1; j++)
    {
        if (has_separators && j % 2 == 0)
        {
            // �ָ���
            cct_showstr(x, y + j, frame_elements[8], COLOR_BLACK, COLOR_WHITE); // ��T��
            for (int i = 1; i < width - 1; i++)
            {
                if (has_separators && i % 3 == 0)
                {
                    cct_showstr(x + i, y + j, frame_elements[10], COLOR_BLACK, COLOR_WHITE); // ʮ��
                }
                else
                {
                    cct_showstr(x + i, y + j, frame_elements[4], COLOR_BLACK, COLOR_WHITE); // ����
                }
            }
            cct_showstr(x + width - 1, y + j, frame_elements[9], COLOR_BLACK, COLOR_WHITE); // ��T��
        }
        else
        {
            // ������
            cct_showstr(x, y + j, frame_elements[5], COLOR_BLACK, COLOR_WHITE); // ����
            for (int i = 1; i < width - 1; i++)
            {
                if (has_separators && i % 3 == 0)
                {
                    cct_showstr(x + i, y + j, frame_elements[5], COLOR_BLACK, COLOR_WHITE); // ����
                }
                else
                {
                    cct_showstr(x + i, y + j, " ", COLOR_BLACK, COLOR_WHITE); // �ո�
                }
            }
            cct_showstr(x + width - 1, y + j, frame_elements[5], COLOR_BLACK, COLOR_WHITE); // ����
        }
    }

    // �����±߿�
    cct_showstr(x, y + height - 1, frame_elements[1], COLOR_BLACK, COLOR_WHITE); // ���½�
    for (int i = 1; i < width - 1; i++)
    {
        if (has_separators && i % 3 == 0)
        {
            cct_showstr(x + i, y + height - 1, frame_elements[7], COLOR_BLACK,
                        COLOR_WHITE); // ��T��
        }
        else
        {
            cct_showstr(x + i, y + height - 1, frame_elements[4], COLOR_BLACK, COLOR_WHITE); // ����
        }
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

    // �����Ƿ��зָ���ȷ����Ԫ���С
    int cell_width = params.has_separators ? 3 : 2;
    int cell_height = params.has_separators ? 2 : 1;

    // ��������С
    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.rows * cell_height + 1;

    // ���Ʊ߿�
    draw_frame(5, 3, matrix_width, matrix_height, params.has_separators);

    // ��ʾ�б��⣨1,2,3,...��
    for (int j = 0; j < params.cols; j++)
    {
        int x = 5 + j * cell_width + cell_width / 2;
        cct_showint(x, 2, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ�б��⣨A,B,C,...��
    for (int i = 0; i < params.rows; i++)
    {
        int y = 3 + i * cell_height + cell_height / 2;
        cct_showch(3, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ��������
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            int x = 6 + j * cell_width;
            int y = 3 + i * cell_height + 1;

            if (params.cheat_mode && matrix.solution[i][j])
            {
                display_cell(j, i, FILLED, params.has_separators);
            }
            else
            {
                display_cell(j, i, EMPTY, params.has_separators);
            }
        }
    }
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

    // �����Ƿ��зָ���ȷ����Ԫ���С
    int cell_width = params.has_separators ? 3 : 2;
    int cell_height = params.has_separators ? 2 : 1;

    // ��������С��λ��
    int hint_width = matrix.hint_width * 3;
    int hint_height = matrix.hint_height * 2;

    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.rows * cell_height + 1;

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;

    // ���ƾ���߿�
    draw_frame(matrix_x, matrix_y, matrix_width, matrix_height, params.has_separators);

    // ��ʾ�б��⣨1,2,3,...��
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + j * cell_width + cell_width / 2;
        cct_showint(x, matrix_y - 1, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ�б��⣨A,B,C,...��
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + i * cell_height + cell_height / 2;
        cct_showch(matrix_x - 2, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ��������
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            if (params.cheat_mode && matrix.solution[i][j])
            {
                display_cell(matrix_x + 1 + j * cell_width, matrix_y + 1 + i * cell_height, FILLED,
                             params.has_separators);
            }
            else
            {
                display_cell(matrix_x + 1 + j * cell_width, matrix_y + 1 + i * cell_height, EMPTY,
                             params.has_separators);
            }
        }
    }

    // ��ʾ����ʾ
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + i * cell_height + cell_height / 2;
        int hint_x = matrix_x - 3 - hint_width;

        // �Ҷ�����ʾ
        for (int h = 0; h < matrix.row_hint_count[i]; h++)
        {
            int x = hint_x + (matrix.hint_width - matrix.row_hint_count[i] + h) * 3;
            cct_showint(x, y, matrix.row_hints[i][h], COLOR_BLACK, COLOR_WHITE);
        }
    }

    // ��ʾ����ʾ
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + j * cell_width + cell_width / 2;
        int hint_y = matrix_y - 2 - hint_height;

        // �¶�����ʾ
        for (int h = 0; h < matrix.col_hint_count[j]; h++)
        {
            int y = hint_y + (matrix.hint_height - matrix.col_hint_count[j] + h) * 2;
            cct_showint(x, y, matrix.col_hints[j][h], COLOR_BLACK, COLOR_WHITE);
        }
    }
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
            bool& is_valid - �����Ƿ���Ч
  �� �� ֵ����
  ˵    �����������Ƿ�����Ч�ľ��������ڣ���ת������
***************************************************************************/
void convert_mouse_to_cell(int mx, int my, int &row, int &col, const GameParams &params,
                           bool &is_valid)
{
    // �����Ƿ��зָ���ȷ����Ԫ���С
    int cell_width = params.has_separators ? 3 : 2;
    int cell_height = params.has_separators ? 2 : 1;

    // ��������С��λ��
    int hint_width = 0;
    int hint_height = 0;

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;

    // �������Ƿ��ھ���������
    if (mx >= matrix_x && mx < matrix_x + params.cols * cell_width + 1 && my >= matrix_y &&
        my < matrix_y + params.rows * cell_height + 1)
    {

        // ������������
        col = (mx - matrix_x) / cell_width;
        row = (my - matrix_y) / cell_height;

        // �������Ƿ��ڷָ�����
        if (params.has_separators)
        {
            int cell_x = (mx - matrix_x) % cell_width;
            int cell_y = (my - matrix_y) % cell_height;

            if (cell_x == 0 || cell_y == 0)
            {
                is_valid = false;
                return;
            }
        }

        // ��������Ƿ�����Ч��Χ��
        if (row >= 0 && row < params.rows && col >= 0 && col < params.cols)
        {
            is_valid = true;
            return;
        }
    }

    is_valid = false;
}