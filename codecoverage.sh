#!/bin/bash

lcov -v -t "tst_viwebapi" --ignore mismatch --include "core*" --include "tests*" -o tst_viwebapi.info -c -d . && \
genhtml -o report tst_viwebapi.info
