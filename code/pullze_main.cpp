#include "pullze.h"
#include <conio.h>

/* 全局变量定义 */
// 游戏参数
int g_rows = 0;
int g_cols = 0;
bool g_cheat_mode = false;
bool g_has_separators = false;

// 游戏矩阵
CellStatus g_cells[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
bool g_solution[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
int g_row_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2];
int g_row_hint_count[MAX_MATRIX_SIZE];
int g_col_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2];
int g_col_hint_count[MAX_MATRIX_SIZE];
int g_hint_width = 0;
int g_hint_height = 0;

/***************************************************************************
  函数名称：main
  功    能：主函数
  输入参数：无
  返 回 值：0-正常结束
  说    明：程序的入口点
***************************************************************************/
int main()
{
    // 初始化随机数生成器
    srand((unsigned int)time(0));

    // 设置控制台属性
    cct_setconsoleborder(120, 40);
    cct_setfontsize("新宋体", 16);
    cct_setcursor(CURSOR_INVISIBLE); // 隐藏光标

    // 主循环
    bool quit = false;
    while (!quit)
    {
        // 显示菜单并获取选择
        int choice = show_menu();

        switch (choice)
        {
        case 1: // A.内部数组，原样输出
            g_has_separators = false;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                display_matrix_text();
                cout << "本小题结束，请输入End继续...";
                char end_str[10];
                cin >> end_str;
            }
            break;

        case 2: // B.内部数组，生成提示行列并输出
            g_has_separators = false;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                display_hints_text();
                cout << "本小题结束，请输入End继续...";
                char end_str[10];
                cin >> end_str;
            }
            break;

        case 3: // C.内部数组，游戏版
            g_has_separators = false;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                play_game_text_mode();
            }
            break;

        case 4: // D.n*n的框架(无分隔线)，原样输出
            g_has_separators = false;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                display_matrix_graphic();
                cout << "请按任意键继续...";
                _getch();
            }
            break;

        case 5: // E.n*n的框架(无分隔线)，含提示行列
            g_has_separators = false;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                display_game_graphic();
                cout << "请按任意键继续...";
                _getch();
            }
            break;

        case 6: // F.n*n的框架(无分隔线)，显示初始状态，鼠标移动可显示坐标
            g_has_separators = false;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                show_mouse_position_mode();
            }
            break;

        case 7: // G.cmd图形界面完整版(无分隔线)
            g_has_separators = false;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                play_game_graphic_mode();
            }
            break;

        case 8: // H.n*n的框架(有分隔线)，原样输出
            g_has_separators = true;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                display_matrix_graphic();
                cout << "请按任意键继续...";
                _getch();
            }
            break;

        case 9: // I.n*n的框架(有分隔线)，含提示行列
            g_has_separators = true;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                display_game_graphic();
                cout << "请按任意键继续...";
                _getch();
            }
            break;

        case 10: // J.n*n的框架(有分隔线)，显示初始状态，鼠标移动可显示坐标
            g_has_separators = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                show_mouse_position_mode();
            }
            break;

        case 11: // K.cmd图形界面完整版(有分隔线)
            g_has_separators = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                play_game_graphic_mode();
            }
            break;

        case 0: // Q.退出
            quit = true;
            break;

        default:
            break;
        }

        // 清屏以准备下一次显示
        cct_cls();
    }

    return 0;
}