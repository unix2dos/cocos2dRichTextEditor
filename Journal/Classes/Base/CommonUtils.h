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


#endif /* CommonUtils_hpp */
