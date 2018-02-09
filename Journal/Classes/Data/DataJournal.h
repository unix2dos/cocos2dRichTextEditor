//
//  DataJournal.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#ifndef DataJournal_hpp
#define DataJournal_hpp

struct Journal_Info
{
    std::string strTitle;//标题
    std::string strContent;//内容
    int createTime;//创建时间
    std::vector<std::string> vecMessage;//留言
    int lickCount;//点赞数量
    bool isPublic;//是否公开
    
    Journal_Info()
    {
        strTitle = "";
        strContent = "";
        createTime = 0;
        vecMessage.clear();
        lickCount = 0;
        isPublic = true;
    }
};

class HttpResponseInfo;
class CDataJournal
{
public:
    CDataJournal();
    ~CDataJournal();
    
public:
    void parseServeData(HttpResponseInfo rep);
    const std::vector<Journal_Info>& getJournals();
    
private:
    std::vector<Journal_Info> m_vecJournals;
};

#endif /* DataJournal_hpp */
