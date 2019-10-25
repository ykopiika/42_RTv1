/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:47:20 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/14 18:50:59 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include "SDL2/SDL.h"
# define ERR_USAGE			0
# define ERR_MALLOC			1
# define ERR_SDL			2
# define ERR_ARGV			3
# define ERR_LEN			4
# define ERR_ROWS			5

# define ERR_WRONG_SYMBOL	9
# define ERR_PIPE			10
# define ERR_DOT			12
# define ERR_NBR			13
# define ERR_MINUS			14
# define ERR_LINE			15

# define WIDTH				1200
# define HEIGHT				800
# define MAX_LEN			200
# define MAX_ROWS			400
# define INTRSCT_EPSILON	0.00001
# define INF				1000000
# define PIPE_NBR			8
# define COMNT				'+'
# define CAMERA				9
# define CMR_NBR			6

enum			e_lights
{
	AMBIENT = 1,
	POINT = 2,
	DIRECTIONAL = 3,
};

enum			e_figures
{
	NON = 10,
	SPHERE = 11,
	PLANE = 12,
	CONE = 13,
	CYLINDER = 14,
};

enum			e_numbers
{
	SPHR_NBR = 8,
	PLN_NBR = 10,
	CLDR_NBR = 11,
	CONE_NBR = 11,
	AMBNT_NBR = 1,
	PNT_NBR = 4,
	DIR_NBR = 4,
};

typedef struct			s_trace_dist
{
	double				t1;
	double				t2;
}						t_td;

typedef struct			s_vct
{
	double				x;
	double				y;
	double				z;
}						t_vct;

typedef struct			s_keys
{
	_Bool				kp_1;
	_Bool				kp_2;
	_Bool				kp_3;
	_Bool				kp_4;
	_Bool				kp_5;
	_Bool				kp_6;
}						t_keys;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Surface			*surf_win;
}						t_sdl;

typedef struct			s_clr
{
	int					r;
	int					g;
	int					b;
	int					a;
}						t_clr;

typedef struct			s_fgrs
{
	int					type;
	t_vct				center;
	double				radius;
	t_vct				color;
	int					specul;
	t_vct				dir;
	double				angl;

	struct s_fgrs		*next;
}						t_fgrs;

typedef struct			s_lght
{
	int					type;
	double				intensity;
	t_vct				pos;

	struct s_lght		*next;
}						t_lght_lst;

typedef struct			s_rt
{
	t_vct				l_dir;
	t_vct				cmr_pos;
	t_vct				dir;
	double				t_min;
	double				t_max;
}						t_rt;

typedef struct			s_intrsct
{
	double				cls_trace;
	t_fgrs				*clsst_fgrs;
}						t_intrsct;

typedef struct			s_light_for_calculation
{

	double				intens_defus;
	double				intens_specul;
	t_clr				color;
	t_vct				pnt;
	t_vct				nrml;

	t_fgrs				*figures;
	t_lght_lst			*lights;
}						t_light_calk;

typedef struct			s_read
{
	char				*line;
	int					row;
	int					len;

	struct s_read		*next;
	struct s_read		*prev;
}						t_read;

typedef struct			s_pasing
{
	int					type;
	int					nbrs;
	t_fgrs				*fgrs;
	t_lght_lst			*lghts;
}						t_parse;

typedef struct			s_for_get_value
{
	int					i;
	int					j;
	int					len;
	char				*str;
}						t_get_val;

typedef struct			s_normal_calculate
{
	double				dir;
	double				scalar_m;
	double				dirc_orig_cntr;
	t_vct				orig_cntr;
	t_vct				pnt_cntr;
}						t_calc;

typedef struct			s_data
{
	t_sdl				sdl;
	t_keys				keys;

	t_read				*read;
	t_fgrs				*figures;
	t_lght_lst			*lights;

	t_vct				cmr_pos;
	t_vct				rotate_rad;

}						t_data;

void					iterate_every_pixel(t_sdl *sdl, t_fgrs *fgrs,
											t_lght_lst *lght, t_data *d);
void					lighting_calculate(t_light_calk *v, t_vct *ray_dir,
											t_fgrs *closest_sphere);
void					figures_normal(t_vct *dst, t_vct point,
											t_intrsct in, t_rt *ray);
t_td					sphere_intersection(t_vct *origin, t_vct *ray_dir,
											t_fgrs *sphere);
int						check_type_count_nbrs(char *str, int len,
											t_read *read, int *nb);
void					which_figure_closer(t_fgrs *figure, t_intrsct *in,
											t_rt *r);
t_td					calculate_discriminant(double coeff1, double coeff2,
											double coeff3);
t_td					cylinder_intersection(t_vct *origin, t_vct *ray_dir,
											t_fgrs *cylinder);
t_td					cone_intersection(t_vct *origin, t_vct *ray_dir,
											t_fgrs *cone);
t_td					plane_intersection(t_vct *origin, t_vct *ray_dir,
											t_fgrs *plane);
void					camera_rotate(t_vct *dir_ray,
											const t_vct *restrict rot);
void					print_error(int error, int row);
void					game_loop(t_data *data);
void					keyboard(t_data *d);
void					ft_nrmlz_vector(t_vct *vector);
double					ft_dot(t_vct *v1, t_vct *v2);
double					ft_len_vector(t_vct *v);
t_vct					ft_sub_vectors(t_vct *v1, t_vct *v2);
t_vct					ft_add_vectors(t_vct *v1, t_vct *v2);
t_vct					ft_multiply_scalar(t_vct *v1, double scalar);
t_clr					ft_vector_to_color(t_vct *v);
t_lght_lst				*malloc_lght(t_lght_lst *lght);
t_fgrs					*malloc_fgrs(t_fgrs *fgr);
void					validation_file(t_data *data, int fd);
void					read_data(t_data *data);
_Bool					in_diapason(double nb, double min, double max);
void					min_max_vect(t_vct *v, double min, double max);
int						get_next_line2(const int fd, char **line);
void					min_max_double(double *dst, double min, double max);
void					min_max_int(int *dst, int min, int max);
void					value_clamp(t_parse *p);

#endif
