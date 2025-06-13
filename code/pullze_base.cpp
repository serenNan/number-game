#include "pullze.h"

/***************************************************************************
  �������ƣ�init_game
  ��    �ܣ���ʼ����Ϸ����
  �����������
  �� �� ֵ����
  ˵    ������վ���׼������Ϸ
***************************************************************************/
void init_game()
{
    // ��ʼ��cells����Ϊ��
    for (int i = 0; i < g_rows; i++)
    {
        for (int j = 0; j < g_cols; j++)
        {
            g_cells[i][j] = EMPTY;
            g_solution[i][j] = false;
        }
    }

    // ��ʼ����ʾ����
    for (int i = 0; i < g_rows; i++)
    {
        g_row_hint_count[i] = 0;
        for (int j = 0; j < MAX_MATRIX_SIZE / 2; j++)
        {
            g_row_hints[i][j] = 0;
        }
    }

    for (int i = 0; i < g_cols; i++)
    {
        g_col_hint_count[i] = 0;
        for (int j = 0; j < MAX_MATRIX_SIZE / 2; j++)
        {
            g_col_hints[i][j] = 0;
        }
    }

    // ��ʾ����Ⱥ͸߶ȳ�ʼ��Ϊ0
    g_hint_width = 0;
    g_hint_height = 0;
}

/***************************************************************************
  �������ƣ�generate_matrix
  ��    �ܣ�������Ϸ����(�������һ�����)
  �����������
  �� �� ֵ����
  ˵    ����������ɾ�����һ�����
***************************************************************************/
void generate_matrix()
{
    int total_cells = g_rows * g_cols;
    int balls_count = (total_cells + 1) / 2; // ����ȡ��

    // ��ʼʱ����λ�ö�û����
    for (int i = 0; i < g_rows; i++)
    {
        for (int j = 0; j < g_cols; j++)
        {
            g_solution[i][j] = false;
        }
    }

    // ���������
    while (balls_count > 0)
    {
        int row = rand() % g_rows;
        int col = rand() % g_cols;

        if (!g_solution[row][col])
        {
            g_solution[row][col] = true;
            balls_count--;
        }
    }
}

/***************************************************************************
  �������ƣ�calculate_hints
  ��    �ܣ������к��е���ʾ����
  �����������
  �� �� ֵ����
  ˵    ��������ÿ��ÿ�е�����������ʾ
***************************************************************************/
void calculate_hints()
{
    // ��������ʾ
    for (int i = 0; i < g_rows; i++)
    {
        int count = 0;
        int hint_idx = 0;

        for (int j = 0; j < g_cols; j++)
        {
            if (g_solution[i][j])
            {
                count++;
            }

            // ���������λ���ߵ�����β������֮ǰ����������
            if ((!g_solution[i][j] || j == g_cols - 1) && count > 0)
            {
                // �������β�������һ��λ��������Ҫ���⴦��
                if (j == g_cols - 1 && g_solution[i][j])
                {
                    g_row_hints[i][hint_idx++] = count;
                }
                else
                {
                    g_row_hints[i][hint_idx++] = count;
                }
                count = 0;
            }
        }

        // �����һ��û���κ��򣬷�һ��0
        if (hint_idx == 0)
        {
            g_row_hints[i][hint_idx++] = 0;
        }

        g_row_hint_count[i] = hint_idx;
    }

    // ��������ʾ
    for (int j = 0; j < g_cols; j++)
    {
        int count = 0;
        int hint_idx = 0;

        for (int i = 0; i < g_rows; i++)
        {
            if (g_solution[i][j])
            {
                count++;
            }

            // ���������λ���ߵ�����β������֮ǰ����������
            if ((!g_solution[i][j] || i == g_rows - 1) && count > 0)
            {
                // �������β�������һ��λ��������Ҫ���⴦��
                if (i == g_rows - 1 && g_solution[i][j])
                {
                    g_col_hints[j][hint_idx++] = count;
                }
                else
                {
                    g_col_hints[j][hint_idx++] = count;
                }
                count = 0;
            }
        }

        // �����һ��û���κ��򣬷�һ��0
        if (hint_idx == 0)
        {
            g_col_hints[j][hint_idx++] = 0;
        }

        g_col_hint_count[j] = hint_idx;
    }

    // ������ʾ����Ŀ�Ⱥ͸߶�
    int max_row_hints = 0;
    for (int i = 0; i < g_rows; i++)
    {
        if (g_row_hint_count[i] > max_row_hints)
        {
            max_row_hints = g_row_hint_count[i];
        }
    }
    g_hint_width = max_row_hints;

    int max_col_hints = 0;
    for (int j = 0; j < g_cols; j++)
    {
        if (g_col_hint_count[j] > max_col_hints)
        {
            max_col_hints = g_col_hint_count[j];
        }
    }
    g_hint_height = max_col_hints;
}

/***************************************************************************
  �������ƣ�validate_solution
  ��    �ܣ���֤��ҵĽ���Ƿ���ȷ
  ���������int& error_row - ������� (�����)
            int& error_col - ������� (�����)
  �� �� ֵ��bool - �Ƿ���ȷ
  ˵    ������֤��ҵĽ�𣬲����ص�һ�������λ��
***************************************************************************/
bool validate_solution(int &error_row, int &error_col)
{
    for (int i = 0; i < g_rows; i++)
    {
        for (int j = 0; j < g_cols; j++)
        {
            // ���ÿ��λ��
            if ((g_cells[i][j] == MARKED && !g_solution[i][j]) ||
                (g_cells[i][j] != MARKED && g_solution[i][j]))
            {
                error_row = i;
                error_col = j;
                return false;
            }
        }
    }
    return true;
}

/***************************************************************************
  �������ƣ�mark_cell
  ��    �ܣ���ǻ�ȡ�����һ����Ԫ��
  ���������int row - ������
            int col - ������
            int mark_type - ������� (1: ��� - ����, 2: �Ҽ� - ����)
  �� �� ֵ����
  ˵    �����ı䵥Ԫ���״̬
***************************************************************************/
void mark_cell(int row, int col, int mark_type)
{
    // ��������������Ч��
    if (row < 0 || row >= g_rows || col < 0 || col >= g_cols)
    {
        return;
    }

    // ���ݱ�����ͺ͵�ǰ״̬���и���
    if (mark_type == 1)
    { // ��� - ���Ϊ����
        if (g_cells[row][col] == EMPTY || g_cells[row][col] == MARKED_NOT)
        {
            // ������ģʽ��������ȷ�ʹ���ı��
            if (g_cheat_mode)
            {
                if (g_solution[row][col])
                {
                    g_cells[row][col] = MARKED; // ��ȷ���
                }
                else
                {
                    g_cells[row][col] = MARKED_WRONG; // ������
                }
            }
            else
            {
                g_cells[row][col] = MARKED; // ��ͨ���
            }
        }
        else if (g_cells[row][col] == MARKED || g_cells[row][col] == MARKED_WRONG)
        {
            g_cells[row][col] = EMPTY; // ȡ�����
        }
    }
    else if (mark_type == 2)
    { // �Ҽ� - ���Ϊ����
        if (g_cells[row][col] == EMPTY)
        {
            g_cells[row][col] = MARKED_NOT; // ���Ϊ����
        }
        else if (g_cells[row][col] == MARKED_NOT)
        {
            g_cells[row][col] = EMPTY; // ȡ�����
        }
    }
}