/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/24 19:54:28 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_point	       get_view_point(t_fdf *u, int y, int x)
{
    t_point     p;
    t_point	    p_tmp;

    p = u->map->map[y][x];
	p.x -= (double)(u->map->nb_col - 1) / 2.0f;
	p.y -= (double)(u->map->nb_row - 1) / 2.0f;
	p.z *= u->depth;
	p.z -= (double)(u->map->deep_min + u->map->deep_max) / 2.0f;

	p_tmp = p;
	p.x = cos(u->y) * p_tmp.x + sin(u->y) * p.z;
	p.z = -sin(u->y) * p_tmp.x + cos(u->y) * p.z;
	p.y = cos(u->x) * p_tmp.y - sin(u->x) * p.z;
	p.z = sin(u->x) * p_tmp.y + cos(u->x) * p.z;

	p.x = (p.x * u->scale) + u->offsetx;
	p.y = (p.y * u->scale) + u->offsety;
	return (p);
}


void        render_map_view_point(t_fdf *u)
{
    int			x;
	int			y;
    y = 0;
	while (y < u->map->nb_row)
	{
		x = 0;
		while (x < u->map->nb_col)
		{   
            t_point pooo = get_view_point(u, y, x);
            image_set_pixel(u->m_img, pooo.x, pooo.y, u->map->map[y][x].color);
            x++;
		}
		y++;
	}
}

void        render_map_view_cross(t_fdf *u)
{
    int			x;
	int			y;
    y = 0;
	while (y < u->map->nb_row)
	{
		x = 0;
		while (x < u->map->nb_col)
		{   
            if (x + 1 < u->map->nb_col)
                draw_vec(u, get_view_point(u, y, x), get_view_point(u, y, x + 1), u->m_img);
            if (y + 1 < u->map->nb_row)
                draw_vec(u, get_view_point(u, y, x), get_view_point(u, y + 1, x), u->m_img);
            if (y + 1 < u->map->nb_row && x + 1 < u->map->nb_col)
                draw_vec(u, get_view_point(u, y, x), get_view_point(u, y + 1, x + 1), u->m_img);
            if (y + 1 < u->map->nb_row && x + 1 < u->map->nb_col)
                draw_vec(u, get_view_point(u, y + 1, x), get_view_point(u, y, x + 1), u->m_img);
            x++;
		}
		y++;
	}
}

void        render_map_view_default_1(t_fdf *u)
{
    int			x;
	int			y;
    y = 0;
	while (y < u->map->nb_row)
	{
		x = 0;
		while (x < u->map->nb_col)
		{   
            if (x + 1 < u->map->nb_col)
                draw_vec(u, get_view_point(u, y, x), get_view_point(u, y, x + 1), u->m_img);
            if (y + 1 < u->map->nb_row)
                draw_vec(u, get_view_point(u, y, x), get_view_point(u, y + 1, x), u->m_img);
            x++;
		}
		y++;
	}
}

void        render_map_view_colored(t_fdf *u)
{
    int			x;
	int			y;
    y = 0;
	while (y < u->map->nb_row)
	{
		x = 0;
		while (x < u->map->nb_col)
		{   
            if (x + 1 < u->map->nb_col)
                draw_vec(u, get_view_point(u, y, x), get_view_point(u, y, x + 1), u->m_img);
            if (y + 1 < u->map->nb_row)
                draw_vec(u, get_view_point(u, y, x), get_view_point(u, y + 1, x), u->m_img);
            
            if (y + 1 < u->map->nb_row && x + 1 < u->map->nb_col)
            {
                t_point ttt;
                t_point ttt2;
                t_point ttt3;

                ttt = get_view_point(u, y + 1, x + 1);
                ttt2 = get_view_point(u, y, x + 1);
                while(ttt2.y < ttt.y)
                {
                    draw_vec(u, get_view_point(u, y, x), ttt2, u->m_img);
                    ttt2.y += 1;
                }
                ttt3 = get_view_point(u, y, x + 1);
                while(ttt3.x < ttt.x)
                {
                    draw_vec(u, get_view_point(u, y, x), ttt3, u->m_img);
                    ttt3.x += 1;
                }
                ttt2 = get_view_point(u, y + 1, x);
                while(ttt2.y < ttt.y)
                {
                    draw_vec(u, get_view_point(u, y, x), ttt2, u->m_img);
                    ttt2.y += 1;
                }
                ttt3 = get_view_point(u, y + 1, x);
                while(ttt3.x < ttt.x)
                {
                    draw_vec(u, get_view_point(u, y, x), ttt3, u->m_img);
                    ttt3.x += 1;
                }
            } 
            
            x++;
		}
		y++;
	}
}

