@echo off
echo 正在设置控制台属性...

:: 创建临时注册表文件
echo Windows Registry Editor Version 5.00 > temp.reg
echo. >> temp.reg
echo [HKEY_CURRENT_USER\Console] >> temp.reg
echo "QuickEdit"=dword:00000000 >> temp.reg
echo "InsertMode"=dword:00000000 >> temp.reg
echo "FontSize"=dword:00100010 >> temp.reg
echo "FontFamily"=dword:00000036 >> temp.reg
echo "FontWeight"=dword:00000190 >> temp.reg
echo "FaceName"="新宋体" >> temp.reg

:: 导入注册表设置
regedit /s temp.reg

:: 删除临时文件
del temp.reg

echo 控制台属性设置完成！
echo 请注意：这些设置将应用于所有新打开的命令提示符窗口。
echo 按任意键继续...
pause > nul 