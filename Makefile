NAME = cub3D
INC = cub3d.h
SRC = main.c cub_init.c draw.c events.c map_init.c map.c math.c ray_cast.c \
		rend3R.c update.c upload_rays.c parcer/map_parcer.c \
		parcer/tools.c parcer/check_line.c parcer/ft_split.c \
		parcer/parcer.c parcer/take_colors_walls.c parcer/free.c

OBJ = $(SRC:.c=.o)

CC = cc
# CFLAGS = 
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(MLXFLAGS) $(SRC) -o $(NAME)

clean :
	$(RM) $(OBJ)
	@echo "Cleaned"

fclean :
	$(RM) $(OBJ) $(NAME)
	@echo "Fully cleaned"
	
re : fclean all