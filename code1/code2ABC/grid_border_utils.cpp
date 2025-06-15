/*
 * 网格边框生成工具库
 *
 * 本文件提取了数字游戏项目中ABC功能的边框生成策略核心部分
 * 可用于其他需要生成表格边框的项目参考
 *
 * 功能特点：
 * 1. 支持简单网格边框（A功能风格）
 * 2. 支持带提示栏的复杂边框（B/C功能风格）
 * 3. 支持每5行/列的分组分隔线
 * 4. 支持行列标题显示
 *
 * 作者：基于数字游戏项目提取
 * 日期：2024
 */

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

// 常量定义
const int MAX_SIZE = 25;            // 最大网格尺寸
const int MAX_HINT_LENGTH = 3 * 25; // 最大提示长度

/*
 * 功能：生成简单网格边框（A功能风格）
 * 参数：
 *   grid - 二维数组，存储网格数据（1表示有内容，0表示空）
 *   size - 网格大小
 * 特点：
 *   - 简洁的边框样式
 *   - 每5行/列有分隔线
 *   - 带行列标题（A-Z, a-z）
 */
void printSimpleGrid(int grid[][MAX_SIZE], int size)
{
    cout << "当前数组(" << size << "*" << size << ")：" << endl;

    // 绘制顶部边框
    cout << "  +";
    for (int j = 0; j < size; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+";
        cout << "--";
    }
    cout << "-+" << endl;

    // 显示列标题行
    cout << "  |";
    for (int j = 0; j < size; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << " |";
        cout << " " << (char)('a' + j);
    }
    cout << " |" << endl;

    // 绘制列标题下方的分隔线
    cout << "+-+";
    for (int j = 0; j < size; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+";
        cout << "--";
    }
    cout << "-+" << endl;

    // 显示矩阵内容
    for (int i = 0; i < size; i++)
    {
        // 显示行标题和内容
        cout << (char)('A' + i) << " |";

        for (int j = 0; j < size; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << " |";
            // 显示单元格内容，每个单元格占2个字符位置
            cout << " " << (grid[i][j] ? "O" : " ");
        }
        cout << " |" << endl;

        // 每5行添加分隔线
        if ((i + 1) % 5 == 0 && i < size - 1)
        {
            cout << "+-+";
            for (int j = 0; j < size; j++)
            {
                if (j > 0 && j % 5 == 0)
                    cout << "-+";
                cout << "--";
            }
            cout << "-+" << endl;
        }
    }

    // 绘制底部边框
    cout << "+-+";
    for (int j = 0; j < size; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+";
        cout << "--";
    }
    cout << "-+" << endl;
}

/*
 * 功能：将提示数组转换为字符串
 * 参数：
 *   hint - 提示数组
 *   count - 提示数量
 *   str - 输出字符串缓冲区
 */
void hintToCString(const int *hint, int count, char *str)
{
    str[0] = '\0';
    for (int i = 0; i < count; i++)
    {
        char numStr[10];
        sprintf(numStr, "%d", hint[i]);
        if (i == 0)
        {
            strcpy(str, numStr);
        }
        else
        {
            strcat(str, " ");
            strcat(str, numStr);
        }
    }
}

/*
 * 功能：生成带提示栏的复杂网格边框（B/C功能风格）
 * 参数：
 *   grid - 二维数组，存储网格数据
 *   size - 网格大小
 *   rowHints - 行提示二维数组
 *   rowHintCounts - 每行提示数量
 *   colHints - 列提示二维数组
 *   colHintCounts - 每列提示数量
 *   marked - 标记数组（可选，用于显示用户标记）
 *   showMarked - 是否显示标记
 * 特点：
 *   - 左侧有行提示栏
 *   - 顶部有列提示栏
 *   - 自动计算提示栏宽度和高度
 *   - 支持每5行/列分组
 */
