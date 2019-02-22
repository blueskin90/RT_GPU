# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 10:15:44 by cvermand          #+#    #+#              #
#    Updated: 2019/02/18 17:09:00 by cvermand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
CC = gcc
C++ = g++

DEBUG = -g3
FLAGS = -Wall -Wextra -Werror

MODE_TYPE = no_mode
ADD_FLAGS = -Wall -Wextra -Werror
C_INCLUDES = -I ${VK_SDK}/macos/include\
			-I ./libs/glfw/deps\
			-I ./libs/glfw/include\
			-I ./libs/libft/includes/\
			-I ./libs/libftg/includes/\
			-I ./libs/ft_printf/includes \
			-I ./includes/c_includes\
			-I ./libs/wgn2/includes

SHADERS = ./shaders
VK_SDK = ./vulknsdk

VK_SDK_PATH = ./libs/vulkansdk/macOS/bin/glslc -fshader-stage=
VK_OBJS_PATH = objs/vulkan/
LIBS = 	./libs/vulkansdk/macos/lib \
		./libs/glfw/src/libglfw3.a \
		./libs/vulkansdk/macos/lib/libvulkan.dylib \
		-framework Cocoa \
		-framework IOKit \
		-framework CoreFoundation \
		-framework CoreVideo \
		./libs/ft_printf/libftprintf.a \
		./libs/libftg/libftg.a \
		./libs/libft/libft.a \
		./libs/wgn2/wgn2.a \

C_HEADERS_DIR = includes/c_includes/
CPP_HEADERS_DIR = ./libs/wgn2/includes/
HEADERS = $(addprefix $(C_HEADERS_DIR), $(addsuffix .h, \
		  json_parser\
		  json_parser_errors\
		  rt_config\
		  rt_math \
		  rt_scene \
		  rt_parser \
		  rt_errors \
		  rt_required_information \
		  rt \
		  rt_object \
		  rt_scene_file \
		)) \

C_OBJS = $(addprefix objs/, $(addsuffix .o, \
		$(addprefix core/, \
			cmain \
			errors\
			malloc\
			check\
			event_handler \
			init \
			core_utils\
		)\
		$(addprefix json_parser/, \
			array_recursive \
			elem_struct_functions \
			free_structure \
			json_parser \
			json_errors \
			json_utils \
			print_elem_architecture \
			recognize_number \
			recognize_string \
			recognize_bool \
			recognize_null \
			recognize_array \
			recognize_object \
			recognize_extension \
			object_recursive \
			recognize_type \
			recognize_key \
			singleton \
		) \
		$(addprefix rt_parser/, \
			$(addprefix parser/, \
				parse_cameras\
				parse_scene\
				parse_object\
				parse_forms\
				parse_quadric\
				parse_vectors\
				parse_transform\
				parse_material\
				parse_basic_quadric\
				parse_arithmetic_values\
				parse_colors \
				parse_hex_rgb \
				parse_child \
				parse_light \
				parse_copy \
				parse_common \
			)\
			$(addprefix config/, \
					extract_config \
					array_config \
					bool_config \
					integer_config\
					float_config\
					string_config\
					string_config_ext\
					object_config\
					parse_config\
					extract_errors\
					check_required_type_config\
					min_max\
					config_errors\
			)\
			$(addprefix utils/, \
				$(addprefix color_utils/, \
					colors_init\
					rgb_functions\
				)\
				compare_tool \
				id_singleton\
				arithmetic_tools\
				key_types_number\
				key_types_utils\
				recognize_type_of_key\
				calculate_up_right_rot\
				defaults \
				objs_struct \
				objs_struct_free \
				objs_struct_get \
				calculate_matrix \
				quadric_utils \
				vector_utils \
				transform_child_parent \
				combine_child_parent \
			)\
			rt_parsing \
			merge_scenes \
		)\
		$(addprefix printing/, \
			print_scenes \
			print_material \
			print_objects \
			print_objects2 \
			print_vec \
			print_transform \
			print_data_type \
		)\
	))

all: $(NAME)

create_dir :
	@mkdir -p objs/vulkan
	@mkdir -p objs/core
	@mkdir -p objs/json_parser
	@mkdir -p objs/rt_parser
	@mkdir -p objs/rt_parser/parser
	@mkdir -p objs/rt_parser/handler
	@mkdir -p objs/rt_parser/utils
	@mkdir -p objs/rt_parser/utils/color_utils
	@mkdir -p objs/rt_parser/config
	@mkdir -p objs/rt_parser/config/extract
	@mkdir -p objs/rt_parser/config/camera
	@mkdir -p objs/rt_parser/config/object
	@mkdir -p objs/rt_parser/config/object/types
	@mkdir -p objs/printing

frameworks :
	@$(VK_SDK_PATH)fragment $(SHADERS)/shader.frag -o $(VK_OBJS_PATH)frag.spv -Werror -O
	@$(VK_SDK_PATH)vertex		$(SHADERS)/shader.vert -o $(VK_OBJS_PATH)vert.spv -Werror -O
	@$(VK_SDK_PATH)compute	$(SHADERS)/shader.comp -o $(VK_OBJS_PATH)comp.spv -Werror -O
	@make -C ./libs/libft
	@make -C ./libs/libftg
	@make -C ./libs/ft_printf
	@make -C ./libs/wgn2

$(NAME) : create_dir frameworks objs $(CPP_OBJS) $(C_OBJS) $(HEADERS)
	@printf "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@$(C++) -Wl,-search_paths_first -Wl,-headerpad_max_install_names $(C_OBJS) $(CPP_OBJS) -o $(NAME)			\
		-Wl,-rpath, $(LIBS) $(DEBUG) $(FAST) $(FLAGS) -I $(CPP_HEADERS_DIR) -Werror -Wextra -Wall

objs/%.o : c_src/%.c
	@printf  "\033[1:92mCompiling $(NAME) c \033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@$(CC) -o $@ -c $< -g $(C_INCLUDES) $(DEBUG) $(FAST) $(FLAGS) -I $(CPP_HEADERS_DIR)
	@printf "\033[A\033[2K"


clean clean2:
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -rf objs

fclean : clean
	@make fclean -C ./libs/libft
	@make fclean -C ./libs/libftg
	@make fclean -C ./libs/ft_printf
	@make clean -C ./libs/wgn2
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -f $(NAME)

re : fclean all

.PHONY: re clean fclean all debug fast flags
