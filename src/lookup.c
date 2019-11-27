/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:30:57 by bsuarez-          #+#    #+#             */
/*   Updated: 2019/11/26 13:36:22 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_node	*lookup(t_data_map *map, unsigned long key, char *room)
{
	t_node *tmp;

	tmp = map->list[key % map->size];
	while (tmp)
	{
		// printf("Mon node %s\n", tmp->room);

		if (tmp->key == key && ft_strcmp(room, tmp->room) == 0)
				return (tmp);
		tmp = tmp->hash_next;
	}
	return (NULL);
}

// t_linkstab *lookuplinknode(t_node *a, t_node *b)
// {
// 	t_linkstab *find;
//
// 	find = a->to;
// 	while (find->nexto)
// 	{
// 		if (find->rooma == a && find->roomb == b)
// 			return (find);
// 		find = find->nexto;
// 	}
// 	return (NULL);
// }

t_linkstab *lookuplink(t_data_map *map, t_node *a, t_node *b)
{
	t_linkstab *find;

	find = map->links;
	while (find->next)
	{
		if (find->rooma == a && find->roomb == b)
			return (find);
		find = find->next;
	}
	return (NULL);
}
