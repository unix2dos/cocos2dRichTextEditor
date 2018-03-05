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
    void updateCell(const std::vector<Journal_Info>&info, int idx);
    std::string getJournalId();
private:
    Size m_winSize;
    std::string m_strJournalId;
};

#endif /* JournalsCell_hpp */
