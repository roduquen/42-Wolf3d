# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/23 16:23:08 by mbenjell          #+#    #+#              #
#    Updated: 2019/05/11 17:52:52 by mbenjell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

INC = doom.h

SRC =	libft_mem.c \
		libft_str.c \
		stream.c \
		automate.c \
		parsing.c \
		extract_sector.c \
		extract_header.c \
		extract_map.c \
		draw.c \
		event.c \
		manage_event.c \
		controller.c \
		data.c \
		mlx.c \
		keys.c \
		view.c \
		draft.c \
		editor.c \
		doom.c

LIBMLX_MACOS = ./minilibx/libmlx.a -framework OpenGL -framework AppKit

FLAG =	#-g3 -fsanitize=address -Wall -Wextra -Werror

RM = 		/bin/rm -f

OBJ = 		$(addsuffix .o,$(basename $(SRC)))

.PHONY: all clean fclean re

all: 		$(NAME)

%.o : 		%.c $(INC)
			gcc -c $(FLAG) -o $@ $<

$(NAME): 	$(OBJ)
			@make -C minilibx
			@gcc $(FLAG) $(OBJ) -o $(NAME) $(LIBMLX_MACOS)

clean:
			make clean -C minilibx
			@$(RM) $(OBJ)

fclean:		clean
			make clean -C minilibx
			@$(RM) $(NAME)

re:			fclean all

fcleanme:
			@$(RM) $(OBJ)
			@$(RM) $(NAME)

reme: fcleanme all
