/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaulaus <apaulaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 12:35:19 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/12 11:50:33 by apaulaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PARSER_H
# define RT_PARSER_H
# define TOLERANCE 0.01
# define VERBOSE_SCENE 0

typedef struct		s_rgb
{
	float			r;
	float			g;
	float			b;
	int				value;

}					t_rgb;

typedef struct		s_json
{
	t_elem			*config;
	t_elem			*elem;
	t_obj_type		type;
}					t_json;

typedef struct		s_objs
{
	void			*obj;
	t_obj_type		type;
	t_json			json;
	int				id;
	int				natural_id;
	char			*name;
	char			absolute;
	char			*combine;
	struct s_objs	*next;
	struct s_objs	*parent_tree;
	struct s_objs	*before;
}					t_objs;

typedef	struct		s_obj_func
{
	t_obj_type		type;
	t_objs			*(*f)(t_json json, t_temp_scene* scene,
						t_objs** parent, t_objs** tree);
}					t_obj_func;

t_scenes			*rt_parsing(t_elem *begin);

/*
**	CONFIG FUNCTIONS
*/
char				*json_string(t_elem *elem, t_elem *config, char *key);
void				json_min_max_int(int value, t_elem *config);
void				json_min_max_float(float value, t_elem *config);
t_elem				*get_childs_of_config(t_elem *parent);
t_elem				*get_config(char *key, t_elem *parent_config);
void				is_req_in_config(char *key, char *parent);
void				missing_in_json(char *key, char *parent);
void				missing_in_config(char *key, char *parent);
void				bad_limits_int(int min, int max, int value, char *key);
void				bad_limits_float(float min, float max, float value,
						char *key);
void				wrong_config_type(t_json_data actual, t_json_data should,
						char *key);
void				error_accepted_entries(char *value, t_elem *config,
					char *key);
t_elem				*get_children_of_parent(t_elem *parent);
t_elem				*get_config(char *key, t_elem *parent_config);
t_elem				*get_child_config(char *key, t_elem *parent_config);
t_elem				*get_config_by_key(t_elem *elem, char *key, char *parent);
int					check_req(t_elem *json, t_elem *config);
int					is_req(t_elem *config);
float				json_float_value_or_infinity(t_elem *elem, t_elem *config,
						char *key);
char				*json_string_value_or_null(t_elem *elem, t_elem *config,
						char *key);
float				json_float(t_elem *elem, t_elem *config, char *key);
char				*json_parse_string(t_elem *elem, t_elem *config);
int					json_bool(t_elem *elem, t_elem *config, char *key);
void				check_nbr_elements(int nbr_elems, t_elem *config);
t_elem				*get_conf_key_in_parent(t_elem *elem, char *key);
t_elem				*extract_config_child(t_elem *elem, char *error_key);
t_elem				*extract_child(t_elem *elem, t_elem *config, char *key,
						int check);
void				check_type(t_elem *json, t_elem *config);
void				check_req_type(t_elem *json, t_elem *config);
t_elem				*json_get_key(t_elem *elem, t_elem *config, char *key);
int					json_integer(t_elem *elem, t_elem *config, char *key);
int					json_parse_int(t_elem *elem, t_elem *config);
void				json_accepted_entries(t_elem *elem, t_elem *config);

/*
**	FIND ELEM
*/

t_elem				*get_elem_by_key(t_elem *elem, char *key);
t_json_data			get_type_of_key(char *key);
t_elem				*get_array_elem(t_elem *elem);
t_elem				*get_object_elem(t_elem *elem);
char				*get_string(t_elem *elem);
float				get_float(t_elem *elem);
int					get_integer(t_elem *elem);

/*
** CHECK TYPES
*/
int					check_type_of_key(char *key, t_json_data type);
int					check_float_keys(char *key);
int					check_int_keys(char *key);
int					check_bool_keys(char *key);

/*
**	RECOGNIZE OBJECTS
*/
int					is_quadric(t_obj_type type);
int					is_basic_quadric(t_obj_type type);
int					is_subtractable(t_obj_type type);

/*
** DEFAULT VALUE functions
*/

t_rgb				default_rgb(t_rgb rgb, t_rgb def);

/*
** PARSERS
*/
int					parse_hex(char *key);
t_vec3				parse_vec3(t_elem *elem, t_elem *config, char *key);
t_vec3				parse_vec3_to_rad(t_elem *elem, t_elem *config, char *key);
void				parse_cameras(t_temp_scenes *scenes, int nbr_scene,
						t_elem *parent_elem, t_elem *config);
float				parse_degree_to_rad(float angle);
t_vec3				parse_color(t_elem *elem, t_elem *config, char *key);
t_rgb				parse_rgb_and_val(t_elem *child_elem);
t_transform			parse_transform(t_elem *elem, t_elem *config,
						t_obj_type type);
t_matrix			parse_translation_matrix(t_vec3 pos);
t_matrix			parse_rotation_matrix(t_vec4 rot);
t_material			parse_material(t_elem *elem, t_elem *config);
t_temp_scene		parse_scene(t_elem	*elem, t_elem *config);
t_objs				*parse_object(t_json json, t_temp_scene *scene,
						t_objs **parent, t_objs **tree);
t_objs				*parse_sphere(t_json json, t_temp_scene *scene,
						t_objs **parent, t_objs **tree);
t_objs				*parse_quadric(t_json json, t_temp_scene *scene,
						t_objs **parent, t_objs **tree);
t_objs				*parse_cone(t_json json, t_temp_scene *scene,
						t_objs **parent, t_objs **tree);
