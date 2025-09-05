/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:05:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/13 19:45:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	append_char(char **s, char c);
static void	handle_variable_expansion(t_expand_state *state, t_shell *shell);
static int	get_var_len(const char *arg);
static char	*get_var_value(const char *name, t_shell *shell);

char	*perform_expansion(const char *arg, t_shell *shell)
{
	t_expand_state	state;

	state.arg = arg;
	state.result = ft_strdup("");
	state.quote_state = 0;
	while (*state.arg)
	{
		if (state.quote_state == 0 && (*state.arg == '\'' || *state.arg == '"'))
			state.quote_state = *state.arg;
		else if (state.quote_state != 0 && *state.arg == state.quote_state)
			state.quote_state = 0;
		else if (*state.arg == '$' && state.quote_state != '\'')
			handle_variable_expansion(&state, shell);
		else
			append_char(&state.result, *state.arg);
		state.arg++;
	}
	return (state.result);
}

static void	handle_variable_expansion(t_expand_state *state, t_shell *shell)
{
	char	*var_name;
	char	*value;
	int		len;

	state->arg++;
	len = get_var_len(state->arg);
	if (len == 0)
	{
		append_char(&state->result, '$');
		return ;
	}
	var_name = ft_substr(state->arg, 0, len);
	value = get_var_value(var_name, shell);
	append_str(&state->result, value);
	if (*var_name == '?')
		free(value);
	free(var_name);
	state->arg += len - 1;
}

static int	get_var_len(const char *arg)
{
	int	len;

	len = 0;
	if (*arg == '?')
		len = 1;
	else if (ft_isalpha(*arg) || *arg == '_')
		while (ft_isalnum(arg[len]) || arg[len] == '_')
			len++;
	return (len);
}

static char	*get_var_value(const char *name, t_shell *shell)
{
	if (*name == '?')
		return (ft_itoa(shell->exit_status));
	return (get_env_value(shell->env_list, name));
}

static void	append_char(char **s, char c)
{
	int		len;
	char	*new;

	len = 0;
	if (*s)
		len = ft_strlen(*s);
	new = malloc(len + 2);
	if (!new)
		return ;
	if (*s)
		ft_memcpy(new, *s, len);
	new[len] = c;
	new[len + 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}
