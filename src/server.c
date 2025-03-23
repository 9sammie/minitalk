/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:40:48 by maballet          #+#    #+#             */
/*   Updated: 2025/03/24 00:36:50 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	get_strlen(int *len, int signum, siginfo_t *info, void *context)
{
    static int		bit_count = 0;
    static pid_t	client_pid = 0;

    (void)context;
    if (!client_pid)
        client_pid = info->si_pid;
    if (signum == SIGUSR2)
        *len |= (1 << bit_count);
    kill(client_pid, SIGUSR1);
    bit_count++;
    if (bit_count == 31)
    {
		ft_printf_fd(1, "ok");
        bit_count = 0;
        return (*len);
    }
	return (1);
}

char	*store_str(char *str, int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bit_count = 0;
	static pid_t			client_pid = 0;
	static int				i = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	if (signum == SIGUSR2)
		c |= (1 << bit_count);
	kill(client_pid, SIGUSR1);
	bit_count++;
	if (bit_count == 8)
	{
		ft_printf_fd(1, "%c", c);
		str[i++] = c;
		c = 0;
		bit_count = 0;
	}
	return (str);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int		len = 0;
	static char		*str = NULL;
	static int		receiving_len = 1;
	static int		received_bits = 0;

	if (receiving_len)
	{
		len = get_strlen(&len, signum, info, context);
		if (len > 0)
		{
			receiving_len = 0;
			received_bits = 0;
			str = malloc(sizeof(char) * (len + 1));
			if (!str)
				return ;
			str[len] = '\0';
		}
		return ;
	}
	str = store_str(str, signum, info, context);
	received_bits++;
	if (received_bits == len * 8)
	{
		ft_printf_fd(1, "%s\n", str);
		free(str);
		str = NULL;
		receiving_len = 1;
		len = 0;
		received_bits = 0;
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
