#define GL_DEBUG

#include "typedef.h"
#include "sdl.h"
#include "gl.h"
#include "shader-indexed-triangle.h"

#include <cstdio>
#include <vector>
#include <cmath>


SDL_Window *window_handle;
SDL_GLContext gl_context;

constexpr u32 SCREEN_WIDTH  = 640;
constexpr u32 SCREEN_HEIGHT = 480;

using namespace sdl;
using namespace gl;

std::vector<Vertex> vertices;
std::vector<u32> indices;

void update_render_data(Vertex *vert_in, Vec2 pos)
{
	static u32 indices_quad[6] = {0, 1, 2, 1, 2, 3};

	Vec2 center = vert_in[3].position * 0.5f;

	for (int i = 0; i < 4; ++i)
	{
		Vertex temp = vert_in[i];
		temp.position = temp.position + pos - (vertices.size() < 4 ? vec2(0,0) : center);
		vertices.push_back(temp);
	}
		
	for (int i = 0; i < 6; ++i)
	{
		u32 temp_index = indices_quad[i] + (vertices.size()/4 -1) * 4;
		indices.push_back(temp_index);
	}

	shader::update_vertex_data(vertices.data(), vertices.size()*sizeof(Vertex));
	shader::update_index_data(indices.data(), indices.size()*sizeof(u32));	
}

#undef main
int main(int argc, char *argv[])
{
	bool sdl_init = sdl::init(window_handle, gl_context, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!sdl_init) goto exit;
	bool gl_init = gl::gl_init();
	if (!gl_init) goto exit;

	SDL_GL_SetSwapInterval(33);


	//setup gl context things
	constexpr float image_scale = 1.0f;
	constexpr u32 test_dist = 16;

	int w, h;
	GLuint image_tex = gl::make_simple_texture("image.png", w, h);

	w *= image_scale;
	h *= image_scale;

	
	//resize window to fit image
	SDL_SetWindowSize(window_handle, w, h);
	SDL_GL_GetDrawableSize(window_handle, &w, &h);
	glViewport(0, 0, w, h);
	SDL_GL_SwapWindow(window_handle);

	glBindTexture(GL_TEXTURE_2D, image_tex);
	shader::init(w, h);

	static Vertex vertices_img[]
	{
		{ vec2(0, 0), vec2(0, 0), vec4(1, 1, 1, 1) },
		{ vec2(w, 0), vec2(1, 0), vec4(1, 1, 1, 1) },
		{ vec2(0, h), vec2(0, 1), vec4(1, 1, 1, 1) },
		{ vec2(w, h), vec2(1, 1), vec4(1, 1, 1, 1) },
	};

	static Vertex vertices_green[]
	{
		{ vec2(0, 0), 					vec2(0, 0), vec4(0, 1, 0, 1) },
		{ vec2(test_dist, 0), 			vec2(0.01, 0), vec4(0, 1, 0, 1) },
		{ vec2(0, test_dist), 			vec2(0, 0.01), vec4(0, 1, 0, 1) },
		{ vec2(test_dist, test_dist), 	vec2(0.01, 0.01), vec4(0, 1, 0, 1) },
	};

	static Vertex vertices_blue[]
	{
		{ vec2(0, 0), 					vec2(0, 0), vec4(0, 0, 1, 1) },
		{ vec2(test_dist, 0), 			vec2(0.01, 0), vec4(0, 0, 1, 1) },
		{ vec2(0, test_dist), 			vec2(0, 0.01), vec4(0, 0, 1, 1) },
		{ vec2(test_dist, test_dist), 	vec2(0.01, 0.01), vec4(0, 0, 1, 1) },
	};

	update_render_data(vertices_img, vec2(0, 0));


	//shader::update_vertex_data(vertices_img, sizeof(vertices_img));
	//shader::update_index_data(indices, sizeof(indices));


	

	bool requested_exit = false;
	while (requested_exit == false)
	{
		sdl::update_events(requested_exit);
		Vec2 mouse = vec2(mouse_pos.x, h-mouse_pos.y); 



		static std::vector<Vec2> points;
		if (mouse_pressed[0])
		{
			bool found = false;

			for (auto &point : points)
			{
				if (found) break;

				float distance = sqrt(pow(point.x-mouse.x, 2) + pow(point.y-mouse.y, 2));

				if (distance <= test_dist)
				{
					mouse = point;
					found = true;
				}
			}

			if (!found)
				points.push_back(mouse);

			printf("%d, %d; ", (int)mouse.x, (int)mouse.y);

			update_render_data(vertices_green, mouse);
		}

		if (mouse_pressed[2])
		{
			u8 *rgb_data = new u8[3];

			glFlush();
			glReadBuffer(GL_BACK);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glReadPixels(mouse.x, mouse.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, rgb_data);

			u32 hex  = (u32)rgb_data[2]
					 | ( (u32)rgb_data[1] << 8 )
					 | ( (u32)rgb_data[2] << 16 );
				//hex += (u32)rgb_data[1] * 16 * 16;
				//hex += (u32)rgb_data[0] * 16 * 16 * 16 * 16;

			printf("#%X\n", hex);

			delete[] rgb_data;

			update_render_data(vertices_blue, mouse);
		}


		shader::draw(indices.size(), 0);
		SDL_GL_SwapWindow(window_handle);
	}


	exit:
	sdl::cleanup(window_handle, gl_context);
	return 0;
}