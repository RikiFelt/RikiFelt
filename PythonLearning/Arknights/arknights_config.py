from enum import Enum

zeroRegion = (0, 0, 0, 0)
FrameCaption = "arknights"
FrameClass = "com.hypergryph.arknights"
IconFolder = 'picture_2160x1360'
enableAgentCount = 3        # 尝试开启代理指挥次数
UseSanity = True            # 是否使用理智药恢复理智
UseStone = False            # 是否使用源石恢复理智


class State(Enum):
    Unknown = 0
    Action = 1
    Prepare = 2
    Operation = 3
    End = 4
    LevelUp = 5
    NoSanity = 6
    Error = 7
