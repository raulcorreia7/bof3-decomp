"""Try SDK setter macros on order-blocked prim pairs; keep a variant only if `check` passes."""
import re,subprocess,sys,json
ROOT='.'
PAIRS={('x0','y0'):'setXY0',('u0','v0'):'setUV0',('w','h'):'setWH'}
pat=re.compile(r'^(\s*)(\w+(?:\[[^\]]*\])?(?:->|\.))(\w+)\s*=\s*([^;]+);\s*$')
files=subprocess.check_output(['git','ls-files','src/*.c']).decode().split()
if len(sys.argv)>1: files=[f for f in files if any(a in f for a in sys.argv[1:])]
def check():
    r=subprocess.run(['meson','compile','-C','build/meson','-j','6','check'],capture_output=True,text=True)
    return r.returncode==0
def cands(L):
    for i,l in enumerate(L):
        m=pat.match(l)
        if not m: continue
        for (a,b),mac in PAIRS.items():
            if m.group(3)!=a: continue
            if re.search(r'rect|clip|\bD_\w+\.',m.group(2)) or m.group(2).endswith('.'): continue
            for j in range(i+1,min(i+8,len(L))):
                if L[j].strip()=='' or '{' in L[j] or '}' in L[j]: break
                m2=pat.match(L[j])
                if m2 and m2.group(2)==m.group(2) and m2.group(3)==b and j>i+0:
                    yield i,j,mac,m,m2
log=open('artifacts/scripts/refactor-topdown-psyq-2/reorder.log','a')
for f in files:
    tried=set()
    while True:
        orig=open(f).read(); L=orig.split('\n'); did=False
        for i,j,mac,m,m2 in cands(L):
            if j==i+1 and False: pass
            key=(m.group(0),m2.group(0))
            if key in tried: continue
            tried.add(key)
            base=m.group(2)[:-2] if m.group(2).endswith('->') else m.group(2)[:-1]
            for var in ('A','B'):
                new=list(L)
                call=f"{m.group(1) if var=='A' else m2.group(1)}{mac}({base}, {m.group(4).strip()}, {m2.group(4).strip()});"
                if var=='A': new[i]=call; del new[j]
                else: new[j]=call; del new[i]
                open(f,'w').write('\n'.join(new))
                ok=check()
                print(f,i+1,mac,var,ok,flush=True); log.write(f"{f}:{i+1}:{mac}:{var}:{ok}\n"); log.flush()
                if ok: did=True; break
                open(f,'w').write(orig)
            if did: break
        if not did: break
