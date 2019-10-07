/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 15:30:27 by tjuzen            #+#    #+#             */
/*   Updated: 2018/10/27 16:04:12 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putendl(char const *s)
{
	int i;

	if (s)
	{
		i = 0;
		while (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
		ft_putchar('\n');
	}
}
