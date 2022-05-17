
#pragma once
#include "stdafx.h"

const ULONG MAX_SAMPLE_COUNT = 50;		// 50ȸ�� ������ ó���ð��� �����Ͽ� ����� ����.

class CGameTimer {
public:
	CGameTimer();
	virtual ~CGameTimer();

	void Start() {}
	void Stop() {}
	void Reset();
	void Tick(float fLockFPS = 0.f);
	unsigned long GetFrameRate(LPTSTR lpszString = nullptr, int nCharacters = 0);
	float GetTimeElapsed();
};

