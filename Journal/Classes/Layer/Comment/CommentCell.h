//
//  CommentCell.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/26.
//

#ifndef CommentCell_hpp
#define CommentCell_hpp

class CCommentCell : public cocos2d::extension::TableViewCell
{
public:
    CCommentCell();
    virtual ~CCommentCell();
    CREATE_FUNC(CCommentCell);
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
public:
    void updateCell(int idx);
private:
    Size m_winSize;
};

#endif /* CommentCell_hpp */
