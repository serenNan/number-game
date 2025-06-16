/*
 * 鼠标事件实现关键源码
 *
 * 本文件总结了项目中鼠标事件处理的关键代码
 */

#include <iomanip>
#include <iostream>
#include <windows.h>

using namespace std;

/* 定义鼠标键盘操作类型 */
#define CCT_MOUSE_EVENT 0
#define CCT_KEYBOARD_EVENT 1

/* 定义鼠标的操作 */
#define MOUSE_NO_ACTION 0x0000                 // 无鼠标操作
#define MOUSE_ONLY_MOVED 0x0001                // 鼠标移动
#define MOUSE_LEFT_BUTTON_CLICK 0x0002         // 按下左键
#define MOUSE_LEFT_BUTTON_DOUBLE_CLICK 0x0004  // 双击左键
#define MOUSE_RIGHT_BUTTON_CLICK 0x0008        // 按下右键
#define MOUSE_RIGHT_BUTTON_DOUBLE_CLICK 0x0010 // 双击右键
#define MOUSE_LEFTRIGHT_BUTTON_CLICK 0x0020    // 同时按下左右键
#define MOUSE_WHEEL_CLICK 0x0040               // 滚轮被按下
#define MOUSE_WHEEL_MOVED_UP 0x0080            // 滚轮向上移动
#define MOUSE_WHEEL_MOVED_DOWN 0x0100          // 滚轮向下移动

// 声明外部控制台句柄
extern HANDLE __hin;  // 标准输入句柄
extern HANDLE __hout; // 标准输出句柄

/***************************************************************************
  函数名称：cct_enable_mouse
  功    能：允许使用鼠标
  输入参数：无
  返 回 值：无
  说    明：如果想使用鼠标，必须先调用本函数打开，才能读到鼠标动作
***************************************************************************/
void cct_enable_mouse(void)
{
    DWORD Mode;

    GetConsoleMode(__hin, &Mode); /* 取得控制台原来的模式 */
    SetConsoleMode(__hin,
                   Mode | ENABLE_MOUSE_INPUT); // 加入鼠标支持（可能原先已支持鼠标，再加也没错）
}

/***************************************************************************
  函数名称：cct_disable_mouse
  功    能：禁止使用鼠标
  输入参数：无
  返 回 值：无
  说    明：用cct_enable_mouse允许使用鼠标后，如果不需要，用本函数关闭
***************************************************************************/
void cct_disable_mouse(void)
{
    DWORD Mode;

    GetConsoleMode(__hin, &Mode); /* 取得控制台原来的模式 */
    SetConsoleMode(
        __hin, Mode & (~ENABLE_MOUSE_INPUT)); // 去除鼠标支持（如果原先已不支持鼠标，再设也没错）
}

