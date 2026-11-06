"""List single-line declarations that a file already gets from an included header."""
import os, re, subprocess, sys, collections
sys.path.insert(0, "tools")
from bof3.source.decls import Tree

files = subprocess.run(["git", "ls-files", "src/**/*.c", "src/**/*.h", "include/**/*.h", "include/*.h"],
                       capture_output=True, text=True).stdout.split()
files = [f for f in files if not f.startswith("include/psyq")]
texts = {f: open(f, encoding="utf-8", errors="replace").read() for f in files}
tree = Tree({f: t for f, t in texts.items()})
DECL = re.compile(r"^\s*(?:extern\s+)?([A-Za-z_][\w\s\*]*?[\s\*])(\w+)\s*(\[[^\]]*\])*\s*(\([^;{}]*\))?\s*;\s*(?:/\*.*\*/)?\s*$")
def norm(line):
    line = re.sub(r"/\*.*?\*/", "", line)
    line = re.sub(r"^\s*extern\s+", "", line.strip())
    return re.sub(r"\s+", "", line)
lines = {}
for f, t in texts.items():
    d = {}
    for i, l in enumerate(t.split("\n")):
        if l.startswith((" ", "\t", "#")) or "=" in l or "typedef" in l: continue
        m = DECL.match(l)
        if m and "static" not in l and "return" not in l:
            d.setdefault(norm(l), []).append(i + 1)
    lines[f] = d
rows = []
for f in files:
    if not lines[f]: continue
    cl = tree.closure(f) - {f}
    for n, ls in lines[f].items():
        owner = next((g for g in sorted(cl) if n in lines.get(g, {})), None)
        if owner:
            for l in ls: rows.append((f, l, owner))
if len(sys.argv) > 1 and sys.argv[1] == "diff":
    # same name declared in an included file with different text
    byname = {}
    for f, t in texts.items():
        for i, l in enumerate(t.split("\n")):
            if l.startswith((" ", "\t", "#")) or "=" in l or "typedef" in l or "static" in l or "return" in l: continue
            m = DECL.match(l)
            if m: byname.setdefault(m.group(2), []).append((f, i + 1, norm(l)))
    for f in files:
        cl = tree.closure(f) - {f}
        for name, ds in byname.items():
            mine = [d for d in ds if d[0] == f]
            if not mine: continue
            for g in ds:
                if g[0] in cl and g[2] != mine[0][2]:
                    print(f, mine[0][1], g[0], g[1], mine[0][2], g[2], sep="\t"); break
    sys.exit()
for r in rows: print(*r, sep="\t")
print(len(rows), "redundant of", sum(len(v) for d in lines.values() for v in d.values()), file=sys.stderr)

if len(sys.argv) > 1 and sys.argv[1] == "diff":
    pass
