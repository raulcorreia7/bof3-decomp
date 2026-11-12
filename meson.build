project('rebof3', version: '0.1.0', meson_version: '>=1.3.0')

# The 428 PSX images, byte-for-byte, with the period toolchain.
#
#   meson setup build/meson
#   meson compile -C build/meson            # every image
#   meson compile -C build/meson check      # every image against its retail SHA-1
#
# tools/split.py runs at configure time. It splits the stale targets, writes each image's
# link script into build/ld and prints the build graph: the objects of every image and how
# each is made. Meson regenerates when a file that decides that graph changes.
#
# Without the extracted disc or the compiler toolchain, setup still works and offers
# only the targets that need neither.

# --- Options and tools: what setup found, and the programs the build runs.

fs = import('fs')
root = meson.project_source_root()
bld = meson.project_build_root()
tools = root / 'tools'
# The generated text files the tools read back: headers.txt, hand.txt, plain-flags.txt,
# images.sha1, compile_commands.json, cflags.txt and asflags.txt.
emit_dir = bld / 'emit'

sh = find_program('sh')
env = find_program('env')
touch = find_program('touch')

# Each entry is the program and what to run when it is missing.
compiler_tools = {
  '.venv/bin/python': 'run tools/setup.sh',
  'toolchains/gcc-2.7.2-psx/gcc': 'run tools/setup.sh',
  'toolchains/psn00b_toolchain/bin/mipsel-none-elf-as': 'run tools/setup.sh',
  'third_party/maspsx/maspsx.py': 'run `git submodule update --init third_party/maspsx`',
}
missing = []
foreach path, fix : compiler_tools
  if not fs.exists(root / path)
    missing += path + ' (' + fix + ')'
  endif
endforeach
have_compiler = missing.length() == 0

# The disc is extracted once into build/disc, and from there into build/bin.
have_payloads = fs.is_dir(root / 'build/bin') or fs.is_dir(root / 'build/disc')
have_psyq = fs.is_dir(root / 'toolchains/psyq')
have_game = have_compiler and have_payloads and have_psyq

if have_compiler
  venv_python = find_program(root / '.venv/bin/python')
  binutils = root / 'bin/internal/binutils'
  as = find_program(binutils / 'as')
  ld = find_program(binutils / 'ld')
  objcopy = find_program(binutils / 'objcopy')
endif

if not have_game
  reasons = missing
  if not have_payloads
    reasons += 'build/bin or build/disc (extracted retail data)'
  endif
  if not have_psyq
    reasons += 'toolchains/psyq (run tools/setup.sh)'
  endif
  message('Disc-free build: no game images. Missing: ' + ', '.join(reasons) + '. To enable the game build, follow README.md, then run: meson setup --reconfigure build/meson')
endif

# --- Graph: the split targets, their link scripts and their object rows.

# One unit per image: its retail identity, its symbol maps and its rows in link order. A
# draft row is a source with a NON_MATCHING function, compiled again for the report.
units = []
drafts = []
payload_of = {}
if have_game
  split = run_command(venv_python, tools / 'split.py', check: false)
  if split.returncode() != 0
    error(split.stderr().strip())
  endif
  message(split.stderr().strip())

  # The hand-written assembly present now; the checks notice one added since.
  hand_files = run_command('find', 'asm', '-path', '*/hand/*.s', check: true).stdout().strip()
  configure_file(input: 'emit/text.in', output: 'hand.txt',
    configuration: configuration_data({'TEXT': hand_files}))

  foreach block : split.stdout().split('\ntarget\t')
    lines = block.strip().split('\n')

    # The first block lists what the graph depends on, then the draft sources.
    if lines[0].startswith('dep\t') or lines[0].startswith('d\t')
      foreach line : lines
        row = line.split('\t')
        if row[0] == 'dep'
          fs.read(row[1])
        else
          drafts += [[row[1], row[2], row[3]]]
        endif
      endforeach
      continue
    endif

    head = lines[0].split('\t')
    image = head[0]
    sym_maps = []
    rows = []
    foreach line : lines
      if line == lines[0]
        continue
      endif
      row = line.split('\t')
      if row[0] == 'm'
        sym_maps += root / row[1]
      else
        rows += [row]
      endif
    endforeach
    payload_of += {image: head[2]}
    units += [{
      'image': image,
      'flat': image.replace('/', '+'),
      'retail_sha1': head[1],
      'payload': head[2],
      'script': head[3],
      'sym_maps': sym_maps,
      'rows': rows,
    }]
  endforeach
endif

# --- Compile: the flags, the header probes and one compile per source.