void		render_map(t_fdf *u)
{
	clear_image(u->m_img);

    if (u->m_view == 1)
        render_map_view_default_1(u);
    else if (u->m_view == 3)
        render_map_view_cross(u);
    else if (u->m_view == 4)
        render_map_view_point(u);
    else if (u->m_view == 5)
        render_map_view_colored(u);
            
	mlx_put_image_to_window(u->mlx_ptr, u->win_ptr, u->m_img->ptr, 0, 0);

}

void        draw_palette(t_fdf *u, int cur_row)
{
	double alpha;
	int x;
	int y;
	int r;
    int color;

	alpha = 0;
	r = 123;
	x = 146;
	y = 146;
    int x2;
    int y2;
    double ooo = ((2 * PI) / 6);
	while(alpha < (2 * PI))
	{
        if (alpha <= ((2 * PI) / 6))
            color = get_color_between_two(RED, 0xff00ff, get_perc_from_val(alpha, 0, ooo));
        else if (alpha <= ((2 * PI) / 6) * 2)
            color = get_color_between_two(0xff00ff, BLUE, get_perc_from_val(alpha, ooo, ooo * 2));
        else if (alpha <= ((2 * PI) / 6) * 3)
            color = get_color_between_two(BLUE, 0x00ffff, get_perc_from_val(alpha, ooo * 2, ooo * 3));
        else if (alpha <= ((2 * PI) / 6) * 4)
            color = get_color_between_two(0x00ffff, GREEN, get_perc_from_val(alpha, ooo * 3, ooo * 4));
        else if (alpha <= (2 * PI) - (((2 * PI) / 3) / 2) )
            color = get_color_between_two(GREEN, 0xffff00, get_perc_from_val(alpha, ooo * 4, ooo * 5));
        else
            color = get_color_between_two(0xffff00, RED, get_perc_from_val(alpha,ooo * 5, ooo * 6));
		
        x2 = x + r * cos(alpha);
        y2 = y + r * sin(alpha);
        draw_vec(
			u, (t_point){x, y, 1, WHITE},
			(t_point){(int)((x + x2) / 2), (int)((y + y2) / 2), 1, color},
            u->p_img
		);
        draw_vec(
			u, (t_point){(int)((x + x2) / 2), (int)((y + y2) / 2), 1, color},
			(t_point){x2, y2, 1, BLACK},
            u->p_img
		);
		alpha += 0.0001;
	}
	mlx_put_image_to_window(u->mlx_ptr, u->win_ptr, u->p_img->ptr, MAP_SIZE + 1, cur_row + 1);
}


void        draw_rect_in_win(t_fdf *u, t_rectangle *rect)
{
    int x;
    int y;

    x = 0;
    while (rect->x + x < rect->x + rect->w)
    {
        mlx_pixel_put(u->mlx_ptr, u->win_ptr, rect->x + x, rect->y, rect->color);
        mlx_pixel_put(u->mlx_ptr, u->win_ptr, rect->x + x++, rect->y + rect->h, rect->color);
    }
       
    y = 0;
    while (rect->y + y < rect->y + rect->h)
    {
        mlx_pixel_put(u->mlx_ptr, u->win_ptr, rect->x, rect->y + y, rect->color);
        mlx_pixel_put(u->mlx_ptr, u->win_ptr, rect->x + rect->w, rect->y + y++, rect->color);
    }
}

void        draw_countour_stat(t_fdf *u)
{
    t_rectangle rect;

    rect.x = MAP_SIZE;
    rect.y = 0;
    rect.w = STAT_SIZE - 1;
    rect.h = MAP_SIZE - 1;
    rect.color = WHITE;
    draw_rect_in_win(u, &rect);
}

void        draw_boxed_text(t_fdf *u, char *str, int text_color, t_point *p)
{
    t_rectangle rect;

    rect.x = p->x;
    rect.y = p->y;
    rect.w = 10 * ft_strlen(str) + 20;
    rect.h = 30 ;
    rect.color = p->color;
    draw_rect_in_win(u, &rect);
    
    mlx_string_put(u->mlx_ptr, u->win_ptr, rect.x + 10, rect.y + 5,
        text_color, str);
}


