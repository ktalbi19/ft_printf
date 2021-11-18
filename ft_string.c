#include "ft_printf.h"

void	ft_string_next(t_flags *flags, char *str, int *len)
{
	int		space;
	int		zero;

	if (flags->width > (*len) && flags->zero)
		zero = flags->width - (*len);
	else
		zero = 0;
	if (flags->width > (*len) && !zero)
		space = flags->width -(*len);
	else
		space = 0;
	flags->ret = flags->ret + (*len) + space + zero;
	if (!flags->dash)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
	if (flags->zero)
		while (zero-- > 0)
			ft_putchar_fd('0', 1);
	while ((*len)--)
		ft_putchar_fd(*str++, 1);
	if (flags->dash)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
}

void	ft_string(va_list ap, t_flags *flags)
{
	char	*str;
	int		len;
	char	*str_null;

	str_null = "(null)";
	str = va_arg(ap, char *);
	if (!str)
		str = str_null;
	len = ft_strlen(str);
	if (flags->precision < len && flags->precision > 0)
		len = flags->precision;
	else if (flags->dot && !flags->precision)
		len = 0;
	ft_string_next(flags, str, &len);
}
