@echo off
echo ===================================================
echo 数字游戏打包脚本
echo ===================================================
echo.

REM 创建打包目录
set package_dir=number-game-package
if exist %package_dir% (
    echo 正在清理旧的打包目录...
    rd /s /q %package_dir%
)
mkdir %package_dir%

echo 正在复制必要文件...

REM 复制源代码文件
copy pullze_main.cpp %package_dir%\ >nul
copy pullze_base.cpp %package_dir%\ >nul
copy pullze_console.cpp %package_dir%\ >nul
copy pullze_tools.cpp %package_dir%\ >nul
copy pullze.h %package_dir%\ >nul
copy cmd_console_tools.cpp %package_dir%\ >nul
copy cmd_console_tools.h %package_dir%\ >nul

REM 复制脚本文件
copy setup.bat %package_dir%\ >nul
copy build.bat %package_dir%\ >nul
copy README.md %package_dir%\ >nul

REM 询问是否包含编译好的exe
set /p include_exe="是否包含编译好的exe文件? (Y/N): "
if /i "%include_exe%"=="Y" (
    if exist 90-b2.exe (
        copy 90-b2.exe %package_dir%\ >nul
        echo 已包含exe文件
    ) else (
        echo 警告: 未找到90-b2.exe文件，无法包含
    )
)

REM 创建压缩包
echo 正在创建压缩包...
set zip_file=number-game.zip

REM 尝试使用PowerShell压缩
powershell -Command "Compress-Archive -Path '%package_dir%\*' -DestinationPath '%zip_file%' -Force" 2>nul
if %ERRORLEVEL% EQU 0 (
    echo 已成功创建压缩包: %zip_file%
) else (
    echo PowerShell压缩失败，尝试其他方法...
    
    REM 检查是否有7-Zip
    where 7z >nul 2>nul
    if %ERRORLEVEL% EQU 0 (
        7z a -tzip %zip_file% %package_dir%\* >nul
        echo 已使用7-Zip创建压缩包: %zip_file%
    ) else (
        echo 未找到压缩工具，将只创建文件夹: %package_dir%
        echo 请手动压缩该文件夹
    )
)

echo.
echo 打包完成！
echo 您可以将"%zip_file%"文件（或%package_dir%文件夹）复制到新电脑上
echo 在新电脑上解压后，运行setup.bat即可安装和运行程序
echo.

pause 