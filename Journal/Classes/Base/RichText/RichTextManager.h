#ifndef __CRichTextManager__
#define __CRichTextManager__


class CRichTextManager
{
public:
    static CRichTextManager* getInstance();
public:
    void writeJournal();
    void showJournal(std::string strContext);
    void exitRichView();
private:
    void _enableRichView(bool enable);
    
private:
    CRichTextManager();
    ~CRichTextManager();
};


#endif /* Recorder_hpp */
