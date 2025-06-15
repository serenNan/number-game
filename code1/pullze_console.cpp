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

    // 绘制顶部边框
    cout << "  +";
    for (int j = 0; j < params.cols; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+";
        cout << "--";
    }
    cout << "-+" << endl;

    // 显示列标题行
    cout << "  |";
    for (int j = 0; j < params.cols; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << " |";
        cout << " " << (char)('a' + j);
    }
    cout << " |" << endl;

    // 绘制列标题下方的分隔线
    cout << "+-+";
    for (int j = 0; j < params.cols; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+";
        cout << "--";
    }
    cout << "-+" << endl;

    // 显示矩阵内容
    for (int i = 0; i < params.rows; i++)
    {
        // 显示行标题（A,B,C,...）
        cout << (char)('A' + i) << " |";

        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << " |";
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
        cout << " |" << endl;

        // 每5行添加分隔线
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

    // 绘制底部边框
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

    // 计算列提示的最大高度
    int max_col_hints = 0;
    for (int j = 0; j < params.cols; j++)
    {
        if (matrix.col_hint_count[j] > max_col_hints)
        {
            max_col_hints = matrix.col_hint_count[j];
        }
    }

    // 打印顶部边框
    for (int i = 0; i < hint_width + 2; ++i)
    {
        cout << '-';
    }
    cout << "--+"; // 数据区起始边框
    for (int j = 0; j < params.cols; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+"; // 每5列分隔线
        cout << "--";     // 横线
    }
    cout << "-+" << endl; // 右侧结束边框

    // 显示列提示（下对齐）
    for (int h = 0; h < max_col_hints; h++)
    {
        // 行提示栏区域留白
        cout << setw(hint_width + 5) << "  |";

        // 打印列提示（下对齐）
        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << " |"; // 每5列分隔线
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

    // 打印网格顶部边框
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

    // 打印列标签行
    cout << setw(hint_width + 2) << " " << "  |";
    for (int j = 0; j < params.cols; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << " |";
        cout << " " << static_cast<char>('a' + j);
    }
    cout << " |" << endl;

    // 打印列标签下的分隔线
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

    // 显示矩阵内容和行提示
    for (int i = 0; i < params.rows; i++)
    {
        // 生成行提示字符串
        string row_hint_str = "";
        for (int h = 0; h < matrix.row_hint_count[i]; h++)
        {
            if (h > 0)
                row_hint_str += " ";
            row_hint_str += to_string(matrix.row_hints[i][h]);
        }

        // 显示行提示，右对齐
        cout << " " << setw(hint_width) << row_hint_str << " |" << static_cast<char>('A' + i)
             << "|";

        // 显示数据
        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << " |";

            // 根据作弊模式显示单元格内容
            if (params.cheat_mode && matrix.solution[i][j])
            {
                cout << " O"; // 显示有球
            }
            else
            {
                cout << "  "; // 空白
            }
        }
        cout << " |" << endl;

        // 每5行添加一个分隔线
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

    // 显示底部边框
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

    // 如果有分隔线，需要调整显示位置到单元格中央
    if (has_separators)
    {
        // 单元格内部的中心位置
        screen_x += 2; // 在5宽的单元格中，内容显示在第3列
        screen_y += 1; // 在3高的单元格中，内容显示在第2行
    }

    // 根据状态设置内容和颜色
    switch (status)
    {
    case EMPTY:
        // 空格，不显示任何内容
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, " ", COLOR_BLACK, COLOR_WHITE);
        break;

    case FILLED:
        // 显示O表示有球，白底黑字
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "O", COLOR_BLACK, COLOR_WHITE);
        break;

    case MARKED:
        // 正常模式下：蓝色背景O（左键选择）
        cct_setcolor(COLOR_BLUE, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "O", COLOR_BLUE, COLOR_WHITE);
        break;

    case MARKED_WRONG:
        // 显示X表示错误标记，红底白字
        cct_setcolor(COLOR_RED, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "X", COLOR_RED, COLOR_WHITE);
        break;

    case MARKED_NOT:
        // 正常模式下：红色背景X（右键标注）
        cct_setcolor(COLOR_RED, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "X", COLOR_RED, COLOR_WHITE);
        break;

    // 以下是作弊模式下的新增显示状态
    case CHEAT_EMPTY:
        // 灰色背景O：有球但尚未选择
        cct_setcolor(COLOR_HBLACK, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "O", COLOR_HBLACK, COLOR_WHITE);
        break;

    case CHEAT_MARKED:
        // 蓝色背景O：有球且已左键选择
        cct_setcolor(COLOR_BLUE, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "O", COLOR_BLUE, COLOR_WHITE);
        break;

    case CHEAT_WRONG:
        // 红色背景O：无球但已左键选择
        cct_setcolor(COLOR_RED, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "O", COLOR_RED, COLOR_WHITE);
        break;

    case CHEAT_NOT_RIGHT:
        // 红色背景X：无球且右键标注
        cct_setcolor(COLOR_RED, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "X", COLOR_RED, COLOR_WHITE);
        break;

    case CHEAT_BALL_RIGHT:
        // 蓝色背景X：有球但已右键标注
        cct_setcolor(COLOR_BLUE, COLOR_WHITE);
        cct_showstr(screen_x, screen_y, "X", COLOR_BLUE, COLOR_WHITE);
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
    const char *frame_elements[] = {"╔", "╚", "╗", "╝", "═", "║", "╦", "╩", "╠", "╣", "╬"};

    if (!has_separators)
    {
        // 简单边框模式
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
    else
    {
        // 复杂单元格模式
        int cell_width = 5;  // 每个单元格宽度为5个字符（包括边框）
        int cell_height = 3; // 每个单元格高度为3行（包括边框）
        int cols = (width - 1) / cell_width;
        int rows = (height - 1) / cell_height;

        // 绘制顶部边框
        cct_showstr(x, y, frame_elements[0], COLOR_BLACK, COLOR_WHITE); // 左上角
        for (int j = 0; j < cols; j++)
        {
            // 每个单元格的顶部横线
            for (int i = 0; i < cell_width - 1; i++)
            {
                cct_showstr(x + j * cell_width + i + 1, y, frame_elements[4], COLOR_BLACK,
                            COLOR_WHITE);
            }
            // 每个单元格的顶部交叉点（除了最后一列）
            if (j < cols - 1)
            {
                cct_showstr(x + (j + 1) * cell_width, y, frame_elements[6], COLOR_BLACK,
                            COLOR_WHITE);
            }
        }
        cct_showstr(x + width - 1, y, frame_elements[2], COLOR_BLACK, COLOR_WHITE); // 右上角

        // 绘制中间行
        for (int i = 0; i < rows; i++)
        {
            // 绘制单元格内部
            for (int k = 1; k < cell_height; k++)
            {
                // 每行的左边框
                cct_showstr(x, y + i * cell_height + k, frame_elements[5], COLOR_BLACK,
                            COLOR_WHITE);

                // 每个单元格的内部和垂直分隔线
                for (int j = 0; j < cols; j++)
                {
                    // 单元格内部空白区域
                    for (int l = 1; l < cell_width; l++)
                    {
                        cct_showstr(x + j * cell_width + l, y + i * cell_height + k, " ",
                                    COLOR_BLACK, COLOR_WHITE);
                    }
                    // 垂直分隔线（除了最后一列）
                    if (j < cols - 1)
                    {
                        cct_showstr(x + (j + 1) * cell_width, y + i * cell_height + k,
                                    frame_elements[5], COLOR_BLACK, COLOR_WHITE);
                    }
                }
                // 每行的右边框
                cct_showstr(x + width - 1, y + i * cell_height + k, frame_elements[5], COLOR_BLACK,
                            COLOR_WHITE);
            }

            // 绘制行分隔线（除了最后一行）
            if (i < rows - 1)
            {
                // 行分隔线的左侧连接点
                cct_showstr(x, y + (i + 1) * cell_height, frame_elements[8], COLOR_BLACK,
                            COLOR_WHITE);

                // 每个单元格的水平分隔线和交叉点
                for (int j = 0; j < cols; j++)
                {
                    // 水平分隔线
                    for (int l = 1; l < cell_width; l++)
                    {
                        cct_showstr(x + j * cell_width + l, y + (i + 1) * cell_height,
                                    frame_elements[4], COLOR_BLACK, COLOR_WHITE);
                    }
                    // 交叉点（除了最后一列）
                    if (j < cols - 1)
                    {
                        cct_showstr(x + (j + 1) * cell_width, y + (i + 1) * cell_height,
                                    frame_elements[10], COLOR_BLACK, COLOR_WHITE);
                    }
                }
                // 行分隔线的右侧连接点
                cct_showstr(x + width - 1, y + (i + 1) * cell_height, frame_elements[9],
                            COLOR_BLACK, COLOR_WHITE);
            }
        }

        // 绘制底部边框
        cct_showstr(x, y + height - 1, frame_elements[1], COLOR_BLACK, COLOR_WHITE); // 左下角
        for (int j = 0; j < cols; j++)
        {
            // 每个单元格的底部横线
            for (int i = 0; i < cell_width - 1; i++)
            {
                cct_showstr(x + j * cell_width + i + 1, y + height - 1, frame_elements[4],
                            COLOR_BLACK, COLOR_WHITE);
            }
            // 每个单元格的底部交叉点（除了最后一列）
            if (j < cols - 1)
            {
                cct_showstr(x + (j + 1) * cell_width, y + height - 1, frame_elements[7],
                            COLOR_BLACK, COLOR_WHITE);
            }
        }
        cct_showstr(x + width - 1, y + height - 1, frame_elements[3], COLOR_BLACK,
                    COLOR_WHITE); // 右下角
    }
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
    int cell_width = params.has_separators ? 5 : 2; // 有分隔线时每个单元格占5列，否则占2列

    // 计算矩阵大小
    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.has_separators ? params.rows * 3 + 1
                                              : params.rows + 2; // 有分隔线时每行占3行，否则占1行

    // 绘制边框
    draw_frame(5, 3, matrix_width, matrix_height, params.has_separators);

    // 显示列标题（1,2,3,...）
    for (int j = 0; j < params.cols; j++)
    {
        int x = 6 + j * cell_width;
        if (params.has_separators)
        {
            x = 5 + j * cell_width + cell_width / 2;
        }
        cct_showint(x, 2, j + 1, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示行标题（A,B,C,...）
    for (int i = 0; i < params.rows; i++)
    {
        int y = 4 + i;
        if (params.has_separators)
        {
            y = 3 + i * 3 + 2; // 在每个单元格的中间行显示
        }
        cct_showch(3, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示矩阵内容
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            int x = 6 + j * cell_width;
            int y = 4 + i;

            if (params.has_separators)
            {
                x = 5 + j * cell_width + 1; // 单元格左上角
                y = 3 + i * 3 + 1;          // 单元格左上角
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
    int cell_width = params.has_separators ? 5 : 2; // 有分隔线时每个单元格占5列，否则占2列

    // 计算矩阵大小和位置
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;

    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.has_separators ? params.rows * 3 + 1
                                              : params.rows + 2; // 有分隔线时每行占3行，否则占1行

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
    draw_frame(matrix_x, matrix_y, matrix_width, matrix_height, params.has_separators);

    // 显示列标题（a,b,c,...）
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + 1 + j * cell_width;
        if (params.has_separators)
        {
            x = matrix_x + j * cell_width + cell_width / 2;
        }
        cct_showch(x, matrix_y - 1, 'a' + j, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示行标题（A,B,C,...）
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + 1 + i;
        if (params.has_separators)
        {
            y = matrix_y + i * 3 + 2; // 在每个单元格的中间行显示
        }
        cct_showch(matrix_x - 2, y, 'A' + i, COLOR_BLACK, COLOR_WHITE);
    }

    // 显示矩阵内容
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            int x = matrix_x + 1 + j * cell_width;
            int y = matrix_y + 1 + i;

            if (params.has_separators)
            {
                x = matrix_x + j * cell_width + 1; // 单元格左上角
                y = matrix_y + i * 3 + 1;          // 单元格左上角
            }

            if (params.cheat_mode)
            {
                // 作弊模式下的显示逻辑
                if (matrix.solution[i][j]) // 有球
                {
                    if (matrix.cells[i][j] == EMPTY) // 有球但尚未选择
                    {
                        display_cell(x, y, CHEAT_EMPTY, params.has_separators);
                    }
                    else if (matrix.cells[i][j] == MARKED) // 有球且已左键选择
                    {
                        display_cell(x, y, CHEAT_MARKED, params.has_separators);
                    }
                    else if (matrix.cells[i][j] == MARKED_NOT) // 有球但已右键标注
                    {
                        display_cell(x, y, CHEAT_BALL_RIGHT, params.has_separators);
                    }
                }
                else // 无球
                {
                    if (matrix.cells[i][j] == MARKED) // 无球但已左键选择
                    {
                        display_cell(x, y, CHEAT_WRONG, params.has_separators);
                    }
                    else if (matrix.cells[i][j] == MARKED_NOT) // 无球且右键标注
                    {
                        display_cell(x, y, CHEAT_NOT_RIGHT, params.has_separators);
                    }
                    else // 无球且未选择
                    {
                        display_cell(x, y, EMPTY, params.has_separators);
                    }
                }
            }
            else
            {
                // 正常模式下的显示逻辑
                display_cell(x, y, matrix.cells[i][j], params.has_separators);
            }
        }
    }

    // 显示行提示
    for (int i = 0; i < params.rows; i++)
    {
        int y = matrix_y + 1 + i;
        if (params.has_separators)
        {
            y = matrix_y + i * 3 + 2; // 在每个单元格的中间行显示
        }

        // 在行提示框内部右对齐显示
        for (int h = 0; h < matrix.row_hint_count[i]; h++)
        {
            // 计算提示位置（右对齐）
            int x = row_hint_x + 1 + (hint_width - matrix.row_hint_count[i] * 2 + h * 2);
            cct_showint(x, y, matrix.row_hints[i][h], COLOR_BLACK, COLOR_WHITE);
        }
    }

    // 显示列提示
    for (int j = 0; j < params.cols; j++)
    {
        int x = matrix_x + 1 + j * cell_width;
        if (params.has_separators)
        {
            x = matrix_x + j * cell_width + cell_width / 2;
        }

        // 在列提示框内部下对齐显示
        for (int h = 0; h < matrix.col_hint_count[j]; h++)
        {
            // 计算提示位置（下对齐）
            int y = col_hint_y + 1 + (hint_height - matrix.col_hint_count[j] + h);
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
    // 设置默认颜色
    cct_setcolor();

    // 计算矩阵大小和位置
    int cell_width = params.has_separators ? 5 : 2;  // 有分隔线时每个单元格占5列，否则占2列
    int cell_height = params.has_separators ? 3 : 1; // 有分隔线时每个单元格占3行，否则占1行

    // 计算表格底部位置，确保坐标提示显示在表格下方
    int hint_height = 3; // 假设提示区高度
    int matrix_height = params.has_separators ? params.rows * 3 + 1 : params.rows + 2;
    int bottom_y = 3 + hint_height + matrix_height + 2;

    // 移动到状态栏位置
    cct_gotoxy(0, bottom_y);

    // 显示鼠标坐标信息
    cout << "鼠标位置: X=" << setw(3) << mx << ", Y=" << setw(3) << my;

    // 尝试转换为矩阵坐标
    int row, col;
    bool is_valid;
    GameMatrix dummy_matrix; // 创建一个临时矩阵用于坐标转换
    dummy_matrix.hint_width = 3;
    dummy_matrix.hint_height = 3;

    convert_mouse_to_cell(mx, my, row, col, params, dummy_matrix, is_valid);

    // 显示矩阵坐标（如果有效）
    if (is_valid)
    {
        cout << " | 矩阵坐标: 行=" << (char)('A' + row) << ", 列=" << (char)('a' + col);
    }
    else
    {
        cout << " | 矩阵坐标: 无效位置                ";
    }

    // 清除行尾可能的残留字符
    cout << "                    ";
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
    int cell_width = params.has_separators ? 5 : 2;  // 有分隔线时每个单元格占5列，否则占2列
    int cell_height = params.has_separators ? 3 : 1; // 有分隔线时每个单元格占3行，否则占1行

    // 计算矩阵大小和位置
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;
    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.rows * cell_height + 1;

    // 初始化为无效值
    row = -1;
    col = -1;
    is_valid = false;

    // 检查鼠标是否在矩阵区域内
    if (mx < matrix_x || mx >= matrix_x + matrix_width || my < matrix_y ||
        my >= matrix_y + matrix_height)
    {
        return; // 鼠标不在矩阵区域内
    }

    // 计算行列索引
    if (params.has_separators)
    {
        // 有分隔线模式
        // 排除边框线和分隔线的点击
        int rel_x = mx - matrix_x;
        int rel_y = my - matrix_y;

        // 检查是否点击在边框或分隔线上
        if (rel_x % cell_width == 0 || rel_y % cell_height == 0)
        {
            return; // 点击在边框或分隔线上，无效
        }

        col = rel_x / cell_width;
        row = rel_y / cell_height;
    }
    else
    {
        // 无分隔线模式
        // 矩阵内容区域从(matrix_x+1, matrix_y+1)开始
        if (mx >= matrix_x + 1 && mx < matrix_x + 1 + params.cols * cell_width &&
            my >= matrix_y + 1 && my < matrix_y + 1 + params.rows)
        {
            col = (mx - matrix_x - 1) / cell_width;
            row = my - matrix_y - 1;
        }
    }

    // 验证计算出的行列是否有效
    if (row >= 0 && row < params.rows && col >= 0 && col < params.cols)
    {
        is_valid = true;
    }
}