/*
 * 网格边框生成工具库 - 头文件
 *
 * 本头文件声明了网格边框生成的核心函数接口
 * 可用于其他需要生成表格边框的项目
 *
 * 作者：基于数字游戏项目提取
 * 日期：2024
 */

#ifndef GRID_BORDER_UTILS_H
#define GRID_BORDER_UTILS_H

// 常量定义
extern const int MAX_SIZE;        // 最大网格尺寸
extern const int MAX_HINT_LENGTH; // 最大提示长度

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
void printSimpleGrid(int grid[][25], int size);

/*
 * 功能：将提示数组转换为字符串
 * 参数：
 *   hint - 提示数组
 *   count - 提示数量
 *   str - 输出字符串缓冲区
 */
void hintToCString(const int *hint, int count, char *str);

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
void printGridWithHints(int grid[][25], int size, int rowHints[][75], int *rowHintCounts,
                        int colHints[][75], int *colHintCounts, int marked[][25] = nullptr,
                        bool showMarked = false);

/*
 * 示例函数：演示如何使用边框生成工具
 */
void demonstrateGridBorders();

#endif // GRID_BORDER_UTILS_H