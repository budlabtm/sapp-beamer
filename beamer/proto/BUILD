proto_library(
    name = "beamer-cfg-proto",
    srcs = ["beamer-cfg.proto"],
    visibility = ["//visibility:public"],
)

proto_library(
    name = "beamer-out-proto",
    srcs = ["beamer-out.proto"],
    visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "beamer-cfg-cc-proto",
    visibility = ["//beamer:__subpackages__"],
    deps = [":beamer-cfg-proto"],
)

cc_proto_library(
    name = "beamer-out-cc-proto",
    visibility = ["//beamer:__subpackages__"],
    deps = [":beamer-out-proto"],
)
