# Documentation

Each fact lives on one page. Start from the task.

| I want to                                       | Read                                                                                     |
| ----------------------------------------------- | ---------------------------------------------------------------------------------------- |
| Install the tools and build                     | [toolchain: host tools and setup](toolchain.md#setup)                                    |
| Work without a disc                             | [toolchain: without a disc](toolchain.md#without-a-disc)                                 |
| Find the next function to match                 | [CONTRIBUTING: find work](../CONTRIBUTING.md#find-work)                                  |
| Match in the cheapest order                     | [matching: route](matching.md#route)                                                     |
| Run every check before a push                   | [CONTRIBUTING: before a pull request](../CONTRIBUTING.md#before-you-open-a-pull-request) |
| Match my first function                         | [CONTRIBUTING: your first match](../CONTRIBUTING.md#your-first-match)                    |
| Find out why a function does not match          | [matching: diagnose](matching.md#diagnose)                                               |
| Compare one function with retail in 0.1 s       | [toolchain: match.sh](toolchain.md#matchsh)                                              |
| Find twins of a function                        | [toolchain: coddog](toolchain.md#coddog)                                                 |
| Find a template for an assembly function        | [tools: templates](../tools/README.md#templates)                                         |
| Run a routine task with one command             | [tools](../tools/README.md)                                                              |
| Check the disc and the extracted files          | [toolchain: disc manifest](toolchain.md#disc-manifest)                                   |
| Use the permuter                                | [matching: permuter](matching.md#permuter), [toolchain](toolchain.md#permuter)           |
| Name a function, global, type or constant       | [conventions: names](conventions.md#names)                                               |
| Add a type, a member or a constant              | [conventions: types and values](conventions.md#types-and-values)                         |
| Decide where a declaration or file goes         | [conventions: files and headers](conventions.md#files-and-headers)                       |
| Check which compiler flags the build uses       | [toolchain: compiler chain](toolchain.md#compiler-chain)                                 |
| Try a function on decomp.me                     | [decomp.me](decomp-me.md)                                                                |
| Understand a failing check                      | [matching: gates](matching.md#gates), [toolchain: commands](toolchain.md#commands)       |
| Find which subsystem owns a directory or record | [subsystems](subsystems.md)                                                              |
| Reproduce a fact from the wiki                  | [reproduce wiki facts](reproduce.md)                                                     |

## Pages

| Page                          | Job                                                                             |
| ----------------------------- | ------------------------------------------------------------------------------- |
| [toolchain](toolchain.md)     | Set up, build, compile, inspect bytes and find twins                            |
| [matching](matching.md)       | Match, diagnose and polish a function: gates, markers, labels, permuter         |
| [conventions](conventions.md) | Write the code: names, types, values, files and headers, comments               |
| [decomp.me](decomp-me.md)     | Scratch settings that reproduce the project build                               |
| [subsystems](subsystems.md)   | Which `src/` directories, records and headers each subsystem owns, and its debt |
| [reproduce](reproduce.md)     | `bof3` commands that reproduce the facts of each wiki page                      |

The root files: [README](../README.md), [CONTRIBUTING](../CONTRIBUTING.md), and
[AGENTS](../AGENTS.md) with the task skills in [`.agents/skills`](../.agents/skills) for coding agents.
