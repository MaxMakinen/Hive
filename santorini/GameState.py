from enum import Enum

class GameState(Enum):
    BUILD = 1
    MOVE = 2
    GAME_OVER = 3
    ADD_BUILDER = 4
    BUILDER_SELECTED = 5
    SELECT_TILE = 6