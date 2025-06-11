#include "pullze.h"

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

    // 游戏参数和矩阵
    GameParams params;
    GameMatrix matrix;

    // 主循环
    bool quit = false;
    while (!quit)
    {
        // 显示菜单并获取选择
        int choice = show_menu();

        switch (choice)
        {
        case 1: // 文本模式-初始化矩阵并打印
            params.has_separators = false;
            params.cheat_mode = true;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                display_matrix_text(matrix, params);
                system("pause");
            }
            break;

        case 2: // 文本模式-生成行/列提示栏并打印
            params.has_separators = false;
            params.cheat_mode = true;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                display_matrix_text(matrix, params);
                display_hints_text(matrix, params);
                system("pause");
            }
            break;

        case 3: // 文本模式-完整游戏
            params.has_separators = false;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                play_game_text_mode(matrix, params);
            }
            break;

        case 4: // 图形模式无分隔线-初始状态
            params.has_separators = false;
            params.cheat_mode = true;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                display_matrix_graphic(matrix, params);
                system("pause");
            }
            break;

        case 5: // 图形模式无分隔线-含提示栏
            params.has_separators = false;
            params.cheat_mode = true;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                display_game_graphic(matrix, params);
                system("pause");
            }
            break;

        case 6: // 图形模式无分隔线-鼠标移动
        case 7: // 图形模式无分隔线-完整游戏
            params.has_separators = false;
            params.cheat_mode = (choice == 6);
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                play_game_graphic_mode(matrix, params);
            }
            break;

        case 8: // 图形模式有分隔线-初始状态
            params.has_separators = true;
            params.cheat_mode = true;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                display_matrix_graphic(matrix, params);
                system("pause");
            }
            break;

        case 9: // 图形模式有分隔线-含提示栏
            params.has_separators = true;
            params.cheat_mode = true;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                display_game_graphic(matrix, params);
                system("pause");
            }
            break;

        case 10: // 图形模式有分隔线-鼠标移动
        case 11: // 图形模式有分隔线-完整游戏
            params.has_separators = true;
            params.cheat_mode = (choice == 10);
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                play_game_graphic_mode(matrix, params);
            }
            break;

        case 0: // 退出
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