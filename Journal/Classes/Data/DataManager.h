//
//  DataManager.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#ifndef DataManager_hpp
#define DataManager_hpp


class CDataUser;
class CDataJournal;
class HttpResponseInfo;
enum class eHttpType;
class CDataManager : public Ref
{
public:
    static CDataManager* getInstance();
    static void destroyInstance();
    
public:
    CDataManager();
    ~CDataManager();
    void init();
    void free();
public:
    void parseServeData(eHttpType myType, HttpResponseInfo rep);
public:
    CDataUser* getDataUser();
    CDataJournal* getDataJournal();
private:
    CDataUser* m_pDataUser;
    CDataJournal* m_pDataJournal;
};

#endif /* DataManager_hpp */
