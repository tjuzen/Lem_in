/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/12/09 20:59:02 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// Augmente de 1 la valeur de selected pour A-B (== tmp) et B-A (== reversed)

int 	add_found_path(t_data_map *map, t_lemin *arg, t_node *room)
{
	printf("\n\nADD FOUND PATH\n\n");
	t_linkstab *tmp;

	while (room)
	{
		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
			tmp->selected++;
			print_colors(map, arg, tmp);
			if (tmp->reversed)
			{
				print_colors(map, arg, tmp->reversed);
				tmp->reversed->selected++;
			}
			printf("\n");
		}
		room = room->parent;
	}
	return (1);
}


int bellman_peugeot(t_data_map **map, t_lemin *arg)
{
	t_linkstab	*link;
	int			countrooms;

	countrooms = arg->totalrooms;
	link = (*map)->links;

	while (--countrooms > 0 && link)
	{
		link = (*map)->links;
		if (bellwhile_ford(link, arg) == 666)
			break;
	}

	return (1);
}

int new_duplicate(t_data_map *map, t_lemin *arg, t_linkstab *link)
{
	t_node		*out;
	t_node		*in = link->roomb;
	t_linkstab	*intern;

	if (!(out = ft_memalloc(sizeof(t_node))))
	{
		arg->malloc_error = 1;
		return (-1);
	}
	if (!(out->room = ft_strdup(link->roomb->room)))
	{
		arg->malloc_error = 1;
		free(out);
		return (-1);
	}
	if (!(intern = ft_memalloc(sizeof(t_linkstab))))
	{
		arg->malloc_error = 1;
		ft_strdel(&out->room);
		free(out);
		return (-1);
	}

	print_colors(map, arg, link);
	in->duplicated = 1;
	out->duplicated = 1;
	out->key = hashCode(out->room);
	out->paths = NULL;
	out->status = 'X';
	out->type = 'O';
	out->in = in;
	in->out = out;
	if (map->list[out->key % map->size] == NULL)
		map->list[out->key % map->size] = out;
	else
	{
		out->hash_next = map->list[out->key % map->size];
		map->list[out->key % map->size] = out;
	}
	printf("Je cree le out %s%c\n", out->room, out->type);
	intern->rooma = link->roomb;
	intern->roomb = out;
	intern->isactive = 1;
	intern->selected = 1;
	intern->rooma->in = intern->roomb;
	intern->roomb->out = intern->rooma;
	intern->rooma->type = 'I';
	intern->roomb->parent = intern->rooma;
	link->rooma->parent = out;
	printf("Je cree le lien interne %s%c ---> %s%c\n", intern->rooma->room, intern->rooma->type, intern->roomb->room, intern->roomb->type);
	add_it(arg, &map, intern);
	return (1);
}

void        update_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	t_linkstab *link;

	link = tmp;
	while (link->next)
	{
        if (link->rooma->type == 'I' && link->rooma->out != link->roomb)
			{
				print_colors(map, arg, link);

				printf("DEVIENS\n");
				link->rooma = link->rooma->out;
				print_colors(map, arg, link);
				printf("\n");
			}
		link = link->next;
	}
}

int duplicate_nodes(t_data_map *map, t_lemin *arg, t_node *room)
{
	printf("\n");

	t_linkstab *tmp;

	while (room)
	{
		tmp = lookuplink(map, room, room->parent);
		if (tmp)
		{
			if (tmp->roomb->status == 'X' && tmp->roomb->duplicated != 1)
				if (new_duplicate(map, arg, tmp) == -1)
					return (-1);
		}
		room = room->parent;
	}
	printf("\n");
	update_links(map, arg, map->links);
	return (1);
}

