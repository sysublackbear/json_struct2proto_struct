#pragma once

#include <string>

#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/message.h>
#include <google/protobuf/dynamic_message.h>

#include "rapidjson/writer.h"
#include "rapidjson/schema.h"

namespace json2pblib
{

class Json2PbLib
{
public:
    Json2PbLib(const std::string & sDirName);
    ~Json2PbLib();

    google::protobuf::Message * GetMessage(
        const std::string & sProtoFile,
        const std::string & sMessageFile );

    int JsonStruct2PbStruct(const std::string & sJsonData, google::protobuf::Message * ptMsg);

private:
    int StringToJsonObj(const std::string & sJsonData, rapidjson::Document & oJsonObj);
    void JsonChangeToPbStruct(rapidjson::Document & oJsonObj, google::protobuf::Message * ptMsg);

private:
    google::protobuf::compiler::MultiFileErrorCollector * m_ptErrorCollector;
    google::protobuf::compiler::DiskSourceTree m_oDiskSourceTree;
    google::protobuf::compiler::Importer m_oImporter;
    static google::protobuf::DynamicMessageFactory m_oFactory;

};

}

