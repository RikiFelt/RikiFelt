from arknights_config import *
from arknights_util import ArkUtil


class ArkState:
    def __init__(self, arkWin, arkImg):
        self.arkWin = arkWin
        self.arkImg = arkImg

    def isValid(self):
        return self.arkWin.isValid() & self.arkImg.isValid()

    def getGameState(self, msg=False):
        state = State.Unknown
        if ArkUtil.findImage(self.arkImg.iconSanityRoT, self.arkWin.RoTRegion):
            state = State.Action
        elif ArkUtil.findImage(self.arkImg.iconBin, self.arkWin.RoTRegion):
            state = State.Prepare
        elif ArkUtil.findImage(self.arkImg.iconGear, self.arkWin.LoTRegion):
            state = State.Operation
        elif ArkUtil.findImage(self.arkImg.iconStar, self.arkWin.leftRegion):
            state = State.End
        elif ArkUtil.findImage(self.arkImg.iconLevelUp, self.arkWin.gameRegion):
            state = State.LevelUp
        elif ArkUtil.findImage(self.arkImg.iconNoSanity, self.arkWin.gameRegion):
            state = State.NoSanity
        else:
            state = State.Unknown

        if msg:
            print(f'当前状态:{state}')
        return state
