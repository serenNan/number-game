@echo off
echo 正在使用静态链接编译程序...

g++ -o 90-b2.exe -std=c++11 -D_HAS_STD_BYTE=0 -DNOMINMAX -DWIN32_LEAN_AND_MEAN -fexec-charset=GBK -finput-charset=GBK -Wno-narrowing -Wno-write-strings -static-libgcc -static-libstdc++ pullze_main.cpp pullze_base.cpp pullze_console.cpp pullze_tools.cpp cmd_console_tools.cpp

if %ERRORLEVEL% EQU 0 (
    echo 编译成功！
    echo 生成的可执行文件应该可以在大多数Windows系统上运行。
) else (
    echo 编译失败！
)
pause 