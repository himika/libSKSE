@echo off

rem 自動でインストールしたくない場合は、下行のコロン(:)を外す。
:goto END

rem ===========================================

rem .libファイルのインストール先パスを指定
set SKSE_LIB=%USERPROFILE%\lib\libSKSE

rem .hファイルのインストール先パスを指定
set SKSE_INC=%USERPROFILE%\include\libSKSE

rem ===========================================

if not exist "%SKSE_LIB%" (
    mkdir "%SKSE_LIB%"
)

copy %2 "%SKSE_LIB%"

cd %1
call install.bat

:END
