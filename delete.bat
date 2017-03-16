@echo off
echo WARNING : this batch will delete all the *.exe *.in *.out recursively
set /p read=Press Y to continue:
if /i %read% EQU Y (
	for /r %%i in (*.exe, *.in, *.out) do (
		echo %%i
	)
) else (
	echo Canceled 
)
set /p A=Press Y to delete:
if /i %A% EQU Y (
	for /r %%i in (*.exe, *.in, *.out) do (
		del "%%i"
		echo %%i deleted
	)
	echo Done
) else (
	echo Canceled
)
pause