void inverse_links(t_data_map *map, t_lemin *arg, t_node *room)
{
	printf("\n");

	t_linkstab *tmp;
	t_node	*tmproom;

	while (room)
	{
		if (room->parent)
		printf("Parent de %s%c : %s%c\n", room->room,room->type, room->parent->room, room->parent->type);

		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
			printf("-------------------------+-+-+-+-+ %s%c ---> %s%c\n", tmp->rooma->room, tmp->rooma->type, tmp->roomb->room, tmp->roomb->type);
			tmproom = tmp->rooma;
			tmp->rooma = tmp->roomb;
			tmp->roomb = tmproom;
			tmp->weight = -1;
			tmp->inversed = 1;
		}
		room = room->parent;
	}
}

void check_inversed(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	while (tmp->next)
	{
		if (tmp->selected > 1)
			tmp->selected = 0;
		if (tmp->reversed && tmp->reversed->selected > 1)
			tmp->reversed->selected = 0;
		tmp = tmp->next;
	}
}

void add_path(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	int p;

	while (tmp->next)
	{
		if (tmp->selected == 1)
		{

			if ((tmp->rooma->in && tmp->rooma->in == tmp->roomb) || (tmp->rooma->out && tmp->rooma->out == tmp->roomb))
				p = 0;
			else
			{
				if (tmp->rooma->type == 'O' && tmp->rooma->in)
					tmp->rooma = tmp->rooma->in;
				if (tmp->roomb->type == 'O' && tmp->roomb->in)
					tmp->roomb = tmp->roomb->in;
				if (tmp->inversed != 1)
				{
					printf("|||| %s %s\n", tmp->rooma->room, tmp->roomb->room);
					if (tmp->rooma->paths == NULL)
						tmp->rooma->paths = tmp;
					else
					{
						tmp->nextpath = tmp->rooma->paths;
						tmp->rooma->paths = tmp;
					}
					if (tmp->roomb->paths == NULL)
						tmp->roomb->paths = tmp;
					else
					{
						tmp->nextpath = tmp->roomb->paths;
						tmp->roomb->paths = tmp;
					}
				}
			}
		}
		tmp = tmp->next;
	}

	t_linkstab *hihi = arg->start->paths;

	while (hihi)
	{
		printf("^^^ %s %s\n", hihi->rooma->room, hihi->roomb->room);
		hihi = hihi->nextpath;
	}
}
/*

1: Find the shortest path P1 from node s to node t
2: for i = 2,..., k
3: For node-disjoint paths, split the intermediate nodes of all Px where x < i (refer to Figure 3)
4: Replace each link of all Px where x < i with a reverse link of inverted link weight in the original graph
5: Find the shortest path Pi from node s to node t
6: Remove all overlapping links to get i disjoint paths Px where x ≤ i.

*/
int find_path(t_data_map **map, t_lemin *arg)
{
	t_node *tmp;
	int nombredepaths = 1;

	bellman_peugeot(map, arg);
	if (add_found_path((*map), arg, arg->end) == -1)
		return (-1);
	print_all_links((*map), arg, (*map)->links);

	while (nombredepaths--)
	{
		printf("\n\n\n                                   CA TOURNE \n\n\n");
		printf("je dup \n");
		if (duplicate_nodes((*map), arg, arg->end) == -1)
			return (-1);
			print_all_links((*map), arg, (*map)->links);

		printf("j'inverse \n");
		inverse_links((*map), arg, arg->end);
		print_all_links((*map), arg, (*map)->links);

		printf("je  reset\n");
		if (reset(map, arg, (*map)->links) == -1)
			return (-1);
			print_all_links((*map), arg, (*map)->links);

		printf("je bellman \n");
		bellman_peugeot(map, arg);
		if (add_found_path((*map), arg, arg->end) == -1)
			return (-1);
			print_all_links((*map), arg, (*map)->links);

		printf("je check inversed\n");
	 	check_inversed((*map), arg, (*map)->links);
		print_all_links((*map), arg, (*map)->links);

	}

	add_path((*map), arg, (*map)->links);
	printf("dddddd");
	return (1);
}
