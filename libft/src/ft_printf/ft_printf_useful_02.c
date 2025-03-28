/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_useful_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:39:34 by maballet          #+#    #+#             */
/*   Updated: 2025/03/20 22:14:26 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "projets/ft_printf.h"

int	ft_putstr_printf(int fd, char *s)
{
	int	len;

	len = 0;
	if (!s)
	{
		len += write(2, "(null)", 6);
		return (len);
	}
	write(fd, s, ft_strlen_printf(s));
	return (ft_strlen_printf(s));
}

int	ft_putnbr_printf(int fd, int n)
{
	long	num;
	int		len;

	num = n;
	len = 0;
	if (num < 0)
	{
		len += write(fd, "-", 1);
		num = -num;
	}
	if (num > 9)
		len += ft_putnbr_printf(fd, num / 10);
	len += ft_putchar_printf(fd, (num % 10) + '0');
	return (len);
}

int	ft_pnbrb(int fd, unsigned long n, char *base, unsigned long baselen)
{
	int		len;

	len = 0;
	if (n >= baselen)
		len += ft_pnbrb(fd, n / baselen, base, baselen);
	len += ft_putchar_printf(fd, base[n % baselen]);
	return (len);
}

int	ft_putptr(int fd, void *ptr)
{
	int				len;

	len = 0;
	if (!ptr)
	{
		len += write(2, "(nil)", 5);
		return (len);
	}
	len += write(fd, "0x", 2);
	len += ft_pnbrb(fd, (unsigned long)ptr, "0123456789abcdef", 16);
	return (len);
}

int	ft_putchar_printf(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}
