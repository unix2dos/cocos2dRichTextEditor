//
//  iOSRichViewManager.h
//  Journal
//
//  Created by liuwei on 2018/2/10.
//

#ifndef iOSRichViewManager_h
#define iOSRichViewManager_h


class iOSRichViewManager : public CRichViewManager
{
public:
    iOSRichViewManager();
    virtual ~iOSRichViewManager();
    
public:
    virtual void initRichView() override;
    virtual void newJournal() override;
    virtual void showJournal(const Journal_Info& info, bool myself) override;
    virtual void closeJournal() override;
    
private:
    void _enableRichView(bool enable);
};

#endif /* iOSRichViewManager_h */
