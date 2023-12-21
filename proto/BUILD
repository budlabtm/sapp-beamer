proto_library(
    name = "beamer_cfg_proto",
    srcs = ["beamer-cfg.proto"],
    visibility = ["//visibility:public"],
)

proto_library(
    name = "beamer_out_proto",
    srcs = ["beamer-out.proto"],
    visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "beamer_cfg_cc_proto",
    deps = [":beamer_cfg_proto"],
    visibility = ["//:__subpackages__"]
)

cc_proto_library(
    name = "beamer_out_cc_proto",
    deps = [":beamer_out_proto"],
    visibility = ["//:__subpackages__"]
)