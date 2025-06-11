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

    cct_cls();
    cct_setcolor();

    cout << "========== 数织游戏 ==========" << endl;
    cout << "1. 文本模式 - 初始化矩阵并打印" << endl;
    cout << "2. 文本模式 - 生成行/列提示栏并打印" << endl;
    cout << "3. 文本模式 - 完整游戏" << endl;
    cout << "4. 图形模式(无分隔线) - 初始状态" << endl;
    cout << "5. 图形模式(无分隔线) - 含提示栏" << endl;
    cout << "6. 图形模式(无分隔线) - 鼠标移动" << endl;
    cout << "7. 图形模式(无分隔线) - 完整游戏" << endl;
    cout << "8. 图形模式(有分隔线) - 初始状态" << endl;
    cout << "9. 图形模式(有分隔线) - 含提示栏" << endl;
    cout << "10. 图形模式(有分隔线) - 鼠标移动" << endl;
    cout << "11. 图形模式(有分隔线) - 完整游戏" << endl;
    cout << "0. 退出" << endl;
    cout << "请选择: ";

    while (!(cin >> choice) || choice < 0 || choice > 11)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "输入错误，请重新选择: ";
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

    cout << "请输入行数 (5-" << MAX_MATRIX_SIZE << "): ";
    while (!(cin >> params.rows) || params.rows < 5 || params.rows > MAX_MATRIX_SIZE)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "输入错误，请重新输入行数 (5-" << MAX_MATRIX_SIZE << "): ";
    }

    cout << "请输入列数 (5-" << MAX_MATRIX_SIZE << "): ";
    while (!(cin >> params.cols) || params.cols < 5 || params.cols > MAX_MATRIX_SIZE)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "输入错误，请重新输入列数 (5-" << MAX_MATRIX_SIZE << "): ";
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
        display_hints_text(matrix, params);

        // 显示当前状态
        for (int i = 0; i < params.rows; i++)
        {
            cout << (char)('A' + i) << ": ";
            for (int j = 0; j < params.cols; j++)
            {
                if (matrix.cells[i][j] == EMPTY)
                {
                    cout << ". ";
                }
                else if (matrix.cells[i][j] == MARKED)
                {
                    cout << "0 ";
                }
                else if (matrix.cells[i][j] == MARKED_WRONG)
                {
                    cout << "X ";
                }
                else if (matrix.cells[i][j] == MARKED_NOT)
                {
                    cout << "· ";
                }

                if (params.cheat_mode && matrix.solution[i][j] && matrix.cells[i][j] == EMPTY)
                {
                    cout << "0 ";
                }
            }
            cout << endl;
        }

        // 用户输入
        cout << "\n输入坐标(如A1)标记球的位置，输入Q退出，输入C提交: ";
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
                cout << "解答错误，第一个错误位置：" << (char)('A' + error_row) << (error_col + 1)
                     << endl;
                system("pause");
            }
        }
        else if (input[0] >= 'A' && input[0] <= 'A' + params.rows - 1 && input[1] >= '1' &&
                 input[1] <= '9')
        {
            // 解析坐标
            int row = input[0] - 'A';
            int col = atoi(input + 1) - 1;

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