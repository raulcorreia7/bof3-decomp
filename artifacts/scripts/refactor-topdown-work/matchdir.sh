#!/bin/sh
# usage: matchdir.sh IMAGE DIR  - match.sh every changed .c under DIR; print the ones that differ or fail to compile
img=$1; dir=$2
for f in $(git diff --name-only HEAD -- "$dir" | grep '\.c$'); do
  n=$(basename "$f" .c)
  grep -q "NON_MATCHING $(echo)" "$f" 2>/dev/null
  r=$(tools/match.sh "$img" "$n" 2>&1 | head -3)
  case "$r" in match:*|*"not covered"*) ;; *) echo "== $n"; echo "$r";; esac
done
