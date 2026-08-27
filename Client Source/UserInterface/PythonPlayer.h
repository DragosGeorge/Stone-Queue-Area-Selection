Search:

DWORD		GetAutoFarmTarget();
void		SetTotalAutoFarmCount(const BYTE bCount) { bTotalQuqueAutoAttack = bCount; }

Add after:

#ifdef ENABLE_METIN_QUEUE_AREA_SELECTION
	int			AutoFarmQueueSelectScreenRect(long lLeft, long lTop, long lRight, long lBottom);
#endif