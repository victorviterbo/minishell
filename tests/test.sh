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
        echo "Tests failed for echo diff !"
		echo "$diff_echo"
        exit 1
fi

leaks --atExit -- ./bin/test_echo

if [ "$?" -ne 0 ]; then
        echo "Tests failed for echo : memory leaks !"
        exit 1
fi

./bin/test_cd_pwd > ./out/test_cd_pwd.out 2>&1

if [ "$?" -ne 0 ]; then
        echo "Tests failed for cd_pwd !"
        exit 1
fi

diff_cd=$(diff <(sort ./out/test_cd_pwd.out) <(sort ./out/ref_cd_pwd.out))

if [ "$?" -ne 0 ]; then
        echo "Tests failed for cd_pwd diff !"
		echo "$diff_cd"
        exit 1
fi

leaks --atExit -- ./bin/test_cd_pwd

if [ "$?" -ne 0 ]; then
        echo "Tests failed for cd_pwd : memory leaks !"
        exit 1
fi

./bin/test_env > ./out/test_env.out 2>&1

if [ "$?" -ne 0 ]; then
        echo "Tests failed for env !"
        exit 1
fi

diff_env=$(diff ./out/test_env.out ./out/ref_env.out)

if [ "$?" -ne 0 ]; then
        echo "Tests failed for env diff !"
		echo "$diff_cd"
        exit 1
fi

leaks --atExit -- ./bin/test_env

if [ "$?" -ne 0 ]; then
        echo "Tests failed for env : memory leaks !"
        exit 1
fi