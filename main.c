/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:20:30 by nolaeche          #+#    #+#             */
/*   Updated: 2025/11/07 13:04:50 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"

#include <stdlib.h> // Para malloc y exit
#include <stdio.h>
#include <time.h>


typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int     w_is_down;
	time_t  w_press_time;
    time_t  last_time_printed;
}				t_vars;

int close_handler(int keycode, t_vars *vars)
{
    // Solo si el evento es una pulsación de tecla, verificamos si es ESC (Keycode 53 en macOS, 65307 o 0xFF1B en Linux/X11)
    if (keycode == 65307 || keycode == 0xFF1B) 
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0); // Opcional, pero asegura la salida limpia del programa
    }
    // Si no es el evento de teclado (es el botón rojo), simplemente cerramos:
    if (keycode == 0) // Usamos 0 o un valor que no sea un keycode válido para el evento 17
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return (0);
}


int resize_handler(int x, int y, t_vars *vars)
{
    (void)vars;
    printf("¡Ventana redimensionada! Nuevo tamaño: %d x %d\n", x, y);
    return (0);
}

int mouse_enter_handler(t_vars *vars)
{
    (void)vars;
    printf("Hello!\n");
    return (0);
}

// Handler para cuando el ratón sale (Evento 8 - LeaveNotify)
int mouse_leave_handler(t_vars *vars)
{
    (void)vars;
    printf("Bye!\n");
    return (0);
}

int key_down_handler(int keycode, t_vars *vars)
{
    // CIERRE INMEDIATO con ESC
    if (keycode == 65307)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    
    // PRUEBA DE TIEMPO con W
    if (keycode == 119)
    {
        if (vars->w_is_down == 0) // Solo registra el tiempo si no estaba ya presionado
        {
            vars->w_is_down = 1;
        }
    }
    return (0);
}

// B) Handler para desactivar la bandera (se llama una vez al soltar)
int key_up_handler(int keycode, t_vars *vars)
{
    // Desactiva la bandera de W cuando se suelta
    if (keycode == 119)
    {
        vars->w_is_down = 0;
    }
    return (0);
}

// C) Handler del Bucle (se llama continuamente)
// loop_checker
int loop_checker(t_vars *vars)
{
    if (vars->w_is_down == 1)
    {
        // 🆕 AHORA REGISTRAMOS EL TIEMPO DE INICIO EN EL PRIMER LOOP DETECTADO
        if (vars->w_press_time == 0) 
        {
            vars->w_press_time = time(NULL);
            vars->last_time_printed = 0; // Resetear la variable de impresión para la nueva cuenta
            printf("DEBUG: W activada. Tiempo de inicio registrado: %ld\n", vars->w_press_time);
            fflush(stdout);
        }
        
        time_t time_elapsed = time(NULL) - vars->w_press_time;
        
        // 1. CONTROL DE DEBUGGING: Solo imprime si el segundo ha cambiado
        if (time_elapsed != vars->last_time_printed)
        {
            printf("DEBUG: Tiempo transcurrido W: %ld segundos\n", time_elapsed);
            fflush(stdout);
            
            // Actualiza el último tiempo impreso
            vars->last_time_printed = time_elapsed;
        }

        // 2. LÓGICA DE DETECCIÓN FINAL: Imprime el mensaje de éxito
        if (time_elapsed >= 3)
        {
            printf("¡PRUEBA EXITOSA! La tecla W ha sido presionada por %ld segundos (más de 3).\n", 
                   time_elapsed);
            
            fflush(stdout); 
            vars->w_is_down = 0; 
            vars->w_press_time = 0; // 🆕 CRÍTICO: Reiniciar el tiempo para el siguiente uso
        }
    }
    // 🆕 CRÍTICO: Si la tecla se suelta, el tiempo debe resetearse también
    else if (vars->w_is_down == 0 && vars->w_press_time != 0) 
    {
        vars->w_press_time = 0;
        vars->last_time_printed = 0;
    }
    return (0);
}
int close_button_handler(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
    return (0);
}

int main(void)
{
    t_vars  vars;

    // Inicializar estado de tiempo para W
    vars.w_is_down = 0; 
    vars.w_press_time = 0;
    
    vars.mlx = mlx_init();
    if (!vars.mlx) return (1);
    vars.win = mlx_new_window(vars.mlx, 800, 600, "Event Full Test (W)");
    if (!vars.win) return (1);
    
    // --- 1. HOOKS DE TECLADO Y CIERRE ---
    
    // Tecla Presionada (Evento 2) - Maneja W (temporizador) y ESC (cierre)
    mlx_hook(vars.win, 2, 1L<<0, key_down_handler, &vars); 
    
    // Tecla Soltada (Evento 3) - Detiene el temporizador de W
    mlx_hook(vars.win, 3, 1L<<1, key_up_handler, &vars); 

    // Botón Rojo (DestroyNotify - Evento 17) - Cierre inmediato
    mlx_hook(vars.win, 17, 1L<<17, close_button_handler, &vars); 

    // --- 2. HOOKS DE RATÓN Y VENTANA ---
    
    // Ratón Entra (EnterNotify - Evento 7)
    mlx_hook(vars.win, 7, 1L<<4, mouse_enter_handler, &vars);
    
    // Ratón Sale (LeaveNotify - Evento 8)
    mlx_hook(vars.win, 8, 1L<<5, mouse_leave_handler, &vars); 

    // Ventana Redimensiona (ConfigureNotify - Evento 22)
    // Nota: El evento 22 es ConfigurationNotify. Se usa la máscara 1L<<17 (StructureNotifyMask)
    // porque es la máscara asociada para la mayoría de los eventos de estructura de ventana.
    mlx_hook(vars.win, 22, 1L<<17, resize_handler, &vars);
    
    // --- 3. BUCLE PRINCIPAL ---
    
    // Bucle Continuo - Chequea el tiempo de W
    mlx_loop_hook(vars.mlx, loop_checker, &vars);

    mlx_loop(vars.mlx);
    return (0);
}

