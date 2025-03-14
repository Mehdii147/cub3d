# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 02:35:02 by ehafiane          #+#    #+#              #
#    Updated: 2025/03/14 02:40:51 by ehafiane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = CC 
CFLAGS = -Wall -Wextra -Werror
mlx =  -I./MLX -I./glfw-3.4.bin.MACOS/include -L./MLX -lmlx42 -L./glfw-3.4.bin.MACOS/lib-x86_64 -lglfw.3 -Wl,-rpath,./glfw-3.4.bin.MACOS/lib-x86_64 -framework Cocoa -framework OpenGL -framework IOKit

SRC = raycasting/main.c raycasting/dda.c raycasting/move_player.c raycasting/draw_map.c

raycasting = raycasting
OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(mlx) -o $(NAME)

$(OBJDIR)/%.o: %.c inc/cub3d.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/raycasting


clean:
	rm -rf $(OBJ) $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: clean all