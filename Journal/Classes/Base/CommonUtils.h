//
//  CommonUtils.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#ifndef CommonUtils_hpp
#define CommonUtils_hpp
#include <regex>

// 获取时间戳
static int getTimeStamp()
{
    timeval tm;
    gettimeofday(&tm, NULL);
    return static_cast<int>(tm.tv_sec);// 单位：秒
    //    return tm.tv_usec; // 单位：毫秒
}

// 格式化时间戳
static std::string getTimeString(int timeStamp)
{
    time_t rawtime = timeStamp;
    struct tm * dt;
    char buffer [30];
    dt = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", dt);
    return std::string(buffer);
}


//解析json
static Json::Value parseJson(std::string strJson)
{
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    Json::Value root;
    std::string errors;
    bool ok = reader->parse(strJson.c_str(), strJson.c_str() + strJson.size(), &root, &errors);
    delete reader;
    if (ok)
    {
        return root;
    }
    return Json::nullValue;
}


//解析服务器json
static Json::Value parseServeJson(std::string strJson)
{
    Json::Value root = parseJson(strJson);
    if (root != Json::nullValue && root.isObject() && root.isMember("ret") && root.isMember("msg") && root.isMember("data"))
    {
        return root;
    }
    return Json::nullValue;
}



//构建json
static std::string buildJson(Json::Value root)
{
    Json::StreamWriterBuilder builder;
    builder.settings_["indentation"] = "";
    string strJson = Json::writeString(builder, root);
    return strJson;
}



//移除html tags
static std::string removeHtmlTags(std::string html)
{
    std::string str = html;
    std::regex e1 ("<[^>]*>");
    str = std::regex_replace (str, e1, " ");
    
    std::regex e2 ("&nbsp;");
    str = std::regex_replace (str, e2, " ");

    return str;
}


#endif /* CommonUtils_hpp */
