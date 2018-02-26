//
//  LayerComment.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/26.
//

#include "Journal.h"
#include "Define.h"
#include "LayerMain.h"
#include "CommentCell.h"
#include "LayerComment.h"


#define COMMENT_CELL_SIZE 11 //table显示的cell数量


CLayerComment::CLayerComment()
:m_pTableView(nullptr)
,m_fTableViewHeight(0.0f)
{
    
}


CLayerComment::~CLayerComment(){
    
}


bool CLayerComment::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerComment::_initUI()
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



void CLayerComment::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
}

void CLayerComment::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{
}

void CLayerComment::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
    auto tableCell = dynamic_cast<CCommentCell*>(cell);
    if (!tableCell)
    {
        return;
    }
}

cocos2d::Size CLayerComment::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return Size(m_winSize.width, m_fTableViewHeight/COMMENT_CELL_SIZE);
}

cocos2d::extension::TableViewCell* CLayerComment::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = CCommentCell::create();
        cell->setContentSize(tableCellSizeForIndex(table,idx));
    }
    dynamic_cast<CCommentCell*>(cell)->updateCell(static_cast<int>(idx));
    return cell;
}

ssize_t CLayerComment::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return 20;
}
