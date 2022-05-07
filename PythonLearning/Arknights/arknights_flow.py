from arknights_config import *


class ArkFlow:
    def __init__(self, arkLogic):
        self.arkLogic = arkLogic
        self.total_count = 0

    def isValid(self):
        return self.arkLogic.isValid()

    def start(self, count=0):
        print('脚本开始')
        if self.isValid():
            if count > 0:
                # 测试用，循环count次
                self.startAction(count)
            else:
                # 实际用，通过控制台输入循环次数
                self.startActionInput()
                count = self.continueOperate()
                while count > 0:
                    self.startAction(count)
                    count = self.continueOperate()
        else:
            input()
        print('脚本结束')

    def startAction(self, loop_count):
        if not self.arkLogic.precheck():
            return
        for count in range(loop_count):
            self.total_count = self.total_count + 1
            print(f'第{self.total_count}次代理指挥开始')
            if not self.actionLoop():
                print(f'第{self.total_count}次代理指挥出错')
                break
            print(f'第{self.total_count}次代理指挥结束')
        print("代理指挥结束")

    def startActionInput(self):
        count = 0
        while True:
            print('请输入一个大于0的整数')
            try:
                count = int(input())
                if count > 0:
                    break
            except BaseException:
                count = 0
        self.startAction(count)

    @staticmethod
    def continueOperate():
        count = 0
        while True:
            print('是否继续执行脚本：')
            print('是：请输入一个大于0的整数')
            print('否：请输入0')
            try:
                count = int(input())
                if count > 0:
                    break
                elif count == 0:
                    break
            except BaseException:
                count = 0
        return count

    def actionLoop(self):
        end_loop = False
        while True:
            state = self.arkLogic.getGameState()
            if state == State.Action:
                if end_loop:
                    break
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