unit_objs = []
all_objs = []
cdb_chunks = []
if have_compiler
  # Run as a script: `python -m` would put the working directory, the build directory,
  # first on the import path, and its modification time changes with every object.
  cc = [venv_python, tools / 'cc.py', '--build-dir', bld]
  # The compiler wrapper is part of the compiler: a change to it rebuilds every object.
  cc_deps = [tools / 'cc.py', tools / 'psxdecomp/dmpsx.py']

  cpp_includes = ['-Isrc', '-Iinclude', '-Iinclude/psyq']
  cpp_defines = ['-DMATCHING']
  cc_opt = ['-O2']
  cc_target = ['-G0', '-funsigned-char', '-msoft-float', '-gcoff']
  as_maspsx = ['-Wa,--aspsx-version=2.56', '-Wa,--expand-div']
  as_target = ['-Wa,-G0,-EL,-mips1']
  as_includes = ['-Wa,-I' + root / 'src', '-Wa,-I' + root / 'asm', '-Wa,-I' + root / 'include/match']
  cflags = cpp_defines + cpp_includes + cc_target + as_maspsx + as_target + as_includes
  asflags = ['-G0', '-EL', '-mips1', '-Iinclude/match']

  # sce10eff reloads a scratchpad value after a branch; these flags stop the compiler
  # reusing it across jumps.
  sce10eff_dir = 'src/overlays/scenario/sce10eff/00/'
  sce10eff_opt = ['-O2', '-fno-cse-follow-jumps', '-fno-cse-skip-blocks']

  dep_flags = ['-MMD', '-MP', '-MF', '@DEPFILE@']

  # The flags `check-plain` compiles with: the C flags without MATCHING and without the
  # assembler ones, which carry the source root.
  plain_flags = configuration_data()
  plain_flags.set('TEXT', ' '.join(cpp_includes + cc_target + cc_opt))
  configure_file(input: 'emit/text.in', output: 'plain-flags.txt', configuration: plain_flags)

  # Header probes: every public header compiles on its own. The probe includes the header
  # into an empty translation unit. The set is the include tree, the group headers
  # (src/overlays/<group>/<group>.h) and the image headers, not the third-party PsyQ
  # headers, the include-time asm macro header and the image-local extras (data.h,
  # shared.h).
  headers = run_command('find', 'include', 'src', '-name', '*.h', check: true).stdout().strip().split('\n')
  probe_headers = []
  foreach h : headers
    parts = h.split('/')
    if parts[0] == 'include'
      if parts[1] != 'psyq'
        probe_headers += h
      endif
    elif h == 'src/shared/etc.h'
      probe_headers += h
    elif parts[-1] == parts[-2] + '.h'
      # the executable, group and logo headers: src/engine/slus/slus.h, src/overlays/boss/boss.h
      probe_headers += h
    elif parts.length() >= 5 and parts[-1] == parts[-3] + '_' + parts[-2] + '.h'
      # an image header: <archive>_<slot>.h beside its sources
      probe_headers += h
    elif parts[-2] == 'area' and parts[-1].startswith('world0')
      probe_headers += h
    endif
  endforeach

  probes = []
  foreach h : probe_headers
    name = 'header-probe+' + h.replace('/', '+') + '.o'
    probes += custom_target(name,
      input: 'emit/empty.c',
      output: name,
      depfile: name + '.d',
      depend_files: cc_deps,
      command: [cc, cflags, '-I.', '-DASM_DIR="asm/exe/slus_004_22"', cc_opt, dep_flags,
                '-include', h, '-c', 'emit/empty.c', '-o', '@OUTPUT@'])
  endforeach
  # The list of headers at configure time; the script notices a header added since.
  configure_file(input: 'emit/text.in', output: 'headers.txt',
    configuration: configuration_data({'TEXT': '\n'.join(headers)}))

  cdb_root = root.replace('\\', '\\\\').replace('"', '\\"')
  cdb_flags = []
  foreach flag : cflags
    cdb_flags += '"' + flag.replace('\\', '\\\\').replace('"', '\\"') + '"'
  endforeach
  # One compile_commands.json entry: ASM_DIR, include directory, optimization, source.
  cdb_entry = '{"directory": "' + cdb_root + '", "arguments": ["clang", ' + ', '.join(cdb_flags) + ', "-DASM_DIR=\\"@0@\\"", "-I@1@", @2@, "-c", "@3@"], "file": "@3@"}'
  cdb_opt = '"' + '", "'.join(cc_opt) + '"'
  cdb_sce10eff_opt = '"' + '", "'.join(sce10eff_opt) + '"'

  as_cmd = [env, '-C', root, as, asflags]

  # A draft compiles its source with -DNON_MATCHING, for the progress report.
  draft_targets = []
  foreach row : drafts
    draft_opt = row[1].startswith(sce10eff_dir) ? sce10eff_opt : cc_opt
    draft_targets += custom_target(row[0],
      input: row[1],
      output: row[0],
      depfile: row[0] + '.d',
      depend_files: cc_deps,
      command: [cc, '--empty-on-failure', cflags, '-DNON_MATCHING',
                '-DASM_DIR="' + row[2] + '"', '-I' + fs.parent(row[1]), draft_opt, dep_flags,
                '-c', row[1], '-o', '@OUTPUT@'])
  endforeach

  foreach unit : units
    objs = []
    cdb_entries = []
    foreach row : unit['rows']
      kind = row[0]
      if kind == 'c'
        src = row[2]
        include_dir = fs.parent(src)
        sce10eff = src.startswith(sce10eff_dir)
        objs += custom_target(row[1],
          input: src,
          output: row[1],
          depfile: row[1] + '.d',
          depend_files: cc_deps,
          command: [cc, cflags, '-DASM_DIR="@0@"'.format(row[3]), '-I' + include_dir,
                    sce10eff ? sce10eff_opt : cc_opt, dep_flags, '-c', src, '-o', '@OUTPUT@'])
        cdb_entries += cdb_entry.format(row[3], include_dir,
          sce10eff ? cdb_sce10eff_opt : cdb_opt, src)
      elif kind == 's'
        # A placement wrapper includes the retail payload, which no depfile names.
        extra = row[2].startswith('build/p2/') ? [root / unit['payload']] : []
        objs += custom_target(row[1],
          input: row[2],
          output: row[1],
          depend_files: extra,
          command: [as_cmd, '-o', bld / '@OUTPUT@', row[2]])
      elif kind == 'b'
        objs += custom_target(row[1],
          input: row[2],
          output: row[1],
          command: [env, '-C', root, objcopy, '-I', 'binary', '-O', 'elf32-littlemips',
                    '-B', 'mips', row[2], bld / '@OUTPUT@'])
      endif
    endforeach
    unit_objs += [objs]
    all_objs += objs
    if cdb_entries.length() > 0
      cdb_chunks += ',\n'.join(cdb_entries)
    endif
  endforeach
