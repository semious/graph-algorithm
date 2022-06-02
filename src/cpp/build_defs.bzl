def graph_algo_cpp_library(name, **kwargs):
    """CC library for spiderjs
    Args:
      name: The name of the spiderjs cpp library to define.
      srcs: The list of source files.
      hdrs: The list of header files.
      deps: The list of additional libraries to be linked.
    """

    native.cc_library(
        name = name,
        linkstatic = True,
        visibility = ["//visibility:public"],
         **kwargs
    )
