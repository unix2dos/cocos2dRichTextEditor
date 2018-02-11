//
//  iOSRichViewManager.h
//  Journal
//
//  Created by liuwei on 2018/2/10.
//

#ifndef iOSRichViewManager_h
#define iOSRichViewManager_h

enum class RichViewType
{
    none,
    write,
    show_self,
    show_others,
};


class iOSRichViewManager : public CRichViewManager
{
public:
    iOSRichViewManager();
    virtual ~iOSRichViewManager();
    
public:
    virtual void initRichView() override;
    virtual void writeJournal() override;
    virtual void showJournal(std::string strContext) override;
    virtual void closeJournal(std::string strContext) override;
    
private:
    void _enableRichView(bool enable);
    RichViewType m_richviewType;
};

#endif /* iOSRichViewManager_h */
