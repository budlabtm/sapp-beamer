load("@rules_qt//:qt.bzl", "qt_cc_library")

qt_cc_library(
    name = "repo",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    deps = [
        "//beamer/model",
        "@lib-msg//msg",
        "@lib-msg//msg/mqtt",
        "@lib-msg//msg/vcas",
        "@rules_qt//:qt_core",
    ],
)
