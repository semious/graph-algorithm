def emscripten_test_linkopts():
    """Emscripten-specific linkopts for unit tests."""
    return [
        "-s ASSERTIONS=2",
        "-s ENVIRONMENT=node,shell,web",
        "-s ERROR_ON_UNDEFINED_SYMBOLS=1",
        "-s DEMANGLE_SUPPORT=1",
        "-s EXIT_RUNTIME=1",
        "-s ALLOW_MEMORY_GROWTH=1",
    ]

def graph_algo_unit_test(name, srcs, deps = [], **kwargs):
    native.cc_test(
        name = name,
        srcs = srcs,
        linkstatic = True,
        copts = ["-Itest/cpp/catch2/", "-Isrc/cpp/"],
        linkopts = select({
            ":emscripten": emscripten_test_linkopts(),
             "//conditions:default": [],
        }),
        deps = [
            "//test/cpp/catch2:catch2",
            "catch-main",
        ] + deps,
        **kwargs
    )

