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
    bool isPublic;//是否公开
    bool isLike;//我是否点赞
    int lickCount;//点赞数量
    
    Journal_Info()
    {
        strId = "";
        strTitle = "";
        strContent = "";
        createTime = 0;
        modifyTime = 0;
        isPublic = true;
        isLike = false;
        lickCount = 0;
    }
};




struct Comment_Info
{
    std::string strId;//评论id
    std::string strContent;//评论内容
    std::string strJournalId;//日志id,可以用来校验
        
    std::string strUserAlias;//评论作者
    std::string strReplyUserAlias;//这条评论回复的谁
   
    int createTime;//创建时间
    int modifyTime;//修改时间
    
    Comment_Info()
    {
        strId = "";
        strContent = "";
        strJournalId = "";
        strUserAlias = "";
        strReplyUserAlias = "";
        createTime = 0;
        modifyTime = 0;
    }
};

class HttpResponseInfo;
class CDataJournal
{
public:
    CDataJournal();
    ~CDataJournal();
    
public:
    const std::vector<Journal_Info>& getJournals();
    const std::vector<Journal_Info>& getArchives();
    const std::vector<Journal_Info>& getJournalsEx();
    const std::vector<Comment_Info>& getJournalComments();
    
public:
    void parseJournalsData(HttpResponseInfo rep);
    void parseAddJournal(HttpResponseInfo rep);
    void parseUpdateJournal(HttpResponseInfo rep);
    
    void parseArchives(HttpResponseInfo rep);
    void parseJournalsEx(HttpResponseInfo rep);
    
    void parseCommentsList(HttpResponseInfo rep);
    void parseCommentAdd(HttpResponseInfo rep);
    
public:
    void requestJournallist();
    void requestAddJournal(const Journal_Info& info);
    void requestUpdateJournal(const Journal_Info& info);
    void requestDeleteJournal(std::string journalId);
    
    void requestArchive();
    void requestJournalsEx();
    
    void requestCommentList(std::string journalId);
    void requestAddComment(std::string text);
    void requestReplyComment(std::string commentId, std::string text);
    
    void requestAddLikeJournal(std::string journalId);
    void requestDelLikeJournal(std::string journalId);
    
    void requestLikeComment(std::string commentId);
    
private:
    std::vector<Journal_Info> m_vecJournals;//只有add,update时更新, 用的时候自己排序
    
    std::vector<Journal_Info> m_vecArchives; //archive, 暂不排序
    
    std::vector<Journal_Info> m_vecJournalsEx;//推荐消息, 暂不排序
    
    std::vector<Comment_Info> m_vecComments;//只是一条日志的所有评论,用的时候自己排序

private:
    std::string m_strJournalId;//存下日志id,因为进去评论了,以后会用到
};

#endif /* DataJournal_hpp */
