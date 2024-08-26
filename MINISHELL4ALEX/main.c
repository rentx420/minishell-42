/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:43:23 by marvin            #+#    #+#             */
/*   Updated: 2024/08/26 13:43:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	pre_input[1024];
	char	*real_input;

	real_input = NULL;
	if (argc == 2 || argv[1])
		return (ft_error(0));
	while (1)
	{
		printf("custom_shell -> ");
		if (fgets(pre_input, sizeof(pre_input), stdin) == 0)
			return (0);
		ft_remove_nl(pre_input);
		ft_heredoc(pre_input);
		// add history
		real_input = ft_clean_input(pre_input);
		if (ft_builtin(real_input, envp) == 0)
			ft_init_minishell(real_input, envp);
		free(real_input);
	}
	return (0);
}

void	ft_remove_nl(char *pre_input)
{
	char	*pos;

	if ((pos = strchr(pre_input, '\n')) != NULL)
		*pos = '\0';
}

void	ft_heredoc(char *pre_input)
{
	int		s_quotes;
	int		d_quotes;
	char	*temp;
	char	hd_input[1024];

	s_quotes = ft_count_q(pre_input, 0);
	d_quotes = ft_count_q(pre_input, 1);
	while (s_quotes % 2 != 0 || d_quotes % 2 != 0)
	{
		printf("quote-> ");
		if (fgets(hd_input, sizeof(hd_input), stdin) == 0)
			return ;
		temp = ft_append_input(pre_input, hd_input);
		strcpy(pre_input, temp);
		free(temp);
		s_quotes = ft_count_q(pre_input, 0);
		d_quotes = ft_count_q(pre_input, 1);
	}
}

int	ft_count_q(char *input, int x)
{
	int	idx;
	int	count;

	count = 0;
	idx = 0;
	while (input[idx] && x == 0)
	{
		if (input[idx] == '\'')
			count++;
		idx++;
	}
	while (input[idx] && x == 1)
	{
		if (input[idx] == '"')
			count++;
		idx++;
	}
	return (count);
}

char	*ft_append_input(char *original, char *add)
{
	char	*new_input;
	int		len;

	len = strlen(original) + strlen(add) + 1;
	new_input = (char *)malloc(len * sizeof(char));
	if (!new_input)
		return (NULL);
	strcpy(new_input, original);
	strcat(new_input, add);
	return (new_input);
}
