//
//  NotificationManager.cpp
//  ReadingFriends
//
//  Created by liuwei on 16/7/4.
//
//

#include "Define.h"
#include "NotificationManager.h"


NotificationManager* NotificationManager::m_pNotificationManager = NULL;
NotificationManager::NotificationManager()
{
    m_iNotifyingCount = 0;
}

NotificationManager::~NotificationManager()
{
}

NotificationManager* NotificationManager::getInstance()
{
    if(m_pNotificationManager == NULL)
    {
        m_pNotificationManager = new NotificationManager;
    }
    return m_pNotificationManager;
}


void NotificationManager::notify(NOTIFY_TYPE type, void* pVoid)
{
    std::map<NOTIFY_TYPE, std::list<NOTIFY_DELEGATE> >::iterator itNofity = m_mapDelegate.find(type);
    if(itNofity == m_mapDelegate.end())
    {
        return;
    }
    
    m_iNotifyingCount++;
    
    for(std::list<NOTIFY_DELEGATE>::iterator itDelegate = itNofity->second.begin(); itDelegate != itNofity->second.end();)
    {
        if(itDelegate->bDelete)
        {
            itDelegate = itNofity->second.erase(itDelegate);
        }
        else
        {
            itDelegate->pDelegate->notifyEvent(type, pVoid);
            if(itDelegate->bDelete)
            {
                itDelegate = itNofity->second.erase(itDelegate);
            }
            else
            {
                itDelegate++;
            }
        }
    }
    
    if(itNofity->second.size() == 0)
    {
        m_mapDelegate.erase(itNofity);
    }
    
    if(m_listAddDelegateBackup.size() > 0)
    {
        for(std::list<NOTIFY_DELEGATE>::iterator itBackup = m_listAddDelegateBackup.begin(); itBackup != m_listAddDelegateBackup.end(); itBackup++)
        {
            _pushDelegate(itBackup->type, *itBackup);
        }
        
        m_listAddDelegateBackup.clear();
    }
    
    m_iNotifyingCount--;
}

void NotificationManager::registerNotification(NOTIFY_TYPE type, CNotificationDelegate* pDelegate)
{
    if(pDelegate == NULL)
    {
        return;
    }
    
    if(_isDelegateExistForAdd(type, pDelegate))
    {
        return;
    }
    
    NOTIFY_DELEGATE delegate;
    delegate.bDelete = false;
    delegate.type = type;
    delegate.pDelegate = pDelegate;
    
    if(m_iNotifyingCount > 0)
    {
        m_listAddDelegateBackup.push_back(delegate);
    }
    else
    {
        _pushDelegate(type, delegate);
    }
}

void NotificationManager::unregisterNotification(NOTIFY_TYPE type, CNotificationDelegate* pDelegate)
{
    if(pDelegate == NULL)
    {
        return;
    }
    
    std::map<NOTIFY_TYPE, std::list<NOTIFY_DELEGATE> >::iterator itNofity = m_mapDelegate.find(type);
    if(itNofity == m_mapDelegate.end())
    {
        return;
    }
    
    for(std::list<NOTIFY_DELEGATE>::iterator itDelegate = itNofity->second.begin(); itDelegate != itNofity->second.end(); itDelegate++)
    {
        if(itDelegate->pDelegate == pDelegate)
        {
            if(m_iNotifyingCount > 0)
            {
                itDelegate->bDelete = true;
            }
            else
            {
                itNofity->second.erase(itDelegate);
            }
            
            break;
        }
    }
    
    if(m_listAddDelegateBackup.size() > 0)
    {
        for(std::list<NOTIFY_DELEGATE>::iterator itBackup = m_listAddDelegateBackup.begin(); itBackup != m_listAddDelegateBackup.end();)
        {
            if(itBackup->type == type && itBackup->pDelegate == pDelegate)
            {
                itBackup = m_listAddDelegateBackup.erase(itBackup);
            }
            else
            {
                itBackup++;
            }
        }
    }
}

void NotificationManager::_pushDelegate(NOTIFY_TYPE type, NOTIFY_DELEGATE& delegate)
{
    std::map<NOTIFY_TYPE, std::list<NOTIFY_DELEGATE> >::iterator itNofity = m_mapDelegate.find(type);
    if(itNofity == m_mapDelegate.end())
    {
        std::list<NOTIFY_DELEGATE> listDelegate;
        listDelegate.push_back(delegate);
        m_mapDelegate[type] = listDelegate;
    }
    else
    {
        itNofity->second.push_back(delegate);
    }
}

bool NotificationManager::_isDelegateExistForAdd(NOTIFY_TYPE type, CNotificationDelegate* pDelegate)
{
    std::map<NOTIFY_TYPE, std::list<NOTIFY_DELEGATE> >::iterator itNofity = m_mapDelegate.find(type);
    if(itNofity == m_mapDelegate.end())
    {
        return false;
    }
    
    for(std::list<NOTIFY_DELEGATE>::iterator itDelegate = itNofity->second.begin(); itDelegate != itNofity->second.end(); itDelegate++)
    {
        if(itDelegate->pDelegate == pDelegate)
        {
            itDelegate->bDelete = false;
            return true;
        }
    }
    
    return false;
}
