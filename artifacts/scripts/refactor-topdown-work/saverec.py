#!/usr/bin/env python3
"""Rewrite loose globals into members of a work record.

usage: saverec.py RECORD OLD=member[,OLD=member...] [--dry]
Replaces each whole-word OLD with RECORD.member in src/ and include/, drops its extern
declaration (and the `/* D_xxxx */` comment line above it), and adds `#include "work/save.h"`
to the image header of every changed .c (or of the .c that include a changed shared body).
"""
import re, subprocess, sys, pathlib, collections

record = sys.argv[1]
pairs = dict(p.split('=') for p in sys.argv[2].split(','))
dry = '--dry' in sys.argv
INC = '#include "work/save.h"'
files = subprocess.run(['git', 'ls-files', 'src', 'include'], capture_output=True, text=True).stdout.split()
files = [f for f in files if f.endswith(('.c', '.h')) and f != 'include/work/save.h']
word = re.compile(r'\b(%s)\b' % '|'.join(map(re.escape, pairs)))
ext = re.compile(r'^extern\b[^;]*\b(%s)\b[^;]*;[^\n]*\n' % '|'.join(map(re.escape, pairs)), re.M)
changed = []
for f in files:
    p = pathlib.Path(f)
    s = p.read_text(encoding='latin-1')
    if not word.search(s):
        continue
    t = s
    if f.endswith('.h'):
        # drop `/* D_xxxx */\n` + extern
        t = re.sub(r'(?:^/\* D_[0-9A-F]{8} \*/\n)?' + ext.pattern, '', t, flags=re.M)
    t = word.sub(lambda m: record + '.' + pairs[m.group(1)], t)
    if t != s:
        changed.append(f)
        if not dry:
            p.write_text(t, encoding='latin-1', newline='')
print(len(changed), 'files changed')
# the include phase covers every file that uses the record, so a rerun repairs a miss
changed = [f for f in files if (record + '.') in pathlib.Path(f).read_text(encoding='latin-1')]
# includes
inc_of = collections.defaultdict(set)
cfiles = [f for f in files if f.endswith('.c')]
for f in changed:
    text = pathlib.Path(f).read_text(encoding='latin-1')
    if f.endswith('.c'):
        inc_of[f].add(f)
    elif f.startswith('src/') and '#ifndef' not in text[:600]:
        base = pathlib.Path(f).name  # a shared body: its includers take the include
        for c in cfiles:
            if re.search(r'#include "(?:[^"]*/)?%s"' % re.escape(base), pathlib.Path(c).read_text(encoding='latin-1')):
                inc_of[c].add(f)
    elif f.startswith('src/'):
        inc_of[f].add(f)  # a guarded header takes the include itself
targets = set()
for c in inc_of:
    if c.endswith('.h'):
        targets.add(pathlib.Path(c)); continue
    m = re.search(r'^#include "([^"]+)"', pathlib.Path(c).read_text(encoding='latin-1'), re.M)
    if not m:
        print('NOINC', c); continue
    inc = m.group(1)
    # image header: resolve relative to the .c dir, else src root, else include/
    for base in (pathlib.Path(c).parent, pathlib.Path('src'), pathlib.Path('include')):
        h = base / inc
        if h.exists():
            targets.add(h); break
    else:
        print('UNRESOLVED', c, inc)
for h in sorted(targets):
    s = h.read_text(encoding='latin-1')
    if INC in s:
        continue
    lines = s.split('\n')
    last = max((i for i, l in enumerate(lines) if l.startswith('#include "')), default=None)
    if last is None:
        print('NO INCLUDE IN', h); continue
    lines.insert(last + 1, INC)
    if not dry:
        h.write_text('\n'.join(lines), encoding='latin-1', newline='')
    print('include ->', h)
for f in changed:
    print(f)
