#include "pullze.h"
#include <Windows.h>

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

    while (!game_over)
    {
        // 显示游戏界面
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
                    if (matrix.cells[i][j] == EMPTY)
                    {
                        if (params.cheat_mode && matrix.solution[i][j])
                        {
                            cout << " O"; // 作弊模式显示普通的O
                        }
                        else
                            cout << "  ";
                    }
                    else if (matrix.cells[i][j] == MARKED)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HGREEN); // 用户标记为绿色高亮
                        cout << " O";
                        cct_setcolor(); // 恢复默认颜色
                    }
                    else if (matrix.cells[i][j] == MARKED_WRONG)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HRED); // 错误标记为红色高亮
                        cout << " X";
                        cct_setcolor(); // 恢复默认颜色
                    }
                    else if (matrix.cells[i][j] == MARKED_NOT)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HBLUE); // 标记为不存在为蓝色高亮
                        cout << " ·";
                        cct_setcolor(); // 恢复默认颜色
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
                    if (matrix.cells[i][j] == EMPTY)
                    {
                        if (params.cheat_mode && matrix.solution[i][j])
                        {
                            cout << " O"; // 作弊模式显示普通的O
                        }
                        else
                            cout << "  ";
                    }
                    else if (matrix.cells[i][j] == MARKED)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HGREEN); // 用户标记为绿色高亮
                        cout << " O";
                        cct_setcolor(); // 恢复默认颜色
                    }
                    else if (matrix.cells[i][j] == MARKED_WRONG)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HRED); // 错误标记为红色高亮
                        cout << " X";
                        cct_setcolor(); // 恢复默认颜色
                    }
                    else if (matrix.cells[i][j] == MARKED_NOT)
                    {
                        cct_setcolor(COLOR_BLACK, COLOR_HBLUE); // 标记为不存在为蓝色高亮
                        cout << " ·";
                        cct_setcolor(); // 恢复默认颜色
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

        // 显示当前作弊模式状态
        cout << "当前" << (params.cheat_mode ? "已开启" : "未开启") << "作弊模式" << endl;

        // 用户输入
        cout << "\n命令形式：Aa=等价于图形游戏中鼠标左键选择Aa位(区分大小写)" << endl;
        cout << "         不需要支持图形界面的右键打叉，再次输入Aa相当于清除" << endl;
        cout << "         X/x=退出(新行仅有X/x，不分大小写)" << endl;
        cout << "         Y/y=提交(新行仅有Y/y，不分大小写)" << endl;
        cout << "         Z/z=作弊(新行仅有Z/z，不分大小写)" << endl;
        cout << "输入命令：";
        char input[10];
        cin >> input;

        // 检查输入
        if ((input[0] == 'X' || input[0] == 'x') && input[1] == '\0')
        {
            game_over = true;
        }
        else if ((input[0] == 'Y' || input[0] == 'y') && input[1] == '\0')
        {
            // 验证解答
            int error_row, error_col;
            if (validate_solution(matrix, params, error_row, error_col))
            {
                cout << "恭喜！你的解答正确！" << endl;
                game_over = true;
                system("pause");
            }
            else
            {
                cout << "解答错误，第一个错误位置：" << (char)('A' + error_row)
                     << (char)('a' + error_col) << endl;
                system("pause");
            }
        }
        else if ((input[0] == 'Z' || input[0] == 'z') && input[1] == '\0')
        {
            // 切换作弊模式
            params.cheat_mode = !params.cheat_mode;
            cout << (params.cheat_mode ? "已开启" : "已关闭") << "作弊模式" << endl;
            system("pause");
        }
        else if (input[0] >= 'A' && input[0] <= 'A' + params.rows - 1 && input[1] >= 'a' &&
                 input[1] <= 'a' + params.cols - 1)
        {
            // 解析坐标
            int row = input[0] - 'A';
            int col = input[1] - 'a';

            // 检查坐标有效性
            if (row >= 0 && row < params.rows && col >= 0 && col < params.cols)
            {
                // 标记或取消标记
                mark_cell(matrix, params, row, col, 1);
            }
        }
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

    // 默认关闭作弊模式
    params.cheat_mode = false;

    // 启用鼠标
    cct_enable_mouse();

    // 绘制初始游戏界面
    display_game_graphic(matrix, params);

    // 显示操作提示
    cct_setcolor();
    cct_gotoxy(0, 25);
    cout << "操作说明：左键标记球存在，右键标记球不存在，Enter键提交，Q键退出，Z键切换作弊模式"
         << endl;
    cct_gotoxy(0, 26);
    cout << "当前" << (params.cheat_mode ? "已开启" : "未开启") << "作弊模式" << endl;

    while (!game_over)
    {
        int mx, my, maction, keycode1, keycode2;
        int ret = cct_read_keyboard_and_mouse(mx, my, maction, keycode1, keycode2);

        if (ret == CCT_MOUSE_EVENT)
        {
            // 鼠标事件
            display_mouse_position(mx, my, params);

            // 处理鼠标坐标显示（包括移动事件）
            int row, col;
            bool is_valid;
            convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

            if (is_valid)
            {
                // 显示当前单元格坐标
                cct_gotoxy(0, 27);
                cout << "当前单元格: " << (char)('A' + row) << (col + 1) << "                ";
            }
            else
            {
                // 清除单元格坐标显示
                cct_gotoxy(0, 27);
                cout << "                                  ";
            }

            if (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_RIGHT_BUTTON_CLICK)
            {
                if (is_valid)
                {
                    // 根据左右键不同的标记方式
                    if (maction == MOUSE_LEFT_BUTTON_CLICK)
                    {
                        mark_cell(matrix, params, row, col, 1);
                    }
                    else if (maction == MOUSE_RIGHT_BUTTON_CLICK)
                    {
                        mark_cell(matrix, params, row, col, 2);
                    }

                    // 重绘游戏界面
                    display_game_graphic(matrix, params);

                    // 显示操作提示
                    cct_setcolor();
                    cct_gotoxy(0, 25);
                    cout << "操作说明：左键标记球存在，右键标记球不存在，Enter键提交，Q键退出，Z键"
                            "切换作弊模式"
                         << endl;
                    cct_gotoxy(0, 26);
                    cout << "当前" << (params.cheat_mode ? "已开启" : "未开启") << "作弊模式"
                         << endl;
                }
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT)
        {
            // 键盘事件
            if (keycode1 == 'q' || keycode1 == 'Q')
            {
                game_over = true;
            }
            else if (keycode1 == 'z' || keycode1 == 'Z')
            {
                // 切换作弊模式
                params.cheat_mode = !params.cheat_mode;

                // 重绘游戏界面
                display_game_graphic(matrix, params);

                // 显示操作提示
                cct_setcolor();
                cct_gotoxy(0, 25);
                cout << "操作说明：左键标记球存在，右键标记球不存在，Enter键提交，Q键退出，Z键切换"
                        "作弊模式"
                     << endl;
                cct_gotoxy(0, 26);
                cout << "当前" << (params.cheat_mode ? "已开启" : "未开启") << "作弊模式" << endl;
                cct_gotoxy(0, 27);
                cout << (params.cheat_mode ? "已开启" : "已关闭") << "作弊模式                   "
                     << endl;
                Sleep(500); // 显示一下切换提示
            }
            else if (keycode1 == '\r')
            {
                // 验证解答
                int error_row, error_col;
                if (validate_solution(matrix, params, error_row, error_col))
                {
                    cct_gotoxy(0, 28);
                    cout << "恭喜！你的解答正确！" << endl;
                    game_over = true;
                    system("pause");
                }
                else
                {
                    cct_gotoxy(0, 28);
                    cout << "解答错误，第一个错误位置：" << (char)('A' + error_row)
                         << (error_col + 1) << "      " << endl;

                    // 标记错误位置
                    int cell_width = params.has_separators ? 5 : 2;
                    int cell_height = params.has_separators ? 3 : 1;
                    int hint_width = matrix.hint_width * 2;
                    int hint_height = matrix.hint_height;
                    int matrix_x = 5 + hint_width;
                    int matrix_y = 3 + hint_height;

                    // 闪烁提示错误位置
                    for (int i = 0; i < 3; i++)
                    {
                        int x = matrix_x + error_col * cell_width;
                        int y = matrix_y + error_row * cell_height;

                        if (params.has_separators)
                        {
                            x += 2; // 在单元格中心位置
                            y += 1;
                        }
                        else
                        {
                            x += 1;
                            y += 1;
                        }

                        cct_gotoxy(x, y);
                        cct_setcolor(COLOR_BLACK, COLOR_HRED);
                        cout << "X";
                        Sleep(300);

                        cct_gotoxy(x, y);
                        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                        cout << " ";
                        Sleep(300);
                    }

                    // 恢复显示
                    display_game_graphic(matrix, params);

                    // 显示操作提示
                    cct_setcolor();
                    cct_gotoxy(0, 25);
                    cout << "操作说明：左键标记球存在，右键标记球不存在，Enter键提交，Q键退出，Z键"
                            "切换作弊模式"
                         << endl;
                    cct_gotoxy(0, 26);
                    cout << "当前" << (params.cheat_mode ? "已开启" : "未开启") << "作弊模式"
                         << endl;
                }
            }
        }
    }

    // 禁用鼠标
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

    // 默认开启作弊模式以显示解答
    params.cheat_mode = true;

    // 启用鼠标
    cct_enable_mouse();

    // 绘制初始游戏界面
    display_game_graphic(matrix, params);

    // 显示操作提示
    cct_setcolor();
    cct_gotoxy(0, 25);
    cout << "操作说明：移动鼠标显示坐标，Q键退出" << endl;

    while (!quit)
    {
        int mx, my, maction, keycode1, keycode2;
        int ret = cct_read_keyboard_and_mouse(mx, my, maction, keycode1, keycode2);

        if (ret == CCT_MOUSE_EVENT)
        {
            // 鼠标事件
            display_mouse_position(mx, my, params);

            // 处理鼠标坐标显示（包括移动事件）
            int row, col;
            bool is_valid;
            convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

            if (is_valid)
            {
                // 显示当前单元格坐标
                cct_gotoxy(0, 27);
                cout << "当前单元格: " << (char)('A' + row) << (col + 1) << "                ";
            }
            else
            {
                // 清除单元格坐标显示
                cct_gotoxy(0, 27);
                cout << "                                  ";
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT)
        {
            // 键盘事件
            if (keycode1 == 'q' || keycode1 == 'Q')
            {
                quit = true;
            }
        }
    }

    // 禁用鼠标
    cct_disable_mouse();
}
