@echo off

if not exist "%SKSE_INC%\skse" (
    mkdir "%SKSE_INC%\skse"
)

copy *.h "%SKSE_INC%\skse"
copy *.inl "%SKSE_INC%\skse"
copy ..\skse.h "%SKSE_INC%"
