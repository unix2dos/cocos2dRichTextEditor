//
//  iOSRichView.h
//  Journal
//
//  Created by liuwei on 2018/2/10.
//

#ifndef iOSRichView_h
#define iOSRichView_h

enum class RichViewType
{
    none,
    write,
    show_self,
    show_others,
};

class iOSRichView : public CRichViewManager
{
public:
    iOSRichView();
    virtual ~iOSRichView();
public:
    virtual void writeJournal() override;
    virtual void showJournal(std::string strContext) override;
    virtual void closeJournal(std::string strContext) override;
private:
    void _enableRichView(bool enable);
    
private:
    RichViewType m_richviewType;
};

#endif /* iOSRichView_h */
