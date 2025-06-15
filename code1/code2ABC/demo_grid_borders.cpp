/*
 * 网格边框生成工具演示程序
 *
 * 本程序演示如何使用grid_border_utils工具库
 * 生成不同风格的网格边框
 */

#include "grid_border_utils.h"
#include <iostream>
using namespace std;

int main()
{
    cout << "=== 网格边框生成工具演示程序 ===" << endl << endl;

    // 运行内置演示
    demonstrateGridBorders();

    cout << endl << "=== 自定义演示 ===" << endl << endl;

    // 创建一个10x10的网格进行演示
    int grid[25][25] = {{0}};
    int size = 10;

    // 创建一个棋盘模式
    cout << "3. 棋盘模式演示（10x10）：" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((i + j) % 2 == 0)
            {
                grid[i][j] = 1;
            }
        }
    }

    printSimpleGrid(grid, size);

    cout << endl << "4. 对角线模式演示：" << endl;

    // 清空网格
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            grid[i][j] = 0;
        }
    }

    // 创建对角线模式
    for (int i = 0; i < size; i++)
    {
        grid[i][i] = 1;            // 主对角线
        grid[i][size - 1 - i] = 1; // 副对角线
    }

    // 创建对应的提示数据
    int rowHints[25][75] = {{0}};
    int colHints[25][75] = {{0}};
    int rowHintCounts[25] = {0};
    int colHintCounts[25] = {0};

    // 为对角线模式生成提示
    for (int i = 0; i < size; i++)
    {
        int count = 0;
        for (int j = 0; j < size; j++)
        {
            if (grid[i][j] == 1)
            {
                if (count == 0 || grid[i][j - 1] == 0)
                {
                    // 新的连续段开始
                    if (rowHintCounts[i] < 75)
                    {
                        rowHints[i][rowHintCounts[i]] = 1;
                        rowHintCounts[i]++;
                    }
                }
                else
                {
                    // 继续当前连续段
                    if (rowHintCounts[i] > 0)
                    {
                        rowHints[i][rowHintCounts[i] - 1]++;
                    }
                }
                count++;
            }
        }
        if (rowHintCounts[i] == 0)
        {
            rowHints[i][0] = 0;
            rowHintCounts[i] = 1;
        }
    }

    // 生成列提示
    for (int j = 0; j < size; j++)
    {
        int count = 0;
        for (int i = 0; i < size; i++)
        {
            if (grid[i][j] == 1)
            {
                if (count == 0 || grid[i - 1][j] == 0)
                {
                    // 新的连续段开始
                    if (colHintCounts[j] < 75)
                    {
                        colHints[j][colHintCounts[j]] = 1;
                        colHintCounts[j]++;
                    }
                }
                else
                {
                    // 继续当前连续段
                    if (colHintCounts[j] > 0)
                    {
                        colHints[j][colHintCounts[j] - 1]++;
                    }
                }
                count++;
            }
        }
        if (colHintCounts[j] == 0)
        {
            colHints[j][0] = 0;
            colHintCounts[j] = 1;
        }
    }

    printGridWithHints(grid, size, rowHints, rowHintCounts, colHints, colHintCounts);

    cout << endl << "=== 演示程序结束 ===" << endl;
    cout << "提示：您可以将这些函数集成到自己的项目中使用！" << endl;

    return 0;
}