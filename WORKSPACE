workspace(
    name = "graph-algo-wasm",
)

# Emscripten toolchain
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
    name = "emsdk",
    sha256 = "d55e3c73fc4f8d1fecb7aabe548de86bdb55080fe6b12ce593d63b8bade54567",
    strip_prefix = "emsdk-3891e7b04bf8cbb3bc62758e9c575ae096a9a518/bazel",
    url = "https://github.com/emscripten-core/emsdk/archive/3891e7b04bf8cbb3bc62758e9c575ae096a9a518.tar.gz",
)

load("@emsdk//:deps.bzl", emsdk_deps = "deps")
emsdk_deps()

load("@emsdk//:emscripten_deps.bzl", emsdk_emscripten_deps = "emscripten_deps")
emsdk_emscripten_deps(emscripten_version = "2.0.31")

# psimd library, used for fallback 128-bit SIMD micro-kernels
http_archive(
    name = "psimd",
    build_file = "@xnnpack//third_party:psimd.BUILD",
    sha256 = "dc615342bcbe51ca885323e51b68b90ed9bb9fa7df0f4419dbfa0297d5e837b7",
    strip_prefix = "psimd-072586a71b55b7f8c584153d223e95687148a900",
    urls = [
        "https://github.com/Maratyszcza/psimd/archive/072586a71b55b7f8c584153d223e95687148a900.zip",
    ],
)

http_archive(
    name = "rules_cc",
    sha256 = "90d5a66950b492cbf86201cdc49c4b59796a85a4eb9fd63c07afe5f7132ea623",
    strip_prefix = "rules_cc-8346df34b6593b051403b8e429db15c7f4ead937",
    urls = [
        "https://github.com/bazelbuild/rules_cc/archive/8346df34b6593b051403b8e429db15c7f4ead937.zip",
    ],
)