endif

# --- Link: one symbol pass for every image, then each image and its binary.

image_bins = []
checksums = []
rz_projects = []
link_maps = {}
if have_game
  # One step gives every image's undefined names their addresses (tools/link_symbols.py
  # --all): one Python start for all images, and only images whose inputs changed are
  # resolved again.
  syms_outputs = []
  syms_images = []
  syms_dep_files = {}
  foreach unit : units
    syms_outputs += [unit['flat'] + '.syms.ld']
    syms_images += [unit['image']]
    # `dep` in a list of tables deduplicates; Meson has no ordered set.
    foreach dep : unit['sym_maps'] + [root / unit['script'],
                                      root / 'build/asm' / unit['image'] / 'undefined_syms_auto.txt',
                                      root / 'build/asm' / unit['image'] / 'undefined_funcs_auto.txt',
                                      root / 'config' / unit['image'] / 'splat.yaml']
      syms_dep_files += {dep: true}
    endforeach
  endforeach
  syms = custom_target('syms',
    output: syms_outputs,
    depends: all_objs,
    depend_files: syms_dep_files.keys() + ['config/link.toml', tools / 'link_symbols.py',
                                    tools / 'bof3/link/symbols.py', tools / 'bof3/link/inputs.py'],
    command: [venv_python, tools / 'link_symbols.py', '--root', root, '--build-dir', bld,
              '--all', syms_images])

  foreach index : range(units.length())
    unit = units[index]
    image = unit['image']
    flat = unit['flat']
    objs = unit_objs[index]
    link_inputs = [root / unit['script'],
                   root / 'build/asm' / image / 'undefined_syms_auto.txt',
                   root / 'build/asm' / image / 'undefined_funcs_auto.txt']
    ld_args = []
    foreach input : link_inputs
      ld_args += ['-T', input]
    endforeach
    ld_args += ['-T', syms[index]]
    elf = custom_target('elf+' + flat,
      output: [flat + '.elf', flat + '.map'],
      depends: objs + [syms[index]],
      depend_files: link_inputs,
      command: [sh, '-c', '''py=$1 tool=$2 root=$3 target=$4 map=$5; shift 5
        "$@" || { "$py" "$tool" --root "$root" --target "$target" --explain "$map"; exit 1; }''',
                'link', venv_python, tools / 'link_symbols.py', root, image, '@OUTPUT1@',
                ld, '-EL', ld_args, '-Map=@OUTPUT1@', '-o', '@OUTPUT0@'])
    image_bin = custom_target('bin+' + flat,
      input: elf[0],
      output: flat + '.bin',
      build_by_default: true,
      command: [objcopy, '-O', 'binary', '@INPUT@', '@OUTPUT@'])
    image_bins += image_bin
    checksums += unit['retail_sha1'] + '  ' + bld / flat + '.bin'

    run_target('check-' + flat,
      command: [sh, '-c', '"$2" hand "$3" && echo "$0  $1" | sha1sum -c -',
                unit['retail_sha1'], bld / flat + '.bin',
                tools / 'check_configured.sh', bld / 'hand.txt'],
      depends: image_bin)

    # The Rizin project for bin/rz.
    rz_deps = [root / unit['payload'], root / 'config' / image / 'splat.yaml'] + unit['sym_maps']
    link_maps += {image: elf[1]}
    rz_projects += {'image': image, 'name': 'rz+' + flat + '.rzdb', 'deps': rz_deps}
  endforeach
