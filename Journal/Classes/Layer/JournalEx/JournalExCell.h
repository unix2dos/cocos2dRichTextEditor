//
//  JournalExCell.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#ifndef JournalExCell_hpp
#define JournalExCell_hpp

class CJournalExCell : public cocos2d::extension::TableViewCell
{
public:
    CJournalExCell();
    virtual ~CJournalExCell();
    CREATE_FUNC(CJournalExCell);
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
public:
    void updateCell(const std::vector<Journal_Info>&info, int idx);
private:
    Size m_winSize;
};

#endif /* JournalExCell_hpp */
