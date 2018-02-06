//
//  LayerJournalCassify.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#ifndef LayerJournalCassify_hpp
#define LayerJournalCassify_hpp

class CLayerJournalClassify: public Layer
{
public:
    CLayerJournalClassify();
    virtual ~CLayerJournalClassify();
    CREATE_FUNC(CLayerJournalClassify);
    bool init() override;
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
    virtual void onEnter() override;
    virtual void onExit() override;
private:
    void _initUI();
    void _onClickLabel(int index);
    void _closeUI();
private:
    Size m_winSize;
    std::vector<Sprite*> m_pLabels;
    Sprite* m_pSelect;
};

#endif /* LayerJournalCassify_hpp */
