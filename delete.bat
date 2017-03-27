@echo off

echo                       		     WARNING : you will delete the files below! 

for /r %%i in (*.exe, *.in, *.out, *.ans) do (
	echo %%i
)

set /p read=Do you really want to delete the files above ? (Y / n)  

if /i %read% EQU Y (
	for /r %%i in (*.exe, *.in, *.out, *.ans) do (
		del "%%i"
		echo %%i deleted
	)
	echo done
) else (
	echo Canceled
)

timeout /t 1 > nul
