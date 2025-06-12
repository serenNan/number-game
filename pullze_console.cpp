#include "pullze.h"

/***************************************************************************
  函数名称：display_matrix_text
  功    能：文本模式下显示矩阵
  输入参数：const GameMatrix& matrix - 游戏矩阵
            const GameParams& params - 游戏参数
  返 回 值：无
  说    明：显示行列标识和矩阵内容
***************************************************************************/
void display_matrix_text(const GameMatrix &matrix, const GameParams &params)
{
    // 清屏
    cct_cls();

    cout << "初始数组：" << endl;

    // 不显示提示信息，直接显示矩阵
    // 显示顶部边框和列标题
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

    // 显示矩阵内容
    for (int i = 0; i < params.rows; i++)
    {
        // 显示行标题（A,B,C,...）
        cout << "|" << (char)('A' + i) << "|";

        for (int j = 0; j < params.cols; j++)
        {
            // 根据作弊模式显示单元格内容
            if (params.cheat_mode && matrix.solution[i][j])
            {
                cout << " O";
            }
            else
            {
                cout << "  ";
            }

            // 每5列添加一个分隔符
            if ((j + 1) % 5 == 0 && j < params.cols - 1)
            {
                cout << " |";
            }
        }
        cout << " |" << endl;

        // 每5行添加一个分隔线
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

    // 显示底部边框
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
  函数名称：display_hints_text
  功    能：文本模式下显示提示栏
  输入参数：const GameMatrix& matrix - 游戏矩阵
            const GameParams& params - 游戏参数
  返 回 值：无
  说    明：显示行列提示
***************************************************************************/
void display_hints_text(const GameMatrix &matrix, const GameParams &params)
{
    // 清屏
    cct_cls();

    cout << "初始数组：" << endl;

    // 计算行提示的最大数量
    int max_row_hints = 0;
    for (int i = 0; i < params.rows; i++)
    {
        if (matrix.row_hint_count[i] > max_row_hints)
        {
            max_row_hints = matrix.row_hint_count[i];
        }
    }

    // 计算每个行提示占用的宽度，每个数字2个字符（数字+空格）
    int hint_width = max_row_hints * 2;

    // 显示顶部边框
    cout << string(hint_width + 1, '-') << "+-----------+-----------+" << endl;

    // 计算列提示的最大高度
    int max_col_hints = 0;
    for (int j = 0; j < params.cols; j++)
    {
        if (matrix.col_hint_count[j] > max_col_hints)
        {
            max_col_hints = matrix.col_hint_count[j];
        }
    }

    // 显示列提示（从上往下）
    for (int h = 0; h < max_col_hints; h++)
    {
        cout << string(hint_width + 1, ' ') << "|";

        // 第一组5列
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

        // 第二组5列
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

    // 显示分隔线
    cout << string(hint_width + 1, '-') << "+-----------+-----------+" << endl;

    // 显示列标题
    cout << string(hint_width + 1, ' ') << "|";

    // 第一组5列
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

    // 第二组5列
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

    // 显示行提示区域和矩阵的分隔线
    for (int i = 0; i < hint_width - 1; i++)
    {
        cout << "-";
    }
    cout << "---+-+-----------+-----------+" << endl;

    // 显示矩阵内容和行提示
    for (int i = 0; i < params.rows; i++)
    {
        // 显示行提示，右对齐
        string row_hint_str = "";
        for (int h = 0; h < matrix.row_hint_count[i]; h++)
        {
            row_hint_str += to_string(matrix.row_hints[i][h]) + " ";
        }

        // 确保行提示区域宽度一致
        cout << setw(hint_width) << right << row_hint_str << " |";

        // 显示行标题（A,B,C,...）
        cout << (char)('A' + i) << "|";

        // 第一组5列
        for (int j = 0; j < 5; j++)
        {
            if (j < params.cols)
            {
                // 根据作弊模式显示单元格内容
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

        // 第二组5列
        for (int j = 5; j < 10; j++)
        {
            if (j < params.cols)
            {
                // 根据作弊模式显示单元格内容
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

        // 每5行添加一个分隔线
        if ((i + 1) % 5 == 0 && i < params.rows - 1)
        {
            for (int k = 0; k < hint_width - 1; k++)
            {
                cout << "-";
            }
            cout << "---+-+-----------+-----------+" << endl;
        }
    }

    // 显示底部边框
    for (int i = 0; i < hint_width - 1; i++)
    {
        cout << "-";
    }
    cout << "---+-+-----------+-----------+" << endl;
}

/***************************************************************************
  函数名称：display_cell
  功    能：在指定位置显示单元格
  输入参数：int x - 列坐标
            int y - 行坐标
            CellStatus status - 单元格状态
            bool has_separators - 是否有分隔线
  返 回 值：无
  说    明：根据单元格状态和样式显示不同内容
***************************************************************************/
void display_cell(int x, int y, CellStatus status, bool has_separators)
{
    // 使用绝对坐标
    int screen_x = x;
    int screen_y = y;

    // 根据状态设置内容
    switch (status)
    {
    case EMPTY:
        // 空格，不显示任何内容
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, " ", COLOR_BLACK, COLOR_WHITE);
        break;

    case FILLED:
        // 显示0表示有球，白底黑字
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "0", COLOR_BLACK, COLOR_WHITE);
        break;

    case MARKED:
        // 显示0表示有球，绿底黑字
        cct_setcolor(COLOR_BLACK, COLOR_HGREEN);
        cct_showstr(screen_x, screen_y, "0", COLOR_BLACK, COLOR_HGREEN);
        break;

    case MARKED_WRONG:
        // 显示X表示错误标记，红底黑字
        cct_setcolor(COLOR_BLACK, COLOR_HRED);
        cct_showstr(screen_x, screen_y, "X", COLOR_BLACK, COLOR_HRED);
        break;

    case MARKED_NOT:
        // 显示·表示标记为不存在，蓝底黑字
        cct_setcolor(COLOR_BLACK, COLOR_HBLUE);
        cct_showstr(screen_x, screen_y, "·", COLOR_BLACK, COLOR_HBLUE);
        break;
    }

    // 恢复默认颜色
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
  函数名称：draw_frame
  功    能：绘制游戏边框
  输入参数：int x - 起始x坐标
            int y - 起始y坐标
            int width - 宽度
            int height - 高度
            bool has_separators - 是否有分隔线
  返 回 值：无
  说    明：使用中文制表符绘制边框
***************************************************************************/
void draw_frame(int x, int y, int width, int height, bool has_separators)
{
    // 框架元素
    const char *frame_elements[] = {"╔", "╚", "╗", "╝", "═", "║"};

    // 绘制上边框
    cct_showstr(x, y, frame_elements[0], COLOR_BLACK, COLOR_WHITE); // 左上角
    for (int i = 1; i < width - 1; i++)
    {
        cct_showstr(x + i, y, frame_elements[4], COLOR_BLACK, COLOR_WHITE); // 横线
    }
    cct_showstr(x + width - 1, y, frame_elements[2], COLOR_BLACK, COLOR_WHITE); // 右上角

    // 绘制中间部分
    for (int j = 1; j < height - 1; j++)
    {
        // 左右边框
        cct_showstr(x, y + j, frame_elements[5], COLOR_BLACK, COLOR_WHITE);             // 左边
        cct_showstr(x + width - 1, y + j, frame_elements[5], COLOR_BLACK, COLOR_WHITE); // 右边
    }

    // 绘制下边框
    cct_showstr(x, y + height - 1, frame_elements[1], COLOR_BLACK, COLOR_WHITE); // 左下角
    for (int i = 1; i < width - 1; i++)
    {
        cct_showstr(x + i, y + height - 1, frame_elements[4], COLOR_BLACK, COLOR_WHITE); // 横线
    }
    cct_showstr(x + width - 1, y + height - 1, frame_elements[3], COLOR_BLACK,
                COLOR_WHITE); // 右下角
}

/***************************************************************************
  函数名称：display_matrix_graphic
  功    能：图形模式下显示矩阵
  输入参数：const GameMatrix& matrix - 游戏矩阵
            const GameParams& params - 游戏参数
  返 回 值：无
  说    明：图形模式下显示行列标识和矩阵内容
***************************************************************************/
void display_matrix_graphic(const GameMatrix &matrix, const GameParams &params)
{
    // 清屏
    cct_cls();

    // 设置单元格大小
    int cell_width = 2; // 每个单元格占2列

    // 计算矩阵大小
    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.rows + 2; // 上下边框各占1行，中间是内容行

    // 绘制边框
    draw_frame(5, 3, matrix_width, matrix_height, false);

    // 显示列标题（1,2,3,...）
    for (int j = 0; j < params.cols; j++)
    {
        int x = 6 + j * cell_width;
        cct_showint(x, 2, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示行标题（A,B,C,...）
    for (int i = 0; i < params.rows; i++)
    {
        int y = 4 + i;
        cct_showch(3, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示矩阵内容
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

    // 将光标移动到图形下方，避免"请按任意键继续..."显示在图形中间
    cct_gotoxy(0, 3 + matrix_height + 2);
}

/***************************************************************************
  函数名称：display_game_graphic
  功    能：图形模式下显示完整游戏界面
  输入参数：const GameMatrix& matrix - 游戏矩阵
            const GameParams& params - 游戏参数
  返 回 值：无
  说    明：图形模式下显示行列标识、矩阵内容和提示栏
***************************************************************************/
void display_game_graphic(const GameMatrix &matrix, const GameParams &params)
{
    // 清屏
    cct_cls();

    // 设置单元格大小
    int cell_width = 2; // 每个单元格占2列

    // 计算矩阵大小和位置
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;

    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.rows + 2; // 上下边框各占1行，中间是内容行

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;

    // 绘制行提示边框
    int row_hint_x = matrix_x - hint_width - 2;
    int row_hint_y = matrix_y;
    int row_hint_width = hint_width;
    int row_hint_height = matrix_height;
    draw_frame(row_hint_x, row_hint_y, row_hint_width, row_hint_height, false);

    // 绘制列提示边框
    int col_hint_x = matrix_x;
    int col_hint_y = matrix_y - hint_height - 1;
    int col_hint_width = matrix_width;
    int col_hint_height = hint_height + 1;
    draw_frame(col_hint_x, col_hint_y, col_hint_width, col_hint_height, false);

    // 绘制矩阵边框
    draw_frame(matrix_x, matrix_y, matrix_width, matrix_height, false);

    // 显示列标题（1,2,3,...）
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + 1 + j * cell_width;
        cct_showint(x, matrix_y - 1, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示行标题（A,B,C,...）
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + 1 + i;
        cct_showch(matrix_x - 2, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示矩阵内容
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

    // 显示行提示
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + 1 + i;
        int hint_x = row_hint_x + 1; // 在行提示框内部开始

        // 右对齐显示
        for (int h = 0; h < matrix.row_hint_count[i]; h++)
        {
            int x = hint_x + (matrix.hint_width - matrix.row_hint_count[i] + h) * 2;
            cct_showint(x, y, matrix.row_hints[i][h], COLOR_BLACK, COLOR_WHITE);
        }
    }

    // 显示列提示
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + 1 + j * cell_width;
        int hint_y = col_hint_y + 1; // 在列提示框内部开始

        // 下对齐显示
        for (int h = 0; h < matrix.col_hint_count[j]; h++)
        {
            int y = hint_y + (matrix.hint_height - matrix.col_hint_count[j] + h);
            cct_showint(x, y, matrix.col_hints[j][h], COLOR_BLACK, COLOR_WHITE);
        }
    }

    // 将光标移动到图形下方，避免"请按任意键继续..."显示在图形中间
    cct_gotoxy(0, matrix_y + matrix_height + 2);
}

/***************************************************************************
  函数名称：display_mouse_position
  功    能：显示鼠标位置
  输入参数：int mx - 鼠标X坐标
            int my - 鼠标Y坐标
            const GameParams& params - 游戏参数
  返 回 值：无
  说    明：在状态栏显示鼠标位置
***************************************************************************/
void display_mouse_position(int mx, int my, const GameParams &params)
{
    cct_setcolor();
    cct_gotoxy(0, 30);
    cout << "鼠标位置: " << mx << "," << my << "                ";
}

/***************************************************************************
  函数名称：convert_mouse_to_cell
  功    能：将鼠标坐标转换为矩阵单元格坐标
  输入参数：int mx - 鼠标X坐标
            int my - 鼠标Y坐标
            int& row - 返回行索引
            int& col - 返回列索引
            const GameParams& params - 游戏参数
            const GameMatrix& matrix - 游戏矩阵
            bool& is_valid - 返回是否有效
  返 回 值：无
  说    明：检查鼠标是否在有效的矩阵区域内，并转换坐标
***************************************************************************/
void convert_mouse_to_cell(int mx, int my, int &row, int &col, const GameParams &params,
                           const GameMatrix &matrix, bool &is_valid)
{
    // 设置单元格大小
    int cell_width = 2; // 每个单元格占2列

    // 计算矩阵大小和位置
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;

    // 检查鼠标是否在矩阵区域内
    if (mx >= matrix_x + 1 && mx < matrix_x + params.cols * cell_width + 1 && my >= matrix_y + 1 &&
        my < matrix_y + params.rows + 1)
    {
        // 计算行列索引
        col = (mx - matrix_x - 1) / cell_width;
        row = (my - matrix_y - 1);

        // 检查行列是否在有效范围内
        if (row >= 0 && row < params.rows && col >= 0 && col < params.cols)
        {
            is_valid = true;
            return;
        }
    }

    is_valid = false;
}