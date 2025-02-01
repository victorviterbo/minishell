#!/bin/bash

cd `dirname "$0"`

make tests

############### TEST ECHO ###############

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

leaks --atExit -- ./bin/test_echo &> /dev/null

if [ "$?" -ne 0 ]; then
        echo "Tests failed for echo : memory leaks !"
        exit 1
fi

############### TEST CD PWD ###############

./bin/test_cd_pwd &> ./out/test_cd_pwd.out

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

leaks --atExit -- ./bin/test_cd_pwd &> /dev/null 

if [ "$?" -ne 0 ]; then
        echo "Tests failed for cd_pwd : memory leaks !"
        exit 1
fi

############### TEST ENV ###############

./bin/test_env > /dev/null 2>&1

if [ "$?" -ne 0 ]; then
        echo "Tests failed for env !"
        exit 1
fi

leaks --atExit -- ./bin/test_env > /dev/null 2>&1

if [ "$?" -ne 0 ]; then
        echo "Tests failed for env : memory leaks !"
        exit 1
fi

############### TEST PARSING ###############

./bin/test_parsing &> ./out/test_parsing.out

if [ "$?" -ne 0 ]; then
        echo "Tests failed for parsing !"
        exit 1
fi

diff_parsing=$(diff ./out/test_parsing.out ./out/ref_parsing.out)

if [ "$?" -ne 0 ]; then
        echo "Tests failed for parsing diff !"
		echo "$diff_parsing"
        exit 1
fi

leaks --atExit -- ./bin/test_parsing &> /dev/null 

if [ "$?" -ne 0 ]; then
        echo "Tests failed for parsing : memory leaks !"
        exit 1
fi

echo "All tests ok !"