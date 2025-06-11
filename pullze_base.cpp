#include "pullze.h"

/***************************************************************************
  �������ƣ�init_game
  ��    �ܣ���ʼ����Ϸ����
  ���������GameMatrix& matrix - ��Ϸ����
            const GameParams& params - ��Ϸ����
  �� �� ֵ����
  ˵    ������վ���׼������Ϸ
***************************************************************************/
void init_game(GameMatrix &matrix, const GameParams &params)
{
    // ��ʼ��cells����Ϊ��
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            matrix.cells[i][j] = EMPTY;
            matrix.solution[i][j] = false;
        }
    }

    // ��ʼ����ʾ����
    for (int i = 0; i < params.rows; i++)
    {
        matrix.row_hint_count[i] = 0;
        for (int j = 0; j < MAX_MATRIX_SIZE / 2; j++)
        {
            matrix.row_hints[i][j] = 0;
        }
    }

    for (int i = 0; i < params.cols; i++)
    {
        matrix.col_hint_count[i] = 0;
        for (int j = 0; j < MAX_MATRIX_SIZE / 2; j++)
        {
            matrix.col_hints[i][j] = 0;
        }
    }

    // ��ʾ����Ⱥ͸߶ȳ�ʼ��Ϊ0
    matrix.hint_width = 0;
    matrix.hint_height = 0;
}

/***************************************************************************
  �������ƣ�generate_matrix
  ��    �ܣ�������Ϸ����(�������һ�����)
  ���������GameMatrix& matrix - ��Ϸ����
            const GameParams& params - ��Ϸ����
  �� �� ֵ����
  ˵    ����������ɾ�����һ�����
***************************************************************************/
void generate_matrix(GameMatrix &matrix, const GameParams &params)
{
    int total_cells = params.rows * params.cols;
    int balls_count = (total_cells + 1) / 2; // ����ȡ��

    // ��ʼʱ����λ�ö�û����
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            matrix.solution[i][j] = false;
        }
    }

    // ���������
    while (balls_count > 0)
    {
        int row = rand() % params.rows;
        int col = rand() % params.cols;

        if (!matrix.solution[row][col])
        {
            matrix.solution[row][col] = true;
            balls_count--;
        }
    }
}

/***************************************************************************
  �������ƣ�calculate_hints
  ��    �ܣ������к��е���ʾ����
  ���������GameMatrix& matrix - ��Ϸ����
            const GameParams& params - ��Ϸ����
  �� �� ֵ����
  ˵    ��������ÿ��ÿ�е�����������ʾ
***************************************************************************/
void calculate_hints(GameMatrix &matrix, const GameParams &params)
{
    // ��������ʾ
    for (int i = 0; i < params.rows; i++)
    {
        int count = 0;
        int hint_idx = 0;

        for (int j = 0; j < params.cols; j++)
        {
            if (matrix.solution[i][j])
            {
                count++;
            }

            // ���������λ���ߵ�����β������֮ǰ����������
            if ((!matrix.solution[i][j] || j == params.cols - 1) && count > 0)
            {
                // �������β�������һ��λ��������Ҫ���⴦��
                if (j == params.cols - 1 && matrix.solution[i][j])
                {
                    matrix.row_hints[i][hint_idx++] = count;
                }
                else
                {
                    matrix.row_hints[i][hint_idx++] = count;
                }
                count = 0;
            }
        }

        // �����һ��û���κ��򣬷�һ��0
        if (hint_idx == 0)
        {
            matrix.row_hints[i][hint_idx++] = 0;
        }

        matrix.row_hint_count[i] = hint_idx;
    }

    // ��������ʾ
    for (int j = 0; j < params.cols; j++)
    {
        int count = 0;
        int hint_idx = 0;

        for (int i = 0; i < params.rows; i++)
        {
            if (matrix.solution[i][j])
            {
                count++;
            }

            // ���������λ���ߵ�����β������֮ǰ����������
            if ((!matrix.solution[i][j] || i == params.rows - 1) && count > 0)
            {
                // �������β�������һ��λ��������Ҫ���⴦��
                if (i == params.rows - 1 && matrix.solution[i][j])
                {
                    matrix.col_hints[j][hint_idx++] = count;
                }
                else
                {
                    matrix.col_hints[j][hint_idx++] = count;
                }
                count = 0;
            }
        }

        // �����һ��û���κ��򣬷�һ��0
        if (hint_idx == 0)
        {
            matrix.col_hints[j][hint_idx++] = 0;
        }

        matrix.col_hint_count[j] = hint_idx;
    }

    // ������ʾ����Ŀ�Ⱥ͸߶�
    int max_row_hints = 0;
    for (int i = 0; i < params.rows; i++)
    {
        if (matrix.row_hint_count[i] > max_row_hints)
        {
            max_row_hints = matrix.row_hint_count[i];
        }
    }
    matrix.hint_width = max_row_hints;

    int max_col_hints = 0;
    for (int j = 0; j < params.cols; j++)
    {
        if (matrix.col_hint_count[j] > max_col_hints)
        {
            max_col_hints = matrix.col_hint_count[j];
        }
    }
    matrix.hint_height = max_col_hints;
}

