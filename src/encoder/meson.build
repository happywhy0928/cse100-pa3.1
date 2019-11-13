HC_tree = library('HC_tree', sources:['HCNode.hpp','HCTree.cpp','HCTree.hpp'],dependencies: [
    input_stream_dep,output_stream_dep])
inc = include_directories('.')

HC_tree_dep = declare_dependency(include_directories:inc, link_with: HC_tree,dependencies: [
    input_stream_dep,output_stream_dep])