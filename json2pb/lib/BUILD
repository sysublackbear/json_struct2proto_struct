from mm_envs import *

cc_library(
    target_bases = [ 'mmcomm',],
    name = 'json2pblib',
    srcs = [
        'json2pblib.cpp',
    ],
    deps = [
        '//comm2/core:core',
        '//mmcomm/comm:mmcomm',
        '//mm3rd/protobuf:protobuf',
        '//mm3rd/rapidjson-1.1:rapidjson',
        '//mmtenpay/mmpaybasic/mmpayentrust/scripts/json2pb:testpb',
    ],
    export_incs = [
        '.',
    ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
    ],
)