void        draw_mid_sep_in_stat(t_fdf *u, int cur_row, int color, int h)
{
    int x;
    int y;

    y = cur_row;
    x = MAP_SIZE + (STAT_SIZE / 2);
    while (y < cur_row + h)
        mlx_pixel_put(u->mlx_ptr, u->win_ptr, x, y++, color);
}

void        draw_line_sep_in_stat(t_fdf *u, int cur_row, int color)
{
    int x;

    x = MAP_SIZE;
    while (x < MAP_SIZE + STAT_SIZE)
        mlx_pixel_put(u->mlx_ptr, u->win_ptr, x++, cur_row, color);
}

void        draw_name_centered(t_fdf *u, int cur_row, int color, char *str)
{
    int x;

    x = MAP_SIZE + ((STAT_SIZE / 2) - ((ft_strlen(str) * 10) / 2));
    mlx_string_put(u->mlx_ptr, u->win_ptr, x, cur_row, color, str);
}

void        draw_fill_choice(t_fdf *u, int cur_row, int color, int choice)
{
    int y;
    int xs;
    int xe;

    y = cur_row + 1;
    while (y < cur_row + 40)
    {
        if (choice)
        {
            xs = MAP_SIZE + 1;
            xe = MAP_SIZE + (STAT_SIZE / 2);
        }
        else
        {
            xs = MAP_SIZE + (STAT_SIZE / 2);
            xe = MAP_SIZE + STAT_SIZE - 1;
        }
        while (xs < xe)
            mlx_pixel_put(u->mlx_ptr, u->win_ptr, xs++, y, color);
        y++;
    }
}

void        draw_choice_m_view(t_fdf *u, int cur_row)
{
    int cur_col;
   
    u->m_view < 3 ? draw_fill_choice(u, cur_row, WHITE, u->m_view % 2) : 0 ; 
    u->m_view > 2 && u->m_view < 5 ? draw_fill_choice(u, cur_row + 40, WHITE, u->m_view % 2) : 0 ; 
    u->m_view > 4 ? draw_fill_choice(u, cur_row + 80, WHITE, u->m_view % 2) : 0 ; 
    draw_line_sep_in_stat(u, cur_row, WHITE);
    draw_mid_sep_in_stat(u, cur_row, WHITE, 40);
    cur_col = MAP_SIZE + ((STAT_SIZE / 4) - ((ft_strlen("Default 1") * 10) / 2));
    mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 10, (u->m_view == 1 ? BLACK : WHITE), "Default 1");
    cur_col = MAP_SIZE + (STAT_SIZE / 2) + ((STAT_SIZE / 4) - ((ft_strlen("Default 2") * 10) / 2));
    mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 10, (u->m_view == 2 ? BLACK : WHITE), "Default 2");
    draw_line_sep_in_stat(u, cur_row + 40, WHITE);    
    draw_mid_sep_in_stat(u, cur_row + 40, WHITE, 40);
    cur_col = MAP_SIZE + ((STAT_SIZE / 4) - ((ft_strlen("Cross") * 10) / 2));
    mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 50, (u->m_view == 3 ? BLACK : WHITE), "Cross");
    cur_col = MAP_SIZE + (STAT_SIZE / 2) + ((STAT_SIZE / 4) - ((ft_strlen("Point") * 10) / 2));
    mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 50, (u->m_view == 4 ? BLACK : WHITE), "Point");
    draw_line_sep_in_stat(u, cur_row + 80, WHITE);    
    draw_mid_sep_in_stat(u, cur_row + 80, WHITE, 40);
    cur_col = MAP_SIZE + ((STAT_SIZE / 4) - ((ft_strlen("Colored") * 10) / 2));
    mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 90, (u->m_view == 5 ? BLACK : WHITE), "Colored");
    cur_col = MAP_SIZE + (STAT_SIZE / 2) + ((STAT_SIZE / 4) - ((ft_strlen("Black") * 10) / 2));
    mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 90, (u->m_view == 6 ? BLACK : WHITE), "Black");
    draw_line_sep_in_stat(u, cur_row + 120, WHITE);


}

