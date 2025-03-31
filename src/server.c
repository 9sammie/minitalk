/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:40:48 by maballet          #+#    #+#             */
/*   Updated: 2025/03/29 16:35:18 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_str_index = 0;

int	get_strlen(int client_pid, int signum)
{
	static int		bit_count = 0;
	static int		len = 0;

	if (bit_count == 0)
		len = 0;
	if (signum == SIGUSR2)
		len |= (1 << bit_count);
	kill(client_pid, SIGUSR1);
	bit_count++;
	if (bit_count >= 32)
	{
		bit_count = 0;
		return (len);
	}
	return (0);
}

char	*store_str(int client_pid, char *str, int signum)
{
	static unsigned char	c = 0;
	static int				bit_count = 0;

	if (signum == SIGUSR2)
		c |= (1 << bit_count);
	kill(client_pid, SIGUSR1);
	bit_count++;
	if (bit_count >= 8)
	{
		str[g_str_index++] = c;
		c = 0;
		bit_count = 0;
	}
	return (str);
}

void	print_str(int len, char **str, int *receiving_len)
{
	static int	received_bits = 0;

	received_bits++;
	if (received_bits >= len * 8)
	{
		*receiving_len = 1;
		ft_printf_fd(1, "%s\n", *str);
		free(*str);
		*str = NULL;
		received_bits = 0;
		g_str_index = 0;
	}
}

char	*str_alloc(int len, int *receiving_len, char *str)
{
	if (len > 0)
	{
		*receiving_len = 0;
		str = malloc(sizeof(char) * (len + 1));
		if (!str)
			return (NULL);
		str[len] = '\0';
		g_str_index = 0;
	}
	return (str);
}

int	main(void)
{
	ft_printf_fd(1, "Server PID : %d\n", getpid());
	if (sigaction_server_init() == 1)
		return (1);
	while (1)
	{
		pause();
	}
	return (0);
}
