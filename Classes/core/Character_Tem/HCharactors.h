#ifndef __H_CHARACTORS_H__
#define __H_CHARACTORS_H__
#include"cocos2d.h"
#include"HNPCTexts.h"
using namespace cocos2d;

/***********************************************************
Warning: 
Most of the functions or methods are not perfect currently,which need many corrections.
Their existence is to work properly and simply during the testing period.
���棺
����������ͷ���Ŀǰ�����������ģ��ں��ڽ����Ķ���
����Ŀǰ���ڵ�ԭ������Ϊ��ǰ���ܱȽϼ򵥵Ĳ���
************************************************************/

//class HCharactorBase, which serves as the base class of all Charactors subclasses.
class HCharactorsBase:public CCSprite
{
public:
	
	//two segments create method Seg1:
	static HCharactorsBase* create()
	{
		HCharactorsBase* pRet = new HCharactorsBase();
		if (pRet != NULL&&pRet->init())
     {
        pRet->autorelease();
		return pRet;
	 }
		else
	 {
		delete pRet;
		pRet=NULL;
		return NULL;
	 }
	}

	//two segments create method Seg2:
	virtual bool init(void);

	//At present it is useless, need more supplementaries
	//�˺���Ŀǰ���ã�������
	void setCPath(std::string cPath);

	//At present it is useless, need more supplementaries
	//�˺���Ŀǰ���ã�������
	CCString getCPath();

	//Currently the following 3 functions are the only way to insert image into Charactors. The picture should be the assembly of a set of movement.
	//���������������ĿǰΨһ�������ͼƬ�ķ�����ʹ�õ�ͼƬӦΪһϵ�ж���ͼƬ�ļ���
	/*Example to insert piction:
	NPC1=NPC::create(new Maid());
	NPC1->addImageUsingTextureCache("maid.png");
	NPC1->insertTextureSpriteFrames(32,48,4,4);
	NPC1->setInitialTexture();*/
	
	//Function1: addImage by picture path
	void addImageUsingTextureCache(const char *cPath);

	//Function2: insert textureSriteFrames by manually setting the arguments of spaces among subpictures
	//�ֶ�������ͼƬ��ľ���
	CCArray* insertTextureSpriteFrames(float width,float height,int row,int column);

	//Function3: set initial (or static) picture for the Charactor
	//�ֶ���������ľ�ֹʱ��ͼƬ
	void setInitialTexture();

	
	
	
protected:
	//There are four arrays each includes a set of walking items on one direction
	//������4�����飬ÿ�����鶼��������ĳ�����������ߵ�һЩ��ͼƬ֡
	CCArray *walkUp;
	CCArray *walkDown;
	CCArray *walkLeft;
	CCArray*walkRight;

	// obtain the direction the Charactor should go, while 1,2,3,4 represent down,left,right,up: down=1,left=2,right=3,up=4
    int directionCal(CCPoint currentPos, CCPoint targetPos);

	// using the num for direction to require the corresponding array, still down=1,left=2,right=3,up=4
	CCArray*sendDirectionArray(int num);

	// texture2D for the static picture of the Charactor
	CCTexture2D*texture;

	//useless currently
	CCString *characPath;

	//array includes total TextureSpriteFrames
	CCArray * TextureSpriteFrame;
	
	
private:
	
};


// class for main Charactor
class MainCharactor: public HCharactorsBase
{
public:
	static MainCharactor* create()
	{
		MainCharactor* pRet = new MainCharactor();
		
		if (pRet != NULL&&pRet->init())
        {
           pRet->autorelease();
		   return pRet;
		}
		else
		{
			delete pRet;
			pRet=NULL;
			return NULL;
		}
	}

	virtual bool init(void);
	// Insert the walking animation to the Charactor. 
	CCActionInterval* walkingAnimation(CCPoint clickPoint, CCPoint currentPoint);

	//only call when the Charactor stops to conduct a conversation.
	void stopForConversation(HCharactorsBase*target);
	
private:
	enum Direction
	{up=0,down,left,right};
	CCArray*reciever;
};


class NPC:public HCharactorsBase
{
public:
	
	virtual bool init(trial*NPCobj);

	static NPC* create(trial*name)
	{
		NPC* pRet = new NPC();
		
		if (pRet != NULL&&pRet->init(name))
        {
           pRet->autorelease();
		   return pRet;
		 }

		else
		{
			delete pRet;
			pRet=NULL;
			return NULL;
		}
	}

	//This function enables the NPC to move automatically according to the points set you send to them.
	//���������ʹNPC�Զ���������ĵ㼯���ƶ��������ڿڴ������е�NPC
	 bool setNPCMovement(CCPoint a,...);
	
	// the following six functions are to conduct the dialog box and dialog texts Warning��this function is incomplete, where bugs exist
	//���µ�������������Ի���ͶԻ����֣��˹����в����ƣ���bug
	void setTextIntoBox();
	void setTextContentByArray();
	void setTextOffBox();
	void ifSetConversationOn(bool On);
	bool iSConservationOn();
	bool ifAndSetBoxStatus();

	CCArray* textGroup;
	int count;
	int scale;
	bool _ifBoxOn;
	bool _ifOnConversation;
	CCLabelTTF * NPCnameLabel;
	CCSprite*textBox;

	~NPC()
	{
		CCSprite::~CCSprite();
		delete H_delete;
	}
private:
	trial* H_delete;
};












#endif //__H_CHARACTORS_H__