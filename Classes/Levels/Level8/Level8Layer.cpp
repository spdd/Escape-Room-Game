#include "Level8Layer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

Level8Layer::Level8Layer() : MainGameLayer() 
	
{
	this->mInvObject1 = nullptr;
	this->mSwitch = nullptr;
	this->mPol = nullptr;
	this->levelNumber = 8;
	this->isSwitchOn = false;
	this->switchOnCount = 0;
}
Level8Layer::~Level8Layer() 
{
	CC_SAFE_RELEASE_NULL(mInvObject1);
	CC_SAFE_RELEASE_NULL(mPol);
	CC_SAFE_RELEASE_NULL(mSwitch);
}

void Level8Layer::onNodeLoaded(Node * node,  NodeLoader * nodeLoader) {
	MainGameLayer::onNodeLoaded(node, nodeLoader);
	setInvGameObjectTouchListener();
	setGameObjectTouchListener();
	// callbacks for inventory touches
	//inventoryLogicCallback = [this]() { this->item2FuncCallback(); };
}

/**
*	Assigh sprite member from ccbi file
**/
bool Level8Layer::onAssignCCBMemberVariable(Ref * pTarget, const char * pMemberVariableName, Node * pNode) {
	MainGameLayer::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mInvObject1", Sprite *, this->mInvObject1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "switch", Sprite *, this->mSwitch);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "pol", Sprite *, this->mPol);
    return false;
}

#pragma mark Inventory Items Callback Logic

#pragma mark Game Objects Touch Logic

void Level8Layer::setInvGameObjectTouchListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [](Touch* touch, Event* event) {
        // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
		//onTouchBegan(touch, event);
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        //Check the click area
        if (rect.containsPoint(locationInNode))
        {			
			//target->setColor(Color3B::RED);
			log("sprite tag:%d  began... x = %f, y = %f",target->getTag(),  locationInNode.x, locationInNode.y);
            target->setOpacity(180);
            return true;
        }
        return false;
    };

	listener1->onTouchMoved = [](Touch* touch, Event* event){};

    //Process the touch end event
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        //log("sprite onTouchesEnded.. ");

		if (target == this->mInvObject1  && this->mInvObject1->isVisible()) {
			if(!this->isInvItem1Selected) {
				// todo set simple inventory images
				int index = this->getItemIndexNumber();
				this->invItem1Index = getItemIndexNumber();
				mInvItem1->setTexture(TextureCache::getInstance()->addImage("item_key.png"));

				std::function<void()> func = [this] { this->gameInvObject1FuncCallback(); };
				this->addFunctor(index, func);
				this->itemsSolutionArray[index] = 1;
			}
			else {
				
			}
        }

    };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->mInvObject1);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mInvItem2);
}

void Level8Layer::setGameObjectTouchListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        //Check the click area
        if (rect.containsPoint(locationInNode))
        {			
            //target->setOpacity(180);
            return true;
        }
        return false;
    };

	listener1->onTouchMoved = [](Touch* touch, Event* event){};

    //Process the touch end event
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        //log("sprite onTouchesEnded.. ");

		if (target == this->mSwitch) {
			if(!this->isSwitchOn) {
				this->isSwitchOn = true;
				this->mSwitch->setTexture(TextureCache::getInstance()->addImage("switch_l8_d.png"));
				this->mPol->setVisible(true);
				if(switchOnCount == 1) {
					this->mDoor->setVisible(false);
					this->mInvObject1->setVisible(true);
				} else if(switchOnCount == 2) {
					this->mDoor->setVisible(true);
				}
				switchOnCount++;

			} else {
				this->isSwitchOn = false;
				this->mSwitch->setTexture(TextureCache::getInstance()->addImage("switch_l8_n.png"));
				this->mPol->setVisible(false);
			}

        }
    };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->mSwitch);
}

void Level8Layer::gameInvObject1FuncCallback()
{
	if(this->invItem1Index != -1 && !this->isInvItem1Selected) {
		this->itemsSpriteArray[this->invItem1Index]->setTexture(TextureCache::getInstance()->addImage("item_key_sel.png"));
	
		this->isInvItem1Selected = true;
		this->isOpenDoor = true;
	} else if(this->invItem1Index != -1 && this->isInvItem1Selected) {
		this->itemsSpriteArray[this->invItem1Index]->setTexture(TextureCache::getInstance()->addImage("item_key.png"));
		this->isInvItem1Selected = false;
		this->isOpenDoor = false;
	}
}

void Level8Layer::gameInvObjToGameObj()
{
	
}