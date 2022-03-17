# Santorini boardgame logic for School project: Rush - Abstract Games.
# Made at Hive Helsinki by student: Max Mäkinen

class Board:
    board_state = [[0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]
    whose_turn = 0

    def __init__(self):
        flag = input("Load game? y/n\n")
        if flag == 'y':
            pass
        Board.whose_turn = 1

    def setup(self):
        pass

    def print_map(self):
        print("currently the map looks like this:")
        for row in Board.board_state:
            print(row)


class Player:

    def __init__(self, player):
        print("Player " + str(player) + ", place your workers.")
#       Need method to get input from player to know where they placed their builders.
        self.builder1 = [0, 4]
        self.builder2 = [1, 1]
        self.player = player
        self.win = False

    def move(self, builder, coord_to):
        legal = self.legal_moves(builder)
        for check in legal:
            if check == coord_to:
                if self.check_win(builder, coord_to):
                    self.win = True
                return coord_to
        return builder

    def build(self, build_to):
        if Board.board_state[build_to[0]][build_to[1]] < 5:
            Board.board_state[build_to[0]][build_to[1]] += 1
            return True
        return False

    def check_win(self, builder, coord_to):
        if Board.board_state[builder[0]][builder[1]] == 2:
            if Board.board_state[coord_to[0]][coord_to[1]] == 3:
                return True
        return False

    @staticmethod
    def legal_moves(builder):
        moves = []
        legal_moves = []
        modifiers = [-1, 0, 1]
        for x in modifiers:
            for y in modifiers:
                check = [builder[0] + x, builder[1] + y]
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
            if (Board.board_state[test[0]][test[1]] - Board.board_state[builder[0]][builder[1]]) < 2:
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
                options.append(check)
        return options

class Engine:

    def __init__(self, player1, player2):
        self.p1 = player1
        self.p2 = player2

    def turn(self):
        self.check = 0
        if Board.whose_turn == 1:
            player = self.p1
        else:
            player = self.p2
        builder = player.builder1
        print("Ready player", Board.whose_turn)
        board.print_map()
        while True:
            print("Your builders are in positions:", player.builder1, "and", player.builder2)
            self.check = int(input("Would you like to move builder 1 or 2?\n"))
            if self.check == 1:
                builder = player.builder1
                break
            elif self.check == 2:
                builder = player.builder2
                break
            else:
                print("Please give your answer as either 1 or 2")
        legal_moves = player.legal_moves(builder)
        while True:
            choice = []
            board.print_map()
            print("your current movement options are :", legal_moves)
            print("Your position is :", builder)
            print("Where would you like to move?")
            row = int(input("row?\n"))
            column = int(input("column?\n"))
            choice.append(row)
            choice.append(column)
            builder = player.move(builder, choice)
            if self.check == 1:
                if builder != player.builder1:
                    player.check_win(player.builder1, builder)
                    player.builder1 = builder
                    break
            elif self.check == 2:
                if builder != player.builder2:
                    player.check_win(player.builder2, builder)
                    player.builder2 = builder
                    break
            print("Invalid choice")
        if player.win:
            print("You've won! Congratulations player " + str(self.check) + "!")
            exit(0)
        while True:
            target = []
            success = False
            legal_builds = player.legal_build(builder)
            print("Where would you like to build?")
            board.print_map()
            print("your position is :", builder)
            print("your options are:", legal_builds)
            row = int(input("Row?\n"))
            column = int(input("Column?\n"))
            target.append(row)
            target.append(column)
            for verify in legal_builds:
                if target == verify:
                    player.build(target)
                    success = True
            if success:
                break
            print("invalid choice")
            continue
        if Board.whose_turn == 1:
            Board.whose_turn = 2
        else:
            Board.whose_turn = 1


board = Board()
p1 = Player(1)
p2 = Player(2)
game = Engine(p1, p2)
while True:
    game.turn()