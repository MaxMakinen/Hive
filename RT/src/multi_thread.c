/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:03:04 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/13 19:33:11 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	init_pthread(t_main *main)
{
	main->multi.tasks_done_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	main->multi.tasks_taken_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	main->multi.frame_start_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	main->multi.frame_end_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	main->multi.frame_start_cv = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	main->multi.frame_end_cv = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	main->multi.tasks_done = 0;
	main->multi.tasks_taken = 0;
}

void	create_threads(t_main *main, int ant_al)
{
	int	i;

	i = 0;
	main->ant_al = ant_al;
	while (i < NUM_THREADS)
	{
		pthread_create(&main->multi.threadpool[i],
			NULL, (void *(*)(void *))taskhandler, (void *)main);
		i++;
	}
}

static void	worker_wait(t_main *ctx)
{
	ctx->multi.threads_done++;
	pthread_mutex_unlock(&ctx->multi.tasks_taken_mutex);
	pthread_mutex_lock(&ctx->multi.frame_start_mutex);
	pthread_cond_wait(&ctx->multi.frame_start_cv,
			&ctx->multi.frame_start_mutex);
	pthread_mutex_unlock(&ctx->multi.frame_start_mutex);
}

static void	worker_task(int *task_n, t_main *ctx)
{
	*task_n = ctx->multi.tasks_taken;
	
	ctx->multi.tasks_taken++;
	pthread_mutex_unlock(&ctx->multi.tasks_taken_mutex);
	render_image(ctx, *task_n, ctx->ant_al);
	pthread_mutex_lock(&ctx->multi.tasks_done_mutex);
	ctx->multi.tasks_done++;
}

static void	worker_broadcast(t_main *ctx)
{
	ctx->multi.threads_done++;
	pthread_mutex_unlock(&ctx->multi.tasks_done_mutex);
	pthread_mutex_lock(&ctx->multi.frame_end_mutex);
	pthread_cond_broadcast(&ctx->multi.frame_end_cv);
	pthread_mutex_unlock(&ctx->multi.frame_end_mutex);
}

void	*taskhandler(void *main)
{
	t_main	*ctx;
	int			task_n;

	ctx = (t_main *) main;
	while (1)
	{
		
		pthread_mutex_lock(&ctx->multi.tasks_taken_mutex);
		if (ctx->multi.tasks_taken >= NUM_TASKS)
			worker_wait(ctx);
		else
		{
			worker_task(&task_n, ctx);
			if (ctx->multi.tasks_done >= NUM_TASKS)
			{
				worker_broadcast(ctx);
				break ;
			}
			else
				pthread_mutex_unlock(&ctx->multi.tasks_done_mutex);
		}
	}
	return (main);
}

int	draw_frame(t_main *main)
{
	main->multi.frame_n++;
	main->multi.threads_done = 0;
	pthread_mutex_lock(&main->multi.tasks_done_mutex);
	pthread_mutex_lock(&main->multi.tasks_taken_mutex);
	main->multi.tasks_taken = 0;
	main->multi.tasks_done = 0;
	pthread_mutex_unlock(&main->multi.tasks_taken_mutex);
	pthread_mutex_unlock(&main->multi.tasks_done_mutex);
	pthread_mutex_lock(&main->multi.frame_start_mutex);
	pthread_cond_broadcast(&main->multi.frame_start_cv);
	pthread_mutex_unlock(&main->multi.frame_start_mutex);
	pthread_mutex_lock(&main->multi.frame_end_mutex);
	pthread_cond_wait(&main->multi.frame_end_cv, &main->multi.frame_end_mutex);
	pthread_mutex_unlock(&main->multi.frame_end_mutex);
	return (1);
}
