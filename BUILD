'''
Copyright (c) 2021, Arjun S Kumar
'''
#load("//engine/build:isaac.bzl", "isaac_app", "isaac_cc_module")

load("//bzl:module.bzl", "isaac_app", "isaac_cc_module" )

isaac_cc_module(
    name = "ping_components",
    srcs = [
        "Ping.cpp",
        "Pong.cpp",
    ],
    hdrs = [
        "Ping.hpp",
        "Pong.hpp",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//third_party:ros",
    ],
)

isaac_app(
    name = "ping_pong_ros",
    modules = [
        "//apps/samples/ping_pong_ros:ping_components",
    ],

)
