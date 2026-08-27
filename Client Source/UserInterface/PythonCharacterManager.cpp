Search:

__RenderSortedDeadActorList();

Add before:

#ifdef ENABLE_METIN_QUEUE_AREA_SELECTION
	__UpdateMetinQueueScreenBounds();
#endif

Search:

void CPythonCharacterManager::RenderShadowMainInstance()

Add before:

#ifdef ENABLE_METIN_QUEUE_AREA_SELECTION
void CPythonCharacterManager::__UpdateMetinQueueScreenBounds()
{
	m_kMetinQueueScreenBounds.clear();
	for (TCharacterInstanceMap::const_iterator it = m_kAliveInstMap.begin(); it != m_kAliveInstMap.end(); ++it)
	{
		CInstanceBase* pkInstance = it->second;
		if (!pkInstance || !pkInstance->IsStone() || pkInstance->IsDead())
			continue;

		const D3DXVECTOR3& c_rPosition = pkInstance->GetGraphicThingInstanceRef().GetPosition();
		const float fHeight = float(pkInstance->GetGraphicThingInstanceRef().GetHeight());
		float fBaseX, fBaseY, fCenterX, fCenterY, fTopX, fTopY;
		CPythonGraphic::Instance().ProjectPosition(c_rPosition.x, c_rPosition.y, c_rPosition.z, &fBaseX, &fBaseY);
		CPythonGraphic::Instance().ProjectPosition(c_rPosition.x, c_rPosition.y, c_rPosition.z + fHeight * 0.5f, &fCenterX, &fCenterY);
		CPythonGraphic::Instance().ProjectPosition(c_rPosition.x, c_rPosition.y, c_rPosition.z + fHeight, &fTopX, &fTopY);

		const float fProjectedHeight = fabsf(fBaseY - fTopY);
		const float fRawHalfWidth = fProjectedHeight * 0.35f;
		const float fHalfWidth = fRawHalfWidth < 20.0f ? 20.0f : (fRawHalfWidth > 80.0f ? 80.0f : fRawHalfWidth);
		RECT kRect;
		kRect.left = long(fCenterX - fHalfWidth);
		kRect.right = long(fCenterX + fHalfWidth);
		kRect.top = long(fTopY < fBaseY ? fTopY : fBaseY);
		kRect.bottom = long(fTopY > fBaseY ? fTopY : fBaseY);
		m_kMetinQueueScreenBounds[it->first] = kRect;
	}
}

bool CPythonCharacterManager::GetMetinQueueScreenBounds(DWORD dwVID, RECT& rkRect) const
{
	std::map<DWORD, RECT>::const_iterator it = m_kMetinQueueScreenBounds.find(dwVID);
	if (it == m_kMetinQueueScreenBounds.end())
		return false;
	rkRect = it->second;
	return true;
}
#endif