class Builder:
	coords = (-1, -1)
	owner = None
	moves = 0
	builds = 0
	num_of_moves = 0
	num_of_builds = 0
	color = None

	def __init__(self, player, coords, num_of_moves, num_of_builds, color):
		self.color = color
		self.coords = coords
		self.owner = player
		self.moves = num_of_moves
		self.builds = num_of_builds
		self.num_of_moves = num_of_moves
		self.num_of_builds = num_of_builds

	def get_x(self):
		return self.coords[0]

	def get_y(self):
		return self.coords[1]

	def get_position(self):
		return self.coords
	def get_color(self):
		return self.color
	def reset_moves(self):
		self.moves = self.num_of_moves
		self.builds = self.num_of_builds

	def move(self, position):
		if (self.moves > 0):
			self.coords = position
			self.moves -= 1

	def build(self):
		self.builds -= 1

	def get_builds(self):
		return self.builds
		
	def __str__(self):
		s = "Builder: "
		s += (str(self.coords))
		return s