#!/usr/bin/env python3
"""usage: whichfn.py IMAGE_ID (e.g. emi/etc/shop/00): objects whose bytes differ from retail."""
import re, subprocess, sys
img = sys.argv[1]
flat = img.replace('/', '+')
a, b = 'build/meson/%s.bin' % flat, 'build/bin/%s.bin' % img
base = None
for l in open('config/%s/splat.yaml' % img):
    m = re.match(r'\s+vram:\s*(0x[0-9A-Fa-f]+)', l)
    if m: base = int(m.group(1), 16); break
if img.startswith('exe/'):
    base -= 0x800
rows = []
txt = open('build/meson/%s.map' % flat).read().split('Linker script and memory map')[1]
cur = None
for l in txt.split('\n'):
    m = re.match(r'\s+(\.\w+)\s+(0x[0-9a-f]+)\s+(0x[0-9a-f]+)\s+(\S+\.o)', l)
    if m and int(m.group(3), 16):
        rows.append((int(m.group(2), 16), int(m.group(3), 16), m.group(4)))
offs = [int(x.split()[0]) - 1 for x in subprocess.run(['cmp', '-l', a, b], capture_output=True, text=True).stdout.splitlines()]
hit = {}
for o in offs:
    ad = base + o
    for s, n, name in rows:
        if s <= ad < s + n: hit.setdefault(name, 0); hit[name] += 1
print(len(offs), 'bytes differ;', 'objects:', hit if hit else 'none found (base %x)' % base)
