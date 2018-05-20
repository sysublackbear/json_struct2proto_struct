#include <stdio.h>
#include <string>
#include <unistd.h>
#include <getopt.h>
#include "utils.h"
#include "lib/json2pblib.h"

void PrintHelp(const char * sProgram)
{
    printf("\n");
    printf("Json to Pb tool. Version 1.0\n");
    printf("\n");
    printf("%s <-j Json file> <-p Proto file> \n", sProgram);
    printf(" Usage: -j <Json file>      # Json File\n");
    printf("        -f <Proto file>     # Proto File\n");
    printf("        -d <Dir name>       # Dir Name\n");
    printf("        -m <Message name>   # Message Name\n");
    printf("Author: sysublackbear\n");
    printf("\n");
    return ;
}

int ParseOption(int argc, char ** argv, std::string & sJsonFile, std::string & sProtoFile, std::string & sDirName, std::string & sMessageName)
{
    int iOpt = 0;
    while ((iOpt = getopt(argc, argv, "j:f:d:m:")) != EOF)
    {
        switch (iOpt)
        {
            case 'j':
                {
                    sJsonFile = optarg;
                    break;
                }
            case 'f':
                {
                    sProtoFile = optarg;
                    break;
                }
            case 'd':
                {
                    sDirName = optarg;
                    break;
                }
            case 'm':
                {
                    sMessageName = optarg;
                    break;
                }
            case 'h':
            case '?':
            default:
                {
                    return -1;
                }
        }
    }
    return 0;
}

int main(int argc, char ** argv)
{
    if (argc != 9)
    {
        PrintHelp(argv[0]);
        return 0;
    }

    std::string sJsonFile;
    std::string sProtoFile;
    std::string sDirName;
    std::string sMessageName;

    int ret = ParseOption(argc, argv, sJsonFile, sProtoFile, sDirName, sMessageName);

    if (0 != ret)
    {
        PrintHelp(argv[0]);
        return 0;
    }

    printf("JsonFile: %s, ProtoFile: %s, DirName: %s, MessageName: %s.\n",
        sJsonFile.c_str(), sProtoFile.c_str(), sDirName.c_str(), sMessageName.c_str());

    // Json文件转字符串
    jsontools::JsonUtils oUtils;
    std::string sJsonData = oUtils.ReadJsonFileToString(sJsonFile);

    // 打印json串
    printf("JsonData: %s.\n", sJsonData.c_str());

    static json2pblib::Json2PbLib oLib(sDirName);

    // 通过生成对应的message结构
    google::protobuf::Message * ptMsg = oLib.GetMessage(sProtoFile, sMessageName);

    if (ptMsg == NULL)
    {
        printf("ERR %s: GetMessage failed. pb_file : %s, dir_name : %s, message_name : %s.\n",
            __func__, sProtoFile.c_str(), sDirName.c_str(), sMessageName.c_str());
        return -1;
    }

    // 带有映射信息的json转pb功能
    ret = oLib.JsonStruct2PbStruct(sJsonData, ptMsg);

    if (0 != ret)
    {
        printf("jsonlib Json2Pb failed. json_file : %s, pb_file : %s, message_name : %s.\n",
            sJsonFile.c_str(), sProtoFile.c_str(), sMessageName.c_str());
        return -1;
    }

    // 输出结构化后的message结构
    printf("After jsonlib::Json2Pb, message is %s.", ptMsg->ShortDebugString().c_str());


    return 0;
}

//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

