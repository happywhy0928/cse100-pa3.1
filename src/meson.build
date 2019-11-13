subdir('bitStream')
subdir('encoder')

compress_exe = executable('compress.cpp.executable',
sources:['compress.cpp'],
dependencies : [HC_tree_dep, input_stream_dep, output_stream_dep, cxxopts_dep],
install: true)

uncompress_exe = executable('uncompress.cpp.executable',
sources: ['uncompress.cpp'],
dependencies : [HC_tree_dep, input_stream_dep, output_stream_dep, cxxopts_dep],
install:true)