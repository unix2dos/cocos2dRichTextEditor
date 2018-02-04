#ifndef __CBASE_IDFA_H__
#define __CBASE_IDFA_H__

class CRichText
{
public:
    static CRichText* getInstance();
public:
    void haha();

private:
    CRichText();
    ~CRichText();
    static CRichText* m_pRichText;
};


#endif /* Recorder_hpp */
