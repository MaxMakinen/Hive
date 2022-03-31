import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
import pygame
from GameState import GameState
from Board import Board
from Player import Player

WIDTH = 1000
HEIGHT = 1000
ROWS = 5
COLS = 5
SQUARE_SIZE = WIDTH//COLS
PLAYER_SIZE = SQUARE_SIZE // 4
BUILDING_LVL_ONE = SQUARE_SIZE // 2
BUILDING_LVL_TWO = SQUARE_SIZE // 3
BUILDING_LVL_THREE = SQUARE_SIZE // 4

RED = (255, 0, 0)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
FPS = 60

selected_tile = (-1, -1)

STATE = None
icon_app = pygame.image.load('./assets/icon.png')
pygame.display.set_icon(icon_app)
WINDOW = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.init()
pygame.display.set_caption('Santorini')
board = Board()
icon_build = pygame.image.load('./assets/build.png')
icon_move = pygame.image.load('./assets/move.png')
map_build0 = pygame.image.load('./assets/build_0.png')
map_build1 = pygame.image.load('./assets/build_1.png')
map_build2 = pygame.image.load('./assets/build_2.png')
map_build3 = pygame.image.load('./assets/build_3.png')
map_build4 = pygame.image.load('./assets/build_4.png')
map_player0 = pygame.image.load('./assets/player_0.png')
map_player1 = pygame.image.load('./assets/player_1.png')
game_over_text = pygame.image.load('./assets/game_over.png')

player0 = Player(2, 'WHITE')
player1 = Player(2, 'BLACK')

def get_coords(slot):
	x = SQUARE_SIZE * slot[0] + SQUARE_SIZE // 2
	y = SQUARE_SIZE * slot[1] + SQUARE_SIZE // 2
	return ((x,y))

def get_slot(coords):
	col = coords[1] // SQUARE_SIZE
	row = coords[0] // SQUARE_SIZE
	return ((row, col))

def draw_board():
	WINDOW.fill(BLACK)
	for row in range(ROWS):
		#for col in range(row % 2, COLS, 2):
		for col in range(COLS):
			#pygame.draw.rect(WINDOW, RED, (row * SQUARE_SIZE, col * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))
			if board.get_cell_level((row, col)) == 0:
				WINDOW.blit(pygame.transform.scale(map_build0, (SQUARE_SIZE, SQUARE_SIZE)), (row * SQUARE_SIZE, col * SQUARE_SIZE))
			if board.get_cell_level((row, col)) == 1:
				WINDOW.blit(pygame.transform.scale(map_build1, (SQUARE_SIZE, SQUARE_SIZE)), (row * SQUARE_SIZE, col * SQUARE_SIZE))
			if board.get_cell_level((row, col)) == 2:
				WINDOW.blit(pygame.transform.scale(map_build2, (SQUARE_SIZE, SQUARE_SIZE)), (row * SQUARE_SIZE, col * SQUARE_SIZE))
			if board.get_cell_level((row, col)) == 3:
				WINDOW.blit(pygame.transform.scale(map_build3, (SQUARE_SIZE, SQUARE_SIZE)), (row * SQUARE_SIZE, col * SQUARE_SIZE))
			if board.get_cell_level((row, col)) == 4:
				WINDOW.blit(pygame.transform.scale(map_build4, (SQUARE_SIZE, SQUARE_SIZE)), (row * SQUARE_SIZE, col * SQUARE_SIZE))
	builders = board.get_builders()
	for builder in builders:
		#print (builder)
		if (builder.get_color() == 'BLACK'):
			WINDOW.blit(pygame.transform.scale(map_player0, (SQUARE_SIZE, SQUARE_SIZE)), (builder.get_x() * SQUARE_SIZE, builder.get_y() * SQUARE_SIZE))
		if (builder.get_color() == 'WHITE'):
			WINDOW.blit(pygame.transform.scale(map_player1, (SQUARE_SIZE, SQUARE_SIZE)), (builder.get_x() * SQUARE_SIZE, builder.get_y() * SQUARE_SIZE))

	# WINDOW.blit(pygame.transform.scale(icon_build, (SQUARE_SIZWINDOW.blit(pygame.transform.scale(icon_build, (SQUARE_SIZE, SQUARE_SIZE)), (0, SQUARE_SIZE))_SIZE)

