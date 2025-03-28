/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:08:25 by maballet          #+#    #+#             */
/*   Updated: 2025/03/20 22:13:54 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "projets/ft_printf.h"

int	ft_check(int fd, va_list ap, int *i, const char *s)
{
	int	len;

	len = 0;
	if (s[*i + 1] == 'c')
		len += ft_putchar_printf(fd, va_arg(ap, int));
	else if (s[*i + 1] == 's')
		len += ft_putstr_printf(fd, va_arg(ap, char *));
	else if (s[*i + 1] == 'p')
		len += ft_putptr(fd, va_arg(ap, void *));
	else if (s[*i + 1] == 'd' || s[*i + 1] == 'i')
		len += ft_putnbr_printf(fd, va_arg(ap, int));
	else if (s[*i + 1] == 'u')
		len += ft_pnbrb(fd, va_arg(ap, unsigned int), "0123456789", 10);
	else if (s[*i + 1] == 'x')
		len += ft_pnbrb(fd, va_arg(ap, unsigned int), "0123456789abcdef", 16);
	else if (s[*i + 1] == 'X')
		len += ft_pnbrb(fd, va_arg(ap, unsigned int), "0123456789ABCDEF", 16);
	else if (s[*i + 1] == '%')
		len += ft_putchar_printf(fd, '%');
	else
	{
		len += ft_putchar_printf(fd, s[*i]);
		len += ft_putchar_printf(fd, s[*i + 1]);
	}
	return (len);
}

int	ft_printf_fd(int fd, const char *s, ...)
{
	va_list	ap;
	int		i;
	int		len;

	va_start(ap, s);
	i = 0;
	len = 0;
	if (s == NULL || (s[i] == '%' && s[i + 1] == '\0'))
		return (-1);
	while (s[i])
	{
		if ((s[i] == '%' && !(ft_strchr_printf("cspdiuxX%", s[i + 1])))
			|| s == 0)
			return (-1);
		if (s[i] == '%')
		{
			len += ft_check(fd, ap, &i, s);
			i++;
		}
		else
			len = ft_putchar_printf(fd, s[i]) + len;
		i++;
	}
	va_end(ap);
	return (len);
}
