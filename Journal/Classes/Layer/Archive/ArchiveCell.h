//
//  ArchiveCell.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/7.
//

#ifndef ArchiveCell_hpp
#define ArchiveCell_hpp

class CArchiveCell : public cocos2d::extension::TableViewCell
{
public:
    CArchiveCell();
    virtual ~CArchiveCell();
    CREATE_FUNC(CArchiveCell);
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
public:
    void updateCell(int idx);
private:
    Size m_winSize;
};

#endif /* ArchiveCell_hpp */
