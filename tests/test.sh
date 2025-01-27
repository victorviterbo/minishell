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

./bin/test_cd > ./out/test_cd.out 2>&1

if [ "$?" -ne 0 ]; then
        echo "Tests failed for cd !"
        exit 1
fi

diff_cd=$(diff <(sort ./out/test_cd.out) <(sort ./out/ref_cd.out))

if [ "$?" -ne 0 ]; then
        echo "Tests failed for cd !"
		echo "$diff_cd"
        exit 1
fi

./bin/test_export > ./out/test_export.out 2>&1

if [ "$?" -ne 0 ]; then
        echo "Tests failed for export !"
        exit 1
fi
