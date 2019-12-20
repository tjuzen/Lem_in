/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:35:51 by bsuarez-          #+#    #+#             */
/*   Updated: 2019/12/20 00:09:52 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# define BLACK    "\033[1;30m"
# define RED      "\033[1;31m"
# define GREEN    "\033[1;32m"
# define YELLOW   "\033[1;33m"
# define BLUE     "\033[1;34m"
# define PURPLE   "\033[1;35m"
# define CYAN     "\033[1;36m"
# define GREY     "\033[1;37m"
# define DEFAULT_COLOR "\033[0;m"
# define INFINITE INT_MAX - 10

/*
**	Définition de ma Data_Map
*/

typedef struct	s_node		t_node;
typedef struct	s_data_map	t_data_map;
typedef	struct	s_lemin		t_lemin;
typedef	struct	s_linkstab	t_linkstab;
typedef	struct	s_path		t_path;
typedef struct	s_ants		t_ants;


struct s_data_map
{
	unsigned long	size;
	t_node			**list;
	t_linkstab		*links;
	t_path			**way;
};

struct			s_node
{
	char			*room;		// nom
	char			type;		// Room in ou room out?
	unsigned long	key;
	unsigned long	pos;
	char			status;		// Start, end, ou autre ?
	int				weight;		// bellman
	t_node 			*parent;	// bellman ford nous set des parents pour chaque room
	t_node			*hash_next; // pour lookup
	t_node			*out;		 // lien vers Xo
	t_node			*in;  		// lien vers Xi
	t_linkstab		*paths;
	int				duplicated; // ma room a été dupliquée
};

struct			s_linkstab
{
	t_node			*rooma;
	t_node			*roomb;

	int 			weight; // poids du lien
	int				isactive; // en avons nous réellement besoin ?
	int				inversed; // Ci->Co deviens Co->Ci, etc
	int				selected; // mon chemin passe par la

	t_linkstab		*reversed; // Stoque l'opposé (A->B contient B->A)
	t_linkstab		*next; // liste de TOUS mes links
	t_linkstab		*nextpath; // lol
};

struct	s_lemin
{
	int				foundpath;
	int				ants;
	int				wrong_line;
	int				malloc_error;
	unsigned long	totalrooms;
	unsigned long	totalinks;
	int				total_weight;
	int				max_path;
	double			nbr_round;
	t_node			*start;
	t_node			*end;
	short			in;
	short			out;
	t_ants			*army;
	int				sum_path;
};

struct s_path
{
	int				path;
	int				weight;
	char			**path_list;
};

struct s_ants
{
	int				nbr;
	int				room;
	int				nrj;
	int				path;
	t_ants			*next;
};

/*
** LEM_IN.C
*/

int				main(void);
t_data_map		*createMap(unsigned long size, t_data_map *map);
t_node			*lookup(t_data_map *map, unsigned long key, char *room);
unsigned long 	hashCode(char *room);

/*
** LOOKUP.C
*/

t_node			*lookup(t_data_map *map, unsigned long key, char *room);
t_linkstab 		*lookuplink(t_data_map *map, t_node *a, t_node *b);

/*
** STUPID_TOOLS.C
*/

t_data_map		*lstreturn_mallocerr(int value, t_lemin *arg, t_data_map *map);
int				intreturn_mallocerr(int value, t_lemin *arg);
t_data_map		*init_arg(t_lemin *arg);
int 			exit_free(t_lemin *arg, t_data_map *map);
t_data_map		*return_delete(t_data_map *map, char *line);

/*
** ADD_INFO.C
*/

int				add_room(t_data_map **map, char *str, char status, t_lemin *arg);
int 			add_room_info(t_data_map **map, char stat, t_lemin *arg, t_node *new);
int				add_link(t_data_map **map, char *line, t_lemin *arg, int directed);
t_linkstab 		*add_link_info(t_linkstab *link, t_node *a, t_node *b, int directed);
void			add_it(t_lemin *arg, t_data_map **map, t_linkstab *newlink);

/*
** READ_FILE.C
*/

