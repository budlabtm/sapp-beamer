load("@rules_qt//:qt.bzl", "qt_cc_library")

qt_cc_library(
    name = "repo",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    deps = [
        "//beamer/proto:beamer-cfg-cc-proto",
        "@lib-msg//msg/mqtt",
        "@rules_qt//:qt_core",
    ],
)
