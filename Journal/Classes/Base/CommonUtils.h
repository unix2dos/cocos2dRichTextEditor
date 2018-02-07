//
//  CommonUtils.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#ifndef CommonUtils_hpp
#define CommonUtils_hpp


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
    return cocos2d::StringUtils::format("%d",timeStamp);
//    return "2016-01-02";
}


//解析服务器json
static Json::Value parseServerJson(std::string strJson)
{
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    Json::Value root;
    std::string errors;
    bool ok = reader->parse(strJson.c_str(), strJson.c_str() + strJson.size(), &root, &errors);
    delete reader;
    if (ok && root.isObject() && root.isMember("ret") && root.isMember("msg") && root.isMember("data"))
    {
        return root;
    }
    return Json::nullValue;
}



#endif /* CommonUtils_hpp */
