#include "json2pblib.h"

#include <stdio.h>
#include "test.pb.h"

namespace json2pblib
{

google::protobuf::DynamicMessageFactory Json2PbLib::m_oFactory;
Json2PbLib::Json2PbLib(const std::string & sDirName):m_oImporter(&m_oDiskSourceTree, m_ptErrorCollector)
{
    m_ptErrorCollector = NULL;
    m_oDiskSourceTree.MapPath("", "/home/mikedeng/QQMail/mmtenpay/mmpaybasic/mmpayentrust/scripts/json2pb/proto");
}


Json2PbLib::~Json2PbLib()
{
}


google::protobuf::Message * Json2PbLib::GetMessage(
    const std::string & sProtoFile,
    const std::string & sMessageName )
{
    printf("%s:pb_file : %s, msg_file : %s.\n",
        __func__, sProtoFile.c_str(), sMessageName.c_str());

    m_oImporter.Import("descriptor.proto");
    m_oImporter.Import(sProtoFile);

    const google::protobuf::Descriptor * ptDescriptor = m_oImporter.pool()->FindMessageTypeByName(sMessageName);
    
    if (NULL == ptDescriptor)
    {
        return NULL;
    }

    google::protobuf::DynamicMessageFactory oFactory;
    google::protobuf::Message * ptMsg = oFactory.GetPrototype(ptDescriptor)->New();
    return ptMsg;
}


int Json2PbLib::JsonStruct2PbStruct(const std::string & sJsonData, google::protobuf::Message * ptMsg)
{
    int ret = 0;

    rapidjson::Document oJsonObj;

    // 字符串转json对象
    ret = StringToJsonObj(sJsonData, oJsonObj);
    if (0 != ret)
    {
        printf("ERR: StringToJsonObj failed. ret is %d.\n", ret);
        return ret;
    }

    JsonChangeToPbStruct(oJsonObj, ptMsg);

    return ret;
}


int Json2PbLib::StringToJsonObj(const std::string & sJsonData, rapidjson::Document & oJsonObj)
{
    std::string sTmpJsonData;

    sTmpJsonData = sJsonData;

    if (sTmpJsonData.empty())
    {
        sTmpJsonData = "{}";
    }

    rapidjson::StringStream ssJson(sTmpJsonData.c_str());

    oJsonObj.ParseStream(ssJson);

    if (oJsonObj.HasParseError())
    {
        return -__LINE__;
    }

    return 0;
}


void Json2PbLib::JsonChangeToPbStruct(rapidjson::Document & oJsonObj, google::protobuf::Message * ptMsg)
{
    // 遍历所有的field
    const google::protobuf::Descriptor * ptDesc = ptMsg->GetDescriptor();
    const google::protobuf::Reflection * ptReflect = ptMsg->GetReflection();

    for (int i = 0; i < ptDesc->field_count(); i++)
    {
        const google::protobuf::FieldDescriptor * ptFieldDesc = ptDesc->field(i);
        std::string sJsonPos = ptFieldDesc->options().GetExtension(test::json_key);

        if (!sJsonPos.empty())
        {
            // 在json结构树里面寻找对应的结构
            rapidjson::Value *v = rapidjson::Pointer(sJsonPos.c_str()).Get(oJsonObj);

            // 赋值
            // 由于判断的数据类型太多了,不做分支判断了
            if (v->IsBool())
            {
                ptReflect->SetBool(ptMsg, ptFieldDesc, v->GetBool());
            }
            else if (v->IsInt())
            {
                ptReflect->SetInt32(ptMsg, ptFieldDesc, v->GetInt());
            }
            else if (v->IsUint())
            {
                ptReflect->SetUInt32(ptMsg, ptFieldDesc, v->GetUint());
            }
            else if (v->IsInt64())
            {
                ptReflect->SetInt64(ptMsg, ptFieldDesc, v->GetInt64());
            }
            else if (v->IsUint64())
            {
                ptReflect->SetUInt64(ptMsg, ptFieldDesc, v->GetUint64());
            }
            else if (v->IsDouble())
            {
                ptReflect->SetDouble(ptMsg, ptFieldDesc, v->GetDouble());
            }
            else if (v->IsString())
            {
                ptReflect->SetString(ptMsg, ptFieldDesc, v->GetString());
            }
        }
    }

}



}


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

