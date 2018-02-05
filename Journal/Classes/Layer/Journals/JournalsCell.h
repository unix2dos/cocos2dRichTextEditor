//
//  JournalsCell.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#ifndef JournalsCell_hpp
#define JournalsCell_hpp


class CJournalsCell : public cocos2d::extension::TableViewCell
{
public:
    CJournalsCell();
    virtual ~CJournalsCell();
    CREATE_FUNC(CJournalsCell);
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
public:
    void updateCell(int idx);
private:
    Size m_winSize;
};

#endif /* JournalsCell_hpp */
