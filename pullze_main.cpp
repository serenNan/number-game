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
        case 1: // A.内部数组，原样输出
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

        case 2: // B.内部数组，生成提示行列并输出
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

        case 3: // C.内部数组，游戏版
            params.has_separators = false;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                play_game_text_mode(matrix, params);
            }
            break;

        case 4: // D.n*n的框架(无分隔线)，原样输出
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

        case 5: // E.n*n的框架(无分隔线)，含提示行列
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

        case 6: // F.n*n的框架(无分隔线)，显示初始状态，鼠标移动可显示坐标
            params.has_separators = false;
            params.cheat_mode = true;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                play_game_graphic_mode(matrix, params);
            }
            break;

        case 7: // G.cmd图形界面完整版(无分隔线)
            params.has_separators = false;
            params.cheat_mode = false;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                play_game_graphic_mode(matrix, params);
            }
            break;

        case 8: // H.n*n的框架(有分隔线)，原样输出
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

        case 9: // I.n*n的框架(有分隔线)，含提示行列
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

        case 10: // J.n*n的框架(有分隔线)，显示初始状态，鼠标移动可显示坐标
            params.has_separators = true;
            params.cheat_mode = true;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                play_game_graphic_mode(matrix, params);
            }
            break;

        case 11: // K.cmd图形界面完整版(有分隔线)
            params.has_separators = true;
            params.cheat_mode = false;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                play_game_graphic_mode(matrix, params);
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