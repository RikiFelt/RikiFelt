import time
from arknights_config import *
from arknights_util import ArkUtil


class ArkLogic:
    def __init__(self, arkWin, arkImg, arkState):
        self.arkWin = arkWin
        self.arkImg = arkImg
        self.arkState = arkState

    def isValid(self):
        return self.arkWin.isValid() & self.arkImg.isValid() & self.arkState.isValid()

    def getGameState(self):
        return self.arkState.getGameState()

    def precheck(self):
        if not self.isValid():
            return False
        state = self.getGameState()
        if state == State.Unknown or state == State.Error:
            print(f"当前游戏状态{state}不正，脚本关闭")
            return False
        return True

    def enableAgent(self):
        if self.getGameState() == State.Action:
            # 常规图，查看右上角是否有星星，右下角开始行动是否有理智图标
            if ArkUtil.findImage(self.arkImg.iconStar, self.arkWin.RoTRegion) and \
                    ArkUtil.findImage(self.arkImg.iconSanity, self.arkWin.RoBRegion):
                return self.__enableAgent_Normal()
            else:
                # 愚人号活动对应
                return self.__enableAgent_StultiferaNavis()
        else:
            print("未处于开始行动界面，脚本关闭")
            return False

    # 常规图的开启代理指挥
    def __enableAgent_Normal(self):
        return self.__enableAgent(self.arkImg.iconCross,
                                  self.arkImg.iconAgentLock,
                                  self.arkImg.iconAgentOff)

    # 愚人号活动对应的开启代理指挥
    def __enableAgent_StultiferaNavis(self):
        return self.__enableAgent(self.arkImg.iconCross_SN,
                                  self.arkImg.iconAgentLock_SN,
                                  self.arkImg.iconAgentOff_SN)

    def __enableAgent(self, iconCross, iconAgentLock, iconAgentOff):
        count = 0
        while True:
            if ArkUtil.findImage(iconCross, self.arkWin.RoBRegion):
                if count > 0:
                    print('开启代理指挥成功')
                return True
            else:
                btm_lock = ArkUtil.getImageLocation(iconAgentLock, self.arkWin.RoBRegion)
                btm_agent = ArkUtil.getImageLocation(iconAgentOff, self.arkWin.RoBRegion)
                if btm_lock is not None:
                    print("该关卡无法代理指挥，请确认关卡信息")
                    return False
                elif btm_agent is None:
                    print("未找到代理指挥确认框，请查看游戏分辨率是否正常")
                    return False
                else:
                    count = count + 1
                    print(f"第{count}次尝试开启代理指挥")
                    ArkUtil.click(btm_agent, sleep=1)
                    if count >= enableAgentCount:
                        print(f"尝试{count}次开启代理指挥失败，脚本关闭")
                        return False

    def actionStart(self):
        print("关卡界面")
        state = State.Action
        if self.enableAgent():
            btm = ArkUtil.getImageLocation(self.arkImg.iconSanity, self.arkWin.RoBRegion)
            if btm is None:
                # 愚人号活动对应
                btm = ArkUtil.getImageLocation(self.arkImg.iconSanity_SN, self.arkWin.RoBRegion)
            if btm is None:
                state = State.Error
                print("未找到'开始行动'，请查看游戏分辨率是否正常")
            else:
                ArkUtil.click(btm, sleep=1)
        else:
            state = State.Error
        return state

    def prepareStart(self):
        print("编队界面")
        state = State.Prepare
        btm = ArkUtil.getImageLocation(
            self.arkImg.iconPrepare,
            self.arkWin.RoBRegion)
        if btm is None:
            state = State.Error
            print("未找到'开始行动'，请查看游戏分辨率是否正常")
        else:
            ArkUtil.click(btm, sleep=1)
        return state

    def operation(self):
        print(f'代理指挥中：{time.ctime()}')
        time.sleep(10.0)
        return State.Operation

    def operationEnd(self):
        print("结算界面")
        ArkUtil.click(self.arkWin.endClickRegion, sleep=2)
        return State.End

    def level_up(self):
        print("升级啦!!!")
        ArkUtil.click(self.arkWin.endClickRegion, sleep=2)

    def noSanity(self):
        state = State.NoSanity
        print("没有理智")
        if UseSanity:
            btm_Y = ArkUtil.getImageLocation(
                self.arkImg.iconY, self.arkWin.RoBRegion)
            if btm_Y is None:
                state = State.Error
                print("无法使用理智药")
            else:
                print("使用理智药,代理继续")
                ArkUtil.click(btm_Y, sleep=2)
        else:
            state = State.Error
            print('不使用理智药，代理结束')
            btm_X = ArkUtil.getImageLocation(
                self.arkImg.iconX, self.arkWin.RoBRegion)
            if btm_X is not None:
                ArkUtil.click(btm_X, sleep=2)
        return state

    def unknown(self):
        print(f'未知界面，等待下一个画面中：{time.ctime()}')
        time.sleep(5)
