# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehafiane <ehafiane@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 02:35:02 by ehafiane          #+#    #+#              #
#    Updated: 2025/05/12 19:58:47 by ehafiane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror  
# Add architecture flag to match libraries
ARCH = -arch x86_64
mlx =  -I./MLX -I./glfw-3.4.bin.MACOS/include -L./MLX -lmlx42 -L./glfw-3.4.bin.MACOS/lib-x86_64 -lglfw.3 -Wl,-rpath,./glfw-3.4.bin.MACOS/lib-x86_64 -framework Cocoa -framework OpenGL -framework IOKit

SRC = raycasting/main.c raycasting/casting.c raycasting/move_player.c raycasting/draw_map.c raycasting/textures.c raycasting/rendering.c raycasting/vert_cast.c raycasting/horiz_cast.c \
	parsing/get_next_line.c \
	parsing/get_next_line_utils.c \
	parsing/parsing_read_map.c \
	parsing/ft_pars.c \
	parsing/parsing_helpe1.c \
	parsing/parsing_helpe2.c \
	parsing/parsing_map.c \
	parsing/parsing_map1.c \
	parsing/parsing_map2.c \
	parsing/parsing_map3.c \
	parsing/parsing_helpe3.c \
	parsing/mohilloc.c \

raycasting = raycasting
OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(ARCH) $(OBJ) $(mlx) -o $(NAME)
	@echo "Compiled successfully"

$(OBJDIR)/%.o: %.c inc/cub3d.h parsing/cub.h | $(OBJDIR)
	@$(CC) $(CFLAGS) $(ARCH) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/raycasting
	@mkdir -p $(OBJDIR)/parsing

clean:
	@rm -rf $(OBJ) $(OBJDIR)
	@echo "Cleaned up object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned up everything"

re: fclean all