/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_dollar_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:46:50 by marvin            #+#    #+#             */
/*   Updated: 2024/08/26 13:46:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_var_len(char *input, int idx)
{
	int	var_len;

	var_len = 1;
	while (input[idx + var_len] != ' ' && input[idx + var_len] != '"' && input[idx + var_len] &&
		input[idx + var_len] != '$')
		var_len++;
	return (var_len);
}

int	ft_var_newlen(char *input)
{
	int		idx;
	int		new_len;
	char	*var_value;
	int		var_len;
	char	*var_name;

	ft_init_doll(&new_len, &idx);
	while (input[idx])
	{
		if (input[idx] == '$')
		{
			var_len = ft_var_len(input, ++idx);	
			var_name = strndup(&input[idx], var_len);
			var_value = getenv(var_name);
			free(var_name);
			new_len += strlen(var_value);
			idx += var_len;
		}
		else
			ft_elevate_doll(&new_len, &idx);
	}
	return (new_len);
}

int	ft_cpy_value(char **input, char *new_input, int *idx, int idy)
{
	int		var_len;
	char	*var_name;
	char	*var_value;

	var_len = ft_var_len(*input, *idx);
	var_name = strndup(&(*input)[*idx + 1], var_len - 1);
	if (!var_name)
		return (-1);
	var_value = getenv(var_name);
	free(var_name);
	while (var_value && *var_value)
		new_input[idy++] = *var_value++;
	*idx += var_len;
	return (idy);
}

void ft_new_input(char **input, int new_len)
{
	char	*new_input;
	int		idx;
	int		idy;

	new_input = (char *)malloc(sizeof(char) * (new_len) + 1);
	if (!new_input)
		return;
	idx = 0;
	idy = 0;
	while ((*input)[idx])
	{
		if ((*input)[idx] == '$')
			idy = ft_cpy_value(input, new_input, &idx, idy);
		else
			new_input[idy++] = (*input)[idx++];
	}
	new_input[idy] = '\0';
	free(*input);
	*input = new_input;
}

void	ft_dollar_exp(char **input, int *dquotes)
{
	int	new_len;

	if (ft_previous_checks(*input, *dquotes) == 0)
		return ;
	new_len = ft_var_newlen(*input);
	if (new_len == -1)
		return ;
	ft_new_input(input, new_len);
	*dquotes -= 2;
}
