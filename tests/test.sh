#!/bin/bash

cd `dirname "$0"`

./bin/test_echo

./bin/test_cd

./bin/test_export "VAR1=test1" "VAR2=test=2" "VAR1=" "=test1" "VAR2+=lala" "VAR2=lili"
./bin/test_export "VAR1=test1" "VAR2=test=2" "VAR1=" "=test1" "VAR2+=lala" "VAR2=lili"

cd tests/

diff test.out test.ref
