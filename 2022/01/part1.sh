#!/bin/bash
awk '/[0-9]+/ { s += $1; next }; { if (s > max) max = s; s = 0 }; END { print max }' < input.txt
