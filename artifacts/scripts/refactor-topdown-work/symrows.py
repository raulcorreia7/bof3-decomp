#!/usr/bin/env python3
"""usage: symrows.py MAPFILE RECORD ROWLINE_FILE: delete symbols.toml rows of mapped names, insert the record row before the first row above its address, rewrite names in source text."""
import re, sys
mapping = dict(p.split('=') for p in open(sys.argv[1]).read().strip().split(','))
record = sys.argv[2]
newrow = open(sys.argv[3]).read().rstrip('\n')
addr = int(re.search(r'addr = (0x[0-9A-Fa-f]+)', newrow).group(1), 16)
lines = open('config/symbols.toml', encoding='latin-1').read().split('\n')
out = []
inserted = False
table = None
word = re.compile(r'\b(%s)\b' % '|'.join(map(re.escape, mapping)))
for l in lines:
    if l.startswith('['):
        table = l
    m = re.match(r'(\w+) = \{ addr = (0x[0-9A-Fa-f]+)', l)
    if m and table == '["exe/slus_004_22"]':
        if m.group(1) in mapping:
            continue
        if not inserted and int(m.group(2), 16) > addr:
            out.append(newrow); inserted = True
    if m:
        l = word.sub(lambda k: record + '.' + mapping[k.group(1)], l)
    out.append(l)
open('config/symbols.toml', 'w', encoding='latin-1', newline='').write('\n'.join(out))
print('inserted', inserted)
