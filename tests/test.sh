#!/bin/bash

cd `dirname "$0"`

make tests

./bin/test_echo > ./out/test_echo.out 2>&1

if [ "$?" -ne 0 ]; then
        echo "Tests failed for echo !"
        exit 1
fi

diff_echo=$(diff ./out/test_echo.out ./out/ref_echo.out)

if [ "$?" -ne 0 ]; then
        echo "Tests failed for echo !"
		echo "$diff_echo"
        exit 1
fi

./bin/test_cd_pwd > ./out/test_cd_pwd.out 2>&1

if [ "$?" -ne 0 ]; then
        echo "Tests failed for cd !"
        exit 1
fi

diff_cd=$(diff <(sort ./out/test_cd_pwd.out) <(sort ./out/ref_cd_pwd.out))

if [ "$?" -ne 0 ]; then
        echo "Tests failed for cd pwd !"
		echo "$diff_cd"
        exit 1
fi

./bin/test_env > ./out/test_export.out 2>&1

if [ "$?" -ne 0 ]; then
        echo "Tests failed for export !"
        exit 1
fi
