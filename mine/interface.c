#include "mine.h"

void resize()
{
        screenw = event.window.data1;
        screenh = event.window.data2;
}

void jump(int down)
{
        if (player[0].wet)
                player[0].jumping = down;
        else if (down)
                player[0].jumping = JUMP_BUFFER_FRAMES;
}

void key_move(int down)
{
        if (event.key.repeat) return;

        switch (event.key.keysym.sym)
        {
                case SDLK_w:      player[0].goingf = down;
                        if (down) player[0].cooldownf += 10; // детект дабл-тапа
                        break;
                case SDLK_s:      player[0].goingb   = down; break;
                case SDLK_a:      player[0].goingl   = down; break;
                case SDLK_d:      player[0].goingr   = down; break;
                case SDLK_LSHIFT: player[0].sneaking = down; break;
                case SDLK_LCTRL:  player[0].running  = down; break;
                case SDLK_z:      zooming            = down; break;

                case SDLK_SPACE:
                        jump(down);
                        break;

                case SDLK_e:
                        player[0].lighting = down;
                        break;

                // menu
                case SDLK_ESCAPE:
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                        mouselook = false;
                        break;

                // debug
                case SDLK_q:
                        if (!down)
                        {
                                player[0].pos.y -= 1000;
                                player[0].grav = GRAV_ZERO;
                        }
                        break;
                case SDLK_f:
                        if (down)
                                fast = (fast == 1.f) ? 8.f : 1.f;
                        break;
                case SDLK_h:
                        if (down)
                                help_layer = (help_layer == 1) ? 0 : 1;
                        break;
                case SDLK_g:
                        if (down)
                                help_layer = (help_layer == 2) ? 0 : 2;
                        break;
                case SDLK_r:
                        if (down)
                        {
                                regulated = !regulated;
                                fprintf(stderr, "%s\n", regulated ? "regulated" : "unregulated");
                        }
                        break;
                case SDLK_v:
                        if (down)
                        {
                                vsync = !vsync;
                                SDL_GL_SetSwapInterval(vsync);
                                fprintf(stderr, "%s\n", vsync ? "vsync" : "no vsync");
                        }
                        break;
                case SDLK_SLASH:
                        if (down)
                        {
                                antialiasing = !antialiasing;
                                fprintf(stderr, "%s\n", antialiasing ? "antialiasing" : "no antialiasing");
                        }
                        break;
                case SDLK_t:
                        if (down) build_test_area();
                        break;
                case SDLK_n:
                        if (down) reverse_sun = !reverse_sun;
                        break;
                case SDLK_l:
                        if (down && place_x >= 0)
                        {
                                show_light_values = true;
                                test_area_x = place_x - TEST_AREA_SZ / 2;
                                test_area_y = place_y;
                                test_area_z = place_z - TEST_AREA_SZ / 2;
                        }
                        break;
                case SDLK_p:
                        if (down) speedy_sun = !speedy_sun;
                        break;
                case SDLK_m:
                        if (!down) shadow_mapping = !shadow_mapping;
                        break;
                case SDLK_F1:
                        if (down) frustum_culling = !frustum_culling;
                        break;
                case SDLK_F2:
                        if (down) lock_culling = !lock_culling;
                        break;
                case SDLK_F3:
                        if (!down) noisy = !noisy;
                        break;
                case SDLK_F4:
                        if (!down) show_fresh_updates = !show_fresh_updates;
                        break;
                case SDLK_F5:
                        if (!down) for(int x=0;x<CHUNKW;x++) for(int y=0;y<TILESH;y++) for(int z=0;z<CHUNKD;z++)
                        {
                                T_(C2B(32) + x, y, C2B(32) + z) = OPEN;
                        }
                        break;
                case SDLK_F12:
                        if (!down) show_shadow_map = !show_shadow_map;
                        break;

                case SDLK_LEFT:  if (down) scoot(-1,  0); break;
                case SDLK_RIGHT: if (down) scoot( 1,  0); break;
                case SDLK_DOWN:  if (down) scoot( 0, -1); break;
                case SDLK_UP:    if (down) scoot( 0,  1); break;
        }
}

void mouse_move()
{
        if (!mouselook) return;

        float pitchlimit = 3.1415926535 * 0.5 - 0.001;
        player[0].yaw += event.motion.xrel * 0.001;
        player[0].pitch += event.motion.yrel * 0.001;

        if (player[0].pitch > pitchlimit)
                player[0].pitch = pitchlimit;

        if (player[0].pitch < -pitchlimit)
                player[0].pitch = -pitchlimit;
}

void mouse_button(int down)
{
        if (!mouselook)
        {
                if (down)
                {
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                        mouselook = true;
                }
        }
        else if (event.button.button == SDL_BUTTON_LEFT)
        {
                player[0].breaking = down;
        }
        else if (event.button.button == SDL_BUTTON_RIGHT)
        {
                player[0].building = down;
        }
        else if (event.button.button == SDL_BUTTON_X1)
        {
                jump(down);
        }
}

