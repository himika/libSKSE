@echo off

if not exist "%SKSE_INC%\skse\common" (
    mkdir "%SKSE_INC%\skse\common"
)

copy *.h "%SKSE_INC%\skse\common"

