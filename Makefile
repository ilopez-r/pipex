# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 11:49:26 by ilopez-r          #+#    #+#              #
#    Updated: 2024/02/28 13:14:23 by ilopez-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

FLAGS = -Wall -Werror -Wextra

FILES = src/pipex.c\
		src/split_commands.c\
		src/split_path.c\
		src/get_route.c\
		src/exec_route.c\

BONUS = srcb/pipex_bonus.c\
		srcb/split_commands_bonus.c\
		srcb/split_path_bonus.c\
		srcb/get_route_bonus.c\
		srcb/exec_route_bonus.c\

OBJS = $(FILES:.c=.o)

OBJS_BONUS = $(BONUS:.c=.o)

LIBFT_PATH = ./libftc

LIBFT = $(LIBFT_PATH)/libft.a

all : $(NAME) $(LIBFT)

$(LIBFT) :
	@make -s -C $(LIBFT_PATH)

$(NAME) : $(OBJS) $(LIBFT)
	@gcc $(FLAGS) $(FILES) $(LIBFT)  -o $(NAME)

$(NAME_BONUS) : $(OBJS_BONUS) $(LIBFT)
	@gcc $(FLAGS) $(BONUS) $(LIBFT)  -o $(NAME_BONUS)

$(OBJS) : $(FILES)
	@gcc $(FLAGS) -c $< -o $@

$(OBJS_BONUS) : $(BONUS)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -fr $(OBJS) $(OBJS_BONUS)
	@make clean -s -C $(LIBFT_PATH)

fclean: clean
	@rm -fr $(NAME) $(NAME_BONUS) 
	@rm -f file2
	@make fclean -s -C $(LIBFT_PATH)

re: fclean all

bonus: $(NAME_BONUS)

.PHONY : all clean fclean re bonus