void        draw_choice_color(t_fdf *u, int cur_row)
{
    int cur_col;

    u->c_selected == 1 ? draw_fill_choice(u, cur_row, WHITE, 1) : 0 ; 
    u->c_selected == 2 ? draw_fill_choice(u, cur_row, WHITE, 0) : 0 ; 
    draw_line_sep_in_stat(u, cur_row, WHITE);
    draw_mid_sep_in_stat(u, cur_row, WHITE, 40);
    cur_col = MAP_SIZE + ((STAT_SIZE / 4) - ((ft_strlen("Min") * 10) / 2));
    mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 10, (u->c_selected == 1 ? BLACK : WHITE), "Min");
    cur_col = MAP_SIZE + (STAT_SIZE / 2) + ((STAT_SIZE / 4) - ((ft_strlen("Max") * 10) / 2));
    mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 10, (u->c_selected == 2 ? BLACK : WHITE), "Max");
    draw_line_sep_in_stat(u, cur_row + 40, WHITE);
}
void        draw_choice_s_view(t_fdf *u, int cur_row)
{
    int cur_col;

    draw_line_sep_in_stat(u, cur_row, WHITE);
    draw_mid_sep_in_stat(u, cur_row, WHITE, 40);
    cur_col = MAP_SIZE + ((STAT_SIZE / 4) - ((ft_strlen("Options") * 10) / 2));
    mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 10, (u->s_view == 1 ? BLACK : WHITE), "Options");
    cur_col = MAP_SIZE + (STAT_SIZE / 2) + ((STAT_SIZE / 4) - ((ft_strlen("Files") * 10) / 2));
    mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 10, (u->s_view == 2 ? BLACK : WHITE), "Files");
    draw_line_sep_in_stat(u, cur_row + 40, WHITE);
}
 

void        draw_options(t_fdf *u)
{
    
    // --------
    draw_line_sep_in_stat(u, 160, WHITE);

    // STR -> VIEW
    draw_name_centered(u, 170, WHITE, "Modes");

    // STR -> VIEW SELECT
    draw_choice_m_view(u, 200);

    // STR -> COLOR TITLE
    draw_name_centered(u, 330, WHITE, "Colors");

    // STR -> COLOR SELECT
    
    draw_choice_color(u, 360);


    draw_palette(u, 410);


    // cur_col = (STAT_SIZE / 2) - (ft_strlen("min") * 10 + 20) / 2;
    // cur_row += 40;
    // draw_boxed_text(u, "min", u->color_max, &(t_point){MAP_SIZE + cur_col, cur_row, 0, WHITE});
    
    // cur_row = 60;
    // ooo = (STAT_SIZE - (ft_strlen("Options") * 10 + ft_strlen("Files") * 10)) / 3;
    // cur_col = MAP_SIZE + ooo;
    // mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row, (u->s_view == 1 ? RED : WHITE), "Options");
    // cur_col = MAP_SIZE + ooo * 2 + ft_strlen("Options") * 10;
    // mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row, (u->s_view == 2 ? RED : WHITE), "Files");



}

void        reinit(t_fdf *u, char *str)
{
    int fd;


    if((fd = open(str, O_RDONLY)) < 1)
    {
        ft_putendl("errorrrrr");
        exit(0);
    }

    if ((!(init_fdf(u, 1))) || !parse_data(u, fd)) 
    {
        ft_putendl("errorrrr");
        exit (0);
    }
    close(fd);
    
    render_map(u);
    render_stat(u);



}

void        draw_file_list(t_fdf *u)
{

    int i;
    int j;

    i = 0;
    j = 100;
    while(u->lst_file[i])
    {
        draw_name_centered(u, j, WHITE, u->lst_file[i]);
        i++;
        j += 40;
    }

}



void        render_stat(t_fdf *u)
{
  
  mlx_put_image_to_window(u->mlx_ptr, u->win_ptr, u->s_img->ptr, MAP_SIZE, 0);

    draw_countour_stat(u);  
    
    // STR -> FILENAME
    draw_name_centered(u, 10, WHITE, "FDF by nboulif");
    // ####
    draw_fill_choice(u, 50, WHITE, u->s_view % 2);

    // STR -> OPTION/FILES SELECT
    draw_choice_s_view(u, 50);

    if (u->s_view == 1)
        draw_options(u);
    else if (u->s_view == 2)
        draw_file_list(u);
    
}