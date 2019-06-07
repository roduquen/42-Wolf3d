CC = clang
CFLAGS = -Wall -Wextra -Werror -O3 -Ofast
NAME = wolf3d
SRCDIR = ./
INCLDIR = ./includes/
LIBDIR = ./libft/
LIB = $(LIBDIR)libft.a
LIBSDL = -L /Users/roduquen/.brew/lib/ -lSDL2-2.0.0 `sdl2-config --cflags --libs`
SRCS = wolf3d.c \
	   init_and_leave_sdl.c \
	   parser.c \
	   commands.c \
	   maths.c \
	   raycasting.c \
	   camera.c \
	   vec2d.c \
	   texture.c \
	   utils.c
OBJ = $(notdir $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ) $(LIB)
	@$(CC) $(CFLAGS) -I $(INCLDIR) $^ -o $@ -L $(LIBDIR) -lft $(LIBSDL)
	@echo "\n\033[36mCreation :\033[0m \033[35;4m$(NAME)\033[0m\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -I $(INCLDIR) -I /Users/roduquen/.brew/include/SDL2
	@echo "\033[36mCompilation :\033[0m \033[32m$*\033[0m"

$(LIB) :
	@echo "\n\033[36mLibs Compilation :\033[0m \033[33m$(LIBDIR)\033[0m\n"
	@make -C libft

clean :
	@rm -rf $(OBJ)
	@echo "\n\033[36mDeletion :\033[0m \033[32mObjects\033[0m\n"

fclean : clean
	@rm -rf $(NAME)
	@make -C libft/ fclean
	@echo "\033[36mDeletion :\033[0m \033[35;4m$(NAME)\033[0m\n"

re : fclean all

.PHONY : all clean fclean re