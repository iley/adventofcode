#!/bin/bash
day="$1"
if [ -z "$day" ]; then
  echo "Usage: $0 XX" >&2
  exit 1
fi

cp -r bin/d00 bin/d$day
cd bin/d$day
mv d00.ml d$day.ml
gsed -i "s/d00/d$day/g" d$day.ml dune
dune build
