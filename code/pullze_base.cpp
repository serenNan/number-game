#include "pullze.h"

/***************************************************************************
  函数名称：init_game
  功    能：初始化游戏矩阵
  输入参数：无
  返 回 值：无
  说    明：清空矩阵，准备新游戏
***************************************************************************/
void init_game()
{
    // 初始化cells数组为空
    for (int i = 0; i < g_rows; i++)
    {
        for (int j = 0; j < g_cols; j++)
        {
            g_cells[i][j] = EMPTY;
            g_solution[i][j] = false;
        }
    }

    // 初始化提示数组
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

    // 提示区宽度和高度初始化为0
    g_hint_width = 0;
    g_hint_height = 0;
}

/***************************************************************************
  函数名称：generate_matrix
  功    能：生成游戏矩阵(随机生成一半的球)
  输入参数：无
  返 回 值：无
  说    明：随机生成矩阵中一半的球
***************************************************************************/
void generate_matrix()
{
    int total_cells = g_rows * g_cols;
    int balls_count = (total_cells + 1) / 2; // 向上取整

    // 初始时所有位置都没有球
    for (int i = 0; i < g_rows; i++)
    {
        for (int j = 0; j < g_cols; j++)
        {
            g_solution[i][j] = false;
        }
    }

    // 随机放置球
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
  函数名称：calculate_hints
  功    能：计算行和列的提示数字
  输入参数：无
  返 回 值：无
  说    明：计算每行每列的连续球数提示
***************************************************************************/
void calculate_hints()
{
    // 计算行提示
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

            // 如果遇到空位或者到达行尾，而且之前有连续的球
            if ((!g_solution[i][j] || j == g_cols - 1) && count > 0)
            {
                // 如果是行尾而且最后一个位置有球，需要特殊处理
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

        // 如果这一行没有任何球，放一个0
        if (hint_idx == 0)
        {
            g_row_hints[i][hint_idx++] = 0;
        }

        g_row_hint_count[i] = hint_idx;
    }

    // 计算列提示
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

            // 如果遇到空位或者到达列尾，而且之前有连续的球
            if ((!g_solution[i][j] || i == g_rows - 1) && count > 0)
            {
                // 如果是列尾而且最后一个位置有球，需要特殊处理
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

        // 如果这一列没有任何球，放一个0
        if (hint_idx == 0)
        {
            g_col_hints[j][hint_idx++] = 0;
        }

        g_col_hint_count[j] = hint_idx;
    }

    // 计算提示区域的宽度和高度
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
  函数名称：validate_solution
  功    能：验证玩家的解答是否正确
  输入参数：int& error_row - 错误的行 (如果有)
            int& error_col - 错误的列 (如果有)
  返 回 值：bool - 是否正确
  说    明：验证玩家的解答，并返回第一个错误的位置
***************************************************************************/
bool validate_solution(int &error_row, int &error_col)
{
    for (int i = 0; i < g_rows; i++)
    {
        for (int j = 0; j < g_cols; j++)
        {
            // 检查每个位置
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
  函数名称：mark_cell
  功    能：标记或取消标记一个单元格
  输入参数：int row - 行索引
            int col - 列索引
            int mark_type - 标记类型 (1: 左键 - 有球, 2: 右键 - 无球)
  返 回 值：无
  说    明：改变单元格的状态
***************************************************************************/
void mark_cell(int row, int col, int mark_type)
{
    // 检查行列坐标的有效性
    if (row < 0 || row >= g_rows || col < 0 || col >= g_cols)
    {
        return;
    }

    // 根据标记类型和当前状态进行更新
    if (mark_type == 1)
    { // 左键 - 标记为有球
        if (g_cells[row][col] == EMPTY || g_cells[row][col] == MARKED_NOT)
        {
            // 在作弊模式下区分正确和错误的标记
            if (g_cheat_mode)
            {
                if (g_solution[row][col])
                {
                    g_cells[row][col] = MARKED; // 正确标记
                }
                else
                {
                    g_cells[row][col] = MARKED_WRONG; // 错误标记
                }
            }
            else
            {
                g_cells[row][col] = MARKED; // 普通标记
            }
        }
        else if (g_cells[row][col] == MARKED || g_cells[row][col] == MARKED_WRONG)
        {
            g_cells[row][col] = EMPTY; // 取消标记
        }
    }
    else if (mark_type == 2)
    { // 右键 - 标记为无球
        if (g_cells[row][col] == EMPTY)
        {
            g_cells[row][col] = MARKED_NOT; // 标记为无球
        }
        else if (g_cells[row][col] == MARKED_NOT)
        {
            g_cells[row][col] = EMPTY; // 取消标记
        }
    }
}