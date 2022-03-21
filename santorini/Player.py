from Builder import Builder

class Player:
	builders = 0
	color = None

	def __init__(self, num_of_builders, color):
		self.builders = num_of_builders
		self.color = color
	
	def get_builders(self):
		return self.builders

	def get_color(self):
		return self.color

	def add_builder(self, board, position):
		if self.builders > 0:
			if board.add_builder(Builder(self, position, 1, 1, self.color)):
				self.builders -= 1
				return True
		else:
			return False


	def __str__(self):
		s = "Player: "
		s += self.color
		return s