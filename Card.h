#pragma once
#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"

USING_NS_CC;

// ��ɫ����
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // ÷��
    CST_DIAMONDS,   // ����
    CST_HEARTS,     // ����
    CST_SPADES,     // ����
    CST_NUM_CARD_SUIT_TYPES
};

// ��������
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

// ����λ������
enum CardLocation {
    CL_PILE,   // ���ƶ�
    CL_HAND    // ������
};

class Card : public Node {
public:
    static Card* createWithFaceAndSuit(CardFaceType face, CardSuitType suit);

    bool initWithFaceAndSuit(CardFaceType face, CardSuitType suit);

    // �����¼��ص�
    bool onTouchBegan(Touch* touch, Event* event);

    // ��ȡ���Ƶ����ֺͻ�ɫ
    CardFaceType getFace() const { return m_face; }
    CardSuitType getSuit() const { return m_suit; }

    // ���úͻ�ȡ����λ��
    void setLocation(CardLocation location) { m_location = location; }
    CardLocation getLocation() const { return m_location; }

    // ���ÿ����Ƿ�ɴ���
    void setTouchable(bool touchable) { m_touchable = touchable; }

private:
    CardFaceType m_face;
    CardSuitType m_suit;
    bool m_touchable;

    CardLocation m_location;

    Sprite* m_cardBackground;
    Sprite* m_faceSprite;
    Sprite* m_suitSprite;

    // ���캯��˽�л�����ֱֹ��ʹ�� new Card
    Card();
    Card(const Card&);
    Card& operator=(const Card&);
};

#endif // __CARD_H__