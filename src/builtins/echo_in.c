/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:32:52 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/02/13 12:58:47 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	printf_args(int i, char **str, int fd)
{
    while (str[i])
    {
        ft_putstr_fd(str[i], fd);
        if (str[i + 1])
            ft_putstr_fd(" ", fd);
        i++;
    }
}

int	ft_echo(t_tools *tools, t_simple_cmds *simple_cmds)
{
	int     i;
	int     j;
    bool    flag;
    i = 1;
    
    (void) tools;
    flag = false;
    printf("\n");
    while (simple_cmds->str[i] && simple_cmds->str[i][0] == '-' && simple_cmds->str[i][1] == 'n')
    {
        j = 1;
        while (simple_cmds->str[i][j] == 'n')
            j++;
        if (simple_cmds->str[i][j] == '\0')
            flag = true;
        i++;
    }
    printf_args(i, simple_cmds->str, STDOUT_FILENO);
    if (flag == false)
        printf("\n");
    return (EXIT_SUCCESS);
}