def draw_building():
	pygame.draw.rect(WINDOW, WHITE, (SQUARE_SIZE * 2 + BUILDING_LVL_ONE / 2, SQUARE_SIZE * 2 + BUILDING_LVL_ONE / 2, BUILDING_LVL_ONE, BUILDING_LVL_ONE))
	pygame.draw.rect(WINDOW, WHITE, (SQUARE_SIZE * 2 + BUILDING_LVL_TWO / 2, SQUARE_SIZE * 2 + BUILDING_LVL_TWO / 2, BUILDING_LVL_TWO, BUILDING_LVL_TWO))
	pygame.draw.rect(WINDOW, WHITE, (SQUARE_SIZE * 2 + BUILDING_LVL_THREE / 2, SQUARE_SIZE * 2 + BUILDING_LVL_THREE / 2, BUILDING_LVL_THREE, BUILDING_LVL_THREE))
def draw_dome(place):
	pass

def draw_selected():
	pygame.draw.rect(WINDOW, GREEN, (selected_tile[0]*SQUARE_SIZE, selected_tile[1]*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))

def draw_icons():
	draw_canmove_icon((0,0))
	draw_canbuild_icon((0,1))

def draw_canmove_icon(place):
	#pygame.transform.scale(pic, (500, 500)),
	#loop allowed moves from builder place
	WINDOW.blit(pygame.transform.scale(icon_move, (SQUARE_SIZE, SQUARE_SIZE)), (0, 0))

def draw_canbuild_icon(place):
	#loop allowed build from all builder place
	WINDOW.blit(pygame.transform.scale(icon_build, (SQUARE_SIZE, SQUARE_SIZE)), (0, SQUARE_SIZE))

def draw_addbuilder_icon(place):
	pass

def select_tile(position):
	global selected_tile
	if (selected_tile == position):
		selected_tile = (-1, -1)
	else:
		selected_tile = position
		# if map has builder state = MOVE_BUILDER
	#print (selected_tile)

def add_builder(position):
	global STATE
	print("add builder to " + str(get_slot(position)))
	player = board.get_selected_player()
	player.add_builder(board, get_slot(position))
	builders = board.get_builders()
	if (player0.get_builders() == 0 and player1.get_builders() == 0):
		board.switch_player()
		STATE = GameState.SELECT_TILE
	elif (player.get_builders() == 0):
		board.switch_player()

def move_builder(position):
	global STATE
	print("move to " + str(position))
	#builder = board.get_selected_builder(position)
	if (board.move_builder(get_slot(position))):
		if board.get_cell_level(get_slot(position)) == 3:
			print (board.get_cell_level(get_slot(position)))
			STATE = GameState.GAME_OVER
		else:
			STATE = GameState.BUILD
			print (board.get_cell_level(get_slot(position)))

def build(position):
	global STATE
	print("build to " + str(get_slot(position)))
	if board.build(get_slot(position)):
		STATE = GameState.SELECT_TILE
def check_player_state(player):
	pass

def main():
	run = True
	global STATE
	clock = pygame.time.Clock()
	# init_board()
	board.add_player(player0)
	board.add_player(player1)
	board.set_selected_player(player0)
	STATE = GameState.ADD_BUILDER

	while run:
		clock.tick(FPS)
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				run = False
			if event.type == pygame.MOUSEBUTTONDOWN:
				position = pygame.mouse.get_pos()
				select_tile(get_slot(position))
				if STATE == GameState.GAME_OVER:
					run = False
				if STATE == GameState.ADD_BUILDER:
					add_builder(position)
				elif STATE == GameState.MOVE:
					move_builder(position)
				elif STATE == GameState.BUILDER_SELECTED:
					draw_canmove_icon(position)
				elif STATE == GameState.SELECT_TILE:
					if board.select_builder(get_slot(position)):
						print ("select builder")
						STATE = GameState.MOVE
				elif STATE == GameState.BUILD:
						build(position)
				# else:
				# 	print(GameState)
		draw_board()
		if STATE == GameState.GAME_OVER:
			WINDOW.blit(game_over_text, (0, HEIGHT//2 - SQUARE_SIZE))
		# if STATE == GameState.SELECT_TILE:
		# 	draw_selected()
		#draw_building()

		#draw_icons()
		# draw_builder((0 + SQUARE_SIZE / 2,0 + SQUARE_SIZE / 2), BLUE)
		# draw_builder(((0 + SQUARE_SIZE / 2) + SQUARE_SIZE * 2, (0 + SQUARE_SIZE / 2) + SQUARE_SIZE * 2), GREEN)
		#print (selected_tile)
		pygame.display.flip()

	pygame.quit()

main()