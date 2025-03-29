/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 11:43:32 by maballet          #+#    #+#             */
/*   Updated: 2025/03/29 16:08:45 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	param_check(int argc, char**argv)
{
	int		i;
	long	server_pid;

	i = 0;
	if (argc < 3 || argv[2][0] == 0)
	{
		ft_printf_fd(2, "Message missing 🛟\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid < INT_MIN || server_pid > INT_MAX || server_pid <= 0)
	{
		ft_printf_fd(2, "Invalid PID 🛟\n");
		return (1);
	}
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			ft_printf_fd(2, "Invalid PID 🛟\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	send_message(pid_t pid, char *message)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(message);
	send_len(pid, len);
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
}
