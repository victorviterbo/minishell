#!/bin/bash

OS=$(uname -s)

cd `dirname "$0"`

make tests

if [ ! -e segfault_test ]; then
	cc -Wall -Wextra -Werror segfault_test.c -o segfault_test
fi

if [ ! -e miniprint ]; then
	cc -Wall -Wextra -Werror miniprint.c -o miniprint
fi

################ TEST ECHO ################

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

if [[ "$OS" = "Linux" ]]; then
        valgrind --leak-check=full ./bin/test_echo > /dev/null 2>&1
elif [[ "$OS" = "Darwin" ]]; then
        leaks --atExit -- ./bin/test_echo > /dev/null 2>&1
fi

if [ "$?" -ne 0 ]; then
        echo "Tests failed for echo : memory leaks !"
        exit 1
fi

echo -e "Tests echo \t OK!"

################ TEST CD PWD ################

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

if [[ "$OS" = "Linux" ]]; then
        valgrind --leak-check=full ./bin/test_cd_pwd > /dev/null 2>&1
elif [[ "$OS" = "Darwin" ]]; then
        leaks --atExit -- ./bin/test_cd_pwd > /dev/null 2>&1
fi

if [ "$?" -ne 0 ]; then
        echo "Tests failed for cd_pwd : memory leaks !"
        exit 1
fi

echo -e "Tests cd pwd \t OK!"
############### TEST ENV ###############

./bin/test_env > /dev/null 2>&1

if [ "$?" -ne 0 ]; then
        echo "Tests failed for env !"
        exit 1
fi

if [[ "$OS" = "Linux" ]]; then
        valgrind --leak-check=full ./bin/test_env > /dev/null 2>&1
elif [[ "$OS" == "Darwin" ]]; then
        leaks --atExit -- ./bin/test_env > /dev/null 2>&1
fi

if [ "$?" -ne 0 ]; then
        echo "Tests failed for env : memory leaks !"
        exit 1
fi

echo -e "Tests env \t OK!"

################ TEST EXECVE ################

./bin/test_execve > ./out/test_execve.out 2>&1

if [ "$?" -ne 0 ]; then
        echo "Tests failed for execve !"
        exit 1
fi

diff_cd=$(diff <(sort ./out/test_execve.out) <(sort ./out/ref_execve.out))

if [ "$?" -ne 0 ]; then
        echo "Tests failed for execve diff !"
	echo "$diff_cd"
        exit 1
fi

make test_execve

if [[ "$OS" = "Linux" ]]; then
        valgrind --leak-check=full ./bin/test_execve_leaks > /dev/null 2>&1
elif [[ "$OS" = "Darwin" ]]; then
        leaks --atExit -- ./bin/test_execve_leaks > /dev/null 2>&1
fi

if [ "$?" -ne 0 ]; then
        echo "Tests failed for execve : memory leaks !"
        exit 1
fi

echo -e "Tests execve \t OK!"

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

echo -e "Tests parsing \t OK!"

echo -e "All tests \t OK!"
