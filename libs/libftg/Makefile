# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <toliver@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/12 01:24:53 by toliver           #+#    #+#              #
#    Updated: 2019/02/11 09:48:48 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftg.a

FLAGS = -Wall -Wextra -Werror -Ofast -g3

FILES = def_vec_3\
		def_vec_4\
		utils_vec3\
		utils_vec4\
		matrix_func\
		matrix_init\
		matrix_init_rot\
		mat4_init\
		mat4_init_rot\
		operations_vec3\
		operations_vec4\
		operations_ext_vec3\
		operations_ext_vec4\
		tools\
		utility\
		vec3_norm \
		vec4_norm \
		qeuler \

INCLUDES = -I./includes

OBJS = $(addprefix objs/, $(addsuffix .o, \
	   $(FILES) \
		))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): objs $(OBJS)
	@printf  "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@ar rcs $(NAME) $(OBJS)

objs/%.o: srcs/%.c
	@printf  "\033[1:92mCompiling $(NAME)\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@gcc -o $@ -c $< $(FLAGS) $(INCLUDES)
	@printf "\033[A\033[2K"

objs:
	mkdir -p objs/

clean:
	@rm -Rf ./objs
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"

fclean: clean
	@rm -rf $(NAME)
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"

re: fclean all
