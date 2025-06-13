#pragma once
#include "cmd_console_tools.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

/* 常量定义 */
#define MAX_MATRIX_SIZE 25 // 最大矩阵尺寸
#define MAX_STR_LEN 256    // 最大字符串长度

/* 矩阵中的元素状态 */
enum CellStatus
{
    EMPTY = 0,        // 空
    FILLED = 1,       // 有球
    MARKED = 2,       // 标记为有球
    MARKED_WRONG = 3, // 标记错误
    MARKED_NOT = 4    // 标记为没有球
};

/* 游戏参数 - 使用普通变量替代结构体 */
// 游戏参数全局变量
extern int g_rows;            // 行数
extern int g_cols;            // 列数
extern bool g_cheat_mode;     // 作弊模式
extern bool g_has_separators; // 是否有分隔线

/* 游戏矩阵 - 使用普通数组替代结构体 */
// 矩阵状态
extern CellStatus g_cells[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
// 解决方案
extern bool g_solution[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
// 行提示
extern int g_row_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2];
// 行提示计数
extern int g_row_hint_count[MAX_MATRIX_SIZE];
// 列提示
extern int g_col_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2];
// 列提示计数
extern int g_col_hint_count[MAX_MATRIX_SIZE];
// 提示区宽度
extern int g_hint_width;
// 提示区高度
extern int g_hint_height;

/* 基本函数 - puzzle_base.cpp */
void init_game();
void generate_matrix();
void calculate_hints();
bool validate_solution(int &error_row, int &error_col);
void mark_cell(int row, int col, int mark_type);

/* 控制台显示函数 - puzzle_console.cpp */
void display_matrix_text();
void display_hints_text();
void display_matrix_graphic();
void display_game_graphic();
void display_cell(int x, int y, CellStatus status, bool has_separators);
void display_mouse_position(int mx, int my);
void convert_mouse_to_cell(int mx, int my, int &row, int &col, bool &is_valid);

/* 工具函数 - puzzle_tools.cpp */
int show_menu();
bool get_game_params();
void play_game_text_mode();
void play_game_graphic_mode();
void show_mouse_position_mode();
void draw_frame(int x, int y, int width, int height, bool has_separators);
void print_repeated_char(char ch, int count); // 新增：打印重复字符的函数