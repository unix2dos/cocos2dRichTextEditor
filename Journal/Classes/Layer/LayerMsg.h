#ifndef __LYAERMSG_H__
#define __LYAERMSG_H__

class CLayerMsg: public cocos2d::Layer
{
public:
    CLayerMsg();
    virtual ~CLayerMsg();
    static CLayerMsg* create(std::string msg);
    bool init(std::string msg);
public:
    static void showMsg(std::string msg);
};

#endif // __SCENELOGIN_H__
