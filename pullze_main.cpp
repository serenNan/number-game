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
        case 1: // �ı�ģʽ-��ʼ�����󲢴�ӡ
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

        case 2: // �ı�ģʽ-������/����ʾ������ӡ
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

        case 3: // �ı�ģʽ-������Ϸ
            params.has_separators = false;
            if (get_game_params(params))
            {
                init_game(matrix, params);
                generate_matrix(matrix, params);
                calculate_hints(matrix, params);
                play_game_text_mode(matrix, params);
            }
            break;

        case 4: // ͼ��ģʽ�޷ָ���-��ʼ״̬
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

        case 5: // ͼ��ģʽ�޷ָ���-����ʾ��
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

        case 6: // ͼ��ģʽ�޷ָ���-����ƶ�
        case 7: // ͼ��ģʽ�޷ָ���-������Ϸ
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

        case 8: // ͼ��ģʽ�зָ���-��ʼ״̬
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

        case 9: // ͼ��ģʽ�зָ���-����ʾ��
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

        case 10: // ͼ��ģʽ�зָ���-����ƶ�
        case 11: // ͼ��ģʽ�зָ���-������Ϸ
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

        case 0: // �˳�
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