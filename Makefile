CC = g++
RM = rm -f

CXXFLAGS += -I./Includes/GDL_lib/includes -I./Includes -I./Includes/SFML/includes/
CXXFLAGS += -Wall -Wextra -Werror

LDFLAGS	+= -L./Includes/GDL_lib/libs -Wl,-rpath=./Includes/GDL_lib/libs
LDFLAGS	+= -lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -lSDL2 -lpthread -rdynamic
LDFLAGS += -L./Includes/SFML/lib -Wl,-rpath=./Includes/SFML/lib
LDFLAGS += -lsfml-system -lsfml-audio -ldl

COLOR_OFF = \033[0m
COLOR_ON = \033[32;01m

GEN =	$(COLOR_ON) [/_\ Generator Compiled /_\] $(COLOR_OFF)
PROG =	$(COLOR_ON) [/_\ Bomberman Compiled /_\] $(COLOR_OFF)
NAME = bomberman

GENNAME = generator

SRC =	Sources/Bomberman.cpp		\
	Sources/Graphic.cpp		\
	Sources/Skybox.cpp		\
	Sources/main.cpp		\
	Sources/Map.cpp			\
	Sources/SaveGameReader.cpp	\
	Sources/Player.cpp		\
	Sources/Bombs.cpp		\
	Sources/Explosions.cpp		\
	Sources/Cube.cpp		\
	Sources/Object.cpp		\
	Sources/Model.cpp		\
	Sources/PlayerStat.cpp		\
	Sources/Powerup.cpp		\
	Sources/Camera.cpp		\
	Sources/AI.cpp			\
	Sources/Configuration.cpp	\
	Sources/Menu.cpp		\
	Sources/PlayerInput.cpp		\
	Sources/Char.cpp		\
	Sources/String.cpp		\
	Sources/Engine.cpp		\
	Sources/SaveGame.cpp		\
	Sources/Ground.cpp		\
	Sources/Art.cpp			\
	Sources/Score.cpp		\
	Sources/Time.cpp		\
	Sources/GenerateMap.cpp		\
	Sources/Random.cpp		\
	Sources/readDir.cpp

GENSRC = Sources/GenerateMap.cpp	\
	Sources/Random.cpp		\
	Sources/genMain.cpp

GENOBJ = $(GENSRC:.cpp=.o)

OBJ = $(SRC:.cpp=.o)

all: $(NAME) $(GENNAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo -e "$(PROG)"

$(GENNAME): $(GENOBJ)
	$(CC) $(GENOBJ) -o $(GENNAME) $(LDFLAGS)
	@echo -e "$(GEN)"

clean:
	$(RM) $(OBJ) $(GENOBJ)

fclean: clean
	$(RM) $(NAME) $(GENNAME)

re: fclean all

.PHONY: all clean fclean re
