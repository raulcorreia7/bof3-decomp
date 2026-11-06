#!/usr/bin/env python3
"""Insert a path before member names clang reports missing. usage: fixmember.py PREFIX TYPES(comma) MEMBERS(comma)"""
import json, re, shlex, subprocess, sys, collections
from concurrent.futures import ThreadPoolExecutor
prefix, types, members = sys.argv[1], sys.argv[2].split(','), sys.argv[3].split(',')
c = json.load(open('build/meson/compile_commands.json'))
seen = {}
for x in c:
    if x['file'].endswith('.c'): x['file']=__import__('os').path.relpath(__import__('os').path.join(x['directory'],x['file'])); seen.setdefault(x['file'], x)
pat = re.compile(r"^(\S+?):(\d+):(\d+): error: no member named '(%s)' in '(?:struct )?(%s)'" % ('|'.join(members), '|'.join(types)))
def run(x):
    a = shlex.split(x['command']); keep = []
    i = 0
    while i < len(a):
        t = a[i]
        if t.startswith('-D') or t.startswith('-I'): keep.append(t)
        i += 1
    cmd = ['clang', '--target=mipsel-unknown-none-elf', '-fsyntax-only', '-w', '-ferror-limit=0', '-fno-color-diagnostics', '-D_ASM_H', '-Wno-error', '-Wno-incompatible-pointer-types', '-Wno-int-conversion', '-Wno-implicit-function-declaration'] + keep + [x['file']]
    r = subprocess.run(cmd, capture_output=True, text=True, cwd='.')
    out = []
    for l in r.stderr.splitlines():
        m = pat.match(l)
        if m: out.append((m.group(1), int(m.group(2)), int(m.group(3)), m.group(4)))
    return out
with ThreadPoolExecutor(6) as ex:
    res = list(ex.map(run, seen.values()))
edits = set(e for r in res for e in r)
by = collections.defaultdict(list)
for f, l, col, m in edits: by[f].append((l, col, m))
for f, es in by.items():
    L = open(f).read().split('\n')
    for l, col, m in sorted(es, reverse=True):
        s = L[l-1]
        if s[col-1:col-1+len(m)] != m: print('SKIP', f, l, col, m); continue
        L[l-1] = s[:col-1] + prefix + s[col-1:]
    open(f, 'w').write('\n'.join(L))
print(len(edits), 'edits in', len(by), 'files')
