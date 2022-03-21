
from engine import *


class Player:

    def __init__(self, player):
        self.player = player
        self.builder1 = Builder(player, 1)
        self.builder2 = Builder(player, 2)
        self.win = False
        self.rules = 0

    def move(self, builder, coord_to):
        legal = self.legal_moves(builder)
        coords = builder.coords
        for check in legal:
            if check == coord_to:
                if self.check_win(builder.coords, coord_to):
                    self.win = True
                return coord_to
        return coords

    def build(self, build_to):
        building = Board.board_state[build_to[0]][build_to[1]][0]
        if building.height < 5:
            building.height += 1
            return True
        return False

    def check_win(self, builder, coord_to):
        if Board.board_state[builder[0]][builder[1]][0].height == 2:
            if Board.board_state[coord_to[0]][coord_to[1]][0].height == 3:
                return True
        return False

    def legal_moves(self, builder):
        moves = []
        legal_moves = []
        coords = builder.coords
        modifiers = [-1, 0, 1]
        for x in modifiers:
            for y in modifiers:
                check = [builder.coords[0] + x, builder.coords[1] + y]
                if check == builder:
                    continue
                moves.append(check)
        for test in moves:
            flag = 0
            for i in test:
                if i < 0 or i > 4:
                    flag = 1
            if flag == 1:
                continue
            if len(Board.board_state[test[0]][test[1]]) > 1:
                continue
            if (Board.board_state[test[0]][test[1]][0].height - Board.board_state[coords[0]][coords[1]][0].height) < 2:
                legal_moves.append(test)
        return legal_moves

    def legal_build(self, builder):
        options = []
        modifiers = [-1, 0, 1]
        for x in modifiers:
            for y in modifiers:
                check = [builder[0] + x, builder[1] + y]
                if check[0] < 0 or check[0] > 4:
                    continue
                if check[1] < 0 or check[1] > 4:
                    continue
                if check == builder:
                    continue
                if len(Board.board_state[check[0]][check[1]]) > 1:
                    continue
                if Board.board_state[check[0]][check[1]][0].height > 3:
                    continue
                options.append(check)
        return options


class Apollo(Player):

    def __init__(self, player):
        super().__init__(player)
        self.rules = 1

    def legal_moves(self, builder):
        moves = []
        legal_moves = []
        coords = builder.coords
        modifiers = [-1, 0, 1]
        for x in modifiers:
            for y in modifiers:
                check = [builder.coords[0] + x, builder.coords[1] + y]
                if check == builder:
                    continue
                moves.append(check)
        for test in moves:
            flag = 0
            for i in test:
                if i < 0 or i > 4:
                    flag = 1
            if flag == 1:
                continue
            if len(Board.board_state[test[0]][test[1]]) > 1:
                if Board.board_state[test[0]][test[1]][1].owner == self.player:
                    continue
            if (Board.board_state[test[0]][test[1]][0].height - Board.board_state[coords[0]][coords[1]][0].height) < 2:
                legal_moves.append(test)
        return legal_moves

    def move(self, builder, coord_to):
        legal = self.legal_moves(builder)
        coords = builder.coords
        for check in legal:
            if check == coord_to:
                if len(Board.board_state[coord_to[0]][coord_to[1]]) > 1:
                    self.swap(builder, Board.board_state[coord_to[0]][coord_to[1]][1])
                if self.check_win(builder.coords, coord_to):
                    self.win = True
                return coord_to
        return coords

    def swap(self, builder, target):
        Board.board_state[target.coords[0]][target.coords[1]][1] = builder
        Board.board_state[builder.coords[0]][builder.coords[1]][1] = target
        memory = target.coords
        target.coords = builder.coords
        builder.coords = memory


class Atlas(Player):

    def __init__(self, player):
        super().__init__(player)
        self.rules = 2

    def build(self, build_to):
        building = Board.board_state[build_to[0]][build_to[1]][0]
        while True:
            choice = input("Do you want to build a (T)ower piece or a (D)ome?\n")
            if choice == 'T' or choice == 'D' or choice == 't' or choice == 'd':
                break
            print("Please give answer as T or D")
        if choice == 'D' or 'd':
            building.height = 4
            return True
        if building.height < 4:
            building.height += 1
            return True
        return False


class Minotaur(Player):

    def __init__(self, player):
        super().__init__(player)
        self.target = []
        self.rules = 3

    def legal_moves(self, builder):
        moves = []
        legal_moves = []
        coords = builder.coords
        modifiers = [-1, 0, 1]
        for x in modifiers:
            for y in modifiers:
                check = [builder.coords[0] + x, builder.coords[1] + y]
                if check == builder:
                    continue
                moves.append(check)
        for test in moves:
            flag = 0
            for i in test:
                if i < 0 or i > 4:
                    flag = 1
            if flag == 1:
                continue
            if len(Board.board_state[test[0]][test[1]]) > 1:
                if Board.board_state[test[0]][test[1]][1].owner == self.player:
                    continue
                if not self.push_check(builder, Board.board_state[test[0]][test[1]][1]):
                    continue
            if (Board.board_state[test[0]][test[1]][0].height - Board.board_state[coords[0]][coords[1]][0].height) < 2:
                legal_moves.append(test)
        return legal_moves

    def move(self, builder, coord_to):
        legal = self.legal_moves(builder)
        coords = builder.coords
        for check in legal:
            if check == coord_to:
                if len(Board.board_state[coord_to[0]][coord_to[1]]) > 1:

                    self.push(builder, Board.board_state[coord_to[0]][coord_to[1]][1])
                if self.check_win(builder.coords, coord_to):
                    self.win = True
                return coord_to
        return coords

    def push(self, builder, target):
        self.push_check(builder, target)
        Board.board_state[target.coords[0]][target.coords[1]].remove(target)
        Board.board_state[builder.coords[0]][builder.coords[1]].remove(builder)
        Board.board_state[target.coords[0]][target.coords[1]].append(builder)
        Board.board_state[self.target[0]][self.target[1]].append(target)
        builder.coords = target.coords
        target.coords = self.target
        self.target = []

    def push_check(self, builder, target):
        x = target.coords[0] - builder.coords[0]
        y = target.coords[1] - builder.coords[1]
        x += target.coords[0]
        y += target.coords[1]
        if 5 > x >= 0:
            if 5 > y >= 0:
                self.target = [x, y]
                return True
        return False


class Pan(Player):

    def __init__(self, player):
        super().__init__(player)
        self.rules = 4

    def check_win(self, builder, coord_to):
        start = Board.board_state[builder[0]][builder[1]][0].height
        end = Board.board_state[coord_to[0]][coord_to[1]][0].height
        if start == 2:
            if end == 3:
                return True
        if start < 1:
            if start - end < 1:
                return True
        return False
