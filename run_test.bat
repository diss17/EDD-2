@echo off

set quantities=1000 5000 10000 15000 20000 21070

rem Executable file name
set executable="./main_ids"
set executable2="./main_usernames"

for %%n in (%quantities%) do (
    %executable% %%n
    %executable2% %%n
)
