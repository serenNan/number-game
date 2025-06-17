#include "pullze.h"
#include <Windows.h>
#include <iostream>

/***************************************************************************
  函数名称：show_menu
  功    能：显示游戏菜单并获取用户选择
  输入参数：无
  返 回 值：int - 用户选择的菜单项
  说    明：显示菜单并返回用户选择
***************************************************************************/
int show_menu()
{
    int choice = 0;
    char ch;

    cct_cls();
    cct_setcolor();

    cout << "---------------------------------------------------------" << endl;
    cout << " A.内部数组，原样输出" << endl;
    cout << " B.内部数组，生成提示行列并输出" << endl;
    cout << " C.内部数组，游戏版" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " D.n*n的框架(无分隔线)，原样输出" << endl;
    cout << " E.n*n的框架(无分隔线)，含提示行列" << endl;
    cout << " F.n*n的框架(无分隔线)，显示初始状态，鼠标移动可显示坐标" << endl;
    cout << " G.cmd图形界面完整版(无分隔线)" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " H.n*n的框架(有分隔线)，原样输出" << endl;
    cout << " I.n*n的框架(有分隔线)，含提示行列" << endl;
    cout << " J.n*n的框架(有分隔线)，显示初始状态，鼠标移动可显示坐标" << endl;
    cout << " K.cmd图形界面完整版(有分隔线)" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " Q.退出" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "[请选择:]  ";

    while (1)
    {
        ch = _getch();

        if (ch >= 'a' && ch <= 'k')
            ch = ch - 'a' + 'A';

        if (ch == 'A')
            choice = 1;
        else if (ch == 'B')
            choice = 2;
        else if (ch == 'C')
            choice = 3;
        else if (ch == 'D')
            choice = 4;
        else if (ch == 'E')
            choice = 5;
        else if (ch == 'F')
            choice = 6;
        else if (ch == 'G')
            choice = 7;
        else if (ch == 'H')
            choice = 8;
        else if (ch == 'I')
            choice = 9;
        else if (ch == 'J')
            choice = 10;
        else if (ch == 'K')
            choice = 11;
        else if (ch == 'Q' || ch == 'q')
            choice = 0;
        else
            continue;

        cout << ch << endl;
        break;
    }

    return choice;
}

/***************************************************************************
  函数名称：get_game_params
  功    能：获取游戏参数
  输入参数：GameParams& params - 游戏参数
  返 回 值：bool - 是否成功获取参数
  说    明：获取用户输入的游戏参数
***************************************************************************/
bool get_game_params(GameParams &params)
{
    cct_cls();
    int choice = 0;
    char ch;

    cout << "请选择游戏大小：" << endl;
    cout << "1. 5×5" << endl;
    cout << "2. 10×10" << endl;
    cout << "3. 15×15" << endl;
    cout << "请选择[1-3]：";

    while (1)
    {
        ch = _getch();

        if (ch >= '1' && ch <= '3')
        {
            choice = ch - '0';
            cout << ch << endl;
            break;
        }
    }

    switch (choice)
    {
    case 1:
        params.rows = params.cols = 5;
        break;
    case 2:
        params.rows = params.cols = 10;
        break;
    case 3:
        params.rows = params.cols = 15;
        break;
    }

    return true;
}

