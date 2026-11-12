# Text files the graph writes into the build directory. text.in holds only the text.
configure_file(input: 'text.in', output: 'compile_commands.json', configuration: cdb)
configure_file(input: 'text.in', output: 'images.sha1', configuration: check_sums)

# The permuter import reads the flags from these.
configure_file(input: 'cflags.in', output: 'cflags.txt', configuration: flag_files)
configure_file(input: 'asflags.in', output: 'asflags.txt', configuration: flag_files)
