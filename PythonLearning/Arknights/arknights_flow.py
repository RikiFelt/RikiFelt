from arknights_config import *
from arknights_util import ArkUtil


class ArkFlow:
    def __init__(self, arkLogic):
        self.arkLogic = arkLogic
        self.total_count = 0
        self.current_count = 0
        self.agent = False

    def isValid(self):
        return self.arkLogic.isValid()

    def start(self, count=0):
        print('明日方舟自动代理指挥脚本开始')
        if self.isValid():
            if count > 0:
                # 测试用，循环count次
                self.startAction(count)
            else:
                # 实际用，通过控制台输入循环次数
                print('请输入一个大于0的整数')
                count = ArkUtil.getInputInt()
                while count > 0:
                    self.startAction(count)
                    print('是否继续执行脚本：')
                    print('是：请输入一个大于0的整数')
                    print('否：请输入0')
                    count = ArkUtil.getInputInt()
        else:
            input()
        print('脚本结束')

    def startAction(self, loop_count):
        if not self.arkLogic.precheck():
            return
        self.total_count += loop_count
        for count in range(loop_count):
            self.current_count += 1
            print(f'第{self.current_count}次代理指挥开始({self.current_count}/{self.total_count})')
            if not self.actionLoop():
                print(f'第{self.current_count}次代理指挥出错')
                break
            print(f'第{self.current_count}次代理指挥结束')
        print("代理指挥结束")

    def actionLoop(self):
        end_loop = False
        while True:
            state = self.arkLogic.getGameState()
            if state == State.Action and end_loop:
                break
            elif state == State.Action and not self.agent:
                self.agent = self.arkLogic.enableAgent()
                if not self.agent:
                    print("开启代理指挥失败，脚本关闭")
                    state = State.Error
            elif state == State.Action:
                state = self.arkLogic.actionStart()
            elif state == State.Prepare:
                state = self.arkLogic.prepareStart()
            elif state == State.Operation:
                state = self.arkLogic.operation()
            elif state == State.End:
                end_loop = True
                state = self.arkLogic.operationEnd()
            elif state == State.LevelUp:
                end_loop = True
                self.arkLogic.level_up()
            elif state == State.NoSanity:
                state = self.arkLogic.noSanity()
            elif state == State.Unknown:
                self.arkLogic.unknown()

            if state == State.Error:
                return False
        return True
