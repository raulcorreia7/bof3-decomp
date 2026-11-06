#!/usr/bin/env python3
"""usage: fixmember.py LOG old=new ... : rewrite the member on every line a compile log flags."""
import re,sys,collections
log=open(sys.argv[1]).read()
ren=dict(a.split('=') for a in sys.argv[2:])
hits=collections.defaultdict(set)
for m in re.finditer(r"^(\S+?):(\d+):(?:\d+: error:)? ?.*?no member named .(\w+)'",log,re.M):
    if m.group(3) in ren: hits[m.group(1)].add(int(m.group(2)))
for f,lines in hits.items():
    L=open(f).read().split('\n')
    for n in lines:
        s=L[n-1]
        for o,nw in ren.items(): s=re.sub(r'\b'+o+r'\b',nw,s)
        L[n-1]=s
    open(f,'w').write('\n'.join(L))
print(len(hits),'files')
