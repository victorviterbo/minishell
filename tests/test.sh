#!/bin/bash

cd `dirname "$0"`

./bin/test_echo > ./out/test_echo.out

./bin/test_cd > ./out/test_cd.out

./bin/test_export > ./out/test_export.out