endif

# --- Checks: what a push needs, and every image again its retail SHA-1.

run_target('check-tree', command: [tools / 'check_tree.sh'])
run_target('include-asm', command: [tools / 'check_asm.sh'])
run_target('check-plain', command: [tools / 'check_plain.sh', bld / 'plain-flags.txt'])
format_sh = find_program(tools / 'format.sh')
run_target('format', command: [format_sh])
run_target('format-check', command: [format_sh, '--check'])
# Every check a push needs, one line each (see tools/pre_push.sh).
run_target('pre-push', command: [tools / 'pre_push.sh'])

# pytest is in the dev group: tools/setup.sh --dev installs it.
if fs.exists(root / '.venv/bin/pytest')
  # The suite compiles the hand-asm C models natively, which can pass Meson's 30 s default
  # on a slow CI runner.
  test('tools', find_program(root / '.venv/bin/pytest'), args: ['-q'],
    workdir: root, timeout: 120)
else
  # `meson test` with no test defined exits 0, so a missing pytest must fail it.
  message('Tool tests cannot run: pytest is missing. Run tools/setup.sh --dev, then meson setup --reconfigure build/meson')
  test('tools', sh, args: ['-c', 'echo "pytest is missing: run tools/setup.sh --dev, then meson setup --reconfigure build/meson" >&2; exit 1'])
endif

if have_compiler
  run_target('check-headers',
    command: [tools / 'check_configured.sh', 'headers', bld / 'headers.txt'],
    depends: probes)
endif

if have_game
  run_target('check',
    command: [sh, '-c', '"$2" hand "$3" && sha1sum --quiet -c "$0" && echo "check: $1 images match"',
              emit_dir / 'images.sha1', checksums.length().to_string(),
              tools / 'check_configured.sh', bld / 'hand.txt'],
    depends: image_bins)
endif

# --- Reports: the text the tools read back, and the progress and Rizin files.

if have_game
  check_sums = configuration_data()
  check_sums.set('TEXT', '\n'.join(checksums))
  cdb = configuration_data()
  cdb.set('TEXT', '[\n' + ',\n'.join(cdb_chunks) + '\n]')
  # The flags the permuter import compiles and assembles with.
  flag_files = configuration_data()
  flag_files.set('CFLAGS', ' '.join(cflags))
  flag_files.set('ASFLAGS', ' '.join(asflags))
  subdir('emit')

  objdiff_json = custom_target('objdiff.json',
    output: ['objdiff.json', 'sdk.json'],
    depends: image_bins + draft_targets,
    depend_files: ['config/sdk/library-units.jsonl', 'tools/objdiff_config.py'],
    command: [venv_python, tools / 'objdiff_config.py', 'generate', '--root', root,
              '--build-dir', bld])
  # The report names the commit that wrote it, so it is always rewritten.
  run_target('report',
    command: [venv_python, tools / 'objdiff_config.py', 'report', '--root', root,
              '--build-dir', bld],
    depends: objdiff_json)

  rz_inputs = custom_target('rz-inputs',
    output: 'rz-inputs.stamp',
    command: [touch, '@OUTPUT@'],
    depend_files: headers + ['config/link.toml', 'config/sdk/library-units.jsonl',
      'config/emi/etc/game/00/splat.yaml', 'config/exe/slus_004_22/splat.yaml',
      'build/symbols/emi+etc+game+00.link', 'build/symbols/exe+slus_004_22.link',
      root / payload_of['exe/slus_004_22'],
      'tools/rzproject.py', 'tools/m2ctx.py', 'tools/bof3/resolve/layout.py',
      'tools/bof3/resolve/manifests.py'])
  foreach project : rz_projects
    custom_target(project['name'],
      input: rz_inputs,
      output: project['name'],
      depend_files: project['deps'],
      # Its own linker map and the resident images' maps name the symbols `rzproject.py` flags.
      depends: [link_maps[project['image']], link_maps['exe/slus_004_22'], link_maps['emi/etc/game/00']],
      command: [venv_python, tools / 'rzproject.py', project['image'], '--output', bld / '@OUTPUT@'])
  endforeach
endif
