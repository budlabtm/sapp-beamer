load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_qt",
    sha256 = "bd8253247c0e45e6a180c87083f20910159e36cd67f6b11d5d3d865a61ea52cd",
    strip_prefix = "rules_qt6-0.0.3",
    url = "https://github.com/Vertexwahn/rules_qt6/releases/download/v0.0.3/rules_qt6-v0.0.3.tar.gz",
)

load("@rules_qt//:fetch_qt.bzl", "fetch_qt6")
load("@rules_qt//tools:qt_toolchain.bzl", "register_qt_toolchains")

fetch_qt6()
register_qt_toolchains()
