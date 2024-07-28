/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_and_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 04:02:33 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/28 04:14:23 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_and_free(char *str1, char *str2)
{
	char	*new_str;

	if (!str1 && str2)
		return (str2);
	if (!str2 && str1)
		return (str1);
	new_str = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (new_str);
}
