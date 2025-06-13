#pragma once
#include "cmd_console_tools.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

/* �������� */
#define MAX_MATRIX_SIZE 25 // ������ߴ�

/* �����е�Ԫ��״̬ */
enum CellStatus
{
    EMPTY = 0,        // ��
    FILLED = 1,       // ����
    MARKED = 2,       // ���Ϊ����(���)
    MARKED_WRONG = 3, // ��Ǵ���
    MARKED_NOT = 4,   // ���Ϊû����(�Ҽ�)
    // ����״̬����������ģʽ�µĲ�ͬ��ʾ
    CHEAT_EMPTY = 5,     // ����ģʽ�£�������δѡ��(��ɫO)
    CHEAT_MARKED = 6,    // ����ģʽ�£������������ѡ��(��ɫO)
    CHEAT_WRONG = 7,     // ����ģʽ�£����������ѡ��(��ɫO)
    CHEAT_NOT_RIGHT = 8, // ����ģʽ�£��������Ҽ���ע(��ɫ��)
    CHEAT_BALL_RIGHT = 9 // ����ģʽ�£��������Ҽ���ע(��ɫ��)
};

/* ��Ϸ�����ṹ�� */
struct GameParams
{
    int rows;            // ����
    int cols;            // ����
    bool cheat_mode;     // ����ģʽ
    bool has_separators; // �Ƿ��зָ���
};

/* ��Ϸ����ṹ�� */
struct GameMatrix
{
    CellStatus cells[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];  // ����״̬
    bool solution[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];     // �������
    int row_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2]; // ����ʾ
    int row_hint_count[MAX_MATRIX_SIZE];                 // ����ʾ����
    int col_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2]; // ����ʾ
    int col_hint_count[MAX_MATRIX_SIZE];                 // ����ʾ����
    int hint_width;                                      // ��ʾ�����
    int hint_height;                                     // ��ʾ���߶�
};

/* �������� - puzzle_base.cpp */
void init_game(GameMatrix &matrix, const GameParams &params);
void generate_matrix(GameMatrix &matrix, const GameParams &params);
void calculate_hints(GameMatrix &matrix, const GameParams &params);
bool validate_solution(const GameMatrix &matrix, const GameParams &params, int &error_row,
                       int &error_col);
void mark_cell(GameMatrix &matrix, const GameParams &params, int row, int col, int mark_type);

/* ����̨��ʾ���� - puzzle_console.cpp */
void display_matrix_text(const GameMatrix &matrix, const GameParams &params);
void display_hints_text(const GameMatrix &matrix, const GameParams &params);
void display_matrix_graphic(const GameMatrix &matrix, const GameParams &params);
void display_game_graphic(const GameMatrix &matrix, const GameParams &params);
void display_cell(int x, int y, CellStatus status, bool has_separators);
void display_mouse_position(int mx, int my, const GameParams &params);
void convert_mouse_to_cell(int mx, int my, int &row, int &col, const GameParams &params,
                           const GameMatrix &matrix, bool &is_valid);

/* ���ߺ��� - puzzle_tools.cpp */
int show_menu();
bool get_game_params(GameParams &params);
void play_game_text_mode(GameMatrix &matrix, GameParams &params);
void play_game_graphic_mode(GameMatrix &matrix, GameParams &params);
void show_mouse_position_mode(GameMatrix &matrix, GameParams &params);
void draw_frame(int x, int y, int width, int height, bool has_separators);