/***************************************************************************
  函数名称：cct_read_keyboard_and_mouse
  功    能：读鼠标按键
  输入参数：int& MX - 返回鼠标X坐标
            int& MY - 返回鼠标Y坐标
            int& MAction - 返回鼠标动作
            int& keycode1 - 返回键盘码1
            int& keycode2 - 返回键盘码2
  返 回 值：CCT_MOUSE_EVENT - 鼠标事件
            CCT_KEYBOARD_EVENT - 键盘事件
  说    明：读取鼠标或键盘事件
***************************************************************************/
int cct_read_keyboard_and_mouse(int &MX, int &MY, int &MAction, int &keycode1, int &keycode2)
{
    static int MX_old = -1, MY_old = -1, MAction_old = MOUSE_ONLY_MOVED;
    INPUT_RECORD InputRec;
    DWORD res;
    COORD crPos;

    while (1)
    {
        /* 从hin中读输入状态（包括鼠标、键盘等） */
        ReadConsoleInput(__hin, &InputRec, 1, &res);

        /* 键盘事件（要优于鼠标事件，否则如果鼠标放在目标区，无法读键） */
        if (InputRec.EventType == KEY_EVENT)
        {
            keycode1 = 0x00;
            keycode2 = 0x00;
            if (InputRec.Event.KeyEvent.bKeyDown)
            { // 只在按下时判断，弹起时不判断
                /* 非箭头键直接返回ASCII形式（Fn、Insert、Delete等均未处理） */
                keycode1 = InputRec.Event.KeyEvent.uChar.AsciiChar;
                return CCT_KEYBOARD_EVENT;
            } // end of if (KEYDOWN)
        } // end of if (键盘事件)

        /* 鼠标事件 */
        if (InputRec.EventType == MOUSE_EVENT)
        {
            /* 从返回中读鼠标指针当前的坐标 */
            crPos = InputRec.Event.MouseEvent.dwMousePosition;
            MX = crPos.X;
            MY = crPos.Y;

            if (InputRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
            { // 鼠标移动
                /* 如果始终是MOUSE_MOVED事件且坐标不变，则不认为是MOUSE_MOVED */
                if (MX_old == MX && MY_old == MY && MAction_old == MOUSE_ONLY_MOVED)
                    continue;

                /* 位置变化则记录下来 */
                MX_old = MX;
                MY_old = MY;
                MAction = MOUSE_ONLY_MOVED;
                MAction_old = MAction;
                return CCT_MOUSE_EVENT;
            }
            MAction_old = MOUSE_NO_ACTION; // 置非MOUSE_ONLY_MOVED值即可

            if (InputRec.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED)
            {                                                             // 滚轮移动
                if (InputRec.Event.MouseEvent.dwButtonState & 0x80000000) // 高位为1，负数
                    MAction = MOUSE_WHEEL_MOVED_DOWN;
                else
                    MAction = MOUSE_WHEEL_MOVED_UP;
                return CCT_MOUSE_EVENT;
            }

            if (InputRec.Event.MouseEvent.dwButtonState ==
                (FROM_LEFT_1ST_BUTTON_PRESSED | RIGHTMOST_BUTTON_PRESSED))
            { // 同时按下左右键
                MAction = MOUSE_LEFTRIGHT_BUTTON_CLICK;
                return CCT_MOUSE_EVENT;
            }
            else if (InputRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            { // 按下左键
                if (InputRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
                    MAction = MOUSE_LEFT_BUTTON_DOUBLE_CLICK;
                else
                    MAction = MOUSE_LEFT_BUTTON_CLICK;
                return CCT_MOUSE_EVENT;
            }
            else if (InputRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
            { // 按下右键
                if (InputRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
                    MAction = MOUSE_RIGHT_BUTTON_DOUBLE_CLICK;
                else
                    MAction = MOUSE_RIGHT_BUTTON_CLICK;
                return CCT_MOUSE_EVENT;
            }
            else if (InputRec.Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED)
            { // 按下滚轮
                MAction = MOUSE_WHEEL_CLICK;
                return CCT_MOUSE_EVENT;
            }
            else // 忽略其它按键操作
                continue;
        } // end of if(鼠标事件)
    } // end of while(1)

    return CCT_MOUSE_EVENT; // 此句应该执行不到，为避免某些编译器报不完全分支错误，加
}

/***************************************************************************
  函数名称：convert_mouse_to_cell
  功    能：将鼠标坐标转换为矩阵单元格坐标
  输入参数：int mx - 鼠标X坐标
            int my - 鼠标Y坐标
            int& row - 返回行索引
            int& col - 返回列索引
            const GameParams& params - 游戏参数
            const GameMatrix& matrix - 游戏矩阵
            bool& is_valid - 返回是否有效
  返 回 值：无
  说    明：检查鼠标是否在有效的矩阵区域内，并转换坐标
***************************************************************************/
void convert_mouse_to_cell(int mx, int my, int &row, int &col, const GameParams &params,
                           const GameMatrix &matrix, bool &is_valid)
{
    // 设置单元格大小
    int cell_width = params.has_separators ? 5 : 2;  // 有分隔线时每个单元格占5列，否则占2列
    int cell_height = params.has_separators ? 3 : 1; // 有分隔线时每个单元格占3行，否则占1行

    // 计算矩阵大小和位置
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;

    int matrix_x = 5 + hint_width;
    int matrix_y = 3 + hint_height;
    int matrix_width = params.cols * cell_width + 1;
    int matrix_height = params.rows * cell_height + 1;

    // 初始化为无效值
    row = -1;
    col = -1;
    is_valid = false;

    // 检查鼠标是否在矩阵区域内
    if (mx < matrix_x || mx >= matrix_x + matrix_width || my < matrix_y ||
        my >= matrix_y + matrix_height)
    {
        return; // 鼠标不在矩阵区域内
    }

    // 计算行列索引
    if (params.has_separators)
    {
        // 有分隔线模式
        // 排除边框线和分隔线的点击
        int rel_x = mx - matrix_x;
        int rel_y = my - matrix_y;

        // 检查是否点击在边框或分隔线上
        if (rel_x % cell_width == 0 || rel_y % cell_height == 0)
        {
            return; // 点击在边框或分隔线上，无效
        }

        col = rel_x / cell_width;
        row = rel_y / cell_height;
    }
    else
    {
        // 无分隔线模式
        // 矩阵内容区域从(matrix_x+1, matrix_y+1)开始
        if (mx >= matrix_x + 1 && mx < matrix_x + 1 + params.cols * cell_width &&
            my >= matrix_y + 1 && my < matrix_y + 1 + params.rows)
        {
            col = (mx - matrix_x - 1) / cell_width;
            row = my - matrix_y - 1;
        }
    }

    // 验证计算出的行列是否有效
    if (row >= 0 && row < params.rows && col >= 0 && col < params.cols)
    {
        is_valid = true;
    }
}

/***************************************************************************
  函数名称：display_mouse_position
  功    能：显示鼠标位置
  输入参数：int mx - 鼠标X坐标
            int my - 鼠标Y坐标
            const GameParams& params - 游戏参数
  返 回 值：无
  说    明：在状态栏显示鼠标位置
***************************************************************************/
void display_mouse_position(int mx, int my, const GameParams &params)
{
    // 设置默认颜色
    cct_setcolor();

    // 计算矩阵大小和位置
    int cell_width = params.has_separators ? 5 : 2;  // 有分隔线时每个单元格占5列，否则占2列
    int cell_height = params.has_separators ? 3 : 1; // 有分隔线时每个单元格占3行，否则占1行

    // 计算表格底部位置，确保坐标提示显示在表格下方
    int hint_height = 3; // 假设提示区高度
    int matrix_height = params.has_separators ? params.rows * 3 + 1 : params.rows + 2;
    int bottom_y = 3 + hint_height + matrix_height + 2;

    // 移动到状态栏位置
    cct_gotoxy(0, bottom_y);

    // 显示鼠标坐标信息
    cout << "鼠标位置: X=" << setw(3) << mx << ", Y=" << setw(3) << my;

    // 尝试转换为矩阵坐标
    int row, col;
    bool is_valid;
    GameMatrix dummy_matrix; // 创建一个临时矩阵用于坐标转换
    dummy_matrix.hint_width = 3;
    dummy_matrix.hint_height = 3;

    convert_mouse_to_cell(mx, my, row, col, params, dummy_matrix, is_valid);

    // 显示矩阵坐标（如果有效）
    if (is_valid)
    {
        cout << " | 矩阵坐标: 行=" << (char)('A' + row) << ", 列=" << (char)('a' + col);
    }
    else
    {
        cout << " | 矩阵坐标: 无效位置                ";
    }

    // 清除行尾可能的残留字符
    cout << "                    ";
}

/***************************************************************************
  函数名称：debug_raw_mouse_event
  功    能：调试模式，直接显示原始鼠标事件
  输入参数：无
  返 回 值：无
  说    明：用于测试鼠标事件
***************************************************************************/
void debug_raw_mouse_event()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hInput, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hInput, mode);

    std::cout << "请在窗口内移动、点击鼠标，按ESC退出\n";
    INPUT_RECORD ir;
    DWORD read;
    while (true)
    {
        ReadConsoleInput(hInput, &ir, 1, &read);
        if (ir.EventType == MOUSE_EVENT)
        {
            auto &me = ir.Event.MouseEvent;
            std::cout << "X=" << me.dwMousePosition.X << " Y=" << me.dwMousePosition.Y
                      << " ButtonState=" << me.dwButtonState << " EventFlags=" << me.dwEventFlags
                      << std::endl;
        }
        else if (ir.EventType == KEY_EVENT)
        {
            if (ir.Event.KeyEvent.bKeyDown && ir.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
            {
                std::cout << "ESC退出\n";
                break;
            }
        }
    }
}

/***************************************************************************
  函数名称：show_mouse_position_mode
  功    能：图形模式下只显示鼠标位置
  输入参数：GameMatrix& matrix - 游戏矩阵
            GameParams& params - 游戏参数
  返 回 值：无
  说    明：示例用法，显示鼠标位置，不进行游戏
***************************************************************************/
void show_mouse_position_mode(GameMatrix &matrix, GameParams &params)
{
    // 兼容Win11，确保鼠标事件能被捕获
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hInput, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hInput, mode);

    bool quit = false;
    int last_mx = -1, last_my = -1;

    // 启用鼠标
    cct_enable_mouse();

    // 绘制初始游戏界面
    display_game_graphic(matrix, params);

    // 计算表格底部位置
    int cell_width = params.has_separators ? 5 : 2;
    int cell_height = params.has_separators ? 3 : 1;
    int hint_width = matrix.hint_width * 2;
    int hint_height = matrix.hint_height;
    int matrix_height = params.has_separators ? params.rows * 3 + 1 : params.rows + 2;
    int matrix_y = 3 + hint_height;
    int bottom_y = matrix_y + matrix_height + 2;

    // 显示操作提示
    cct_setcolor();
    cct_gotoxy(0, bottom_y);
    cout << "操作说明：移动鼠标显示坐标，Q键退出" << endl;

    INPUT_RECORD ir;
    DWORD read;
    while (!quit)
    {
        ReadConsoleInput(hInput, &ir, 1, &read);
        if (ir.EventType == MOUSE_EVENT)
        {
            auto &me = ir.Event.MouseEvent;
            int mx = me.dwMousePosition.X;
            int my = me.dwMousePosition.Y;
            DWORD btn = me.dwButtonState;
            DWORD evt = me.dwEventFlags;

            // 只有坐标变化时刷新显示，减少闪烁
            if (mx != last_mx || my != last_my)
            {
                last_mx = mx;
                last_my = my;

                // 显示鼠标位置信息
                display_mouse_position(mx, my, params);

                // 转换鼠标坐标为矩阵单元格坐标
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

                // 显示单元格信息
                cct_gotoxy(0, bottom_y + 2);
                if (is_valid)
                {
                    cout << "当前单元格: " << (char)('A' + row) << (char)('a' + col) << " ("
                         << row + 1 << "," << col + 1 << ")           ";
                }
                else
                {
                    cout << "当前位置: 不在有效单元格内                     ";
                }
            }

            // 处理鼠标点击事件
            if (btn != 0)
            {
                int row, col;
                bool is_valid;
                convert_mouse_to_cell(mx, my, row, col, params, matrix, is_valid);

                if (is_valid)
                {
                    cct_gotoxy(0, bottom_y + 3);
                    cout << "检测到点击: 位置=" << (char)('A' + row) << (char)('a' + col)
                         << "      ";
                }
            }
        }
        else if (ir.EventType == KEY_EVENT)
        {
            if (ir.Event.KeyEvent.bKeyDown)
            {
                int keycode1 = ir.Event.KeyEvent.uChar.AsciiChar;
                if (keycode1 == 'q' || keycode1 == 'Q')
                {
                    quit = true;
                }
            }
        }
    }
    cct_disable_mouse();
}