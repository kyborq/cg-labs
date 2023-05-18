#include <vector>
#include <windows.h>

#include "CAWindow.h"
#include "CFigure.h"

#pragma once
class CHangman : public CAWindow
{
public:
	CHangman(CAWindow& window);

	void Start(HDC hdc) override;
	void Update() override;

private:
	int m_tries;
	std::vector<CFigure> m_graphics;
};

