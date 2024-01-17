load("@rules_qt//:qt.bzl", "qt_cc_library")

qt_cc_library(
    name = "libbeamer",
    srcs = glob(
        ["*.cc"],
        exclude = ["main.cc"],
    ),
    hdrs = glob(["*.h"]),
    linkopts = ["-lgsl"],
    deps = [
        "//beamer/proto:beamer-cfg-cc-proto",
        "//beamer/proto:beamer-res-cc-proto",
        "@lib-msg//msg/mqtt",
        "@lib-msg//msg/vcas",
        "@rules_qt//:qt_core",
    ],
)

cc_binary(
    name = "beamer",
    srcs = ["main.cc"],
    deps = [":libbeamer"],
)
