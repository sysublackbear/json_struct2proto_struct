#pragma once

#include <string>

namespace jsontools
{

class JsonUtils
{
public:
    JsonUtils();
    ~JsonUtils();

    std::string ReadJsonFileToString(const std::string & sJsonFile);


};

}
