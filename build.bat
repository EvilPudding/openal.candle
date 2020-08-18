@ECHO OFF
SETLOCAL

CD /D %~dp0

set sources= listener.c openal.c sound.c speaker.c
set subdirs=components

set DIR=build
set CFLAGS=/O2 /W1 /D_CRT_SECURE_NO_WARNINGS /Iopenal-soft\include
mkdir %DIR%
mkdir %DIR%\alsoft

CALL ..\candle\vcenv.bat

cmake -B %DIR%\alsoft openal-soft
cmake --build %DIR%\alsoft

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

echo openal.candle\%DIR%\export.lib openal.candle\%DIR%\alsoft\Debug\OpenAL32.lib openal.candle\%DIR%\alsoft\Debug\common.lib openal.candle\%DIR%\alsoft\Debug\ex-common.lib > %DIR%\libs

lib !objects! /out:"%DIR%\export.lib"

:END
