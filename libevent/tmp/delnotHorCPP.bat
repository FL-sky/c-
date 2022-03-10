@echo off
::删除本文件夹中扩展名非ext的文件,要删除含子目录的，改下面的dir /b/a-d为dir /b/s/a-d
::set "ext=txt doc docx xls xlsx pdf jpg bmp"
set "ext=h cpp"
for /f "delims=" %%a in ('dir /b/s/a-d *.*') do (
set .=
if /i not "%%~nxa"=="%~nx0" (
for %%i in (%ext%) do if /i "%%~xa"==".%%i" set .=.
) else set .=.
if not defined . del /a/q/f "%%a"
)