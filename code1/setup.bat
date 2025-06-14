@echo off
echo ===================================================
echo 数字游戏安装和运行脚本
echo ===================================================
echo.

REM 检查是否已安装MinGW
where g++ >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo 未检测到G++编译器，将为您安装MinGW...
    echo.
    echo 请选择安装方式:
    echo 1. 自动下载并安装MinGW (需要网络连接)
    echo 2. 手动安装 (将提供安装指南)
    echo 3. 跳过安装 (如果您确定已经安装但未添加到PATH)
    echo.
    set /p choice="请输入选择 (1/2/3): "
    
    if "%choice%"=="1" (
        echo 正在下载MinGW安装程序...
        powershell -Command "Invoke-WebRequest -Uri 'https://sourceforge.net/projects/mingw-w64/files/Toolchains%%20targetting%%20Win32/Personal%%20Builds/mingw-builds/installer/mingw-w64-install.exe/download' -OutFile 'mingw-installer.exe'"
        
        if exist mingw-installer.exe (
            echo 下载完成，正在启动安装程序...
            echo 请在安装程序中选择:
            echo - Architecture: x86_64
            echo - Threads: win32
            echo - Exception: seh
            echo 安装完成后，请确保将MinGW的bin目录添加到系统PATH中
            echo 例如: C:\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\mingw64\bin
            start mingw-installer.exe
            echo 请在安装完成后重新运行此脚本
            pause
            exit
        ) else (
            echo 下载失败，请选择手动安装方式
            set choice=2
        )
    )
    
    if "%choice%"=="2" (
        echo.
        echo 请按照以下步骤手动安装MinGW:
        echo 1. 访问 https://sourceforge.net/projects/mingw-w64/files/
        echo 2. 下载并安装最新版本的MinGW-W64
        echo 3. 安装时选择:
        echo    - Architecture: x86_64
        echo    - Threads: win32
        echo    - Exception: seh
        echo 4. 将MinGW的bin目录添加到系统PATH中
        echo    例如: C:\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\mingw64\bin
        echo.
        echo 安装完成后，请重新运行此脚本
        pause
        exit
    )
    
    if "%choice%"=="3" (
        echo 跳过安装，继续执行...
    ) else (
        echo 无效选择，退出安装
        pause
        exit
    )
) else (
    echo 已检测到G++编译器，继续执行...
)

echo.
echo 检查必要文件...

set missing_files=0
if not exist cmd_console_tools.cpp (
    echo 缺少文件: cmd_console_tools.cpp
    set /a missing_files+=1
)
if not exist cmd_console_tools.h (
    echo 缺少文件: cmd_console_tools.h
    set /a missing_files+=1
)
if not exist pullze.h (
    echo 缺少文件: pullze.h
    set /a missing_files+=1
)
if not exist pullze_base.cpp (
    echo 缺少文件: pullze_base.cpp
    set /a missing_files+=1
)
if not exist pullze_console.cpp (
    echo 缺少文件: pullze_console.cpp
    set /a missing_files+=1
)
if not exist pullze_main.cpp (
    echo 缺少文件: pullze_main.cpp
    set /a missing_files+=1
)
if not exist pullze_tools.cpp (
    echo 缺少文件: pullze_tools.cpp
    set /a missing_files+=1
)

if %missing_files% NEQ 0 (
    echo.
    echo 警告: 缺少%missing_files%个必要文件，程序可能无法正常运行
    echo 请确保所有源文件都在当前目录中
    echo.
)

echo.
echo 选择操作:
echo 1. 编译并运行程序
echo 2. 直接运行现有的exe程序
echo.
set /p run_choice="请输入选择 (1/2): "

if "%run_choice%"=="1" (
    echo.
    echo 正在编译...
    g++ -o 90-b2.exe -std=c++11 -D_HAS_STD_BYTE=0 -DNOMINMAX -DWIN32_LEAN_AND_MEAN -fexec-charset=GBK -finput-charset=GBK -Wno-narrowing -Wno-write-strings pullze_main.cpp pullze_base.cpp pullze_console.cpp pullze_tools.cpp cmd_console_tools.cpp 
    
    if %ERRORLEVEL% EQU 0 (
        echo 编译成功！
        echo.
        echo 正在运行程序...
        90-b2.exe
    ) else (
        echo 编译失败！请检查错误信息
    )
) else if "%run_choice%"=="2" (
    if exist 90-b2.exe (
        echo 正在运行程序...
        90-b2.exe
    ) else (
        echo 错误: 未找到90-b2.exe文件
        echo 请先编译程序或确保可执行文件在当前目录中
    )
) else (
    echo 无效选择
)

echo.
pause 