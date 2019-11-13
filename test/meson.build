test_HC_tree_exe = executable('test_HCTree.cpp.executable',
sources: ['test_HCTree.cpp'],
dependencies: [HC_tree_dep, input_stream_dep, output_stream_dep, gtest_dep])
test('my HCTree test', test_HC_tree_exe)


test_Bitoutput_exe = executable('test_BitOutputStream.cpp.executable',
sources: ['test_BitOutputStream.cpp'],
dependencies: [HC_tree_dep, input_stream_dep, output_stream_dep, gtest_dep])
test('my Bitoutput test', test_Bitoutput_exe)

test_Bitinput_exe = executable('test_BitInputStream.cpp.executable',
sources: ['test_BitInputStream.cpp'],
dependencies: [HC_tree_dep, input_stream_dep, output_stream_dep, gtest_dep])
test('my Bitinput test', test_Bitinput_exe)

