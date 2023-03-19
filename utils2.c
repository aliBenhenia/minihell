/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:20:50 by mazaroua          #+#    #+#             */
/*   Updated: 2023/03/18 13:37:45 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end_of_line(char *line, int i)
{
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	how_much_to_allocate(char *line)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			i++;
			j++;
			k = 0;
		}
		if (line[i] == ' ')
		{
			if (check_end_of_line(line, i))
				break;
			else if (k == 0)
			{
				j++;
				k = 1;
			}
			i++;
		}
	}
	return (j);
}

char *remove_additional_spaces(char *line)
{
	int		i;
	int		j;
	int		k;
	int		l;
    int     flag;
	char	*new;

	i = 0;
	j = how_much_to_allocate(line);
	k = 0;
    flag = 0;
	new = malloc(j + 1);
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] != ' ')
		{
            if ((line[i] == 34 || line[i] == 39) && flag == 1)
                flag = 0;
            else if (line[i] == 34 || line[i] == 39)
                flag = 1;
			new[k++] = line[i++];
			l = 0;
		}
		else if (line[i] == ' ')
		{
            if (flag == 1)
                new[k++] = line[i];
			else if (l == 0)
			{
				new[k++] = line[i];
				l = 1;
			}
			i++;
		}
	}
	new[k] = '\0';
    free(line);
	return (new);
}