/***************************************************************************
  �������ƣ�validate_solution
  ��    �ܣ���֤��ҵĽ���Ƿ���ȷ
  ���������const GameMatrix& matrix - ��Ϸ����
            const GameParams& params - ��Ϸ����
            int& error_row - ������� (�����)
            int& error_col - ������� (�����)
  �� �� ֵ��bool - �Ƿ���ȷ
  ˵    ������֤��ҵĽ�𣬲����ص�һ�������λ��
***************************************************************************/
bool validate_solution(const GameMatrix &matrix, const GameParams &params, int &error_row,
                       int &error_col)
{
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            // ���ÿ��λ��
            if ((matrix.cells[i][j] == MARKED && !matrix.solution[i][j]) ||
                (matrix.cells[i][j] != MARKED && matrix.solution[i][j]))
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
  ���������GameMatrix& matrix - ��Ϸ����
            const GameParams& params - ��Ϸ����
            int row - ������
            int col - ������
            int mark_type - ������� (1: ��� - ����, 2: �Ҽ� - ����)
  �� �� ֵ����
  ˵    �����ı䵥Ԫ���״̬
***************************************************************************/
void mark_cell(GameMatrix &matrix, const GameParams &params, int row, int col, int mark_type)
{
    // ��������������Ч��
    if (row < 0 || row >= params.rows || col < 0 || col >= params.cols)
    {
        return;
    }

    // ���ݱ�����ͺ͵�ǰ״̬���и���
    if (mark_type == 1)
    { // ��� - ���Ϊ����
        if (matrix.cells[row][col] == EMPTY || matrix.cells[row][col] == MARKED_NOT)
        {
            // ���������ģʽ������Ƿ���ȷ
            if (params.cheat_mode)
            {
                if (matrix.solution[row][col])
                {
                    matrix.cells[row][col] = MARKED;
                }
                else
                {
                    matrix.cells[row][col] = MARKED_WRONG;
                }
            }
            else
            {
                matrix.cells[row][col] = MARKED;
            }
        }
        else if (matrix.cells[row][col] == MARKED || matrix.cells[row][col] == MARKED_WRONG)
        {
            // ȡ�����
            matrix.cells[row][col] = EMPTY;
        }
    }
    else if (mark_type == 2)
    { // �Ҽ� - ���Ϊ����
        if (matrix.cells[row][col] == EMPTY || matrix.cells[row][col] == MARKED ||
            matrix.cells[row][col] == MARKED_WRONG)
        {
            matrix.cells[row][col] = MARKED_NOT;
        }
        else if (matrix.cells[row][col] == MARKED_NOT)
        {
            // ȡ�����
            matrix.cells[row][col] = EMPTY;
        }
    }
}