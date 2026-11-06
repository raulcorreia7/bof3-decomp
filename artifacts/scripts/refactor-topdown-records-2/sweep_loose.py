#!/usr/bin/env python3
"""Replace loose D_ scalars that are PartyBattler members with the member; keep each only if `check` stays 428."""
import re,subprocess,sys,os
BASE=0x80145E90
M={0:('flags',1),1:('mode',1),2:('step',1),3:('unk_03',1),4:('unk_04',1),5:('slot',1),7:('unk_07',1),8:('facing',1),9:('unk_09',1),0xA:('timer',1),0xB:('unk_0B',1),
0xC:('unk_0C',4),0x10:('unk_10',4),0x14:('unk_14',4),0x18:('unk_18',4),0x1C:('unk_1C',4),0x20:('unk_20',4),0x24:('unk_24',1),0x25:('unk_25',1),0x26:('unk_26',1),0x27:('unk_27',1),0x28:('unk_28',1),
0x29:('unk_29',1),0x2A:('unk_2A',1),0x2B:('unk_2B',1),0x2C:('unk_2C',2),0x2E:('unk_2E',2),0x30:('unk_30',2),0x32:('depth',2),
0x34:('pos.x.fixed',4),0x38:('pos.y.fixed',4),0x3C:('pos.z.fixed',4),0x40:('scale_x',4),0x44:('scale_y',4),0x48:('unk_48',1),0x49:('unk_49',1),0x4A:('unk_4A',1),0x4B:('unk_4B',1),0x4C:('unk_4C',4),
0x118:('command.target',1),0x119:('command.type',1),0x11A:('command.id',2),0x11C:('hp_change',2),0x11E:('ap_change',2),0x120:('unk_120',1),0x121:('counter_121',1),0x122:('unk_122',1),0x123:('unk_123',1),
0x136:('counter_136',1),0x137:('counter_137',1),0x138:('focus_counter',1),0x139:('unk_139',1),0x13C:('record_slot',1)}
SZ={'u8':1,'s8':1,'u16':2,'s16':2,'u32':4,'s32':4}
def sh(c): return subprocess.run(c,shell=True,capture_output=True,text=True).stdout
decl=sh(r"git grep -nE 'extern\s.*\bD_8014[56][0-9A-F]{3}\b' -- include src").splitlines()
syms={}
for l in decl:
    f,n,t=l.split(':',2)
    m=re.search(r'extern\s+(?:volatile\s+)?(\w+)\s+(D_8014[56][0-9A-F]{3})\b(\[?)',t)
    if not m: continue
    a=int(m.group(2)[2:],16)
    if not BASE<=a<BASE+3*0x140: continue
    ok=m.group(1) in SZ and not m.group(3)
    syms.setdefault(m.group(2),[]).append(ok and SZ[m.group(1)])
only=sys.argv[1:]
for s,v in sorted(syms.items()):
    if only and s not in only: continue
    a=int(s[2:],16)-BASE; r,o=divmod(a,0x140)
    if o not in M or not all(v) or set(v)!={M[o][1]}: continue
    rep=f"g_BattlePartyBattlers[{r}].{M[o][0]}"
    files=sh(f"git grep -lw {s} -- src include").split()
    touched=[]
    for f in files:
        t=open(f).read(); n=t
        n=re.sub(r'^[ \t]*extern\s[^;\n]*\b'+s+r'\b;[^\n]*\n','',n,flags=re.M)
        n=re.sub(r'\b'+s+r'\b',rep,n)
        if n!=t: open(f,'w').write(n); touched.append(f)
    r_=subprocess.run("ninja -C build/meson -j 8 -k 0 check",shell=True,capture_output=True,text=True).stdout.strip().splitlines()[-1]
    if r_.endswith("428 images match"): print("KEEP",s,rep,len(touched),flush=True)
    else:
        subprocess.run(["git","checkout","--"]+touched); print("DROP",s,rep,r_[:80],flush=True)
