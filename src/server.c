/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:40:48 by maballet          #+#    #+#             */
/*   Updated: 2025/03/28 17:58:05 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	str_index = 0;

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
		str[str_index++] = c;
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
		ft_printf_fd(1, "%s\n", *str);
		free(*str);
		*str = NULL;
		received_bits = 0;
		str_index = 0;
		*receiving_len = 1;
	}
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int		len = 0;
	static char		*str = NULL;
	static int		receiving_len = 1;
	int				client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (receiving_len == 1)
	{
		len = get_strlen(client_pid, signum);
		if (len > 0)
		{
			receiving_len = 0;
			str = malloc(sizeof(char) * (len + 1));
			if (!str)
				return ;
			str[len] = '\0';
			str_index = 0;
		}
		return ;
	}
	str = store_str(client_pid, str, signum);
	print_str(len, &str, &receiving_len);
	if (receiving_len == 1)
	{
		kill(client_pid, SIGUSR2);
		len = 0;
	}
}

int	sigaction_init(void)
{
	struct sigaction	sa;
	
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf_fd(2, "Error: Failed to set up SIGUSR1\n");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf_fd(2, "Error: Failed to set up SIGUSR2\n");
		return (1);
	}
	return (0);
}

int	main(void)
{
	ft_printf_fd(1, "Server PID : %d\n", getpid());
	if (sigaction_init() == 1)
		return (1);
	while (1)
	{
		pause();
	}
	return (0);
}
