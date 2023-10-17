@echo off
rem objファイルをfieldファイルへ変換
rem -f 対象ファイル -l メッシュ分割距離　-m メッシュ分割数　-c 衝突判定用メッシュ分割
@echo on

ConvertField.exe -f Desert.obj -m 20 -c 10

pause