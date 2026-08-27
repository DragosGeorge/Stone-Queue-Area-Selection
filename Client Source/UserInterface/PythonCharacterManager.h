Search:

// Access Instance
void SelectInstance(DWORD VirtualID);
CInstanceBase* GetSelectedInstancePtr();

Add before:

#ifdef ENABLE_METIN_QUEUE_AREA_SELECTION
	bool GetMetinQueueScreenBounds(DWORD dwVID, RECT& rkRect) const;
#endif

Search:

void __RenderSortedDeadActorList();

Add after:

#ifdef ENABLE_METIN_QUEUE_AREA_SELECTION
	void __UpdateMetinQueueScreenBounds();
#endif


Search:

TCharacterInstanceMap m_kAliveInstMap;

Add after:

#ifdef ENABLE_METIN_QUEUE_AREA_SELECTION
	std::map<DWORD, RECT> m_kMetinQueueScreenBounds;
#endif