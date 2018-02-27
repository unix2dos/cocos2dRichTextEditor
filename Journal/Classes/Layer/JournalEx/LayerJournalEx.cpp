//
//  LayerJournalEx.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#include "Journal.h"
#include "Define.h"
#include "LayerMain.h"
#include "RichViewManager.h"
#include "DataManager.h"
#include "DataJournal.h"
#include "JournalExCell.h"
#include "LayerComment.h"
#include "LayerJournalEx.h"

#define JOURNALEX_CELL_SIZE 4.5 //table显示的cell数量


CLayerJournalEx::CLayerJournalEx()
:m_pTableView(nullptr)
,m_fTableViewHeight(0.0f)
,m_iJournalId(-1)
{
    
}


CLayerJournalEx::~CLayerJournalEx(){
    
}


bool CLayerJournalEx::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerJournalEx::_initUI()
{
    m_winSize = Director::getInstance()->getWinSize();
    
    m_fTableViewHeight = m_winSize.height - MAIN_BOTTOM_HEIGHT;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_fTableViewHeight -= 50;
#endif
    
    m_pTableView = TableView::create(this, Size(m_winSize.width, m_fTableViewHeight));
    m_pTableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    m_pTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    m_pTableView->setDelegate(this);
    m_pTableView->setPositionY(MAIN_BOTTOM_HEIGHT);
    this->addChild(m_pTableView);
    m_pTableView->reloadData();
}



void CLayerJournalEx::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
}

void CLayerJournalEx::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{
}

void CLayerJournalEx::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
    auto tableCell = dynamic_cast<CJournalExCell*>(cell);
    if (!tableCell)
    {
        return;
    }
    if (CRichViewManager::getInstance()->getRichViewType() != RichViewType::none)
    {
        return;
    }
    auto data = CDataManager::getInstance()->getDataJournal()->getJournalsEx();
    int idx = static_cast<int>(cell->getIdx());
    CRichViewManager::getInstance()->showJournal(data[idx], false);
}

cocos2d::Size CLayerJournalEx::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return Size(m_winSize.width, m_fTableViewHeight/JOURNALEX_CELL_SIZE);
}

cocos2d::extension::TableViewCell* CLayerJournalEx::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = CJournalExCell::create();
        cell->setContentSize(tableCellSizeForIndex(table,idx));
        cell->setUserObject(this);
    }
    auto data = CDataManager::getInstance()->getDataJournal()->getJournalsEx();
    dynamic_cast<CJournalExCell*>(cell)->updateCell(data, static_cast<int>(idx));
    return cell;
}

ssize_t CLayerJournalEx::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    auto data = CDataManager::getInstance()->getDataJournal()->getJournalsEx();
    return data.size();
}


void CLayerJournalEx::endWithHttpData(eHttpType myType, HttpResponseInfo rep)
{
    if (myType == eHttpType::comment_list)
    {
        if (rep.status == eHttpStatus::success)
        {
            if (!Director::getInstance()->getRunningScene()->getChildByName("CLayerComment"))
            {
                auto layer = CLayerComment::create();
                layer->setJournalId(m_iJournalId);
                layer->setName("CLayerComment");
                Director::getInstance()->getRunningScene()->addChild(layer);//直接加到最上面
            }
        }
    }
}

void CLayerJournalEx::requestCommentList()
{
    std::string str = StringUtils::format("/jid=%d", m_iJournalId);
    CHttpManager::getInstance()->HttpGet(eHttpType::comment_list, str);
}

void CLayerJournalEx::requestLikeJournal()
{
}

void CLayerJournalEx::updateUI()
{
    m_pTableView->reloadData();
}

void CLayerJournalEx::setJournalId(int journalId)
{
    m_iJournalId = journalId;
}
