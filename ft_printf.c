#include "ft_printf.h"

void	ft_initialize(t_flags *flags)
{
	flags->dash = 0;
	flags->precision = 0;
	flags->width = 0;
	flags->dot = 0;
	flags->zero = 0;
	flags->negative = 0;
	flags->zero_per = 0;
}

static void	specifiers(const char *format, va_list ap,
				t_flags *flags, int *count)
{
	(*count)++;
	ft_verif_flags(format, ap, flags, count);
	if (format[(*count)] == 'c')
		ft_char(ap, flags);
	else if (format[(*count)] == 's')
		ft_string(ap, flags);
	else if (format[(*count)] == 'i' || format[(*count)] == 'd')
		ft_int(ap, flags);
	else if (format[(*count)] == 'p')
		ft_hex(ap, flags);
	else if (format[(*count)] == 'x')
		ft_uns_hex(ap, flags);
	else if (format[(*count)] == 'X')
		ft_uns_maj_hex(ap, flags);
	else if (format[(*count)] == 'u')
		ft_uns(ap, flags);
	else if (format[(*count)] == '%')
		ft_percent(flags);
	else
	{
		write(1, "%", 1);
		flags->ret++;
		(*count)--;
	}
	ft_initialize(flags);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_flags	flags;
	int		count;

	count = 0;
	flags.ret = 0;
	ft_initialize(&flags);
	va_start(ap, format);
	while (format[count])
	{
		if (format[count] == '%')
			specifiers(format, ap, &flags, &count);
		else
		{
			ft_putchar_fd(format[count], 1);
			flags.ret++;
		}
		count++;
	}
	va_end(ap);
	return (flags.ret);
}
