/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_to_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 17:52:38 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 08:56:41 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_string_to_int(const char *str)
{
	int			i;
	long long	result;
	long long	neg;

	i = 0;
	neg = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || '9' < str[i])
			return (result * neg);
		else
			result = (result * 10) + (long long)(str[i] - '0');
		i++;
	}
	return (result * neg);
}
