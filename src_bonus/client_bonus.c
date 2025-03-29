/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:22:26 by maballet          #+#    #+#             */
/*   Updated: 2025/03/29 16:08:44 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_signal_received = 0;

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_signal_received = 1;
	if (signum == SIGUSR2)
		ft_printf_fd(1, "Message entirely received by the server 🏝️\n");
}

void	send_char(pid_t pid, unsigned char c)
{
	int	bit_index;
	int	time_out;

	time_out = 0;
	bit_index = 0;
	while (bit_index < 8)
	{
		g_signal_received = 0;
		if ((c &(1 << bit_index)) != 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (g_signal_received == 0)
		{
			pause();
		}
		bit_index++;
	}
}

void	send_len(pid_t pid, int len)
{
	int	bit_index;
	int	time_out;

	time_out = 0;
	bit_index = 0;
	while (bit_index < 32)
	{
		g_signal_received = 0;
		if ((len &(1 << bit_index)) != 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (g_signal_received == 0)
		{
			pause();
		}
		bit_index++;
	}
}

int	sigaction_init(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	char				*message;

	if (argc > 3)
	{
		ft_printf_fd(2, "Too many arguments 🛟\n");
		return (1);
	}
	if (param_check(argc, argv) == 1)
		return (1);
	sigaction_init();
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) != 0)
	{
		ft_printf_fd(2, "No process with PID : %d 🛟\n", server_pid);
		return (1);
	}
	message = argv[2];
	ft_printf_fd(1, "Sending message to the server 🏄 (PID: %d)\n", server_pid);
	send_message(server_pid, message);
	return (0);
}
