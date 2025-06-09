#include "GameScene.h"
#include "Card.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "json/document.h"
#include <string>

Scene* GameScene::createGameScene() {
    return GameScene::create();
}

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 创建白色背景层
    auto background = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(background, -1);

    // 其他初始化代码...

    GameScene::setupCardsFromJson();

    return true;
}

// "C:/Users/zwx/Desktop/work/test/Classes/cards_layout.json"

void GameScene::setupCardsFromJson() {
    log("Resources directory: %s", FileUtils::getInstance()->getWritablePath().c_str());

    auto data = FileUtils::getInstance()->getDataFromFile("C:/Users/zwx/Desktop/work/test/Classes/cards_layout.json");
    if (data.isNull()) {
        log("Failed to load JSON file: cards_layout.json");
        log("Please check the file path and ensure the file exists in the resources directory.");
        return;
    }

    std::string jsonStr((char*)data.getBytes(), data.getSize());

    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    if (doc.HasParseError()) {
        log("Failed to parse JSON file: Parse error at offset %zu", doc.GetErrorOffset());
        return;
    }

    // 处理 Playfield 中的卡牌
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
        const rapidjson::Value& playfield = doc["Playfield"];
        for (const auto& cardItem : playfield.GetArray()) {
            if (cardItem.IsObject()) {
                CardFaceType face = static_cast<CardFaceType>(cardItem["CardFace"].GetInt());
                CardSuitType suit = static_cast<CardSuitType>(cardItem["CardSuit"].GetInt());
                Vec2 position(cardItem["Position"]["x"].GetDouble(), cardItem["Position"]["y"].GetDouble());

                auto card = Card::createWithFaceAndSuit(face, suit);
                if (card != nullptr) {
                    card->setPosition(position);
                    card->setLocation(CL_PILE);
                    this->addChild(card);
                    log("Card created: Face = %d, Suit = %d, Position = (%f, %f)", static_cast<int>(face), static_cast<int>(suit), position.x, position.y);
                }
                else {
                    log("Failed to create card: Face = %d, Suit = %d", static_cast<int>(face), static_cast<int>(suit));
                }
            }
        }
    }

    // 处理 Stack 中的卡牌
    if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
        const rapidjson::Value& stack = doc["Stack"];
        for (const auto& cardItem : stack.GetArray()) {
            if (cardItem.IsObject()) {
                CardFaceType face = static_cast<CardFaceType>(cardItem["CardFace"].GetInt());
                CardSuitType suit = static_cast<CardSuitType>(cardItem["CardSuit"].GetInt());
                Vec2 position(cardItem["Position"]["x"].GetDouble(), cardItem["Position"]["y"].GetDouble());

                auto card = Card::createWithFaceAndSuit(face, suit);
                if (card != nullptr) {
                    card->setPosition(position);
                    card->setLocation(CL_HAND);
                    this->addChild(card);
                    log("Card created: Face = %d, Suit = %d, Position = (%f, %f)", static_cast<int>(face), static_cast<int>(suit), position.x, position.y);
                }
                else {
                    log("Failed to create card: Face = %d, Suit = %d", static_cast<int>(face), static_cast<int>(suit));
                }
            }
        }
    }
}