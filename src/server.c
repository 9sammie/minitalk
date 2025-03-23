/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:40:48 by maballet          #+#    #+#             */
/*   Updated: 2025/03/23 15:26:12 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bit_count = 0;
	static pid_t			client_pid = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	if (signum == SIGUSR2)
		c = c | (1 << bit_count);
	kill(client_pid, SIGUSR1);
	bit_count++;
	if (bit_count == 8)
	{
		if (c == '\0' || c == '\n')
		{
			kill(client_pid, SIGUSR2);
			write(1, "\n", 1);
			client_pid = 0;
		}
		else
			write(1, &c, 1);
		c = 0;
		bit_count = 0;
	}
}

int	sigaction_init(void)
{
	struct sigaction	sa;
	
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = signal_handler;
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
		sleep(100);
	}
	return (0);
}