/***************************************************************************
  函数名称：play_game_text_mode
  功    能：文本模式下的游戏主循环
  输入参数：GameMatrix& matrix - 游戏矩阵
            GameParams& params - 游戏参数
  返 回 值：无
  说    明：文本模式下的完整游戏流程
***************************************************************************/
void play_game_text_mode(GameMatrix &matrix, GameParams &params)
{
    bool game_over = false;

    // 默认关闭作弊模式
    params.cheat_mode = false;

    // 用于显示用户标记的临时数组
    int marked[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = {0};

    while (!game_over)
    {
        // 显示游戏界面
        cct_cls();

        cout << "游戏进行中..." << endl;

        // 计算行提示栏最大宽度
        int maxRowHintWidth = 0;
        char tempStr[MAX_MATRIX_SIZE * 4] = "";
        for (int i = 0; i < params.rows; i++)
        {
            char hint_str[MAX_MATRIX_SIZE * 4] = "";
            char temp[8];
            for (int h = 0; h < matrix.row_hint_count[i]; h++)
            {
                if (h > 0)
                    strcat(hint_str, " ");
                sprintf(temp, "%d", matrix.row_hints[i][h]);
                strcat(hint_str, temp);
            }
            maxRowHintWidth = max(maxRowHintWidth, (int)strlen(hint_str));
        }

        // 计算列提示栏最大高度
        int maxColHintHeight = 0;
        for (int j = 0; j < params.cols; j++)
        {
            maxColHintHeight = max(maxColHintHeight, matrix.col_hint_count[j]);
        }

        // 打印顶部边框
        for (int i = 0; i < maxRowHintWidth + 2; ++i)
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

        // 打印列提示栏（下对齐）
        for (int h = 0; h < maxColHintHeight; h++)
        {
            // 行提示栏区域留白
            cout << setw(maxRowHintWidth + 5) << "  |";

            // 打印列提示（下对齐）
            for (int j = 0; j < params.cols; j++)
            {
                if (j > 0 && j % 5 == 0)
                    cout << " |"; // 每5列分隔线
                int index = matrix.col_hint_count[j] - maxColHintHeight + h;
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
        for (int i = 0; i < maxRowHintWidth + 2; ++i)
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
        cout << setw(maxRowHintWidth + 2) << " " << "  |";
        for (int j = 0; j < params.cols; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << " |";
            cout << " " << static_cast<char>('a' + j);
        }
        cout << " |" << endl;

        // 打印列标签下的分隔线
        for (int i = 0; i < maxRowHintWidth + 2; ++i)
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
            char row_hint_str[MAX_MATRIX_SIZE * 4] = "";
            char temp[8];
            for (int h = 0; h < matrix.row_hint_count[i]; h++)
            {
                if (h > 0)
                    strcat(row_hint_str, " ");
                sprintf(temp, "%d", matrix.row_hints[i][h]);
                strcat(row_hint_str, temp);
            }

            // 显示行提示，右对齐
            cout << " " << setw(maxRowHintWidth) << row_hint_str << " |"
                 << static_cast<char>('A' + i) << "|";

            // 显示数据
            for (int j = 0; j < params.cols; j++)
            {
                if (j > 0 && j % 5 == 0)
                    cout << " |";

                // 根据单元格状态显示内容
                if (matrix.cells[i][j] == EMPTY)
                {
                    if (params.cheat_mode && matrix.solution[i][j])
                    {
                        // 作弊模式下显示有球的位置
                        cct_setcolor(COLOR_HBLACK, COLOR_BLACK);
                        cout << " O";
                        cct_setcolor(); // 恢复默认颜色
                    }
                    else
                    {
                        cout << "  "; // 空白
                    }
                }
                else if (matrix.cells[i][j] == MARKED)
                {
                    // 用户标记为有球
                    if (params.cheat_mode)
                    {
                        if (matrix.solution[i][j])
                        {
                            // 标记正确
                            cct_setcolor(COLOR_BLUE, COLOR_WHITE);
                            cout << " O";
                        }
                        else
                        {
                            // 标记错误
                            cct_setcolor(COLOR_RED, COLOR_WHITE);
                            cout << " O";
                        }
                    }
                    else
                    {
                        // 普通模式下的标记
                        cct_setcolor(COLOR_BLUE, COLOR_WHITE);
                        cout << " O";
                    }
                    cct_setcolor(); // 恢复默认颜色
                }
                else if (matrix.cells[i][j] == MARKED_NOT)
                {
                    // 用户标记为无球
                    if (params.cheat_mode)
                    {
                        if (!matrix.solution[i][j])
                        {
                            // 标记正确
                            cct_setcolor(COLOR_RED, COLOR_WHITE);
                            cout << " X";
                        }
                        else
                        {
                            // 标记错误
                            cct_setcolor(COLOR_BLUE, COLOR_WHITE);
                            cout << " X";
                        }
                    }
                    else
                    {
                        // 普通模式下的标记
                        cct_setcolor(COLOR_RED, COLOR_WHITE);
                        cout << " X";
                    }
                    cct_setcolor(); // 恢复默认颜色
                }
            }
            cout << " |" << endl;

            // 每5行添加一个分隔线
            if ((i + 1) % 5 == 0 && i < params.rows - 1)
            {
                for (int i = 0; i < maxRowHintWidth + 2; ++i)
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
        for (int i = 0; i < maxRowHintWidth + 2; ++i)
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

        // 显示当前作弊模式状态和操作说明
        cout << "当前" << (params.cheat_mode ? "已开启" : "未开启") << "作弊模式" << endl << endl;
        cout << "命令说明：" << endl;
        cout << "  Aa  - 标记位置(A行a列)为有球，再次输入相同位置则取消标记" << endl;
        cout << "  Aa# - 标记位置(A行a列)为无球，再次输入相同位置则取消标记" << endl;
        cout << "  X/x - 退出游戏" << endl;
        cout << "  Y/y - 提交答案" << endl;
        cout << "  Z/z - 切换作弊模式" << endl;

        // 用户输入
        cout << "\n请输入命令：";
        char cmd[64];
        cin.getline(cmd, 64);

        // 处理输入命令
        if (strlen(cmd) == 0)
        {
            continue; // 空命令，继续
        }
        else if (strlen(cmd) == 1)
        {
            char c = toupper(cmd[0]);
            if (c == 'X')
            {
                game_over = true; // 退出
                continue;
            }
            else if (c == 'Y')
            {
                // 提交答案
                int error_row, error_col;
                if (validate_solution(matrix, params, error_row, error_col))
                {
                    cout << "\n恭喜！你的解答正确！" << endl;
                    game_over = true;
                    system("pause");
                    continue;
                }
                else
                {
                    cout << "\n解答错误，第一个错误位置：" << (char)('A' + error_row)
                         << (char)('a' + error_col) << " (" << error_row + 1 << "," << error_col + 1
                         << ")" << endl;
                    system("pause");
                    continue;
                }
            }
            else if (c == 'Z')
            {
                // 切换作弊模式
                params.cheat_mode = !params.cheat_mode;
                cout << "\n已" << (params.cheat_mode ? "开启" : "关闭") << "作弊模式" << endl;
                system("pause");
                continue;
            }
        }
        else if (strlen(cmd) >= 2)
        {
            // 处理坐标输入
            char row_char = cmd[0];
            char col_char = cmd[1];

            // 检查是否为有效的行列标识
            if (row_char >= 'A' && row_char < 'A' + params.rows && col_char >= 'a' &&
                col_char < 'a' + params.cols)
            {
                int row = row_char - 'A';
                int col = col_char - 'a';

                // 检查是否为标记无球命令
                bool mark_empty = (strlen(cmd) > 2 && cmd[2] == '#');

                // 更新标记
                if (mark_empty)
                {
                    // 标记为无球或取消标记
                    if (matrix.cells[row][col] == MARKED_NOT)
                        matrix.cells[row][col] = EMPTY; // 取消标记
                    else
                        matrix.cells[row][col] = MARKED_NOT; // 标记为无球
                }
                else
                {
                    // 标记为有球或取消标记
                    if (matrix.cells[row][col] == MARKED)
                        matrix.cells[row][col] = EMPTY; // 取消标记
                    else if (matrix.cells[row][col] == EMPTY ||
                             matrix.cells[row][col] == MARKED_NOT)
                        matrix.cells[row][col] = MARKED; // 标记为有球
                }

                continue;
            }
        }

        // 无效命令
        cout << "\n无效命令，请重试" << endl;
        system("pause");
    }
}

/***************************************************************************
  函数名称：play_game_graphic_mode
  功    能：图形模式下的游戏主循环
  输入参数：GameMatrix& matrix - 游戏矩阵
            GameParams& params - 游戏参数
  返 回 值：无
  说    明：图形模式下的完整游戏流程
***************************************************************************/
void play_game_graphic_mode(GameMatrix &matrix, GameParams &params)
{
    // 兼容Win11，确保鼠标事件能被捕获
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hInput, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hInput, mode);

    bool game_over = false;
    int last_mx = -1, last_my = -1;

    // 默认关闭作弊模式
    params.cheat_mode = false;

    // 启用鼠标
    cct_enable_mouse();

    // 绘制初始游戏界面
    display_game_graphic(matrix, params);

    // 计算表格底部位置
    int cell_width = params.has_separators ? 5 : 2;
    int cell_height = params.has_separators ? 3 : 1;
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;
    int matrix_height = params.has_separators ? params.rows * 3 + 1 : params.rows + 2;
    int matrix_y = 3 + hint_height;
    int bottom_y = matrix_y + matrix_height + 2;

    // 显示操作提示
    cct_setcolor();
    cct_gotoxy(0, bottom_y);
    cout << "操作说明：左键标记球存在，右键标记球不存在，Enter键提交，Q键退出，Z键切换作弊模式"
         << endl;
    cct_gotoxy(0, bottom_y + 1);
    cout << "当前" << (params.cheat_mode ? "已开启" : "未开启") << "作弊模式" << endl;

    INPUT_RECORD ir;
    DWORD read;
    while (!game_over)
    {
        ReadConsoleInput(hInput, &ir, 1, &read);
        if (ir.EventType == MOUSE_EVENT)
        {
            auto &me = ir.Event.MouseEvent;
            int mx = me.dwMousePosition.X;
            int my = me.dwMousePosition.Y;
            DWORD btn = me.dwButtonState;
            DWORD evt = me.dwEventFlags;

            // 只有坐标变化时刷新显示，减少闪烁
            if (mx != last_mx || my != last_my)
            {
                last_mx = mx;
                last_my = my;

                // 显示鼠标位置信息
                display_mouse_position(mx, my, params);

                // 转换鼠标坐标为矩阵单元格坐标
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

                // 显示单元格信息
                cct_gotoxy(0, bottom_y + 2);
                if (is_valid)
                {
                    cout << "当前单元格: " << (char)('A' + row) << (char)('a' + col) << " ("
                         << row + 1 << "," << col + 1 << ")           ";
                }
                else
                {
                    cout << "当前位置: 不在有效单元格内                     ";
                }
            }

            // 处理鼠标点击事件
            if (btn != 0)
            {
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

                if (is_valid)
                {
                    // 左键标记为有球，右键标记为无球
                    if (btn & FROM_LEFT_1ST_BUTTON_PRESSED)
                    {
                        // 左键点击 - 标记为有球
                        if (matrix.cells[row][col] == EMPTY || matrix.cells[row][col] == MARKED_NOT)
                        {
                            matrix.cells[row][col] = MARKED;
                        }
                        else if (matrix.cells[row][col] == MARKED)
                        {
                            // 如果已经标记，则取消标记
                            matrix.cells[row][col] = EMPTY;
                        }
                    }
                    else if (btn & RIGHTMOST_BUTTON_PRESSED)
                    {
                        // 右键点击 - 标记为无球
                        if (matrix.cells[row][col] == EMPTY || matrix.cells[row][col] == MARKED ||
                            matrix.cells[row][col] == MARKED_WRONG)
                        {
                            matrix.cells[row][col] = MARKED_NOT;
                        }
                        else if (matrix.cells[row][col] == MARKED_NOT)
                        {
                            // 如果已经标记为无球，则取消标记
                            matrix.cells[row][col] = EMPTY;
                        }
                    }

                    // 刷新游戏界面
                    display_game_graphic(matrix, params);

                    // 重新显示操作提示
                    cct_setcolor();
                    cct_gotoxy(0, bottom_y);
                    cout << "操作说明：左键标记球存在，右键标记球不存在，Enter键提交，Q键退出，Z键"
                            "切换作弊模式"
                         << endl;
                    cct_gotoxy(0, bottom_y + 1);
                    cout << "当前" << (params.cheat_mode ? "已开启" : "未开启") << "作弊模式"
                         << endl;
                }
            }
        }
        else if (ir.EventType == KEY_EVENT)
        {
            if (ir.Event.KeyEvent.bKeyDown)
            {
                int keycode1 = ir.Event.KeyEvent.uChar.AsciiChar;
                if (keycode1 == 'q' || keycode1 == 'Q')
                {
                    game_over = true;
                }
                else if (keycode1 == 'z' || keycode1 == 'Z')
                {
                    // 切换作弊模式
                    params.cheat_mode = !params.cheat_mode;

                    // 刷新游戏界面
                    display_game_graphic(matrix, params);

                    // 显示模式切换提示
                    cct_setcolor();
                    cct_gotoxy(0, bottom_y);
                    cout << "操作说明：左键标记球存在，右键标记球不存在，Enter键提交，Q键退出，Z键"
                            "切换作弊模式"
                         << endl;
                    cct_gotoxy(0, bottom_y + 1);
                    cout << "当前" << (params.cheat_mode ? "已开启" : "未开启") << "作弊模式"
                         << endl;
                    cct_gotoxy(0, bottom_y + 2);
                    cout << (params.cheat_mode ? "已开启" : "已关闭")
                         << "作弊模式                   " << endl;
                    Sleep(500);
                }
                else if (keycode1 == '\r')
                {
                    // 验证解答
                    int error_row, error_col;
                    if (validate_solution(matrix, params, error_row, error_col))
                    {
                        // 解答正确
                        cct_gotoxy(0, bottom_y + 3);
                        cout << "恭喜！你的解答正确！" << endl;
                        game_over = true;
                        system("pause");
                    }
                    else
                    {
                        // 解答错误，高亮显示错误位置
                        cct_gotoxy(0, bottom_y + 3);
                        cout << "解答错误，第一个错误位置：" << (char)('A' + error_row)
                             << (char)('a' + error_col) << " (" << error_row + 1 << ","
                             << error_col + 1 << ")      " << endl;

                        // 计算错误位置的屏幕坐标
                        int matrix_x = 5 + hint_width;
                        int matrix_y = 3 + hint_height;

                        // 闪烁显示错误位置
                        for (int i = 0; i < 3; i++)
                        {
                            int x = matrix_x + error_col * cell_width;
                            int y = matrix_y + error_row * cell_height;

                            // 调整到单元格中心位置
                            if (params.has_separators)
                            {
                                x += 2; // 单元格中心
                                y += 1; // 单元格中心
                            }
                            else
                            {
                                x += 1; // 单元格中心
                                y += 0; // 单元格中心
                            }

                            // 闪烁显示错误标记
                            cct_gotoxy(x, y);
                            cct_setcolor(COLOR_WHITE, COLOR_RED);
                            cout << "X";
                            Sleep(300);
                            cct_gotoxy(x, y);
                            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                            cout << " ";
                            Sleep(300);
                        }

                        // 恢复游戏界面
                        display_game_graphic(matrix, params);
                        cct_setcolor();
                        cct_gotoxy(0, bottom_y);
                        cout << "操作说明：左键标记球存在，右键标记球不存在，Enter键提交，Q键退出，"
                                "Z键切换作弊模式"
                             << endl;
                        cct_gotoxy(0, bottom_y + 1);
                        cout << "当前" << (params.cheat_mode ? "已开启" : "未开启") << "作弊模式"
                             << endl;
                    }
                }
            }
        }
    }
    cct_disable_mouse();
}

/***************************************************************************
  函数名称：show_mouse_position_mode
  功    能：图形模式下只显示鼠标位置
  输入参数：GameMatrix& matrix - 游戏矩阵
            GameParams& params - 游戏参数
  返 回 值：无
  说    明：F选项专用，只显示鼠标位置，不进行游戏
***************************************************************************/
void show_mouse_position_mode(GameMatrix &matrix, GameParams &params)
{
    // 兼容Win11，确保鼠标事件能被捕获
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hInput, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hInput, mode);

    bool quit = false;
    int last_mx = -1, last_my = -1;

    // 默认开启作弊模式以显示解答
    params.cheat_mode = true;

    // 启用鼠标
    cct_enable_mouse();

    // 绘制初始游戏界面
    display_game_graphic(matrix, params);

    // 计算表格底部位置
    int cell_width = params.has_separators ? 5 : 2;
    int cell_height = params.has_separators ? 3 : 1;
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;
    int matrix_height = params.has_separators ? params.rows * 3 + 1 : params.rows + 2;
    int matrix_y = 3 + hint_height;
    int bottom_y = matrix_y + matrix_height + 2;

    // 显示操作提示
    cct_setcolor();
    cct_gotoxy(0, bottom_y);
    cout << "操作说明：移动鼠标显示坐标，Q键退出" << endl;

    INPUT_RECORD ir;
    DWORD read;
    while (!quit)
    {
        ReadConsoleInput(hInput, &ir, 1, &read);
        if (ir.EventType == MOUSE_EVENT)
        {
            auto &me = ir.Event.MouseEvent;
            int mx = me.dwMousePosition.X;
            int my = me.dwMousePosition.Y;
            DWORD btn = me.dwButtonState;
            DWORD evt = me.dwEventFlags;

            // 只有坐标变化时刷新显示，减少闪烁
            if (mx != last_mx || my != last_my)
            {
                last_mx = mx;
                last_my = my;

                // 显示鼠标位置信息
                display_mouse_position(mx, my, params);

                // 转换鼠标坐标为矩阵单元格坐标
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

                // 显示单元格信息
                cct_gotoxy(0, bottom_y + 2);
                if (is_valid)
                {
                    cout << "当前单元格: " << (char)('A' + row) << (char)('a' + col) << " ("
                         << row + 1 << "," << col + 1 << ")           ";

                    // 显示单元格内容信息
                    cout << " | 内容: ";
                    if (matrix.solution[row][col])
                    {
                        cout << "有球";
                    }
                    else
                    {
                        cout << "无球";
                    }
                }
                else
                {
                    cout << "当前位置: 不在有效单元格内                     ";
                }
            }

            // 处理鼠标点击事件
            if (btn != 0)
            {
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

                if (is_valid)
                {
                    cct_gotoxy(0, bottom_y + 3);
                    cout << "检测到点击: 位置=" << (char)('A' + row) << (char)('a' + col)
                         << " 内容=" << (matrix.solution[row][col] ? "有球" : "无球") << "      ";
                }
            }
        }
        else if (ir.EventType == KEY_EVENT)
        {
            if (ir.Event.KeyEvent.bKeyDown)
            {
                int keycode1 = ir.Event.KeyEvent.uChar.AsciiChar;
                if (keycode1 == 'q' || keycode1 == 'Q')
                {
                    quit = true;
                }
            }
        }
    }
    cct_disable_mouse();
}

void debug_raw_mouse_event()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hInput, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hInput, mode);

    std::cout << "请在窗口内移动、点击鼠标，按ESC退出\n";
    INPUT_RECORD ir;
    DWORD read;
    while (true)
    {
        ReadConsoleInput(hInput, &ir, 1, &read);
        if (ir.EventType == MOUSE_EVENT)
        {
            auto &me = ir.Event.MouseEvent;
            std::cout << "X=" << me.dwMousePosition.X << " Y=" << me.dwMousePosition.Y
                      << " ButtonState=" << me.dwButtonState << " EventFlags=" << me.dwEventFlags
                      << std::endl;
        }
        else if (ir.EventType == KEY_EVENT)
        {
            if (ir.Event.KeyEvent.bKeyDown && ir.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
            {
                std::cout << "ESC退出\n";
                break;
            }
        }
    }
}
