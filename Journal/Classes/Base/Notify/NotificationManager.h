//
//  NotificationManager.h
//  ReadingFriends
//
//  Created by liuwei on 16/7/4.
//
//

#ifndef NotificationManager_h
#define NotificationManager_h


enum class NOTIFY_TYPE;
class CNotificationDelegate
{
public:
    CNotificationDelegate(){}
    virtual ~CNotificationDelegate(){}
public:
    virtual void notifyEvent(NOTIFY_TYPE type, void* pVoid = nullptr) = 0;
};

struct NOTIFY_DELEGATE
{
    bool bDelete;
    NOTIFY_TYPE type;
    CNotificationDelegate* pDelegate;
};

class NotificationManager
{
protected:
    NotificationManager();
    ~NotificationManager();
public:
    static NotificationManager* getInstance();
private:
    static NotificationManager* m_pNotificationManager;
public:
    /* 通知函数，参数为类型加数据 */
    void notify(NOTIFY_TYPE type, void* pVoid = nullptr);
public:
    /* 注册通知 */
    void registerNotification(NOTIFY_TYPE type, CNotificationDelegate* pDelegate);
    /* 反注通知 */
    void unregisterNotification(NOTIFY_TYPE type, CNotificationDelegate* pDelegate);
protected:
    /* 存放通知 */
    void _pushDelegate(NOTIFY_TYPE type, NOTIFY_DELEGATE& delegate);
    /* 判断通知是否存在 */
    bool _isDelegateExistForAdd(NOTIFY_TYPE type, CNotificationDelegate* pDelegate);
private:
    std::map<NOTIFY_TYPE, std::list<NOTIFY_DELEGATE> > m_mapDelegate;
    std::list<NOTIFY_DELEGATE> m_listAddDelegateBackup;
    int m_iNotifyingCount;
};

#endif /* NotificationManager_h */
