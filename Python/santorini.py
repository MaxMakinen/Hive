# Santorini boardgame logic for School project: Rush - Abstract Games.
# Made at Hive Helsinki by student: Max Mäkinen

class Board:
    board_state = []

    def __init__(self):
        flag = input("Load game? y/n\n")
        if flag == 'y':
            pass
        else:
            x = 0
            while x < 5:
                y = 0
                row = []
                while y < 5:
                    square = []
                    building_level = BuildingLevel()
                    square.append(building_level)
                    row.append(square)
                    y += 1
                Board.board_state.append(row)
                x += 1
        self.whose_turn = 1

    def setup(self):
        pass

    def print_map(self):
        print("Currently the map looks like this:")
        for row in Board.board_state:
            line = []
            for column in row:
                if len(column) > 1:
                    line.append(str(column[1].owner) + 'B' + str(column[1].id))
                else:
                    line.append(column[0].height)
            for i in line:
                print(i, end="\t")
            print("\n")


class BuildingLevel:

    def __init__(self):
        self.height = 0


class Builder:

    def __init__(self, player, id):
        while True:
            print("Place worker", id)
            while True:
                x = int(input("Builder row?\n"))
                if x < 5 and x >= 0:
                    break
                print("Give value between 0 and 4")
            while True:
                y = int(input("Builder column?\n"))
                if y < 5 and y >= 0:
                    break
                print("Give value between 0 and 4")
            if len(board.board_state[x][y]) < 2:
                break
            print("Position occupied, try again")
        self.coords = [x, y]
        self.owner = player
        self.id = id


class Player:

    def __init__(self, player):
#       move the prompt into game engine
        print("Player " + str(player) + ", place your workers.")
#       Need method to get input from player to know where they placed their builders.
        self.builder1 = Builder(player, 1)
        board.board_state[self.builder1.coords[0]][self.builder1.coords[1]].append(self.builder1)
        self.builder2 = Builder(player, 2)
        board.board_state[self.builder2.coords[0]][self.builder2.coords[1]].append(self.builder2)
        self.player = player
        self.win = False

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
            if len(board.board_state[test[0]][test[1]]) > 1:
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
                if len(board.board_state[check[0]][check[1]]) > 1:
                    continue
                if board.board_state[check[0]][check[1]][0].height > 3:
                    continue
                options.append(check)
        return options


class Engine:

    def __init__(self, player1, player2):
        board.print_map()
        self.p1 = player1
        self.p2 = player2

    def turn(self):
        if board.whose_turn == 1:
            player = self.p1
        else:
            player = self.p2
        print("Ready player", board.whose_turn)
        board.print_map()
        while True:
            print("Your builders are in positions:", player.builder1.coords, "and", player.builder2.coords)
            check = int(input("Would you like to move builder 1 or 2?\n"))
            if check == 1:
                builder = player.builder1
                break
            elif check == 2:
                builder = player.builder2
                break
            else:
                print("Please give your answer as either 1 or 2")
        legal_moves = player.legal_moves(builder)
        while True:
            choice = []
            board.print_map()
            print("your current movement options are :", legal_moves)
            print("Your position is :", builder.coords)
            print("Where would you like to move?")
            choice = get_coords()
            builder = player.move(builder, choice)
            if check == 1:
                if builder != player.builder1:
                    board.board_state[player.builder1.coords[0]][player.builder1.coords[1]].remove(player.builder1)
                    board.board_state[builder[0]][builder[1]].append(player.builder1)
                    player.builder1.coords = builder
                    break
            elif check == 2:
                if builder != player.builder2:
                    board.board_state[player.builder2.coords[0]][player.builder2.coords[1]].remove(player.builder2)
                    board.board_state[builder[0]][builder[1]].append(player.builder2)
                    player.builder2.coords = builder
                    break
            print("Invalid choice")
        if player.win:
            print("You've won! Congratulations player " + str(check) + "!")
            exit(0)
        while True:
            target = []
            success = False
            legal_builds = player.legal_build(builder)
            print("Where would you like to build?")
            board.print_map()
            print("your position is :", builder)
            print("your options are:", legal_builds)
            target = get_coords()
            for verify in legal_builds:
                if target == verify:
                    player.build(target)
                    success = True
            if success:
                break
            print("invalid choice")
            continue
        if board.whose_turn == 1:
            board.whose_turn = 2
        else:
            board.whose_turn = 1


def get_coords():
    while True:
        row = int(input("Row?\n"))
        if row >= 0 and row < 5:
            break
        print("Give value between 0 and 4")
    while True:
        column = int(input("Column?\n"))
        if column >= 0 and column < 5:
            break
        print("Give value between 0 and 4")
    return [row, column]



board = Board()
board.print_map()
p1 = Player(1)
board.print_map()
p2 = Player(2)
game = Engine(p1, p2)
while True:
    game.turn()
