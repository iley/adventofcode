#!/bin/bash
watch -n1 -d "awk -v INPUT=\$(head -1 input.txt) -f exec.awk program.txt | column"
