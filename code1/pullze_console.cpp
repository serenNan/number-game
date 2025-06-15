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

    // ���ƶ����߿�
    cout << "  +";
    for (int j = 0; j < params.cols; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+";
        cout << "--";
    }
    cout << "-+" << endl;

    // ��ʾ�б�����
    cout << "  |";
    for (int j = 0; j < params.cols; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << " |";
        cout << " " << (char)('a' + j);
    }
    cout << " |" << endl;

    // �����б����·��ķָ���
    cout << "+-+";
    for (int j = 0; j < params.cols; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+";
        cout << "--";
    }
    cout << "-+" << endl;

    // ��ʾ��������
    for (int i = 0; i < params.rows; i++)
    {
        // ��ʾ�б��⣨A,B,C,...��
        cout << (char)('A' + i) << " |";

        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << " |";
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
        cout << " |" << endl;

        // ÿ5����ӷָ���
        if ((i + 1) % 5 == 0 && i < params.rows - 1)
        {
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

    // ���Ƶײ��߿�
    cout << "+-+";
    for (int j = 0; j < params.cols; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+";
        cout << "--";
    }
    cout << "-+" << endl;
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

    // ��������ʾ�����߶�
    int max_col_hints = 0;
    for (int j = 0; j < params.cols; j++)
    {
        if (matrix.col_hint_count[j] > max_col_hints)
        {
            max_col_hints = matrix.col_hint_count[j];
        }
    }

    // ��ӡ�����߿�
    for (int i = 0; i < hint_width + 2; ++i)
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

    // ��ʾ����ʾ���¶��룩
    for (int h = 0; h < max_col_hints; h++)
    {
        // ����ʾ����������
        cout << setw(hint_width + 5) << "  |";

        // ��ӡ����ʾ���¶��룩
        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << " |"; // ÿ5�зָ���
            int index = matrix.col_hint_count[j] - max_col_hints + h;
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
    for (int i = 0; i < hint_width + 2; ++i)
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
    cout << setw(hint_width + 2) << " " << "  |";
    for (int j = 0; j < params.cols; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << " |";
        cout << " " << static_cast<char>('a' + j);
    }
    cout << " |" << endl;

    // ��ӡ�б�ǩ�µķָ���
    for (int i = 0; i < hint_width + 2; ++i)
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
        string row_hint_str = "";
        for (int h = 0; h < matrix.row_hint_count[i]; h++)
        {
            if (h > 0)
                row_hint_str += " ";
            row_hint_str += to_string(matrix.row_hints[i][h]);
        }

        // ��ʾ����ʾ���Ҷ���
        cout << " " << setw(hint_width) << row_hint_str << " |" << static_cast<char>('A' + i)
             << "|";

        // ��ʾ����
        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << " |";

            // ��������ģʽ��ʾ��Ԫ������
            if (params.cheat_mode && matrix.solution[i][j])
            {
                cout << " O"; // ��ʾ����
            }
            else
            {
                cout << "  "; // �հ�
            }
        }
        cout << " |" << endl;

        // ÿ5�����һ���ָ���
        if ((i + 1) % 5 == 0 && i < params.rows - 1)
        {
            for (int i = 0; i < hint_width + 2; ++i)
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
    for (int i = 0; i < hint_width + 2; ++i)
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

    // ����״̬�������ݺ���ɫ
    switch (status)
    {
    case EMPTY:
        // �ո񣬲���ʾ�κ�����
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, " ", COLOR_BLACK, COLOR_WHITE);
        break;

    case FILLED:
        // ��ʾO��ʾ���򣬰׵׺���
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "O", COLOR_BLACK, COLOR_WHITE);
        break;

    case MARKED:
        // ����ģʽ�£���ɫ����O�����ѡ��
        cct_setcolor(COLOR_BLUE, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "O", COLOR_BLUE, COLOR_WHITE);
        break;

    case MARKED_WRONG:
        // ��ʾX��ʾ�����ǣ���װ���
        cct_setcolor(COLOR_RED, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "X", COLOR_RED, COLOR_WHITE);
        break;

    case MARKED_NOT:
        // ����ģʽ�£���ɫ����X���Ҽ���ע��
        cct_setcolor(COLOR_RED, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "X", COLOR_RED, COLOR_WHITE);
        break;

    // ����������ģʽ�µ�������ʾ״̬
    case CHEAT_EMPTY:
        // ��ɫ����O��������δѡ��
        cct_setcolor(COLOR_HBLACK, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "O", COLOR_HBLACK, COLOR_WHITE);
        break;

    case CHEAT_MARKED:
        // ��ɫ����O�������������ѡ��
        cct_setcolor(COLOR_BLUE, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "O", COLOR_BLUE, COLOR_WHITE);
        break;

    case CHEAT_WRONG:
        // ��ɫ����O�����������ѡ��
        cct_setcolor(COLOR_RED, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "O", COLOR_RED, COLOR_WHITE);
        break;

    case CHEAT_NOT_RIGHT:
        // ��ɫ����X���������Ҽ���ע
        cct_setcolor(COLOR_RED, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "X", COLOR_RED, COLOR_WHITE);
        break;

    case CHEAT_BALL_RIGHT:
        // ��ɫ����X���������Ҽ���ע
        cct_setcolor(COLOR_BLUE, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "X", COLOR_BLUE, COLOR_WHITE);
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
    const char *frame_elements[] = {"�X", "�^", "�[", "�a", "�T", "�U", "�j", "�m", "�d", "�g", "�p"};

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
        cct_showstr(x, y, frame_elements[0], COLOR_BLACK, COLOR_WHITE); // ���Ͻ�
        for (int j = 0; j < cols; j++)
        {
            // ÿ����Ԫ��Ķ�������
            for (int i = 0; i < cell_width - 1; i++)
            {
                cct_showstr(x + j * cell_width + i + 1, y, frame_elements[4], COLOR_BLACK,
                            COLOR_WHITE);
            }
            // ÿ����Ԫ��Ķ�������㣨�������һ�У�
            if (j < cols - 1)
            {
                cct_showstr(x + (j + 1) * cell_width, y, frame_elements[6], COLOR_BLACK,
                            COLOR_WHITE);
            }
        }
        cct_showstr(x + width - 1, y, frame_elements[2], COLOR_BLACK, COLOR_WHITE); // ���Ͻ�

        // �����м���
        for (int i = 0; i < rows; i++)
        {
            // ���Ƶ�Ԫ���ڲ�
            for (int k = 1; k < cell_height; k++)
            {
                // ÿ�е���߿�
                cct_showstr(x, y + i * cell_height + k, frame_elements[5], COLOR_BLACK,
                            COLOR_WHITE);

                // ÿ����Ԫ����ڲ��ʹ�ֱ�ָ���
                for (int j = 0; j < cols; j++)
                {
                    // ��Ԫ���ڲ��հ�����
                    for (int l = 1; l < cell_width; l++)
                    {
                        cct_showstr(x + j * cell_width + l, y + i * cell_height + k, " ",
                                    COLOR_BLACK, COLOR_WHITE);
                    }
                    // ��ֱ�ָ��ߣ��������һ�У�
                    if (j < cols - 1)
                    {
                        cct_showstr(x + (j + 1) * cell_width, y + i * cell_height + k,
                                    frame_elements[5], COLOR_BLACK, COLOR_WHITE);
                    }
                }
                // ÿ�е��ұ߿�
                cct_showstr(x + width - 1, y + i * cell_height + k, frame_elements[5], COLOR_BLACK,
                            COLOR_WHITE);
            }

            // �����зָ��ߣ��������һ�У�
            if (i < rows - 1)
            {
                // �зָ��ߵ�������ӵ�
                cct_showstr(x, y + (i + 1) * cell_height, frame_elements[8], COLOR_BLACK,
                            COLOR_WHITE);

                // ÿ����Ԫ���ˮƽ�ָ��ߺͽ����
                for (int j = 0; j < cols; j++)
                {
                    // ˮƽ�ָ���
                    for (int l = 1; l < cell_width; l++)
                    {
                        cct_showstr(x + j * cell_width + l, y + (i + 1) * cell_height,
                                    frame_elements[4], COLOR_BLACK, COLOR_WHITE);
                    }
                    // ����㣨�������һ�У�
                    if (j < cols - 1)
                    {
                        cct_showstr(x + (j + 1) * cell_width, y + (i + 1) * cell_height,
                                    frame_elements[10], COLOR_BLACK, COLOR_WHITE);
                    }
                }
                // �зָ��ߵ��Ҳ����ӵ�
                cct_showstr(x + width - 1, y + (i + 1) * cell_height, frame_elements[9],
                            COLOR_BLACK, COLOR_WHITE);
            }
        }

        // ���Ƶײ��߿�
        cct_showstr(x, y + height - 1, frame_elements[1], COLOR_BLACK, COLOR_WHITE); // ���½�
        for (int j = 0; j < cols; j++)
        {
            // ÿ����Ԫ��ĵײ�����
            for (int i = 0; i < cell_width - 1; i++)
            {
                cct_showstr(x + j * cell_width + i + 1, y + height - 1, frame_elements[4],
                            COLOR_BLACK, COLOR_WHITE);
            }
            // ÿ����Ԫ��ĵײ�����㣨�������һ�У�
            if (j < cols - 1)
            {
                cct_showstr(x + (j + 1) * cell_width, y + height - 1, frame_elements[7],
                            COLOR_BLACK, COLOR_WHITE);
            }
        }
        cct_showstr(x + width - 1, y + height - 1, frame_elements[3], COLOR_BLACK,
                    COLOR_WHITE); // ���½�
    }
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
    int cell_width = params.has_separators ? 5 : 2; // �зָ���ʱÿ����Ԫ��ռ5�У�����ռ2��

    // ��������С
    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.has_separators ? params.rows * 3 + 1
                                              : params.rows + 2; // �зָ���ʱÿ��ռ3�У�����ռ1��

    // ���Ʊ߿�
    draw_frame(5, 3, matrix_width, matrix_height, params.has_separators);

    // ��ʾ�б��⣨1,2,3,...��
    for (int j = 0; j < params.cols; j++)
    {
        int x = 6 + j * cell_width;
        if (params.has_separators)
        {
            x = 5 + j * cell_width + cell_width / 2;
        }
        cct_showint(x, 2, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ�б��⣨A,B,C,...��
    for (int i = 0; i < params.rows; i++)
    {
        int y = 4 + i;
        if (params.has_separators)
        {
            y = 3 + i * 3 + 2; // ��ÿ����Ԫ����м�����ʾ
        }
        cct_showch(3, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ��������
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            int x = 6 + j * cell_width;
            int y = 4 + i;

            if (params.has_separators)
            {
                x = 5 + j * cell_width + 1; // ��Ԫ�����Ͻ�
                y = 3 + i * 3 + 1;          // ��Ԫ�����Ͻ�
            }

            if (params.cheat_mode && matrix.solution[i][j] && matrix.cells[i][j] == EMPTY)
            {
                display_cell(x, y, FILLED, params.has_separators);
            }
            else
            {
                display_cell(x, y, matrix.cells[i][j], params.has_separators);
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
    int cell_width = params.has_separators ? 5 : 2; // �зָ���ʱÿ����Ԫ��ռ5�У�����ռ2��

    // ��������С��λ��
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;

    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.has_separators ? params.rows * 3 + 1
                                              : params.rows + 2; // �зָ���ʱÿ��ռ3�У�����ռ1��

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
    draw_frame(matrix_x, matrix_y, matrix_width, matrix_height, params.has_separators);

    // ��ʾ�б��⣨a,b,c,...��
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + 1 + j * cell_width;
        if (params.has_separators)
        {
            x = matrix_x + j * cell_width + cell_width / 2;
        }
        cct_showch(x, matrix_y - 1, 'a' + j, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ�б��⣨A,B,C,...��
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + 1 + i;
        if (params.has_separators)
        {
            y = matrix_y + i * 3 + 2; // ��ÿ����Ԫ����м�����ʾ
        }
        cct_showch(matrix_x - 2, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // ��ʾ��������
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            int x = matrix_x + 1 + j * cell_width;
            int y = matrix_y + 1 + i;

            if (params.has_separators)
            {
                x = matrix_x + j * cell_width + 1; // ��Ԫ�����Ͻ�
                y = matrix_y + i * 3 + 1;          // ��Ԫ�����Ͻ�
            }

            if (params.cheat_mode)
            {
                // ����ģʽ�µ���ʾ�߼�
                if (matrix.solution[i][j]) // ����
                {
                    if (matrix.cells[i][j] == EMPTY) // ������δѡ��
                    {
                        display_cell(x, y, CHEAT_EMPTY, params.has_separators);
                    }
                    else if (matrix.cells[i][j] == MARKED) // �����������ѡ��
                    {
                        display_cell(x, y, CHEAT_MARKED, params.has_separators);
                    }
                    else if (matrix.cells[i][j] == MARKED_NOT) // �������Ҽ���ע
                    {
                        display_cell(x, y, CHEAT_BALL_RIGHT, params.has_separators);
                    }
                }
                else // ����
                {
                    if (matrix.cells[i][j] == MARKED) // ���������ѡ��
                    {
                        display_cell(x, y, CHEAT_WRONG, params.has_separators);
                    }
                    else if (matrix.cells[i][j] == MARKED_NOT) // �������Ҽ���ע
                    {
                        display_cell(x, y, CHEAT_NOT_RIGHT, params.has_separators);
                    }
                    else // ������δѡ��
                    {
                        display_cell(x, y, EMPTY, params.has_separators);
                    }
                }
            }
            else
            {
                // ����ģʽ�µ���ʾ�߼�
                display_cell(x, y, matrix.cells[i][j], params.has_separators);
            }
        }
    }

    // ��ʾ����ʾ
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + 1 + i;
        if (params.has_separators)
        {
            y = matrix_y + i * 3 + 2; // ��ÿ����Ԫ����м�����ʾ
        }

        // ������ʾ���ڲ��Ҷ�����ʾ
        for (int h = 0; h < matrix.row_hint_count[i]; h++)
        {
            // ������ʾλ�ã��Ҷ��룩
            int x = row_hint_x + 1 + (hint_width - matrix.row_hint_count[i] * 2 + h * 2);
            cct_showint(x, y, matrix.row_hints[i][h], COLOR_BLACK, COLOR_WHITE);
        }
    }

    // ��ʾ����ʾ
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + 1 + j * cell_width;
        if (params.has_separators)
        {
            x = matrix_x + j * cell_width + cell_width / 2;
        }

        // ������ʾ���ڲ��¶�����ʾ
        for (int h = 0; h < matrix.col_hint_count[j]; h++)
        {
            // ������ʾλ�ã��¶��룩
            int y = col_hint_y + 1 + (hint_height - matrix.col_hint_count[j] + h);
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
    // ����Ĭ����ɫ
    cct_setcolor();

    // ��������С��λ��
    int cell_width = params.has_separators ? 5 : 2;  // �зָ���ʱÿ����Ԫ��ռ5�У�����ռ2��
    int cell_height = params.has_separators ? 3 : 1; // �зָ���ʱÿ����Ԫ��ռ3�У�����ռ1��

    // ������ײ�λ�ã�ȷ��������ʾ��ʾ�ڱ���·�
    int hint_height = 3; // ������ʾ���߶�
    int matrix_height = params.has_separators ? params.rows * 3 + 1 : params.rows + 2;
    int bottom_y = 3 + hint_height + matrix_height + 2;

    // �ƶ���״̬��λ��
    cct_gotoxy(0, bottom_y);

    // ��ʾ���������Ϣ
    cout << "���λ��: X=" << setw(3) << mx << ", Y=" << setw(3) << my;

    // ����ת��Ϊ��������
    int row, col;
    bool is_valid;
    GameMatrix dummy_matrix; // ����һ����ʱ������������ת��
    dummy_matrix.hint_width = 3;
    dummy_matrix.hint_height = 3;

    convert_mouse_to_cell(mx, my, row, col, params, dummy_matrix, is_valid);

    // ��ʾ�������꣨�����Ч��
    if (is_valid)
    {
        cout << " | ��������: ��=" << (char)('A' + row) << ", ��=" << (char)('a' + col);
    }
    else
    {
        cout << " | ��������: ��Чλ��                ";
    }

    // �����β���ܵĲ����ַ�
    cout << "                    ";
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
    int cell_width = params.has_separators ? 5 : 2;  // �зָ���ʱÿ����Ԫ��ռ5�У�����ռ2��
    int cell_height = params.has_separators ? 3 : 1; // �зָ���ʱÿ����Ԫ��ռ3�У�����ռ1��

    // ��������С��λ��
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;
    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.rows * cell_height + 1;

    // ��ʼ��Ϊ��Чֵ
    row = -1;
    col = -1;
    is_valid = false;

    // �������Ƿ��ھ���������
    if (mx < matrix_x || mx >= matrix_x + matrix_width || my < matrix_y ||
        my >= matrix_y + matrix_height)
    {
        return; // ��겻�ھ���������
    }

    // ������������
    if (params.has_separators)
    {
        // �зָ���ģʽ
        // �ų��߿��ߺͷָ��ߵĵ��
        int rel_x = mx - matrix_x;
        int rel_y = my - matrix_y;

        // ����Ƿ����ڱ߿��ָ�����
        if (rel_x % cell_width == 0 || rel_y % cell_height == 0)
        {
            return; // ����ڱ߿��ָ����ϣ���Ч
        }

        col = rel_x / cell_width;
        row = rel_y / cell_height;
    }
    else
    {
        // �޷ָ���ģʽ
        // �������������(matrix_x+1, matrix_y+1)��ʼ
        if (mx >= matrix_x + 1 && mx < matrix_x + 1 + params.cols * cell_width &&
            my >= matrix_y + 1 && my < matrix_y + 1 + params.rows)
        {
            col = (mx - matrix_x - 1) / cell_width;
            row = my - matrix_y - 1;
        }
    }

    // ��֤������������Ƿ���Ч
    if (row >= 0 && row < params.rows && col >= 0 && col < params.cols)
    {
        is_valid = true;
    }
}