t_objs				*parse_cylinder(t_json json, t_temp_scene *scene,
						t_objs **parent, t_objs **tree);
t_objs				*parse_capsule(t_json json, t_temp_scene *scene,
						t_objs **parent, t_objs **tree);
t_objs				*parse_torus(t_json json, t_temp_scene *scene,
						t_objs **parent, t_objs **tree);
t_objs				*parse_cube(t_json json, t_temp_scene *scene,
						t_objs **parent, t_objs **tree);
t_objs				*parse_plane(t_json json, t_temp_scene *scene,
						t_objs **parent, t_objs **tree);
t_objs				*parse_copy(t_json json, t_temp_scene *scene,
						t_objs **parent, t_objs **tree);
t_objs				*parse_light(t_json json, t_temp_scene *scene,
						t_objs **parent, t_objs **tree);
void				parse_child(t_temp_scene *scene, t_json json,
						t_objs **parent, t_objs **tree);
void				parse_common(t_default *def, t_elem *elem, t_elem *config,
						t_obj_type type);
void				parse_default_material(t_material *material,
						t_elem *config);

/*
**	INFORMATION HANDLERS
*/
t_vec3				handle_vec3(t_elem *elem, char *key,
						int required, t_vec3 default_vec);
float				handle_float(t_elem *elem, char *key, int required,
						float def_float);
int					handle_int(t_elem *elem, char *key, int required,
						int default_int);
float				handle_rad_float(t_elem *elem, char *key, int required,
						float def_float);
t_vec3				handle_rad_vec3(t_elem *elem, char *key,
						int required, t_vec3 default_vec);
t_matrix			handle_matrix(t_elem *elem, char *key, int required,
						t_matrix default_mat);
t_vec3				handle_rad_quadric_vec3(t_elem *elem, char *key,
						int required, t_vec3 default_vec);

/*
** ARTHIMETIC TOOLS
*/
int					is_equal_float(float a, float b);
int					is_equal_vec3(t_vec3 a, t_vec3 b);
int					is_opposite_vec3(t_vec3 a, t_vec3 b);
t_vec3				get_right_dir(t_vec3 dir);
t_vec3				get_up_dir(t_vec3 dir, t_vec3 right);
t_vec3				vec_rot_zaxis_angle(t_vec3 v, t_vec3 zaxis, float angle);
int					float_is_bigger(int included, float big, float x);
int					float_is_smaller(int included, float small, float x);
int					int_is_bigger(int included, int big, int x);
int					int_is_smaller(int included, int small, int x);

/*
** UTILS
*/
int					is_quadric(t_obj_type type);
int					is_basic_quadric(t_obj_type type);
int					is_subtractable(t_obj_type type);
t_vec4				qmult(t_vec4 q1, t_vec4 q2);
t_vec4				qconjugate(t_vec4 q);
t_vec3				qmulvec(t_vec3 v, t_vec4 q);
t_vec4				vec4_hadamard(t_vec4 a, t_vec4 b);
void				parent_not_quadric(t_objs *child, t_objs *parent);
void				child_not_quadric(t_objs *child, t_objs *parent);
void				both_are_quadrics(t_objs *child, t_objs *parent);
void				transform_child_with_parent(t_objs *child, t_objs *parent);
void				errors_in_cutting(t_objs *parent, t_objs *obj);
int					get_child_id_from_objs(t_objs *obj);
int					get_negative_from_objs(t_objs *obj);

/*
**	WORK ON MATRIX
*/
void				combine_child_and_parent(t_objs *parent, t_objs *obj,
						t_objs **tree);
void				calculate_all_matrices(t_objs **tree);
/*
**	ID SINGLETON
*/
int					get_obj_id(void);
void				set_id(int nbr);
void				add_id(int nbr);

/*
**	MERGE STRUCTURES
*/
t_quadric			merge_quadrics(t_temp_quadric quad);
void				merge_temp_scenes_to_scenes(t_temp_scenes *sc,
						t_scenes *new_scenes);

/*
** COLORS
*/
int					rgb_getvalue(t_rgb rgb);
void				rgb_updatevalue(t_rgb *rgb);
t_rgb				rgb_add(t_rgb a, t_rgb b);
t_rgb				rgb_mul_rgb(t_rgb a, t_rgb b);
t_rgb				rgb_mul(t_rgb a, float scalar);
t_rgb				rgb_div(t_rgb a, float scalar);
t_rgb				color_from_value(int value);
t_rgb				color_from_rgb_and_value(t_rgb color, t_rgb def_rgb);

/*
**	STRUCTURE FUNCTIONS
*/
t_objs				*new_objs(void *obj, t_obj_type type, char *name);
void				free_objs(t_objs *tree);
void				add_obj_to_chain(t_objs **main, t_objs *new);
t_obj_type			free_in_parent_tree_from_child(t_objs **tree, t_objs *obj);
t_objs				*get_obj_by_id(t_objs *main, int obj_id);
t_objs				*get_obj_by_natural_id(t_objs *main, int obj_id);
t_objs				*get_obj_by_name(t_objs **tree, char *key);
void				complete_object(t_objs *obj, t_json json, int natural_id);
int					number_of_objs_with_name(t_objs **tree, char *key);
t_objs				*copy_tree(t_objs **tree);
void				print_temp_quadric(t_temp_quadric quadric, int quad_nbr);
void				free_objs_parent(t_objs *tree);
void				feed_the_trees(t_objs **tree, t_objs *obj, int count);
#endif
