
#pragma once
#include "stdafx.h"

const ULONG MAX_SAMPLE_COUNT = 50;		// 50회의 프레임 처리시간을 누적하여 평균을 낸다.

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

