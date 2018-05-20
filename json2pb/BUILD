from mm_envs import *

proto_library(
    name = 'testpb',
    srcs = [ 'proto/test.proto', ],
    export_incs = ['.', 'proto'],
)

cc_binary(
        target_bases = [ 'mmcomm',],
        name = 'json2pb_test',
        srcs = [
            'json2pb_test.cpp',
            'utils.cpp',
        ],
        deps = [
            '//comm2/core:core',
            '//mmcomm/comm:mmcomm',
            '//mmtenpay/mmpaybasic/mmpayentrust/scripts/json2pb/lib:json2pblib',
            ':testpb',
        ],
        export_incs = [
            '.',
        ],
        extra_cppflags = [
            '-Wall',
            '-Werror',
        ],
)
