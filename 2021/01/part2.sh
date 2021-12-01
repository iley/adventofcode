#!/bin/sh
# Usage: part2.sh input.txt
awk -f window.awk $1 | awk -f part1.awk
