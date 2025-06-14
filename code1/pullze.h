#pragma once
#include "cmd_console_tools.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

/* 常量定义 */
#define MAX_MATRIX_SIZE 25 // 最大矩阵尺寸

/* 矩阵中的元素状态 */
enum CellStatus
{
    EMPTY = 0,        // 空
    FILLED = 1,       // 有球
    MARKED = 2,       // 标记为有球(左键)
    MARKED_WRONG = 3, // 标记错误
    MARKED_NOT = 4,   // 标记为没有球(右键)
    // 新增状态，用于作弊模式下的不同显示
    CHEAT_EMPTY = 5,     // 作弊模式下：有球但尚未选择(灰色O)
    CHEAT_MARKED = 6,    // 作弊模式下：有球且已左键选择(蓝色O)
    CHEAT_WRONG = 7,     // 作弊模式下：无球但已左键选择(红色O)
    CHEAT_NOT_RIGHT = 8, // 作弊模式下：无球且右键标注(红色×)
    CHEAT_BALL_RIGHT = 9 // 作弊模式下：有球但已右键标注(蓝色×)
};

/* 游戏参数结构体 */
struct GameParams
{
    int rows;            // 行数
    int cols;            // 列数
    bool cheat_mode;     // 作弊模式
    bool has_separators; // 是否有分隔线
};

/* 游戏矩阵结构体 */
struct GameMatrix
{
    CellStatus cells[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];  // 矩阵状态
    bool solution[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];     // 解决方案
    int row_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2]; // 行提示
    int row_hint_count[MAX_MATRIX_SIZE];                 // 行提示计数
    int col_hints[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE / 2]; // 列提示
    int col_hint_count[MAX_MATRIX_SIZE];                 // 列提示计数
    int hint_width;                                      // 提示区宽度
    int hint_height;                                     // 提示区高度
};

/* 基本函数 - puzzle_base.cpp */
void init_game(GameMatrix &matrix, const GameParams &params);
void generate_matrix(GameMatrix &matrix, const GameParams &params);
void calculate_hints(GameMatrix &matrix, const GameParams &params);
bool validate_solution(const GameMatrix &matrix, const GameParams &params, int &error_row,
                       int &error_col);
void mark_cell(GameMatrix &matrix, const GameParams &params, int row, int col, int mark_type);

/* 控制台显示函数 - puzzle_console.cpp */
void display_matrix_text(const GameMatrix &matrix, const GameParams &params);
void display_hints_text(const GameMatrix &matrix, const GameParams &params);
void display_matrix_graphic(const GameMatrix &matrix, const GameParams &params);
void display_game_graphic(const GameMatrix &matrix, const GameParams &params);
void display_cell(int x, int y, CellStatus status, bool has_separators);
void display_mouse_position(int mx, int my, const GameParams &params);
void convert_mouse_to_cell(int mx, int my, int &row, int &col, const GameParams &params,
                           const GameMatrix &matrix, bool &is_valid);

/* 工具函数 - puzzle_tools.cpp */
int show_menu();
bool get_game_params(GameParams &params);
void play_game_text_mode(GameMatrix &matrix, GameParams &params);
void play_game_graphic_mode(GameMatrix &matrix, GameParams &params);
void show_mouse_position_mode(GameMatrix &matrix, GameParams &params);
void draw_frame(int x, int y, int width, int height, bool has_separators);