#include "Card.h"

using namespace cocos2d;

Card::Card() : m_touchable(false), m_location(CL_PILE) {
}

Card* Card::createWithFaceAndSuit(CardFaceType face, CardSuitType suit) {
    Card* card = new Card();
    if (card && card->initWithFaceAndSuit(face, suit)) {
        card->autorelease();
        return card;
    }
    CC_SAFE_DELETE(card);
    return nullptr;
}

bool Card::initWithFaceAndSuit(CardFaceType face, CardSuitType suit) {
    if (!Node::init()) {
        return false;
    }

    m_face = face;
    m_suit = suit;
    m_touchable = true;
    m_location = CL_PILE;

    // 加载卡牌背景
    m_cardBackground = Sprite::create("C:/Users/zwx/Desktop/work/test/Resources/res/card_general.png");
    this->addChild(m_cardBackground);

    // 设置卡牌的大小
    this->setContentSize(m_cardBackground->getContentSize());

    // 创建牌面值图片
    std::string facePath;
    switch (face) {
    case CardFaceType::CFT_ACE: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_A.png"; break;
    case CardFaceType::CFT_TWO: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_2.png"; break;
    case CardFaceType::CFT_THREE: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_3.png"; break;
    case CardFaceType::CFT_FOUR: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_4.png"; break;
    case CardFaceType::CFT_FIVE: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_5.png"; break;
    case CardFaceType::CFT_SIX: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_6.png"; break;
    case CardFaceType::CFT_SEVEN: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_7.png"; break;
    case CardFaceType::CFT_EIGHT: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_8.png"; break;
    case CardFaceType::CFT_NINE: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_9.png"; break;
    case CardFaceType::CFT_TEN: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_10.png"; break;
    case CardFaceType::CFT_JACK: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_J.png"; break;
    case CardFaceType::CFT_QUEEN: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_Q.png"; break;
    case CardFaceType::CFT_KING: facePath = "C:/Users/zwx/Desktop/work/test/Resources/res/number/big_black_K.png"; break;
    default: facePath = ""; break;
    }
    if (!facePath.empty()) {
        m_faceSprite = Sprite::create(facePath);
        if (m_faceSprite) {
            //m_faceSprite->setAnchorPoint(Vec2(0,0));
            m_faceSprite->setPosition(m_cardBackground->getContentSize().width - 250, m_cardBackground->getContentSize().height - 375);
            this->addChild(m_faceSprite, 1);
        }
        else {
            log("Failed to load face sprite: %s", facePath.c_str());
        }
    }

    // 创建花色图片
    std::string suitPath;
    switch (suit) {
    case CST_CLUBS: suitPath = "C:/Users/zwx/Desktop/work/test/Resources/res/suits/club.png"; break;
    case CST_DIAMONDS: suitPath = "C:/Users/zwx/Desktop/work/test/Resources/res/suits/diamond.png"; break;
    case CST_HEARTS: suitPath = "C:/Users/zwx/Desktop/work/test/Resources/res/suits/heart.png"; break;
    case CST_SPADES: suitPath = "C:/Users/zwx/Desktop/work/test/Resources/res/suits/spade.png"; break;
    default: suitPath = ""; break;
    }
    if (!suitPath.empty()) {
        m_suitSprite = Sprite::create(suitPath);
        if (m_suitSprite) {
            m_suitSprite->setAnchorPoint(Vec2(0,1));
            m_suitSprite->setPosition(Vec2(50, m_cardBackground->getContentSize().height - 200));
            this->addChild(m_suitSprite, 1);
        }
        else {
            log("Failed to load suit sprite: %s", suitPath.c_str());
        }
    }

    // 使卡牌可触摸
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

bool Card::onTouchBegan(Touch* touch, Event* event) {
    if (!m_touchable) return false;

    Rect cardRect = this->getBoundingBox();
    if (cardRect.containsPoint(touch->getLocation())) {
        // 根据卡牌位置进行不同处理
        switch (m_location) {
        case CL_PILE:
            // 牌堆中的触摸逻辑
            log("Touched a card in the pile");
            break;
        case CL_HAND:
            // 手牌中的触摸逻辑
            log("Touched a card in the hand");
            break;
        }
        return true;
    }
    return false;
}