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

    # 事前检查
    def precheck(self):
        if not self.isValid():
            return False
        state = self.getGameState()
        if state == State.Unknown or state == State.Error:
            print(f"当前游戏状态{state}不正，脚本关闭")
            return False
        if not self.enableAgent():
            print("开启代理指挥失败，脚本关闭")
            return False
        return True

    # 开启代理指挥
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

    # 开启代理指挥
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

    # 关卡界面，点击开始行动
    def actionStart(self):
        print("关卡界面")
        state = State.Action
        # 在右下角找"行动开始“下面的理智图标
        btm = ArkUtil.getImageLocation(self.arkImg.iconSanity, self.arkWin.RoBRegion)
        if btm is None:
            # 愚人号活动对应
            btm = ArkUtil.getImageLocation(self.arkImg.iconSanity_SN, self.arkWin.RoBRegion)
        if btm is None:
            state = State.Error
            print("未找到'开始行动'，请查看游戏分辨率是否正常")
        else:
            ArkUtil.click(btm, sleep=1)
        return state

    # 编队界面，点击开始行动
    def prepareStart(self):
        print("编队界面")
        state = State.Prepare
        if not ArkUtil.findAndClick(self.arkImg.iconPrepare,
                                    self.arkWin.RoBRegion,
                                    sleep=2):
            state = State.Error
            print("未找到'开始行动'，请查看游戏分辨率是否正常")
        return state

    # 代理指挥中
    def operation(self):
        print(f'代理指挥中：{time.ctime()}')
        time.sleep(10.0)
        return State.Operation

    # 代理指挥结束
    def operationEnd(self):
        print("结算界面")
        ArkUtil.click(self.arkWin.endClickRegion, sleep=2)
        return State.End

    # 升级界面
    def level_up(self):
        print("升级啦!!!")
        ArkUtil.click(self.arkWin.endClickRegion, sleep=2)

    # 补充理智界面
    def noSanity(self):
        state = State.NoSanity
        print("没有理智")
        if UseSanity and UseStone:
            # 使用理智药，源石恢复理智
            if ArkUtil.findImage(self.arkImg.iconClearSelect, self.arkWin.RoBRegion):
                state = self.__noSanity_clickY("理智药")
            elif ArkUtil.findImage(self.arkImg.iconStone, self.arkWin.RoTRegion):
                # todo 没有源石的时候图标会怎么样，有待测试
                state = self.__noSanity_clickY("源石")
            else:
                state = self.__noSanity_clickX("理智药或源石")
        elif UseSanity and not UseStone:
            # 只使用理智药恢复理智
            if ArkUtil.findImage(self.arkImg.iconClearSelect, self.arkWin.RoBRegion):
                state = self.__noSanity_clickY("理智药")
            else:
                state = self.__noSanity_clickX("理智药")
        elif not UseSanity and UseStone:
            # 只使用源石恢复理智，一般不存在这种状况
            # todo 没有源石的时候图标会怎么样，有待测试
            if ArkUtil.findImage(self.arkImg.iconStone, self.arkWin.RoTRegion):
                state = self.__noSanity_clickY("源石")
            else:
                state = self.__noSanity_clickX("源石")
        else:
            # 不恢复理智
            state = self.__noSanity_clickX()
        return state

    # 补充理智界面，点击X按钮
    def __noSanity_clickX(self, use_item=""):
        if len(use_item) == 0:
            print("不恢复理智，代理结束")
        else:
            print(f"无法使用{use_item}恢复理智，代理结束")
        ArkUtil.findAndClick(self.arkImg.iconX, self.arkWin.RoBRegion, sleep=2)
        return State.Error

    # 补充理智界面，点击Y按钮
    def __noSanity_clickY(self, use_item):
        if ArkUtil.findAndClick(self.arkImg.iconY, self.arkWin.RoBRegion, sleep=2):
            print(f"使用{use_item}恢复理智,代理继续")
            return State.NoSanity
        else:
            print(f"无法使用{use_item}恢复理智，代理结束")
            return State.Error

    # 未知界面
    def unknown(self):
        print(f'未知界面，等待下一个画面中：{time.ctime()}')
        time.sleep(5)
