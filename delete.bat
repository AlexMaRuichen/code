@echo off
for /r %%i in (*.exe) do (
	del %%i
)
for /r %%i in (*.in) do (
	del %%i
)
for /r %%i in (*.out) do (
	del %%i
)
pause