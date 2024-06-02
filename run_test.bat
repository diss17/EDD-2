@echo off

set quantities=1000 2500 5000 7500 10000 12500 15000 17500 20000 21070

rem Executable file name
set executable="./main_ids.exe"
set executable1="./hashing_usernames.exe"
for /L %%i in (1,1,5) do (
    echo "Running test %%i"
    for %%n in (%quantities%) do (
        %executable% %%n
        %executable1% %%n
    )
)