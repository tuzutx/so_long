/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:20:30 by nolaeche          #+#    #+#             */
/*   Updated: 2025/10/16 16:35:37 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"

#include <stdlib.h> // Para malloc y exit

// Definiciones de la ventana
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define WINDOW_TITLE "So_Long Pixel Test"

// Estructura de datos global para MLX
typedef struct s_data {
	void	*mlx; // Conexión a la MLX
	void	*win; // Puntero a la ventana
	void	*img; // Puntero a la imagen (buffer)
	char	*addr; // Dirección de memoria de la imagen
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

// --- FUNCIÓN DE DIBUJO OPTIMIZADA ---
// Implementación directa de la función my_mlx_pixel_put
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	// 1. Verificar límites (importante para evitar segfaults)
	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;

	// 2. Calcular la posición exacta en la memoria (offset)
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

	// 3. Escribir el color
	*(unsigned int *)dst = color;
}

// --- FUNCIÓN DE DIBUJO DE PRUEBA (Dibujar un gradiente) ---
void	draw_test_image(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			// Crear un color de gradiente simple basado en X e Y
			// Color = RRGGBB. Aquí usamos el valor de X para R y el de Y para G
			color = (x * 255 / WIN_WIDTH) << 16 | (y * 255 / WIN_HEIGHT) << 8;
			
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

// --- MANEJADOR DE EVENTOS (Para cerrar la ventana) ---
int	close_window(t_data *data)
{
	// Liberar memoria (se simplifica aquí, en el proyecto final debe ser exhaustivo)
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx); // Necesario para mlx_linux
	exit(0);
	return (0);
}


// --- FUNCIÓN PRINCIPAL ---
int	main(void)
{
	t_data	data;

	// 1. Inicializar la conexión MLX
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);

	// 2. Crear la ventana
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, WINDOW_TITLE);
	if (!data.win)
		return (1);
	
	// 3. Crear el buffer de imagen
	data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data.img)
		return (1);

	// 4. Obtener la dirección de memoria y los parámetros
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, 
								&data.line_length, &data.endian);

	// 5. Dibujar la imagen de prueba en el buffer
	draw_test_image(&data);
	
	// 6. Poner el buffer de imagen en la ventana
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	// 7. Configurar el hook de cerrado de ventana (cruz roja o ESC)
	// Hook para la cruz roja
	mlx_hook(data.win, 17, 0, close_window, &data); 
	
	// Hook para la tecla ESC (código 65307 o 53 en macOS/algunos Linux)
	// Depende de tu configuración de teclado en Linux, pero 17 es para la cruz
	
	// 8. Iniciar el loop de eventos de la MLX (mantiene la ventana abierta)
	mlx_loop(data.mlx);

	return (0);
}

