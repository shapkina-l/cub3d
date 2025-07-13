/* Function to display a loaded texture in a window for testing */

#include "../includes/cub3d.h" // Your header file

// Display texture in a separate window for testing
void display_texture_test(t_game *game, t_texture *tex, char *texture_name)
{
    void    *test_win;
    void    *test_img;
    char    *test_addr;
    int     bpp, line_len, endian;
    int     x, y;
    int     color;
    
    if (!tex || !tex->img)
    {
        printf("Error: Texture %s not loaded!\n", texture_name);
        return;
    }
    
    // Create test window
    test_win = mlx_new_window(game->mlx, tex->width, tex->height, texture_name);
    if (!test_win)
    {
        printf("Error: Could not create test window\n");
        return;
    }
    
    // Create image for the test window
    test_img = mlx_new_image(game->mlx, tex->width, tex->height);
    test_addr = mlx_get_data_addr(test_img, &bpp, &line_len, &endian);
    
    // Copy texture data to test image
    y = 0;
    while (y < tex->height)
    {
        x = 0;
        while (x < tex->width)
        {
            // Get pixel color from texture
            color = *(int*)(tex->addr + (y * tex->line_len + x * (tex->bpp / 8)));
            
            // Put pixel to test image
            *(int*)(test_addr + (y * line_len + x * (bpp / 8))) = color;
            x++;
        }
        y++;
    }
    
    // Display the image
    mlx_put_image_to_window(game->mlx, test_win, test_img, 0, 0);
    
    printf("Texture %s loaded successfully!\n", texture_name);
    printf("Dimensions: %dx%d\n", tex->width, tex->height);
    printf("Bits per pixel: %d\n", tex->bpp);
    printf("Line length: %d\n", tex->line_len);
    printf("Press any key in the texture window to continue...\n");
    
    // Clean up test image
    mlx_destroy_image(game->mlx, test_img);
}

// Alternative: Print texture info to console
void print_texture_info(t_texture *tex, char *texture_name)
{
    printf("=== Texture Info: %s ===\n", texture_name);
    if (!tex || !tex->img)
    {
        printf("❌ Texture not loaded!\n");
        return;
    }
    
    printf("✅ Texture loaded successfully\n");
    printf("📏 Dimensions: %dx%d pixels\n", tex->width, tex->height);
    printf("🎨 Bits per pixel: %d\n", tex->bpp);
    printf("📐 Line length: %d bytes\n", tex->line_len);
    printf("🔄 Endian: %d\n", tex->endian);
    printf("📍 Image address: %p\n", tex->img);
    printf("📍 Data address: %p\n", tex->addr);
    
    // Sample a few pixels to verify data
    if (tex->addr && tex->width > 0 && tex->height > 0)
    {
        int color = *(int*)(tex->addr);
        printf("🎨 First pixel color: 0x%X\n", color);
        
        if (tex->width > 1 && tex->height > 1)
        {
            color = *(int*)(tex->addr + (tex->line_len + (tex->bpp / 8)));
            printf("🎨 Sample pixel (1,1): 0x%X\n", color);
        }
    }
    printf("========================\n\n");
}

// Test all textures at once
void test_all_textures(t_game *game)
{
    printf("\n🧪 TESTING ALL TEXTURES 🧪\n");
    printf("================================\n");
    
    print_texture_info(game->no_texture, "NORTH");
    print_texture_info(game->so_texture, "SOUTH");
    print_texture_info(game->ea_texture, "WEST");
    print_texture_info(game->we_texture, "EAST");
    
    //printf("Floor color: R=%d, G=%d, B=%d\n", 
    //       game->textures.floor_r, game->textures.floor_g, game->textures.floor_b);
    //printf("Ceiling color: R=%d, G=%d, B=%d\n", 
    //       game->textures.ceiling_r, game->textures.ceiling_g, game->textures.ceiling_b);
    
    // Display textures in windows (optional)
    char input;
    printf("\nDisplay textures in windows? (y/n): ");
    if (scanf("%c", &input) == 1 && (input == 'y' || input == 'Y'))
    {
        display_texture_test(game, game->no_texture, "North Texture");
        display_texture_test(game, game->so_texture, "South Texture");
        display_texture_test(game, game->ea_texture, "West Texture");
        display_texture_test(game, game->we_texture, "East Texture");
    }
}