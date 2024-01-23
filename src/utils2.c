/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:46:18 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/01/23 11:46:55 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_export(char **copy)
{
	int		i;
	char	**sorted_export;

	i = 0;
	ft_join_export(copy);
	sorted_export = ft_sort_export(copy);
	while (sorted_export[i])
	{
		printf("declare -x %s\n", copy[i]);
		i++;
	}
} 
char	**ft_update_export(char **exp, char **new_exp, char *var)
{
	int		i;

	i = 0;
	while (exp[i])
	{
		new_exp[i] = exp[i];
		i++;
	}
	new_exp[i] = var;
	return (new_exp);
}