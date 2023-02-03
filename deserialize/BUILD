load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "deserialize",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    deps = [
        "//helpers:helpers",
        "//rapidjson:rapidjson"
    ],
    visibility = [
        "//visibility:public"
    ]
)
