@echo off
echo WARNING : this batch could delete all the *.exe *.in *.out recursively
set /p read=Press Y to continue:
set A=
if /i %read% EQU Y (
	for /r %%i in (*.exe, *.in, *.out) do (
		echo %%i
	)
	set /p A=Press Y to delete:
) else (
	echo Canceled 
)
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