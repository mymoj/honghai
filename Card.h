#pragma once
#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"

USING_NS_CC;

// 花色类型
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // 梅花
    CST_DIAMONDS,   // 方块
    CST_HEARTS,     // 红桃
    CST_SPADES,     // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};

// 正面类型
enum class CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

// 卡牌位置类型
enum CardLocation {
    CL_PILE,   // 在牌堆
    CL_HAND    // 在手牌
};

class Card : public Node {
public:
    static Card* createWithFaceAndSuit(CardFaceType face, CardSuitType suit);

    bool initWithFaceAndSuit(CardFaceType face, CardSuitType suit);

    // 触摸事件回调
    bool onTouchBegan(Touch* touch, Event* event);

    // 获取卡牌的数字和花色
    CardFaceType getFace() const { return m_face; }
    CardSuitType getSuit() const { return m_suit; }

    // 设置和获取卡牌位置
    void setLocation(CardLocation location) { m_location = location; }
    CardLocation getLocation() const { return m_location; }

    // 设置卡牌是否可触摸
    void setTouchable(bool touchable) { m_touchable = touchable; }

private:
    CardFaceType m_face;
    CardSuitType m_suit;
    bool m_touchable;

    CardLocation m_location;

    Sprite* m_cardBackground;
    Sprite* m_faceSprite;
    Sprite* m_suitSprite;

    // 构造函数私有化，防止直接使用 new Card
    Card();
    Card(const Card&);
    Card& operator=(const Card&);
};

#endif // __CARD_H__