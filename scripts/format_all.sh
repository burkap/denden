#!/bin/bash
clang-format --style='{BasedOnStyle: Google, IndentWidth: 4}' -i src/*.cpp &&
clang-format --style='{BasedOnStyle: Google, IndentWidth: 4}' -i inc/*.h