import re,sys,subprocess
files=subprocess.check_output(['git','ls-files','src/*.c','src/**/*.c']).decode().split()
pat=re.compile(r'^(\s*)(\w+(?:\[[^\]]*\])?(?:->|\.))(x0|y0|u0|v0|r0|g0|b0|w|h|x1|y1|x2|y2|x3|y3|u1|v1|u2|v2|u3|v3)\s*=\s*([^;=]+);\s*$')
PAIRS=[('x0','y0'),('u0','v0'),('w','h'),('x1','y1'),('x2','y2'),('x3','y3'),('u1','v1'),('u2','v2'),('u3','v3')]
for f in files:
    L=open(f).read().split('\n')
    for i,l in enumerate(L):
        m=pat.match(l)
        if not m: continue
        for a,b in PAIRS:
            if m.group(3)==a:
                for j in range(i+1,min(i+8,len(L))):
                    m2=pat.match(L[j])
                    if m2 and m2.group(2)==m.group(2) and m2.group(3)==b:
                        print(f"{f}:{i+1}:{j+1}:{j-i}:{a}{b}")
                    if '}' in L[j] and '{' not in L[j] or L[j].strip()=='' : break
