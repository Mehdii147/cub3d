# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/11 11:14:45 by amandour          #+#    #+#              #
#    Updated: 2025/04/19 19:01:25 by ehafiane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 						= cc 
FLAGS                   = -Wall -Wextra -Werror 
NAME					= cub3D

SRCS					= get_next_line.c \
						  get_next_line_utils.c \
                          parsing_read_map.c \
                          ft_pars.c \
                          parsing_helpe1.c \
                          parsing_helpe2.c \
                          parsing_map.c \
                          parsing_map1.c \
                          parsing_map2.c \
						  parsing_map3.c \
						  parsing_helpe3.c \
						  mohilloc.c \
						  cub3D.c

OBJS					= $(SRCS:.c=.o)

all						: $(NAME)

$(NAME)					: $(OBJS)
						  $(CC) $(FLAGS)  $(OBJS) -o $(NAME)

%.o						: %.c parsing/cub.h
						  @echo "\033[0;34mCompiling $<...\033[0;m"
						  $(CC) $(FLAGS) -c $< -o $@

clean                   :
						 @echo "\033[0;31mRemoving object files.\033[0;m"
						 rm -f $(OBJS)
						 @echo "\033[1;32mCleaning DONE ✅\033[0;m"
fclean                  : clean
						 @echo "\033[0;31mRemoving object files.\033[0;m"
						 rm -f $(NAME) 
						 @echo "\033[1;32mCleaning DONE ✅\033[0;m"

re                      : fclean all
.PHONY					: clean
