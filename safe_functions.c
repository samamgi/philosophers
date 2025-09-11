/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 11:05:30 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/07 11:27:50 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	handle_mutex_error(int etat, t_opcode status)
{
	if (etat == 0)
		return ;
	if (etat == EINVAL && (status == LOCK || status == UNLOCK))
		exit_error("Invalid settings in attr.");
	else if (etat == EINVAL && status == INIT)
		exit_error("Invalid settings in attr.\n");
	else if (etat == EDEADLK)
		exit_error("Locked Mutex");
	else if (etat == EPERM)
		exit_error("thread not locked on mutex");
	else if (etat == ENOMEM)
		exit_error("Cant allocate for a new mutex");
	else if (etat == EBUSY)
		exit_error("Mutex is locked");
}

static void	handle_thread_error(int status, t_opcode etat)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		exit_error("Insufficient resources to create another thread.\n");
	else if (status == EPERM)
		exit_error("No permission.\n");
	else if (status == EINVAL && etat == CREATE)
		exit_error("Invalid settings in attr.\n");
	else if (status == EINVAL && (etat == JOIN || etat == DETACH))
		exit_error("Invalid settings in attr.\n");
	else if (status == ESRCH)
		exit_error("No thread could be found corresponding to that");
	else if (status == EDEADLK)
		exit_error("A deadlock was detected or the value of");
}

void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode etat)
{
	if (etat == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), etat);
	else if (etat == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), etat);
	else if (etat == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), etat);
	else if (etat == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), etat);
	else
		exit_error("mutex unvalaible\n");
}

void	safe_thread_handle(pthread_t *thread, void *(*fct)(void *), void *data,
		t_opcode status)
{
	if (status == CREATE)
		handle_thread_error(pthread_create(thread, NULL, fct, data), status);
	else if (status == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), status);
	else if (status == DETACH)
		handle_thread_error(pthread_detach(*thread), status);
	else
		exit_error("Status unvalaible\n");
}
