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

/*
** Définition de ma structure
*/

typedef	struct	s_lemin
{
	int	ants;
	int wrong_line;
	int malloc_error;
	int start;
	int end;
}				t_lemin;

/*
** Définition de ma liste
*/

typedef struct s_list_lemin	t_list_lemin;

struct			s_list_lemin
{
	char	*room;
	char	status;
	t_list_lemin	*next;
};

/*
** STUPID_TOOLS.C
*/

t_list_lemin	*lstreturn_mallocerr(int value, t_lemin *arg);
int				intreturn_mallocerr(int value, t_lemin *arg);
void			init_arg(t_lemin *arg);
int 			exit_free(t_lemin *arg, t_list_lemin *mylist);
t_list_lemin	*return_delete(t_list_lemin *mylist, char *line);

/*
** LISTS.C
*/

t_list_lemin	*reverse_list(t_list_lemin *mylist);
t_list_lemin	*add_room(t_list_lemin *mylist, char *str, char state, t_lemin *arg);
void			print_delete(t_list_lemin *mylist, t_lemin *arg);
void			delete(t_list_lemin *mylist, t_lemin *arg);

/*
** PARSING.C
*/

t_list_lemin	*get_infos(char *line, t_list_lemin *mylist, t_lemin *arg);
t_list_lemin	*read_file(t_lemin *arg);

/*
** PARSING_TOOLS.C
*/

int 			get_number_of_ants(t_lemin *arg);
t_list_lemin	*start(t_lemin *arg, t_list_lemin *mylist);
t_list_lemin 	*end(t_lemin *arg, t_list_lemin *mylist);

/*
** VALID_LINE.C
*/

int 			is_room(char *line, t_lemin *arg);
int 			is_comment(char *line, t_lemin *arg);



#endif
