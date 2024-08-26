/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_clean_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:46:12 by marvin            #+#    #+#             */
/*   Updated: 2024/08/26 13:46:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_clean_input(char *pre_input)
{
	char	*new_input;
	int		dollar_count;
	int		idx;
	int		dquotes;

	dollar_count = 0;
	idx = 0;
	dquotes = 0;
	while (pre_input[idx] != '\n' && pre_input[idx])
	{
		if (pre_input[idx] == '$')
			dollar_count++;
		if (pre_input[idx] == '"')
			dquotes++;
		idx++;
	}
	new_input = ft_create_input(pre_input);
	while (dollar_count != 0)
	{
		ft_dollar_exp(&new_input, &dquotes);
		dollar_count--;
	}
	return (new_input);
}

char	*ft_create_input(char *old_input)
{
	char	*new_input;
	int		idx;
	int		idy;

	idx = 0;
	idy = 0;
	new_input = (char *)malloc(sizeof(char *) * ft_strlen(old_input) + 1);
	while (old_input[idx])
	{
		if (old_input[idx] == '"')
			idx++;
		if (old_input[idx] == '\n')
			break ;
		new_input[idy++] = old_input[idx++];
	}
	new_input[idy] = ' ';
	new_input[idy + 1] = '\0';
	return (new_input);
}
