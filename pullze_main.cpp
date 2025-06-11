#include "pullze.h"

/***************************************************************************
  �������ƣ�main
  ��    �ܣ�������
  �����������
  �� �� ֵ��0-��������
  ˵    �����������ڵ�
***************************************************************************/
int main()
{
    // ��ʼ�������������
    srand((unsigned int)time(0));

    // ���ÿ���̨����
    cct_setconsoleborder(120, 40);
    cct_setfontsize("������", 16);
    cct_setcursor(CURSOR_INVISIBLE); // ���ع��

    // ��Ϸ�����;���
    GameParams params;
    GameMatrix matrix;

    // ��ѭ��
    bool quit = false;
    while (!quit)
    {
        // ��ʾ�˵�����ȡѡ��
        int choice = show_menu();

        switch (choice)
        {
        case 1: // A.�ڲ����飬ԭ�����
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

        case 2: // B.�ڲ����飬������ʾ���в����
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

        case 3: // C.�ڲ����飬��Ϸ��
            params.has_separators = false;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                play_game_text_mode(matrix, params);
            }
            break;

        case 4: // D.n*n�Ŀ��(�޷ָ���)��ԭ�����
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

        case 5: // E.n*n�Ŀ��(�޷ָ���)������ʾ����
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

        case 6: // F.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬������ƶ�����ʾ����
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

        case 7: // G.cmdͼ�ν���������(�޷ָ���)
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

        case 8: // H.n*n�Ŀ��(�зָ���)��ԭ�����
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

        case 9: // I.n*n�Ŀ��(�зָ���)������ʾ����
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

        case 10: // J.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬������ƶ�����ʾ����
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

        case 11: // K.cmdͼ�ν���������(�зָ���)
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

        case 0: // Q.�˳�
            quit = true;
            break;

        default:
            break;
        }

        // ������׼����һ����ʾ
        cct_cls();
    }

    return 0;
}