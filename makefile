files = game_grid.cpp main.cpp point_system.cpp shapes.cpp
sfml = -lsfml-graphics -lsfml-window -lsfml-system
Tetris: $(files)
	g++ -o Tetris $(files) $(sfml) -I.
