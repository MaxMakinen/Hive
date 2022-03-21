from santorini import *
from gods import *


class Engine:

    def __init__(self):
        self.board = Board()
        self.menu()

    def default(self):
        print("Invalid choice, give choice as 1, 2 or 3.")
        self.menu()

    def exit(self):
        print("Santorini closing down.")
        exit(0)

    def new_game(self):
        self.board.new_game()
        self.choose_players()
        self.player1.builder1.new_builder(1, 1)
        self.add_builder(self.player1.builder1)
        self.player1.builder2.new_builder(1, 2)
        self.add_builder(self.player1.builder2)
        self.player2.builder1.new_builder(2, 1)
        self.add_builder(self.player2.builder1)
        self.player2.builder2.new_builder(2, 2)
        self.add_builder(self.player2.builder2)

    def add_builder(self, builder):
        x = builder.coords[0]
        y = builder.coords[1]
        Board.board_state[x][y].append(builder)

    def choose_players(self):
        print("Do you want to play with normal rules?")
        print("Or do you want to use the god rules?")
        choice = input("Choose your game style\n(C) for Classic\n(G) for God rules\n")
        if choice == 'C' or choice == 'c':
            self.player1 = self.list_gods(0, 1)
            self.player2 = self.list_gods(0, 2)
        elif choice == 'G' or choice == 'g':
            print("Choose for player 1")
            self.player1 = self.choose_rules(1, 0)
            print("Choose for player 2")
            self.player2 = self.choose_rules(2, self.player1.rules)
        else:
            print("Invalid choice")
            self.choose_players()

    def make_player(self, god, index):
        return self.list_gods(god, index)

    def choose_rules(self, index, god):
        print("You can choose from the list of gods:")
        if god != 1:
            print("(1)Apollo: Your builder may move into an opponent builders space")
            print("by forcing their worker to the space yours just vacated.")
        if god != 2:
            print("(2)Atlas: Your builder may build a dome at any level.")
        if god != 3:
            print("(3)Minotaur: Your builder may move into an opponent builders space,")
            print("if their builder can be forced one space straight backwards to an unoccupied space at any level.")
        if god != 4:
            print("(4)Pan: You also win if your Builder moves down two or more levels.")
        choice = int(input("Choose your God:\n"))
        if 5 > choice > 0:
            if choice != god:
                return self.make_player(choice, index)
        self.choose_rules(index, god)

    def menu(self):
        print("Welcome to Santorini!\n(1) New game\n(2) Load game\n(3) Quit")
        options = {
            1: self.new_game,
            2: self.load_state,
            3: self.exit,
        }
        select = int(input("Please choose your action:\n"))
        options.get(select, self.default)()
        if 0 > select > 3:
            print("Invalid action")
            self.menu()

    def load_state(self):
        save = []
        temp = []
        name = str(input("Name save file to open:\n"))
        try:
            savefile = open(name, "r")
            temp = savefile.read()
            savefile.close()
        except IOError:
            print("Load failed")
            exit()
        for x in temp:
            if x != '[' and x != ']' and x != ',' and x != ' ':
                save.append(int(x))
        x = 0
        position = 0
        while x < 5:
            y = 0
            row = []
            while y < 5:
                square = []
                building_level = BuildingLevel(int(save[position]))
                square.append(building_level)
                row.append(square)
                y += 1
                position += 1
            Board.board_state.append(row)
            x += 1
        self.player1 = self.make_player(save[position], 1)
        position += 1
        position = self.load_workers(save, position, self.player1)
        self.player2 = self.make_player(save[position], 2)
        position += 1
        position = self.load_workers(save, position, self.player2)
        self.board.whose_turn = save[position]

    def load_workers(self, save, position, player):
        self.load_worker(save[position], save[position + 1], player, save[position + 2])
        position += 3
        self.load_worker(save[position], save[position + 1], player, save[position + 2])
        position += 3
        return position

    def load_worker(self, x, y, player, number):
        coords = [x, y]
        builder = Builder(player.player, number)
        builder.load_builder(coords)
        if builder.number == 1:
            player.builder1 = builder
            Board.board_state[x][y].append(builder)
        else:
            player.builder2 = builder
            Board.board_state[x][y].append(builder)

    def list_gods(self, god, index):
        gods = {
            0: Player,
            1: Apollo,
            2: Atlas,
            3: Minotaur,
            4: Pan,
        }
        return gods.get(god)(index)

    def name_gods(self, god):
        gods = {
            0: "Generic",
            1: "Apollo",
            2: "Atlas",
            3: "Minotaur",
            4: "Pan"
        }
        return gods.get(god)

    def turn(self):
        if self.board.whose_turn == 1:
            player = self.player1
        else:
            player = self.player2
        print("Ready player", self.board.whose_turn)
        self.board.print_map()
        print("You're playing with", self.name_gods(player.rules), "rules.")
        while True:
            print("Your builders are in positions:", player.builder1.coords, "and", player.builder2.coords)
            check = int(input("Would you like to move builder 1 or 2?\nChoose 0 to quit and save the game\n"))
            if check == 1:
                builder = player.builder1
                break
            elif check == 2:
                builder = player.builder2
                break
            elif check == 0:
                self.board.save_state(self.player1, self.player2)
                self.exit()
            else:
                print("Please give your answer as either 0, 1 or 2")
        legal_moves = player.legal_moves(builder)
        while True:
            self.board.print_map()
            print("your current movement options are :", legal_moves)
            print("Your position is :", builder.coords)
            print("Where would you like to move?")
            while True:
                choice = get_coords()
                if choice in legal_moves:
                    break
                print("Illegal move")
            builder = player.move(builder, choice)
            if check == 1:
                if builder != player.builder1:
                    self.board.board_state[player.builder1.coords[0]][player.builder1.coords[1]].remove(player.builder1)
                    self.board.board_state[builder[0]][builder[1]].append(player.builder1)
                    player.builder1.coords = builder
                    break
            elif check == 2:
                if builder != player.builder2:
                    self.board.board_state[player.builder2.coords[0]][player.builder2.coords[1]].remove(player.builder2)
                    self.board.board_state[builder[0]][builder[1]].append(player.builder2)
                    player.builder2.coords = builder
                    break
            print("Invalid choice")
        if player.win:
            print("You've won! Congratulations player " + str(check) + "!")
            exit(0)
        while True:
            success = False
            legal_builds = player.legal_build(builder)
            print("Where would you like to build?")
            self.board.print_map()
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
        if self.board.whose_turn == 1:
            self.board.whose_turn = 2
        else:
            self.board.whose_turn = 1


def get_coords():
    while True:
        row = int(input("Row?\n"))
        if 0 <= row < 5:
            break
        print("Give value between 0 and 4")
    while True:
        column = int(input("Column?\n"))
        if 0 <= column < 5:
            break
        print("Give value between 0 and 4")
    return [row, column]


game = Engine()
while True:
    game.turn()
