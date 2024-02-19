/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcervill <pcervill@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:47:51 by pcervill          #+#    #+#             */
/*   Updated: 2024/02/19 18:52:00 by pcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_env(char *str, char **env, int *i)
{
	char	*var;
	char	*tmp;
	int		j;
	int		k;
	int		l;

//	printf("%sENTRA EN CHECK_ENV%s\n", BLUE, NORMAL);
	var = ft_strdup("");
	tmp = ft_strdup("");
	j = 0;
	*i += 1;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		var[j++] = str[(*i)++];
	var[j++] = '=';
	var[j] = '\0';
	j = 0;
	while (env[j])
	{
		if (!ft_strncmp(var, env[j], (ft_strlen(var))))
		{
			l = ft_strlen(var);
			k = 0;
			while (env[j][l])
				tmp[k++] = env[j][l++];
			tmp[k] = '\0';
		}
		j++;
	}
	printf("new_stfgdfgfr ($): %s len: %zu\n", tmp, ft_strlen(tmp));
	return (tmp);
}

char	*detect_dollar_sign(char *str, char **env)
{
	int		i;
	char	*new_str;
	char	*tmp;

//	printf("%sENTRA EN DETECT_DOllAR\n%s", RED, NORMAL);
	new_str = ft_strdup("");
	tmp = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			new_str = ft_itoa(127);		// cambiar por señal de error
			printf("new_str ($?): %s\n", new_str);
			tmp = ft_strjoin(tmp, new_str);
			i += 2;
		}
		else if (str[i] == '$' && str[i + 1] == '_')
		{
			new_str = ft_strdup("env");
			tmp = ft_strjoin(tmp, new_str);
			i += 2;
		}
		else if (str[i] == '$' && (str[i + 1] != '"'
				|| str[i + 1] != '\'') && str[i + 1] != '\0')
		{
			new_str = check_env(str, env, &i);
			printf("new_str ($): %s\n", new_str);
			tmp = ft_strjoin(tmp, new_str);
			printf("tmp ($): %s\n", tmp);
		}
		else
		{
			tmp = ft_strjoin(tmp, &str[i]);
			i++;
		}
	}
	return (tmp);
}

int	cmp_dollar(char *str, int *i, char flag)
{
	*i += 1;
	while (str[*i] && str[*i] != flag)
	{
		if (str[*i] == '$')
		{
			while (str[*i + 1] != flag)
				(*i)++;
			if (flag == '\'')
				return (-1);
			return (1);
		}
		else
			(*i)++;
	}
	return (0);
}

int	quotes_dollar(char *str)
{
	int	i;
	int	double_q;
	int	single_q;

	i = 0;
	double_q = 0;
	single_q = 0;
	while (str[i])
	{
		if (str[i] == '\"' && single_q == 0 && double_q == 0)
		{
			double_q = cmp_dollar(str, &i, '\"');
		}
		if (str[i] == '\'' && double_q == 0)
		{
			single_q = cmp_dollar(str, &i, '\'');
		}
		if (single_q == -1)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

char	**expansor(char **str, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (dollar_sign(str[i]) != 0 && quotes_dollar(str[i]))
		{
//			printf("%sENTRA EN EXPANSOR%s\n", GREEN, NORMAL);
			tmp = detect_dollar_sign(str[i], env);
			printf("tmp: %s\n", tmp);
			free(str[i]);
			ft_strlcpy(str[i], tmp, ft_strlen(tmp) + 1);
			printf("str[i]: %s\n", str[i]);
		}
		i++;
	}
	return (str);
}

int	main(int argc, char **argv, char **env)
{
	char	**input;
	int		i;

	if (argc != 1 || argv[1])
		return (0);
	while (1)
	{
		i = 0;
		input = ft_split(readline(PROMPT_MSG), ' ');
		if (!input[0] || !ft_strcmp(input[0], "exit") || !ft_strcmp(input[0], ""))
		{
			printf("HASTA LUEGO\n");
			return (0) ;
		}
		input = expansor(input, env);
		printf("HOLA\n");
		while (input[i])
			printf("Nuevo input: %s\n", input[i++]);
	}
	return (0);
}

// /System/Volumes/Data/sgoinfre/students/pcervill/minishell

/*	TMPDIR
	ZSH
	NVM_DIR
	SSH_AUTH_SOCK
	MAIL
	PATH
*/