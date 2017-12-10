rem
rem    Copyright 2017 (C) Alexey Dynda
rem
rem    This file is part of Tiny Protocol Library.
rem
rem    Protocol Library is free software: you can redistribute it and/or modify
rem    it under the terms of the GNU Lesser General Public License as published by
rem    the Free Software Foundation, either version 3 of the License, or
rem    (at your option) any later version.
rem
rem    Protocol Library is distributed in the hope that it will be useful,
rem    but WITHOUT ANY WARRANTY; without even the implied warranty of
rem    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
rem    GNU Lesser General Public License for more details.
rem
rem    You should have received a copy of the GNU Lesser General Public License
rem    along with Protocol Library.  If not, see <http://www.gnu.org/licenses/>.

set PATH=%PATH%;C:\MinGW\bin

"C:/MinGW/bin/gcc.exe" -shared -fpic -o plc.dll -I ../../plc_main ^
       ../../plc_main/plc_basic.cpp ../../plc_main/plc_compiler.cpp

"C:/MinGW/bin/g++.exe" -o plc.exe -I ../../plc_main -L . -lplc plc.cpp
