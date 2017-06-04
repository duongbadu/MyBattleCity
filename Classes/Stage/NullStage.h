#ifndef _NullStage_H_
#define _NullStage_H_


#include "StageBase.h"

/**
*	@class : NullStage
*	@brief : ���ڱ�ʶ�յ���״̬
*/
class NullStage : public StageBase
{
public:
	virtual void update(float dt) override
	{

	}

	NullStage()
		: StageBase(nullptr, StageNull, nullptr)
	{

	}
};

#endif
