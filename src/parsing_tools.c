/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:47:12 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/08 12:09:06 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 	get_number_of_ants(char *line, t_lemin *arg)
{
	if (arg->ants == -1)
		arg->ants = ft_atoi(line);
	if (arg->ants <= 0)
		return (-1);
	return (0);
}

int		valid_end_start(int i, t_lemin *arg, char s)
{
	if (s == 'I')
	{
		i = arg->in;
		arg->in = 1;
	}
	if (s == 'O')
	{
		i = arg->out;
		arg->out = 1;
	}
	return (i);
}

int 	add_end_start(char *line, t_data_map **map, t_lemin *arg, char s)
{
	int i;

	i = valid_end_start(0, arg, s);
	while (i == 0)
	{
		get_next_line(0, &line, 1);
		if (!line)
			return (-1);
		if (is_room(line, arg) == 1)
		{
			i++;
			add_room(map, line, s, arg);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (0);
}

int 	assign_ants(t_lemin *arg, int i, t_path *way, int j)
{
	t_ants *walker;
	// printf("ants: %02i weight: %02i path: %02i  actif %2i\n", i, way->weight, way->path, j);

	if (j == 1)
	{
		if (!(walker = ft_memalloc(sizeof(t_ants))))
			return (-1);
		walker->nbr = -1;
		walker->nrj = 0;
		walker->path = way->path;
		walker->room = 0;
		walker->spotted = j;
		if (arg->army == NULL)
			arg->army = walker;
		else
		{
			walker->next = arg->army;
			arg->army = walker;
		}
	}
	else
	{
		if (!(walker = ft_memalloc(sizeof(t_ants))))
			return (-1);
		walker->nbr = i;
		walker->nrj = way->weight;
		walker->path = way->path;
		walker->room = 0;
		walker->spotted = j;
		if (arg->army == NULL)
			arg->army = walker;
		else
		{
			walker->next = arg->army;
			arg->army = walker;
		}
	}
	return (0);
}

int		gives_order(t_lemin *arg, t_path **way, int path)
{
	int i;
	int a;
	int j;
	int l;
	int turn = 0;
	int antscount = 0;
	int modif = 1;
	int k = 0;
	int round;
	t_ants *list;

	i = 1;
	l = 1;
	a = 0;
	round = 1;
	printf ("path %i\n", path);

	while (i <= arg->ants)
	{
		j = 0;
		while (j < path && i <= arg->ants)
		{
			if (turn + way[j]->weight <= (int)arg->nbr_round + 1)
			{
				if ((assign_ants(arg, i++, way[j], 0)) == -1)
					return (-1);
				arg->army->turn = turn + 1;
				antscount++;
				a = j;
				printf ("  antscount %i turn %i path[%i] %i  NBR_ROUND: %i\n", antscount, turn, way[j]->path, way[j]->weight, (int)arg->nbr_round + 1);
			}
			j++;
		}
		turn++;
	}
	j = 0;
	i = 0;
	while (modif == 1)
	{
		list = arg->army;
		modif = 0;
		if (l > 0)
			printf ("[LINE]: %02i ", l);
		// int oui = ilyadesfourmisapush(list);
		while (list)
		{
			// printf("koukou: j: %i    path: %i     round : %i\n", j, path, round);
			if (list->nrj > 0 && list->turn <= l)
			{
				list->nrj--;
				printf ("L%02i-%s ", list->nbr, way[list->path]->path_list[list->room++]);
				modif = 1;
			}
			j++;
			// if (list->nbr == arg->ants)
			// {
			// 	break ;
			// }
			list = list->next;
		}
		k = 0;
		printf ("\n");
		j = 0;
		round -= -1;
		 l++;
		// if (list->nbr == arg->ants && list->nrj == 0)
		// 	return (l);
	}
	return (0);
}
