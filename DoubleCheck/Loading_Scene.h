#pragma once
#include "State.h"
#include <atomic>


class Loading_Scene : public State
{
public:
	Loading_Scene();
	virtual void Load() override;
	virtual void Update(float dt) override;

	virtual void UnLoad() override;

	void Set_Done(bool toggle)
	{
		done = toggle;
	}

private:
	Object* volatile image;
	std::atomic<bool> done;
};