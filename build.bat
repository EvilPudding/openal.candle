@ECHO OFF
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

CD /D %~dp0

set sources=listener.c openal.c sound.c speaker.c alw.c
set subdirs=components

set DIR=build
set CFLAGS=/O2 /W1 /D_CRT_SECURE_NO_WARNINGS /Iopenal-soft\include
mkdir %DIR%
mkdir %DIR%\alsoft

CALL ..\candle\vcenv.bat

cmake -B %DIR%\alsoft openal-soft
cmake --build %DIR%\alsoft --config Release

set objects=
FOR %%f IN (%sources%) DO @IF EXIST "%%f" (
	set src=%DIR%\%%f
	CALL set object=%%src:.c=.obj%%
	..\candle\build\datescomp.exe %%f !object! || (
		cl /c "%%f" /Fo"!object!" %CFLAGS% || (
			echo Error compiling %%f
			GOTO END
		)
	)
	CALL set objects=!objects! !object!
)

echo openal.candle\%DIR%\export.lib > %DIR%\libs
echo speaker.png build\alsoft\Release\OpenAL32.dll > %DIR%\res

lib !objects! /out:"%DIR%\export.lib"

:END
