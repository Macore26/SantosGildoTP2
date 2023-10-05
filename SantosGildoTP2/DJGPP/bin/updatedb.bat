@echo off
rem -----------------------------------------------------------------
rem
rem             UpdateDB.Bat
rem
rem Beside GNU Findutils, you will need ports of these utilities:
rem
rem    sort
rem    tr
rem    uniq
rem    gawk
rem
rem Only `sort' is required for the new-style data-base format; the
rem rest are used when creating old-style data-bases.
rem
rem ------------------------------------------------------------------
rem
rem This is a pale imitation of the original `updatedb.sh' (which see).
rem
rem          Written by Eli Zaretskii "<eliz@is.elta.co.il>"
rem
rem ------------------------------------------------------------------
rem
set old_format=
set locate_args=
:again
If "%1" == "?" Goto help
If "%1" == "/?" Goto help
If "%1" == "-h" Goto help
If "%1" == "--help" Goto help
If "%1" == "--version" Goto version
If "%1" == "--old-format" Goto old
Goto doit
:help
echo.
echo Usage: updatedb [--old-format] [dir1 dir2...]
echo   or   updatedb [--version] [--help]
echo.
echo  Warning: Keep the list of directories short, lest it makes
echo           some command-lines longer than 126 characters!
echo.
Goto end
:version
echo GNU updatedb version 4.1 (for MS-DOS)
Goto end
:old
set old_format=OLD
shift
Goto again
:doit
set locate_args=%1 %2 %3 %4 %5 %6 %7 %8 %9
If "%1" == "" Set locate_args=/
If "%old_format%" == "" Goto New
rem
rem  ---- Old format ---
rem
set tmp_prefix=
If "%TMPDIR%" == "" Goto try_temp
set tmp_prefix=%TMPDIR%
Goto action
:try_temp
If "%TEMP%" == "" Goto try_tmp
set tmp_prefix=%TEMP%
Goto action
:try_tmp
If "%TMP%" == "" Goto action
set tmp_prefix=%TMP%
:action
If "%tmp_prefix%" == "" set tmp_prefix=.
set bigrams_file=%tmp_prefix%\bigrams.tmp
set filelist=%tmp_prefix%\filelist
find %locate_args% ( -type d -iregex '^[a-zA-Z]:/te?mp$' ) -prune -o -print > %filelist%.1
tr / "\001" < %filelist%.1 | sort -f | tr "\001" / > %filelist%.2
bigram < %filelist%.2 | sort | uniq -c | sort -nr > %filelist%.3
gawk "{ if (NR <= 128) print $2 }" < %filelist%.3 | tr -d "\012" > %bigrams_file%
code %bigrams_file% < %filelist%.2 > locatedb.dat
If exist %bigrams_file% Del %bigrams_file%
If exist %filelist%.* Del %filelist%.*
set bigrams_file=
set filelist=
set tmp_prefix=
Goto end
:New
rem
rem  ---- New format ---
rem
find %locate_args% ( -type d -iregex '^[a-zA-Z]:/te?mp$' ) -prune -o -print | sort -f | frcode > locatedb.n
find locatedb.n -empty
If errorlevel 1 goto end
If exist locatedb.dat Del locatedb.dat
Ren locatedb.n locatedb.dat
:end
set old_format=
set locate_args=
