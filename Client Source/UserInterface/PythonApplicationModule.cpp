#ifdef ENABLE_METIN_QUEUE_AREA_SELECTION
	PyModule_AddIntConstant(poModule, "ENABLE_METIN_QUEUE_AREA_SELECTION", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_METIN_QUEUE_AREA_SELECTION", 0);
#endif