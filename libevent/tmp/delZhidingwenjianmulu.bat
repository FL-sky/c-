rem 1 删除文件夹
rem FOR /F "tokens=*" %%G IN ('DIR /B /AD /S *.svn') DO RMDIR /S /Q "%%G"
FOR /F "tokens=*" %%G IN ('DIR /B /AD /S include') DO RMDIR /S /Q "%%G"

rem 2. 删除文件

rem FOR /F "tokens=*" %%G IN ('DIR /B /A-D /S *.DS_Store') DO DEL /S /Q "%%G"
