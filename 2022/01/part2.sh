#!/bin/bash
awk '/[0-9]+/ { s += $1; next }; { print s; s = 0 }' < input.txt | sort -nr | head -3 | awk '{ s += $1 }; END { print s }'
