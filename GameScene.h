#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Scene {
public:
    static Scene* createGameScene();
    virtual bool init() override;
    CREATE_FUNC(GameScene);
private:
    void setupCardsFromJson();
};

#endif // __GAME_SCENE_H__