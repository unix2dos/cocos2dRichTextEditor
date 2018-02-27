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
    std::string strId;//id
    std::string strTitle;//标题
    std::string strContent;//内容
    int createTime;//创建时间
    int modifyTime;//修改时间
    int lickCount;//点赞数量
    bool isPublic;//是否公开
    
    Journal_Info()
    {
        strId = "";
        strTitle = "";
        strContent = "";
        createTime = 0;
        modifyTime = 0;
        lickCount = 0;
        isPublic = true;
    }
};

struct Comment_Info
{
    std::string strId;
    std::string strContent;
    std::string strUserId;
    std::string strJournalId;
    int createTime;//创建时间
    int modifyTime;//修改时间
};

class HttpResponseInfo;
class CDataJournal
{
public:
    CDataJournal();
    ~CDataJournal();
    
public:
    void parseJournalsData(HttpResponseInfo rep);
    void parseAddJournal(HttpResponseInfo rep);
    void parseUpdateJournal(HttpResponseInfo rep);
    
    void parseJournalsEx(HttpResponseInfo rep);
    void parseCommentsList(HttpResponseInfo rep);
    
    const std::vector<Journal_Info>& getJournals();
    const std::vector<Journal_Info>& getJournalsEx();
    const std::vector<Comment_Info>& getJournalComments();
    
private:
    std::vector<Journal_Info> m_vecJournals;//只有add,update时更新, 用的时候自己排序
    std::vector<Journal_Info> m_vecJournalsEx;//推荐消息, 不排序
    std::vector<Comment_Info> m_vecComments;//只是一条日志的所有评论,用的时候自己排序
};

#endif /* DataJournal_hpp */
