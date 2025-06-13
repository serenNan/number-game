#pragma once
#include "cmd_console_tools.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

/* �������� */
#define MAX_MATRIX_SIZE 25 // ������ߴ�
#define MAX_STR_LEN 256    // ����ַ�������

/* �����е�Ԫ��״̬ */
enum CellStatus
{
    EMPTY = 0,        // ��
    FILLED = 1,       // ����
    MARKED = 2,       // ���Ϊ����
    MARKED_WRONG = 3, // ��Ǵ���
    MARKED_NOT = 4    // ���Ϊû����
};

/* ��Ϸ���� - ʹ����ͨ��������ṹ�� */
// ��Ϸ����ȫ�ֱ���
extern int g_rows;            // ����
extern int g_cols;            // ����
extern bool g_cheat_mode;     // ����ģʽ
extern bool g_has_separators; // �Ƿ��зָ���

/* ��Ϸ���� - ʹ����ͨ��������ṹ�� */
// ����״̬
extern CellStatus g_cells[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
// �������
extern bool g_solution[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
// ����ʾ
extern int g_row_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2];
// ����ʾ����
extern int g_row_hint_count[MAX_MATRIX_SIZE];
// ����ʾ
extern int g_col_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2];
// ����ʾ����
extern int g_col_hint_count[MAX_MATRIX_SIZE];
// ��ʾ�����
extern int g_hint_width;
// ��ʾ���߶�
extern int g_hint_height;

/* �������� - puzzle_base.cpp */
void init_game();
void generate_matrix();
void calculate_hints();
bool validate_solution(int &error_row, int &error_col);
void mark_cell(int row, int col, int mark_type);

/* ����̨��ʾ���� - puzzle_console.cpp */
void display_matrix_text();
void display_hints_text();
void display_matrix_graphic();
void display_game_graphic();
void display_cell(int x, int y, CellStatus status, bool has_separators);
void display_mouse_position(int mx, int my);
void convert_mouse_to_cell(int mx, int my, int &row, int &col, bool &is_valid);

/* ���ߺ��� - puzzle_tools.cpp */
int show_menu();
bool get_game_params();
void play_game_text_mode();
void play_game_graphic_mode();
void show_mouse_position_mode();
void draw_frame(int x, int y, int width, int height, bool has_separators);
void print_repeated_char(char ch, int count); // ��������ӡ�ظ��ַ��ĺ���