@echo off

set quantities=1000 5000 10000 15000 20000 21070

rem Executable file name
set executable="./main_ids.exe"
set executable1="./hashing_usernames.exe"
for %%n in (%quantities%) do (
    %executable% %%n
    %executable1% %%n
)
