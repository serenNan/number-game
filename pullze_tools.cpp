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

    // 询问作弊模式（如果菜单选项没有预设）
    if (!params.cheat_mode)
    {
        char cheat;
        cout << "是否启用作弊模式(Y/N)? ";
        cin >> cheat;
        params.cheat_mode = (cheat == 'Y' || cheat == 'y');
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

    while (!game_over)
    {
        // 显示游戏界面
        cct_cls();

        cout << "初始数组：" << endl;

        // 显示列提示
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

        // 显示矩阵内容和行提示
        for (int i = 0; i < params.rows; i++)
        {
            // 显示行提示
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

            // 显示行标题（A,B,C,...）
            cout << (char)('A' + i) << "|";

            for (int j = 0; j < params.cols; j++)
            {
                if (matrix.cells[i][j] == EMPTY)
                {
                    if (params.cheat_mode && matrix.solution[i][j])
                        cout << " O";
                    else
                        cout << "  ";
                }
                else if (matrix.cells[i][j] == MARKED)
                {
                    cout << " O";
                }
                else if (matrix.cells[i][j] == MARKED_WRONG)
                {
                    cout << " X";
                }
                else if (matrix.cells[i][j] == MARKED_NOT)
                {
                    cout << " ·";
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

        // 显示底部边框
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

        // 用户输入
        cout << "\n输入坐标(如Aa)标记球的位置，输入Q退出，输入C提交: ";
        char input[10];
        cin >> input;

        // 检查输入
        if (input[0] == 'Q' || input[0] == 'q')
        {
            game_over = true;
        }
        else if (input[0] == 'C' || input[0] == 'c')
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
    bool game_over = false;

    // 启用鼠标
    cct_enable_mouse();

    // 绘制初始游戏界面
    display_game_graphic(matrix, params);

    // 显示操作提示
    cct_setcolor();
    cct_gotoxy(0, 25);
    cout << "操作说明：左键标记球存在，右键标记球不存在，Enter键提交，Q键退出" << endl;

    while (!game_over)
    {
        int mx, my, maction, keycode1, keycode2;
        int ret = cct_read_keyboard_and_mouse(mx, my, maction, keycode1, keycode2);

        if (ret == CCT_MOUSE_EVENT)
        {
            // 鼠标事件
            display_mouse_position(mx, my, params);

            if (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_RIGHT_BUTTON_CLICK)
            {
                int row, col;
                bool is_valid;

                convert_mouse_to_cell(mx, my, row, col, params, is_valid);

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
                    cout << "操作说明：左键标记球存在，右键标记球不存在，Enter键提交，Q键退出"
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
                    int cell_width = params.has_separators ? 3 : 2;
                    int cell_height = params.has_separators ? 2 : 1;
                    int hint_width = matrix.hint_width * 3;
                    int hint_height = matrix.hint_height * 2;
                    int matrix_x = 5 + hint_width;
                    int matrix_y = 3 + hint_height;

                    // 闪烁提示错误位置
                    for (int i = 0; i < 3; i++)
                    {
                        cct_gotoxy(matrix_x + error_col * cell_width + 1,
                                   matrix_y + error_row * cell_height + 1);
                        cct_setcolor(COLOR_BLACK, COLOR_HRED);
                        cout << "X";
                        Sleep(300);

                        cct_gotoxy(matrix_x + error_col * cell_width + 1,
                                   matrix_y + error_row * cell_height + 1);
                        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                        cout << " ";
                        Sleep(300);
                    }

                    // 恢复显示
                    display_game_graphic(matrix, params);

                    // 显示操作提示
                    cct_setcolor();
                    cct_gotoxy(0, 25);
                    cout << "操作说明：左键标记球存在，右键标记球不存在，Enter键提交，Q键退出"
                         << endl;
                }
            }
        }
    }

    // 禁用鼠标
    cct_disable_mouse();
}