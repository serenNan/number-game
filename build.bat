@echo off
chcp 936 > nul
echo 正在编译...
g++ -o number-game.exe puzzle_main.cpp puzzle_base.cpp puzzle_console.cpp puzzle_tools.cpp cmd_console_tools.cpp -fexec-charset=GBK -finput-charset=GBK -lwinmm
if %ERRORLEVEL% EQU 0 (
    echo 编译成功！
    echo 正在运行程序...
    number-game.exe
) else (
    echo 编译失败！
)
pause 