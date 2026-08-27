Search:

        player.SetGameWindow(self)


Add after:

        if app.ENABLE_METIN_QUEUE_AREA_SELECTION:
            self.metinQueueAreaSelecting = False
            self.metinQueueAreaStart = (0, 0)
            self.metinQueueAreaVisuals = []
            self.__CreateMetinQueueAreaVisuals()

Search:

    def Close(self):


Add after:

        if app.ENABLE_METIN_QUEUE_AREA_SELECTION:
            self.__CancelMetinQueueAreaSelection()

Search:

    def OnMouseLeftButtonDown(self):

Add before:

    if app.ENABLE_METIN_QUEUE_AREA_SELECTION:
        def __CreateMetinQueueAreaVisuals(self):
            fill = ui.Box("TOP_MOST")
            fill.SetParent(self)
            fill.AddFlag("not_pick")
            fill.SetColor(grp.GenerateColor(0.15, 0.55, 1.0, 0.18))
            fill.Hide()
            self.metinQueueAreaVisuals.append(fill)

            for i in xrange(4):
                border = ui.Bar("TOP_MOST")
                border.SetParent(self)
                border.AddFlag("not_pick")
                border.SetColor(grp.GenerateColor(0.2, 0.65, 1.0, 0.95))
                border.Hide()
                self.metinQueueAreaVisuals.append(border)

        def __UpdateMetinQueueAreaVisuals(self, mouseX, mouseY):
            startX, startY = self.metinQueueAreaStart
            left = min(startX, mouseX)
            top = min(startY, mouseY)
            width = max(1, abs(mouseX - startX))
            height = max(1, abs(mouseY - startY))

            fill, topBorder, bottomBorder, leftBorder, rightBorder = self.metinQueueAreaVisuals
            fill.SetPosition(left, top)
            fill.SetSize(width, height)
            topBorder.SetPosition(left, top)
            topBorder.SetSize(width, 2)
            bottomBorder.SetPosition(left, top + height - 2)
            bottomBorder.SetSize(width, 2)
            leftBorder.SetPosition(left, top)
            leftBorder.SetSize(2, height)
            rightBorder.SetPosition(left + width - 2, top)
            rightBorder.SetSize(2, height)
            for visual in self.metinQueueAreaVisuals:
                visual.Show()

        def __CancelMetinQueueAreaSelection(self):
            self.metinQueueAreaSelecting = False
            for visual in self.metinQueueAreaVisuals:
                visual.Hide()

Search:

    def OnMouseLeftButtonDown(self):

Add after:

        if app.ENABLE_METIN_QUEUE_AREA_SELECTION and not mouseModule.mouseController.isAttached():
            if app.IsPressed(app.DIK_LCONTROL) or app.IsPressed(app.DIK_RCONTROL):
                self.metinQueueAreaSelecting = True
                self.metinQueueAreaStart = wndMgr.GetMousePosition()
                self.__UpdateMetinQueueAreaVisuals(*self.metinQueueAreaStart)
                return True

Search:

    def OnMouseLeftButtonUp(self):

Add after:

        if app.ENABLE_METIN_QUEUE_AREA_SELECTION and self.metinQueueAreaSelecting:
            startX, startY = self.metinQueueAreaStart
            endX, endY = wndMgr.GetMousePosition()
            self.__CancelMetinQueueAreaSelection()
            if abs(endX - startX) >= 5 and abs(endY - startY) >= 5:
                addedCount = player.SelectMetinQueueScreenRect(startX, startY, endX, endY)
                chat.AppendChat(chat.CHAT_TYPE_INFO, "[Metin Queue] %d target(s) added." % addedCount)
            return True

Search:

    def OnUpdate(self):
        app.UpdateGame()

Add after:

        if app.ENABLE_METIN_QUEUE_AREA_SELECTION and self.metinQueueAreaSelecting:
            self.__UpdateMetinQueueAreaVisuals(*wndMgr.GetMousePosition())