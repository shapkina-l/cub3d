
#include "../../includes/cub3d.h"

// // X11 Event Codes
// #define KeyPress        2
// #define KeyRelease      3
// #define ButtonPress     4    // Mouse button press
// #define ButtonRelease   5    // Mouse button release
// #define MotionNotify    6    // Mouse movement
// #define EnterNotify     7    // Mouse enters window
// #define LeaveNotify     8    // Mouse leaves window
// #define FocusIn         9    // Window gains focus
// #define FocusOut        10   // Window loses focus
// #define Expose          12   // Window needs redraw
// #define DestroyNotify   17   // Window is being destroyed

// // X11 Event Masks (what events to capture)
// #define NoEventMask         0L
// #define KeyPressMask        (1L<<0)  // Capture key presses
// #define KeyReleaseMask      (1L<<1)  // Capture key releases
// #define ButtonPressMask     (1L<<2)  // Capture mouse button presses
// #define ButtonReleaseMask   (1L<<3)  // Capture mouse button releases
// #define PointerMotionMask   (1L<<6)  // Capture mouse movement
// #define StructureNotifyMask (1L<<17) // Capture window structure changes

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		exit_game(game);
	else if (keycode == W_KEY)
		game->player->move_forward = 1;
	else if (keycode == S_KEY)
		game->player->move_backward = 1;
	else if (keycode == A_KEY)
		game->player->move_left = 1;
	else if (keycode == D_KEY)
		game->player->move_right = 1;
	else if (keycode == LEFT_KEY)
		game->player->rotate_left = 1;
	else if (keycode == RIGHT_KEY)
		game->player->rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		exit_game(game);
	else if (keycode == W_KEY)
		game->player->move_forward = 0;
	else if (keycode == S_KEY)
		game->player->move_backward = 0;
	else if (keycode == A_KEY)
		game->player->move_left = 0;
	else if (keycode == D_KEY)
		game->player->move_right = 0;
	else if (keycode == LEFT_KEY)
		game->player->rotate_left = 0;
	else if (keycode == RIGHT_KEY)
		game->player->rotate_right = 0;
	return (0);
}

int	setup_events(t_game *game)
{
	mlx_hook(game->mlx->win_ptr, 2, (1L << 0), key_press, game);
	mlx_hook(game->mlx->win_ptr, 3, (1L << 1), key_release, game);
	mlx_hook(game->mlx->win_ptr, 17, (1L << 17), exit_game, game);
	mlx_loop_hook(game->mlx->mlx_ptr, game_loop, game);
	return (0);
}