void printGridWithHints(int grid[][MAX_SIZE], int size, int rowHints[][MAX_HINT_LENGTH],
                        int *rowHintCounts, int colHints[][MAX_HINT_LENGTH], int *colHintCounts,
                        int marked[][MAX_SIZE] = nullptr, bool showMarked = false)
{
    // 计算行提示栏最大宽度
    int maxRowHintWidth = 0;
    char tempStr[MAX_HINT_LENGTH] = "";
    for (int i = 0; i < size; i++)
    {
        hintToCString(rowHints[i], rowHintCounts[i], tempStr);
        int len = strlen(tempStr);
        maxRowHintWidth = max(maxRowHintWidth, len);
    }

    // 计算列提示栏最大高度
    int maxColHintHeight = 0;
    for (int j = 0; j < size; j++)
    {
        maxColHintHeight = max(maxColHintHeight, colHintCounts[j]);
    }

    // 打印顶部边框
    for (int i = 0; i < maxRowHintWidth + 2; ++i)
    {
        cout << '-';
    }
    cout << "--+"; // 数据区起始边框
    for (int j = 0; j < size; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+"; // 每5列分隔线
        cout << "--";     // 横线
    }
    cout << "-+" << endl; // 右侧结束边框

    // 打印列提示栏（下对齐）
    for (int h = 0; h < maxColHintHeight; h++)
    {
        // 行提示栏区域留白
        cout << setw(maxRowHintWidth + 5) << "  |";

        // 打印列提示（下对齐）
        for (int j = 0; j < size; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << " |"; // 每5列分隔线
            int index = colHintCounts[j] - maxColHintHeight + h;
            if (index >= 0 && index < colHintCounts[j])
            {
                cout << setw(2) << colHints[j][index];
            }
            else
            {
                cout << "  ";
            }
        }
        cout << " |" << endl;
    }

    // 打印网格顶部边框
    for (int i = 0; i < maxRowHintWidth + 2; ++i)
    {
        cout << '-';
    }
    cout << "--+";
    for (int j = 0; j < size; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+";
        cout << "--";
    }
    cout << "-+" << endl;

    // 打印列标签行
    cout << setw(maxRowHintWidth + 2) << " " << "  |";
    for (int j = 0; j < size; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << " |";
        cout << " " << static_cast<char>('a' + j);
    }
    cout << " |" << endl;

    // 打印列标签下的分隔线
    for (int i = 0; i < maxRowHintWidth + 2; ++i)
    {
        cout << '-';
    }
    cout << "+-+";
    for (int j = 0; j < size; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+";
        cout << "--";
    }
    cout << "-+" << endl;

    // 打印数据行（含行提示栏）
    for (int i = 0; i < size; i++)
    {
        // 生成行提示字符串
        char rowHintStr[MAX_HINT_LENGTH] = "";
        hintToCString(rowHints[i], rowHintCounts[i], rowHintStr);

        // 打印行提示（右对齐）
        cout << " " << setw(maxRowHintWidth) << rowHintStr << " |" << static_cast<char>('A' + i)
             << "|";

        // 打印数据
        for (int j = 0; j < size; j++)
        {
            if (j > 0 && j % 5 == 0)
                cout << " |";

            // 根据是否显示标记来决定显示内容
            if (showMarked && marked && marked[i][j])
            {
                cout << " O"; // 显示标记
            }
            else if (!showMarked && grid[i][j])
            {
                cout << " O"; // 显示原始数据
            }
            else
            {
                cout << "  "; // 空白
            }
        }
        cout << " |" << endl;

        // 打印分隔行
        if ((i + 1) % 5 == 0 && i != size - 1)
        {
            for (int i = 0; i < maxRowHintWidth + 2; ++i)
            {
                cout << '-';
            }
            cout << "+-+";
            for (int j = 0; j < size; j++)
            {
                if (j > 0 && j % 5 == 0)
                    cout << "-+";
                cout << "--";
            }
            cout << "-+" << endl;
        }
    }

    // 打印底部边框
    for (int i = 0; i < maxRowHintWidth + 2; ++i)
    {
        cout << '-';
    }
    cout << "+-+";
    for (int j = 0; j < size; j++)
    {
        if (j > 0 && j % 5 == 0)
            cout << "-+";
        cout << "--";
    }
    cout << "-+" << endl;
}

