//
//  LayerArchive.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#include "Journal.h"
#include "Define.h"
#include "LayerMain.h"
#include "ArchiveCell.h"
#include "DataManager.h"
#include "DataJournal.h"
#include "LayerArchive.h"

#define JOURNALEX_CELL_SIZE 5 //table显示的cell数量


CLayerArchive::CLayerArchive()
:m_pTableView(nullptr)
,m_fTableViewHeight(0.0f)
{
    
}


CLayerArchive::~CLayerArchive(){
    
}


bool CLayerArchive::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerArchive::_initUI()
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



void CLayerArchive::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
}

void CLayerArchive::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{
}

void CLayerArchive::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
    auto tableCell = dynamic_cast<CArchiveCell*>(cell);
    if (!tableCell)
    {
        return;
    }
}

cocos2d::Size CLayerArchive::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return Size(m_winSize.width, m_fTableViewHeight/JOURNALEX_CELL_SIZE);
}

cocos2d::extension::TableViewCell* CLayerArchive::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = CArchiveCell::create();
        cell->setContentSize(tableCellSizeForIndex(table,idx));
    }
    dynamic_cast<CArchiveCell*>(cell)->updateCell(static_cast<int>(idx));
    return cell;
}

ssize_t CLayerArchive::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    auto data = CDataManager::getInstance()->getDataJournal()->getArchives();
    return data.size();
}


void CLayerArchive::updateUI()
{
    m_pTableView->reloadData();
}

void CLayerArchive::endWithHttpData(eHttpType myType, HttpResponseInfo rep)
{
    if (myType == eHttpType::archive_get)
    {
        if (rep.status == eHttpStatus::success)
        {
            
        }
    }
}
