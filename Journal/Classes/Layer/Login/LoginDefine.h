//
//  LoginDefine.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/9.
//

#ifndef LoginDefine_hpp
#define LoginDefine_hpp



static Node* _crateEditBox(std::string strBg, std::string strHolder)
{
    auto node = Node::create();
    auto pBack = Sprite::create(strBg);
    node->addChild(pBack);
    
    auto editBoxSize = Size(460, 110);
    ui::EditBox* r = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create());
    r->setPlaceHolder(strHolder.c_str());
    r->setPlaceholderFontSize(40);
    r->setPlaceholderFontColor(Color3B::GRAY);
    r->setFontColor(Color3B::BLACK);
    r->setFontSize(40);
    r->setMaxLength(16);
    r->setName("EditBox");
    r->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);
    r->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
    //    r->setDelegate(this);
    node->addChild(r);
    return node;
}

#endif /* LoginDefine_hpp */
