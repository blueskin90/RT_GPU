/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaulaus <apaulaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 19:52:52 by dibarqui          #+#    #+#             */
/*   Updated: 2019/02/18 16:57:15 by apaulaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# define NUMBER_SCENES 50
# define NUMBER_OBJECT 128
# define NUMBER_OBJECTS NUMBER_OBJECT * 5
# define NUMBER_CAMERAS 50
# define NUMBER_TEXTURES 8
# define GLFW_INCLUDE_NONE
# define GLFW_INCLUDE_VULKAN

# include <sys/stat.h>
# include <stdlib.h>
# include "rt_scene_file.h"
# include <GLFW/glfw3.h>
# include <stdint.h>
# include <limits.h>
# include "libftg.h"
# include "libft.h"
# include "rt_scene.h"
# include "json_parser.h"
# include "rt_parser.h"
# include "rt_errors.h"
# include "rt_required_information.h"
# include "libftprintf.h"
# include "rt_config.h"
# include "wgn2.h"

typedef struct		s_huge
{
	t_matrix		rotmat;
	double			prevx;
	double			prevy;
	double			xpos;
	double			ypos;
	double			xdelta;
	double			ydelta;
	float			r;
	float			f;
	float			u;

	int				tmp;
	int				current_scene;
	int				current_cam;
	float			wait_time;

	float			time;
	float			previous_time;
	uint32_t		frame;
	int				timestamp;

	int				wehaveafuckingmobius;
	int				moused;
	int				blur;
}					t_huge;

/*
** ERRORS HANDLING
*/

void				wrong_format(char *form, t_json_data type);
void				is_required(char *key, int one);

/*
** 	MAIN UTILS
*/

void				check_mobius(GLFWwindow *wnd, t_huge *data,
						t_scenes *scenes);
void				check_blur(GLFWwindow *wnd, t_huge *data, t_scenes *scenes);
void				check_mouse(GLFWwindow *wnd, t_huge *data);
void				check_hot(char *path, t_huge *data, t_scenes **scenes);

/*
**  EVENT HANDLER
*/

int					move(GLFWwindow *wnd, float delta, t_cam *cam,
						t_huge *data);
void				update(t_scenes *scenes, t_huge *data);
void				loop(GLFWwindow *wnd, char *path, t_huge *data,
						t_scenes *scenes);
int					change_scene(GLFWwindow *wnd, t_scenes *scenes,
						t_huge *data);
void				handle_events(GLFWwindow *wnd, char *path, t_huge *data,
						t_scenes **scenes);

/*
**	INIT
*/
void				init_cam(GLFWwindow *wnd, t_huge *data);
void				init_material(t_quadric *q, int i, int count);
void				init_loop(t_huge *data);
void				nicenorm(t_huge *data, t_scenes *scenes);
void				nicenorm0(t_huge *data, t_scenes *scenes);

/*
**	CORE UTILS
*/
void				functional_function(t_huge *data, float delta, t_cam *cam);
void				transform_quadric_matrix(t_quadric *q, t_vec3 t);
void				sphere_torus(t_scene *scene);
void				wows(t_huge *data, t_scenes **scenes);

void				save_image(GLFWwindow *wnd);
void				add_buffers(void);

/*
** UTILS
*/

void				*ft_malloc(size_t size);

/*
**	PRINTING FUNCTIONS
*/

void				print_scenes(t_scenes *scenes);
void				print_vec3(t_vec3 vec3, int padding);
void				print_vec4(t_vec4 vec4, int padding);
void				print_cam(t_cam cam, int cam_nbr);
void				print_objects(t_scene scene);
void				print_material(t_material mat, int padding);
void				print_transform(t_transform trs, int padding);
void				print_color(t_vec3 vec, int padding);
void				print_material(t_material mat, int padding);
void				print_rgb(t_rgb c, int padding);
void				print_data_type(t_json_data type);
void				print_obj_type(t_obj_type type);
void				print_matrix(t_matrix mat, int padding);
void				print_t_objs(t_objs *obj, char *name);
void				print_one_objs(t_objs *obj);
void				print_lights(t_temp_scenes scenes);
void				print_temp_quadric(t_temp_quadric quadric, int quad_nbr);
void				print_quadric(t_quadric quadric, int quad_nbr);
void				print_cube(t_cube cube, int cube_nbr);
void				print_torus(t_torus torus, int torus_nbr);
void				print_capsule(t_capsule capsule, int capsule_nbr);
void				print_common(t_transform trs, t_material mat);
#endif
