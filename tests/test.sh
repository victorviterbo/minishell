#!/bin/bash

cd `dirname "$0"`
cd ../
make

./minishell "VAR1=test1" "VAR2=test=2" "VAR1=" "=test1"
# > tests/test.out

cd tests/

diff test.out test.ref
