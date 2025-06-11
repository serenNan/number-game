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

    // 显示列标题（1,2,3,...）
    cout << "  ";
    for (int j = 0; j < params.cols; j++)
    {
        cout << " " << (j + 1);
        // 每5列添加一个分隔符
        if ((j + 1) % 5 == 0 && j < params.cols - 1)
        {
            cout << " |";
        }
    }
    cout << endl;

    // 显示横向分隔线
    cout << "  ";
    for (int j = 0; j < params.cols; j++)
    {
        cout << "--";
        // 每5列添加一个分隔符
        if ((j + 1) % 5 == 0 && j < params.cols - 1)
        {
            cout << "-+";
        }
    }
    cout << endl;

    // 显示矩阵内容
    for (int i = 0; i < params.rows; i++)
    {
        // 显示行标题（A,B,C,...）
        cout << (char)('A' + i) << " |";

        for (int j = 0; j < params.cols; j++)
        {
            // 根据作弊模式显示单元格内容
            if (params.cheat_mode && matrix.solution[i][j])
            {
                cout << "0 ";
            }
            else
            {
                cout << "  ";
            }

            // 每5列添加一个分隔符
            if ((j + 1) % 5 == 0 && j < params.cols - 1)
            {
                cout << "|";
            }
        }
        cout << endl;

        // 每5行添加一个分隔线
        if ((i + 1) % 5 == 0 && i < params.rows - 1)
        {
            cout << "  ";
            for (int j = 0; j < params.cols; j++)
            {
                cout << "--";
                // 在分隔线交叉处使用不同的符号
                if ((j + 1) % 5 == 0 && j < params.cols - 1)
                {
                    cout << "+";
                }
            }
            cout << endl;
        }
    }
    cout << endl;
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
    cout << "行提示栏：" << endl;
    for (int i = 0; i < params.rows; i++)
    {
        cout << (char)('A' + i) << ": ";
        for (int h = 0; h < matrix.row_hint_count[i]; h++)
        {
            cout << matrix.row_hints[i][h] << " ";
        }
        cout << endl;
    }

    cout << "\n列提示栏：" << endl;
    for (int j = 0; j < params.cols; j++)
    {
        cout << (j + 1) << ": ";
        for (int h = 0; h < matrix.col_hint_count[j]; h++)
        {
            cout << matrix.col_hints[j][h] << " ";
        }
        cout << endl;
    }
    cout << endl;
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
    // 设置单元格的宽度和高度
    int cell_width = has_separators ? 3 : 2;
    int cell_height = has_separators ? 2 : 1;

    // 计算单元格的屏幕坐标
    int screen_x = x * cell_width;
    int screen_y = y * cell_height;

    // 根据状态设置颜色和内容
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
            cct_showstr(screen_x, screen_y, " · ", COLOR_BLACK, COLOR_HBLUE);
            cct_showstr(screen_x, screen_y + 1, "   ", COLOR_BLACK, COLOR_HBLUE);
        }
        else
        {
            cct_showstr(screen_x, screen_y, "· ", COLOR_BLACK, COLOR_HBLUE);
        }
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
    // 框架元素（双线框架）
    const char *frame_elements[] = {"╔", "╚", "╗", "╝", "═", "║", "╦", "╩", "╠", "╣", "╬"};

    // 绘制上边框
    cct_showstr(x, y, frame_elements[0], COLOR_BLACK, COLOR_WHITE); // 左上角
    for (int i = 1; i < width - 1; i++)
    {
        if (has_separators && i % 3 == 0)
        {
            cct_showstr(x + i, y, frame_elements[6], COLOR_BLACK, COLOR_WHITE); // 上T型
        }
        else
        {
            cct_showstr(x + i, y, frame_elements[4], COLOR_BLACK, COLOR_WHITE); // 横线
        }
    }
    cct_showstr(x + width - 1, y, frame_elements[2], COLOR_BLACK, COLOR_WHITE); // 右上角

    // 绘制中间部分
    for (int j = 1; j < height - 1; j++)
    {
        if (has_separators && j % 2 == 0)
        {
            // 分隔行
            cct_showstr(x, y + j, frame_elements[8], COLOR_BLACK, COLOR_WHITE); // 左T型
            for (int i = 1; i < width - 1; i++)
            {
                if (has_separators && i % 3 == 0)
                {
                    cct_showstr(x + i, y + j, frame_elements[10], COLOR_BLACK, COLOR_WHITE); // 十字
                }
                else
                {
                    cct_showstr(x + i, y + j, frame_elements[4], COLOR_BLACK, COLOR_WHITE); // 横线
                }
            }
            cct_showstr(x + width - 1, y + j, frame_elements[9], COLOR_BLACK, COLOR_WHITE); // 右T型
        }
        else
        {
            // 常规行
            cct_showstr(x, y + j, frame_elements[5], COLOR_BLACK, COLOR_WHITE); // 竖线
            for (int i = 1; i < width - 1; i++)
            {
                if (has_separators && i % 3 == 0)
                {
                    cct_showstr(x + i, y + j, frame_elements[5], COLOR_BLACK, COLOR_WHITE); // 竖线
                }
                else
                {
                    cct_showstr(x + i, y + j, " ", COLOR_BLACK, COLOR_WHITE); // 空格
                }
            }
            cct_showstr(x + width - 1, y + j, frame_elements[5], COLOR_BLACK, COLOR_WHITE); // 竖线
        }
    }

    // 绘制下边框
    cct_showstr(x, y + height - 1, frame_elements[1], COLOR_BLACK, COLOR_WHITE); // 左下角
    for (int i = 1; i < width - 1; i++)
    {
        if (has_separators && i % 3 == 0)
        {
            cct_showstr(x + i, y + height - 1, frame_elements[7], COLOR_BLACK,
                        COLOR_WHITE); // 下T型
        }
        else
        {
            cct_showstr(x + i, y + height - 1, frame_elements[4], COLOR_BLACK, COLOR_WHITE); // 横线
        }
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

    // 根据是否有分隔线确定单元格大小
    int cell_width = params.has_separators ? 3 : 2;
    int cell_height = params.has_separators ? 2 : 1;

    // 计算矩阵大小
    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.rows * cell_height + 1;

    // 绘制边框
    draw_frame(5, 3, matrix_width, matrix_height, params.has_separators);

    // 显示列标题（1,2,3,...）
    for (int j = 0; j < params.cols; j++)
    {
        int x = 5 + j * cell_width + cell_width / 2;
        cct_showint(x, 2, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示行标题（A,B,C,...）
    for (int i = 0; i < params.rows; i++)
    {
        int y = 3 + i * cell_height + cell_height / 2;
        cct_showch(3, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示矩阵内容
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

    // 根据是否有分隔线确定单元格大小
    int cell_width = params.has_separators ? 3 : 2;
    int cell_height = params.has_separators ? 2 : 1;

    // 计算矩阵大小和位置
    int hint_width = matrix.hint_width * 3;
    int hint_height = matrix.hint_height * 2;

    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.rows * cell_height + 1;

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;

    // 绘制矩阵边框
    draw_frame(matrix_x, matrix_y, matrix_width, matrix_height, params.has_separators);

    // 显示列标题（1,2,3,...）
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + j * cell_width + cell_width / 2;
        cct_showint(x, matrix_y - 1, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示行标题（A,B,C,...）
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + i * cell_height + cell_height / 2;
        cct_showch(matrix_x - 2, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示矩阵内容
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

    // 显示行提示
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + i * cell_height + cell_height / 2;
        int hint_x = matrix_x - 3 - hint_width;

        // 右对齐显示
        for (int h = 0; h < matrix.row_hint_count[i]; h++)
        {
            int x = hint_x + (matrix.hint_width - matrix.row_hint_count[i] + h) * 3;
            cct_showint(x, y, matrix.row_hints[i][h], COLOR_BLACK, COLOR_WHITE);
        }
    }

    // 显示列提示
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + j * cell_width + cell_width / 2;
        int hint_y = matrix_y - 2 - hint_height;

        // 下对齐显示
        for (int h = 0; h < matrix.col_hint_count[j]; h++)
        {
            int y = hint_y + (matrix.hint_height - matrix.col_hint_count[j] + h) * 2;
            cct_showint(x, y, matrix.col_hints[j][h], COLOR_BLACK, COLOR_WHITE);
        }
    }
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
            bool& is_valid - 返回是否有效
  返 回 值：无
  说    明：检查鼠标是否在有效的矩阵区域内，并转换坐标
***************************************************************************/
void convert_mouse_to_cell(int mx, int my, int &row, int &col, const GameParams &params,
                           bool &is_valid)
{
    // 根据是否有分隔线确定单元格大小
    int cell_width = params.has_separators ? 3 : 2;
    int cell_height = params.has_separators ? 2 : 1;

    // 计算矩阵大小和位置
    int hint_width = 0;
    int hint_height = 0;

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;

    // 检查鼠标是否在矩阵区域内
    if (mx >= matrix_x && mx < matrix_x + params.cols * cell_width + 1 && my >= matrix_y &&
        my < matrix_y + params.rows * cell_height + 1)
    {

        // 计算行列索引
        col = (mx - matrix_x) / cell_width;
        row = (my - matrix_y) / cell_height;

        // 检查鼠标是否在分隔线上
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

        // 检查行列是否在有效范围内
        if (row >= 0 && row < params.rows && col >= 0 && col < params.cols)
        {
            is_valid = true;
            return;
        }
    }

    is_valid = false;
}