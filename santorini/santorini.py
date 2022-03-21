# Santorini boardgame logic for School project: Rush - Abstract Games.
# Made at Hive Helsinki by student: Max Mäkinen


class Board:
    board_state = []
    whose_turn = 0

    def __init__(self):
        pass

    def new_game(self):
        x = 0
        while x < 5:
            y = 0
            row = []
            while y < 5:
                square = []
                building_level = BuildingLevel(0)
                square.append(building_level)
                row.append(square)
                y += 1
            Board.board_state.append(row)
            x += 1
        self.whose_turn = 1

    def save_state(self, player1, player2):
        table = []
        save = []
        p1_workers = []
        p2_workers = []
        for row in self.board_state:
            for column in row:
                table.append(column[0].height)
                if len(column) > 1:
                    worker = [column[1].coords[0], column[1].coords[1], column[1].number]
                    if column[1].owner == 1:
                        p1_workers.extend(worker)
                    elif column[1].owner == 2:
                        p2_workers.extend(worker)
        save.extend(table)
        save.append(player1.rules)
        save.extend(p1_workers)
        save.append(player2.rules)
        save.extend(p2_workers)
        save.append(self.whose_turn)
        name = input("Name save file:\n")
        try:
            savefile = open(name, "w")
            savefile.write(str(save))
            savefile.close()
            print("Save successful")
        except IOError:
            print("Save failed")

    @classmethod
    def print_map(cls):
        print("Currently the map looks like this:")
        for row in Board.board_state:
            line = []
            for column in row:
                if len(column) > 1:
                    line.append(str(column[1].owner) + 'B' + str(column[1].number))
                elif column[0].height == 4:
                    line.append('X')
                else:
                    line.append(column[0].height)
            for i in line:
                print(i, end="\t")
            print("\n")


class BuildingLevel:

    def __init__(self, height):
        self.height = height


class Builder:
    owner = 0
    number = 0
    coords = []

    def __init__(self, owner, number):
        self.owner = owner
        self.number = number

    def load_builder(self, coords):
        self.coords = coords

    def new_builder(self, player, number):
        Board.print_map()
        while True:
            print("Place worker", number)
            while True:
                x = int(input("Builder row?\n"))
                if 5 > x >= 0:
                    break
                print("Give value between 0 and 4")
            while True:
                y = int(input("Builder column?\n"))
                if 5 > y >= 0:
                    break
                print("Give value between 0 and 4")
            if len(Board.board_state[x][y]) < 2:
                break
            print("Position occupied, try again")
        self.coords = [x, y]
        self.owner = player
        self.number = number


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
