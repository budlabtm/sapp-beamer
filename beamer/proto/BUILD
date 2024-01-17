proto_library(
    name = "beamer-cfg-proto",
    srcs = ["beamer-cfg.proto"],
    visibility = ["//visibility:public"],
)

proto_library(
    name = "beamer-res-proto",
    srcs = ["beamer-res.proto"],
    visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "beamer-cfg-cc-proto",
    visibility = ["//beamer:__subpackages__"],
    deps = [":beamer-cfg-proto"],
)

cc_proto_library(
    name = "beamer-res-cc-proto",
    visibility = ["//beamer:__subpackages__"],
    deps = [":beamer-res-proto"],
)
