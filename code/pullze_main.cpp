#include "pullze.h"
#include <conio.h>

/* ȫ�ֱ������� */
// ��Ϸ����
int g_rows = 0;
int g_cols = 0;
bool g_cheat_mode = false;
bool g_has_separators = false;

// ��Ϸ����
CellStatus g_cells[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
bool g_solution[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
int g_row_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2];
int g_row_hint_count[MAX_MATRIX_SIZE];
int g_col_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2];
int g_col_hint_count[MAX_MATRIX_SIZE];
int g_hint_width = 0;
int g_hint_height = 0;

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

    // ��ѭ��
    bool quit = false;
    while (!quit)
    {
        // ��ʾ�˵�����ȡѡ��
        int choice = show_menu();

        switch (choice)
        {
        case 1: // A.�ڲ����飬ԭ�����
            g_has_separators = false;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                display_matrix_text();
                cout << "��С�������������End����...";
                char end_str[10];
                cin >> end_str;
            }
            break;

        case 2: // B.�ڲ����飬������ʾ���в����
            g_has_separators = false;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                display_hints_text();
                cout << "��С�������������End����...";
                char end_str[10];
                cin >> end_str;
            }
            break;

        case 3: // C.�ڲ����飬��Ϸ��
            g_has_separators = false;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                play_game_text_mode();
            }
            break;

        case 4: // D.n*n�Ŀ��(�޷ָ���)��ԭ�����
            g_has_separators = false;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                display_matrix_graphic();
                cout << "�밴���������...";
                _getch();
            }
            break;

        case 5: // E.n*n�Ŀ��(�޷ָ���)������ʾ����
            g_has_separators = false;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                display_game_graphic();
                cout << "�밴���������...";
                _getch();
            }
            break;

        case 6: // F.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬������ƶ�����ʾ����
            g_has_separators = false;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                show_mouse_position_mode();
            }
            break;

        case 7: // G.cmdͼ�ν���������(�޷ָ���)
            g_has_separators = false;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                play_game_graphic_mode();
            }
            break;

        case 8: // H.n*n�Ŀ��(�зָ���)��ԭ�����
            g_has_separators = true;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                display_matrix_graphic();
                cout << "�밴���������...";
                _getch();
            }
            break;

        case 9: // I.n*n�Ŀ��(�зָ���)������ʾ����
            g_has_separators = true;
            g_cheat_mode = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                display_game_graphic();
                cout << "�밴���������...";
                _getch();
            }
            break;

        case 10: // J.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬������ƶ�����ʾ����
            g_has_separators = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                show_mouse_position_mode();
            }
            break;

        case 11: // K.cmdͼ�ν���������(�зָ���)
            g_has_separators = true;
            if (get_game_params())
            {
                init_game();
                generate_matrix();
                calculate_hints();
                play_game_graphic_mode();
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