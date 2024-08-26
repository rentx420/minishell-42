/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_dollar_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:44:25 by marvin            #+#    #+#             */
/*   Updated: 2024/08/26 13:44:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_elevate_doll(int *new_len, int *idx)
{
	*new_len += 1;
	*idx += 1;
}

void	ft_init_doll(int *new_len, int *idx)
{
	*new_len = 0;
	*idx = 0;
}

int	ft_previous_checks(char *input, int dquotes)
{
	char	*var;
	int		idx;
	int		idy;

	idy = 0;
	idx = 0;
	var = malloc(sizeof(char) * 42);
	while (input[idx])
	{
		if (input[idx] == '$')
		{
			while (input[idx + 1] != ' ' && input[idx + 1])
				var[idy++] = input[++idx];
			break ;
		}
		idx++;
	}
	var[idy] = '\0';
	if (getenv(var) == NULL || dquotes < 2)
	{
		free(var);
		return (0);
	}
	free(var);
	return (1);
}

int ft_is_cmd(char *input)
{
    char *path;
    char *path_dup;
    char *dir;
    char complete_path[1024];

    path = getenv("PATH");
    if (!path)
        return 0;

    path_dup = strdup(path);
    if (!path_dup)
        return 0;

    dir = strtok(path_dup, ":");
    while (dir != NULL)
    {
        strcpy(complete_path, dir);
        if (complete_path[strlen(complete_path) - 1] != '/')
            strcat(complete_path, "/");
        strcat(complete_path, input);
        if (access(complete_path, X_OK) == 0)
        {
            free(path_dup);
            return 1;
        }
        dir = strtok(NULL, ":");
    }
    free(path_dup);
    return 0;
}

int ft_are_cmds(char *input)
{
    char *cmd;
    char *input_dup = strdup(input);
    if (!input_dup)
        return 0;

    cmd = strtok(input_dup, ";");
    while (cmd != NULL)
    {
        while (*cmd == ' ') cmd++;
        char *end = cmd + strlen(cmd) - 1;
        while (end > cmd && *end == ' ') end--;
        *(end + 1) = '\0';

        if (!ft_is_cmd(cmd))
        {
            free(input_dup);
            return 0;
        }
        cmd = strtok(NULL, ";");
    }
    free(input_dup);
    return 1;
}
