#include "utils.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <stdlib.h>

namespace jsontools
{

JsonUtils::JsonUtils()
{
}


JsonUtils::~JsonUtils()
{
}


std::string JsonUtils::ReadJsonFileToString(const std::string & sJsonFile)
{
    std::ifstream iFile(sJsonFile.c_str());
    std::ostringstream oBuf;
    char ch;
    while (oBuf && iFile.get(ch))
    {
        oBuf.put(ch);
    }

    return oBuf.str();
}



}

//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

