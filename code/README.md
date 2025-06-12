# 数字游戏程序

这是一个基于控制台的数字游戏程序，使用C++编写。

## 程序文件说明

- `pullze_main.cpp` - 主程序入口
- `pullze_base.cpp` - 游戏基础逻辑
- `pullze_console.cpp` - 控制台显示相关功能
- `pullze_tools.cpp` - 工具函数
- `pullze.h` - 头文件，包含游戏相关常量和函数声明
- `cmd_console_tools.cpp` - 控制台工具函数实现
- `cmd_console_tools.h` - 控制台工具函数声明
- `90-b2.exe` - 编译后的可执行文件
- `build.bat` - 编译脚本
- `setup.bat` - 安装和运行脚本

## 在新电脑上运行程序

### 方法1：使用安装脚本（推荐）

1. 将所有程序文件复制到新电脑的任意文件夹中
2. 运行 `setup.bat` 脚本
3. 按照脚本提示进行操作：
   - 如果未安装MinGW(G++)，脚本会提供安装选项
   - 脚本会检查必要文件是否存在
   - 您可以选择编译并运行程序，或直接运行已有的exe文件

### 方法2：手动安装

1. 安装MinGW-W64：
   - 访问 https://sourceforge.net/projects/mingw-w64/files/
   - 下载并安装最新版本
   - 安装时选择：
     * Architecture: x86_64
     * Threads: win32
     * Exception: seh
   - 将MinGW的bin目录添加到系统PATH中
     * 例如：C:\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\mingw64\bin

2. 编译程序：
   - 打开命令提示符，进入程序文件所在目录
   - 运行以下命令：
     ```
     g++ -o 90-b2.exe -std=c++11 -D_HAS_STD_BYTE=0 -DNOMINMAX -DWIN32_LEAN_AND_MEAN -fexec-charset=GBK -finput-charset=GBK -Wno-narrowing -Wno-write-strings pullze_main.cpp pullze_base.cpp pullze_console.cpp pullze_tools.cpp cmd_console_tools.cpp
     ```

3. 运行程序：
   - 直接双击 `90-b2.exe` 或在命令提示符中运行 `90-b2.exe`

## 注意事项

- 程序需要在Windows环境下运行
- 请确保所有源文件都在同一目录中
- 如果遇到中文显示问题，请确认编译时使用了GBK编码
- `cmd_console_tools.cpp` 和 `cmd_console_tools.h` 文件不可修改 