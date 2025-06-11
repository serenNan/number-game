@echo off
echo 正在编译...
g++ -o 90-b2.exe -std=c++11 -D_HAS_STD_BYTE=0 -DNOMINMAX -DWIN32_LEAN_AND_MEAN -fexec-charset=GBK -finput-charset=GBK -Wno-narrowing -Wno-write-strings pullze_main.cpp pullze_base.cpp pullze_console.cpp pullze_tools.cpp cmd_console_tools.cpp 
if %ERRORLEVEL% EQU 0 (
    echo 编译成功！
    echo 正在运行程序...
    90-b2.exe
) else (
    echo 编译失败！
)
pause 