int 			read_file(t_lemin *arg, t_data_map **map);
int 			get_infos(char *line, t_data_map **map, t_lemin *arg);


/*
** PARSING_TOOLS.C
*/

int 			add_end_start(char *line, t_data_map **map, t_lemin *arg, char s);
int 			get_number_of_ants(char *line, t_lemin *arg);
int				max_path(t_lemin *arg, t_data_map **map);
int				check_links(t_data_map *map, t_node *a, t_node *b);
int				valid_end_start(int i, t_lemin *arg, char s);

/*
** VALID_LINE.C
*/

int				is_ant(char *line, t_lemin *arg);
int 			is_room(char *line, t_lemin *arg);
int 			is_comment(char *line, t_lemin *arg);
int				is_command(char *line);
int				is_link(char *line, t_data_map **map, t_lemin *arg);


/*
** LEM_IN.C
*/

unsigned long	hashCode(char *room);
t_data_map		*createMap(unsigned long size, t_data_map *map);
int				main(void);


/*
** ALGO_TOOLS.C
*/

int 	bellwhile_ford(t_linkstab *link, t_lemin *arg);
void 	reset_a(t_node *a);
void 	reset_b(t_node *b);
int 	reset(t_data_map **map, t_lemin *arg, t_linkstab *links);


/*
** ALGO.C
*/

int		find_nbr_way(t_data_map **map, t_lemin *arg, t_linkstab *links);
int 	add_found_path(t_data_map *map, t_lemin *arg, t_node *room);
int 	bellman_peugeot(t_data_map **map, t_lemin *arg);
void 	out_infos(t_data_map *map, t_lemin *arg, t_linkstab *link, t_node *out);
int 	intern_infos(t_data_map *map, t_lemin *arg, t_linkstab *link, t_node *out);
int 	new_duplicate(t_data_map *map, t_lemin *arg, t_linkstab *link);
void    update_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp);
int 	duplicate_nodes(t_data_map *map, t_lemin *arg, t_node *room);
void 	inverse_links(t_data_map *map, t_lemin *arg, t_node *room);
void 	check_inversed(t_data_map *map, t_lemin *arg, t_linkstab *tmp);
int 	stock_room_path(t_data_map **map, t_linkstab *tmp, t_linkstab *path, int way, t_lemin *arg);
int 	stock_path(t_data_map **map, t_lemin *arg, t_linkstab *links, int way);
int 	find_path(t_data_map **map, t_lemin *arg);


/*
** ADD_PATH_TOOLS.C
*/

t_node		*switch_room(t_linkstab *links, t_lemin *arg);
int			check_way(t_lemin *arg, t_data_map **map, t_linkstab *links, int way);
int 		check_follow(t_path *new, t_lemin *arg, t_node *links);


/*
** ADD_PATH.C
*/

t_node		*follow_path(t_path *new, t_lemin *arg, t_data_map **map, t_node *tmp);
int 		stock_path(t_data_map **map, t_lemin *arg, t_linkstab *links, int way);
int			find_nbr_way(t_data_map **map, t_lemin *arg, t_linkstab *links);
void		print_way(t_data_map **map, t_lemin *arg, int nbr, int ant);
void 		send_ant(t_data_map **map, t_lemin *arg, int nbr);

/*
** PARSING_TOOLS.C
*/

int 	get_number_of_ants(char *line, t_lemin *arg);
int		valid_end_start(int i, t_lemin *arg, char s);
int 	add_end_start(char *line, t_data_map **map, t_lemin *arg, char s);
int		gives_order(t_lemin *arg, t_path **way, int path);


/*
** PRINT.C
*/

void 	print_all_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp);
void 	print_colors(t_linkstab *tmp);

/*
** FREE_MAP.C
*/

int			exit_free(t_lemin *arg, t_data_map	*map);
void 		free_map(t_data_map* map);
void 		free_node(t_node* node);
t_data_map	*return_delete(t_data_map	*map, char *line);
t_data_map	*init_arg(t_lemin *arg);
t_data_map	*lstreturn_mallocerr(int value, t_lemin *arg, t_data_map *map);

#endif
