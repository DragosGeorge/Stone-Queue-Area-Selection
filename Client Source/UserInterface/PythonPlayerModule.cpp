Search:

PyObject* playerSetMouseFunc(PyObject* poSelf, PyObject* poArgs)

Add before:

#if defined(__AUTO_QUQUE_ATTACK__) && defined(ENABLE_METIN_QUEUE_AREA_SELECTION)
PyObject* playerSelectMetinQueueScreenRect(PyObject* poSelf, PyObject* poArgs)
{
	int iLeft, iTop, iRight, iBottom;
	if (!PyTuple_GetInteger(poArgs, 0, &iLeft) ||
		!PyTuple_GetInteger(poArgs, 1, &iTop) ||
		!PyTuple_GetInteger(poArgs, 2, &iRight) ||
		!PyTuple_GetInteger(poArgs, 3, &iBottom))
		return Py_BadArgument();

	return Py_BuildValue("i", CPythonPlayer::Instance().AutoFarmQueueSelectScreenRect(iLeft, iTop, iRight, iBottom));
}
#endif

Search:

{ "SetMouseState", playerSetMouseState, METH_VARARGS },

Add after:

#if defined(__AUTO_QUQUE_ATTACK__) && defined(ENABLE_METIN_QUEUE_AREA_SELECTION)
		{ "SelectMetinQueueScreenRect", playerSelectMetinQueueScreenRect, METH_VARARGS },
#endif