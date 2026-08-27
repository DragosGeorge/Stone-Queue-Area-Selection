Search:

void CPythonPlayer::AutoFarmLoop()

Add before:

#ifdef ENABLE_METIN_QUEUE_AREA_SELECTION
int CPythonPlayer::AutoFarmQueueSelectScreenRect(long lLeft, long lTop, long lRight, long lBottom)
{
	if (lLeft > lRight)
		std::swap(lLeft, lRight);
	if (lTop > lBottom)
		std::swap(lTop, lBottom);

	struct SMetinCandidate
	{
		DWORD dwVID;
		float fDistanceSq;
	};

	std::vector<SMetinCandidate> kCandidates;
	CPythonCharacterManager& rkChrMgr = CPythonCharacterManager::Instance();
	CInstanceBase* pkMain = NEW_GetMainActorPtr();
	TPixelPosition kMainPosition;
	if (pkMain)
		pkMain->NEW_GetPixelPosition(&kMainPosition);

	for (CPythonCharacterManager::CharacterIterator it = rkChrMgr.CharacterInstanceBegin();
		it != rkChrMgr.CharacterInstanceEnd(); ++it)
	{
		CInstanceBase* pkInstance = *it;
		if (!pkInstance || !pkInstance->IsStone() || pkInstance->IsDead())
			continue;

		const DWORD dwVID = pkInstance->GetVirtualID();
		if (std::find(m_vecQuqueAutoAttack.begin(), m_vecQuqueAutoAttack.end(), dwVID) != m_vecQuqueAutoAttack.end())
			continue;

		RECT kScreenBounds;
		if (!rkChrMgr.GetMetinQueueScreenBounds(dwVID, kScreenBounds))
			continue;
		if (kScreenBounds.right < lLeft || kScreenBounds.left > lRight ||
			kScreenBounds.bottom < lTop || kScreenBounds.top > lBottom)
			continue;

		TPixelPosition kPosition;
		pkInstance->NEW_GetPixelPosition(&kPosition);

		const float fDX = pkMain ? kPosition.x - kMainPosition.x : 0.0f;
		const float fDY = pkMain ? kPosition.y - kMainPosition.y : 0.0f;
		SMetinCandidate kCandidate = { dwVID, fDX * fDX + fDY * fDY };
		kCandidates.push_back(kCandidate);
	}

	std::sort(kCandidates.begin(), kCandidates.end(), [](const SMetinCandidate& a, const SMetinCandidate& b) {
		return a.fDistanceSq < b.fDistanceSq;
	});

	int iAdded = 0;
	for (const SMetinCandidate& rkCandidate : kCandidates)
	{
		if (m_vecQuqueAutoAttack.size() >= bTotalQuqueAutoAttack)
			break;
		if (AutoFarmQuqueSet(true, rkCandidate.dwVID))
			++iAdded;
	}
	return iAdded;
}
#endif

