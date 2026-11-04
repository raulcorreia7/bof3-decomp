# Change a tool, build file or doc

1. State the success check before the edit: a command, a count or a link target.
2. Prefer deleting code, then the standard library or an existing dependency, then new code. Keep
   public verbs and output stable unless `scope` allows a change.
3. Read the owner first: commands and tools in [toolchain](../../../../docs/toolchain.md), the rule a
   doc states on its page ([index](../../../../docs/README.md)). Change a generated file through its
   source script. Write each fact once and link it elsewhere.
4. Edit. For a doc or prompt: present tense, the current contract, short sentences, tables for
   lookups, no history. Check every relative link and `#anchor` resolves.
5. Add a test only for a byte-identity gate or a risky pure transform (`tools/tests/`).
6. Run the success check. The job ends when it passes and every link resolves.

Report: result, changed paths, checks run, behavior changes, remaining problems with one concrete fix
each.
