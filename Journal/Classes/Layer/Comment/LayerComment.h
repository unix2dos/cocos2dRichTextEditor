//
//  LayerComment.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/26.
//

#ifndef LayerComment_hpp
#define LayerComment_hpp

#define COMMENT_INPUT_HEIGHT   100 //评论框高度
#define COMMENT_NAV_HEIGHT     80  //评论伪导航栏高度

#define COMMENT_WIDTH_OFFSET   200 //评论条目宽度差值

#define COMMENT_HEIGHT_MIN     50  //评论条目最小高度
#define COMMENT_HEIGHT_PADDING 160 //评论条目加的延长

#include "HttpManager.h"


enum class CommentType
{
    none,
    add,
    reply,
};

class CLayerComment: public Layer
, public cocos2d::extension::TableViewDataSource
, public cocos2d::extension::TableViewDelegate
, public CDataHttpDelegate
{
public:
    CLayerComment();
    virtual ~CLayerComment();
    CREATE_FUNC(CLayerComment);
    bool init() override;
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)override ;
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override;
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)override;
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table) override;
    virtual void endWithHttpData(eHttpType myType, HttpResponseInfo rep) override;
    virtual void onEnter() override;
public:
    void setCommentType(CommentType type);
    void replyComment(int idx);
    void likeComment(int idx);
private:
    void _initUI();
    void _addComment();
private:
    Size m_winSize;
    float m_fTableViewHeight;
    cocos2d::extension::TableView* m_pTableView;
private:
    CommentType m_type;
    ui::EditBox* m_editBox;
    std::string m_strReplyCommentId;//存下来现在回复的id,因为即将会发送请求
    std::string m_strPlaceholder;
};

#endif /* LayerComment_hpp */