/*
 * 边框生成策略核心算法说明：
 *
 * 1. 简单边框策略（A功能）：
 *    - 使用 '+', '-', '|' 字符构建边框
 *    - 每5行/列插入分隔线实现分组
 *    - 行列标题占用固定空间
 *
 * 2. 复杂边框策略（B/C功能）：
 *    - 动态计算提示栏所需空间
 *    - 列提示采用下对齐方式显示
 *    - 行提示采用右对齐方式显示
 *    - 提示栏与数据区用分隔线区分
 *
 * 3. 分组分隔线策略：
 *    - 每5行/列插入分隔线
 *    - 分隔线与边框保持一致的字符风格
 *    - 交叉点使用 '+' 字符连接
 *
 * 4. 空间计算策略：
 *    - 行提示宽度 = max(所有行提示字符串长度)
 *    - 列提示高度 = max(所有列提示数量)
 *    - 每个数据单元格固定占用2个字符宽度
 *
 * 使用示例：
 *
 * // 简单网格
 * int grid[MAX_SIZE][MAX_SIZE] = {{0}};
 * // ... 填充数据 ...
 * printSimpleGrid(grid, 10);
 *
 * // 带提示的复杂网格
 * int rowHints[MAX_SIZE][MAX_HINT_LENGTH] = {{0}};
 * int colHints[MAX_SIZE][MAX_HINT_LENGTH] = {{0}};
 * int rowHintCounts[MAX_SIZE] = {0};
 * int colHintCounts[MAX_SIZE] = {0};
 * // ... 生成提示数据 ...
 * printGridWithHints(grid, 10, rowHints, rowHintCounts, colHints, colHintCounts);
 */

// 示例函数：演示如何使用边框生成工具
void demonstrateGridBorders()
{
    cout << "=== 网格边框生成工具演示 ===" << endl << endl;

    // 创建示例数据
    int grid[MAX_SIZE][MAX_SIZE] = {{0}};
    int size = 5;

    // 填充一些示例数据
    grid[0][0] = 1;
    grid[0][2] = 1;
    grid[1][1] = 1;
    grid[1][3] = 1;
    grid[2][0] = 1;
    grid[2][4] = 1;
    grid[3][2] = 1;
    grid[4][1] = 1;
    grid[4][3] = 1;

    cout << "1. 简单网格边框演示：" << endl;
    printSimpleGrid(grid, size);

    cout << endl << "2. 带提示栏的复杂网格边框演示：" << endl;

    // 创建示例提示数据
    int rowHints[MAX_SIZE][MAX_HINT_LENGTH] = {{0}};
    int colHints[MAX_SIZE][MAX_HINT_LENGTH] = {{0}};
    int rowHintCounts[MAX_SIZE] = {0};
    int colHintCounts[MAX_SIZE] = {0};

    // 简单的提示数据
    rowHints[0][0] = 2;
    rowHintCounts[0] = 1;
    rowHints[1][0] = 2;
    rowHintCounts[1] = 1;
    rowHints[2][0] = 2;
    rowHintCounts[2] = 1;
    rowHints[3][0] = 1;
    rowHintCounts[3] = 1;
    rowHints[4][0] = 2;
    rowHintCounts[4] = 1;

    colHints[0][0] = 2;
    colHintCounts[0] = 1;
    colHints[1][0] = 2;
    colHintCounts[1] = 1;
    colHints[2][0] = 2;
    colHintCounts[2] = 1;
    colHints[3][0] = 2;
    colHintCounts[3] = 1;
    colHints[4][0] = 1;
    colHintCounts[4] = 1;

    printGridWithHints(grid, size, rowHints, rowHintCounts, colHints, colHintCounts);

    cout << endl << "=== 演示结束 ===" << endl;
}