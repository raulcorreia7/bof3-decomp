#!/bin/sh
# usage: loop.sh old=new ... ; rebuild, fix flagged lines, repeat until no member errors
for n in 1 2 3 4 5 6; do
  ninja -C build/meson -j 8 -k 0 check >| /tmp/rec2-loop.log 2>&1
  c=$(grep -c "no member named" /tmp/rec2-loop.log)
  echo "pass $n: $c"
  [ "$c" = 0 ] && break
  python3 artifacts/scripts/refactor-topdown-records-2/fixmember.py /tmp/rec2-loop.log "$@"
done
tail -2 /tmp/rec2-loop.log
