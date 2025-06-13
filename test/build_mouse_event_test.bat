@echo off
REM 编译 mouse_event_test.cpp 为 mouse_event_test.exe

g++ mouse_event_test.cpp -o mouse_event_test.exe

if %errorlevel%==0 (
    echo 编译成功！
) else (
    echo 编译失败，请检查环境和代码。
)
pause 