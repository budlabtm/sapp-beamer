load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "lib-msg",
    sha256 = "f7408cb05db3c72fc3986a4fdf83deb548f366792b434cbc3a301665982a772f",
    strip_prefix = "lib-msg-1.0.0",
    urls = ["https://github.com/budlabtm/lib-msg/archive/refs/tags/v1.0.0.tar.gz"],
)

load("@lib-msg//:lib_msg_deps.bzl", "lib_msg_deps")

lib_msg_deps()

load("@rules_qt//:fetch_qt.bzl", "fetch_qt6")

fetch_qt6()

load("@rules_qt//tools:qt_toolchain.bzl", "register_qt_toolchains")

register_qt_toolchains()

load("@paho-mqtt-cpp//:paho_mqtt_cpp_deps.bzl", "paho_mqtt_cpp_deps")

paho_mqtt_cpp_deps()

load("@paho-mqtt-c//:paho_mqtt_c_deps.bzl", "paho_mqtt_c_deps")

paho_mqtt_c_deps()
