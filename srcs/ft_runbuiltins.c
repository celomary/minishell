/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_runbuiltins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settaqi <settaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:12:57 by settaqi           #+#    #+#             */
/*   Updated: 2020/10/14 11:39:54 by settaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_runrightcmd(t_command *item, int c)
{
	int		i;

	if (item->builtins == 1)
		ft_echo_builtins(item, c);
	else if (item->builtins == 2)
		ft_pwd(0);
	else if (item->builtins == 3)
		ft_changedirectory(item, c);
	else if (item->builtins == 4)
		printf("hello from export\n");
	else if (item->builtins == 5)
		ft_unset(item);
	else if (item->builtins == 6)
		update_print_env(c);
	else if (item->builtins == 7)
	{
		if (c == 0)
			printf("exit\n");
		exit(0);
	}
}
