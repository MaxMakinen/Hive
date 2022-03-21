import pygame
from Builder import Builder
from Player import Player

class Board:
	board_state = []
	builders = []
	players = []
	selected_builder = None
	selected_player = None
	moved_builder = None

	def __init__(self):
		# # flag = input("Load game? y/n\n")
		# # if flag == 'y':
		# #     pass
		# else:
		x = 0
		while x < 5:
			y = 0
			row = []
			while y < 5:
				square = []
				building_level = 0
				square.append(building_level)
				row.append(square)
				y += 1
			Board.board_state.append(row)
			x += 1
		self.whose_turn = 1

	def get_cell_level(self, position):
		return self.board_state[position[0]][position[1]][0]

	def add_builder(self, builder):
		if (len(self.builders) > 0):
			for b in self.builders:
				if b.get_position() == builder.get_position():
					return False
		self.builders.append(builder)
		return True
		#print (self.builders)

	def add_player(self, player):
		self.players.append(player)

	def switch_player(self):
		if self.selected_player == self.players[0]:
			self.selected_player = self.players[1]
		else:
			self.selected_player = self.players[0]
		self.moved_builder = None
		for b in self.builders:
			if b.get_color() == self.selected_player.get_color():
				b.reset_moves()

		print ("switch player: " + str(self.selected_player))
	def get_selected_player(self):
		return self.selected_player

	def get_builders(self):
		return self.builders
	
	def set_selected_player(self, player):
		self.selected_player = player

	def select_builder(self, position):
		for builder in self.builders:
			if builder.get_position() == position and builder.get_color() == self.selected_player.get_color():
				self.selected_builder = builder
				return True
		return False

	def get_selected_builder(self):
		return self.selected_builder

	def build(self, build_to):
		for builder in self.builders:
			if builder.get_position() == build_to:
				return False
		if (self.selected_builder.get_builds() < 1):
			return False
		a = pygame.Vector2(build_to)
		b = pygame.Vector2(self.moved_builder.get_position())
		if a.distance_to(b) > 1.5:
			return False

		building = self.board_state[build_to[0]][build_to[1]][0]
		if self.get_cell_level(build_to) < 4:
			self.board_state[build_to[0]][build_to[1]][0] += 1
			self.selected_builder.build()
			self.switch_player()
			return True
		return False
    # def move(self, coord_to):
	# 	legal = self.legal_moves(builder)
	# 	coords = self.coords
	# 	for check in legal:
	# 		if check == coord_to:
	# 			if self.check_win(self.coords, coord_to):
	# 				self.win = True
	# 			return coord_to
	# 	return coords

	def move_builder(self, position):
		for builder in self.builders:
			if builder.get_position() == position:
				return False
		a = pygame.Vector2(position)
		b = pygame.Vector2(self.selected_builder.get_position())
		if a.distance_to(b) > 1.5:
			return False
		if self.get_cell_level(position) == 4:
			return False
		if self.get_cell_level(position) - self.get_cell_level(self.selected_builder.get_position()) > 1:
			return False
		
		self.selected_builder.move(position)
		self.moved_builder = self.selected_builder
		return True

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
			if len(self.board_state[test[0]][test[1]]) > 1:
				continue
			if (self.board_state[test[0]][test[1]][0].height - self.board_state[coords[0]][coords[1]][0].height) < 2:
				legal_moves.append(test)
		return legal_moves

	#def get_cell_builder(self, position):

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
				if len(self.board_state[check[0]][check[1]]) > 1:
					continue
				if self.board_state[check[0]][check[1]][0].height > 3:
					continue
				options.append(check)
		return options

	def check_win(self, builder, coord_to):
		if Board.board_state[builder[0]][builder[1]][0].height == 2:
			if Board.board_state[coord_to[0]][coord_to[1]][0].height == 3:
				return True
		return False
		
	def __str__(self):
		s = ""
		for row in range(5):
			for col in range(5):
				s.append(self.board_state[row][col])
		return (s)