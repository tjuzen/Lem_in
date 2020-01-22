/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 11:32:43 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/22 10:05:40 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_freetab_str(char **element)
{
	int i;

	i = -1;
	if (!element)
		return ;
	while (element[++i])
		free(element[i]);
	free(element);
}
