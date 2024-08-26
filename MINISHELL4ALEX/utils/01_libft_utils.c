/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_libft_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:44:48 by marvin            #+#    #+#             */
/*   Updated: 2024/08/26 13:44:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *string)
{
	int	len;

	len = 0;
	while (string[len] != '\0' && string[len] != '\n')
		len++;
	return (len);
}

int	ft_error(int x)
{
	if (x == 0)
	{
		printf("Error de entrada.\n");
		return (0);
	}
	return (0);
}

int	ft_strncmp(const char *str, const char *str2, size_t c)
{
	size_t			i;
	unsigned int	diff;

	diff = 0;
	i = 0;
	while ((str[i] != '\0') && (str2[i] != '\0')
		&& (diff == 0) && (i < c))
	{
		diff = (unsigned char)str[i] - (unsigned char)str2[i];
		i++;
	}
	if ((diff == 0) && (i < c))
		diff = (unsigned char)str[i] - (unsigned char)str2[i];
	return (diff);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > 2147483647)
			return (sign == -1 ? 0 : -1);
		result *= 10;
		result += (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	ft_free_spltinput(char **input)
{
	int	idx;

	idx = 0;
	while (input[idx])
	{
		free(input[idx]);
		idx++;
	}
	free(input);
	return ;
}
