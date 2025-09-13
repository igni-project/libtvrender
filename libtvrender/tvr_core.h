#ifndef _LIBTVRENDER_TVR_CORE_H
#define _LIBTVRENDER_TVR_CORE_H 1

#define TVRENDER_VERSION 0

#include <stdint.h>

/* Opcodes */
enum
{
	TVR_OPCODE_SET_VERSION = 0,

	/* VERTEX BUFFER requests */

	TVR_OPCODE_VERTEX_BUFFER_CREATE,
	TVR_OPCODE_VERTEX_BUFFER_DESTROY,

	/* INDEX BUFFER requests */

	TVR_OPCODE_INDEX_BUFFER_CREATE,
	TVR_OPCODE_INDEX_BUFFER_DESTROY,

	/* MESH requests */

	TVR_OPCODE_MESH_CREATE,
	TVR_OPCODE_MESH_BIND_VERTEX_BUFFER,
	TVR_OPCODE_MESH_BIND_INDEX_BUFFER,
	TVR_OPCODE_MESH_BIND_MAT,
	TVR_OPCODE_MESH_SET_LOC,
	TVR_OPCODE_MESH_SET_ROT,
	TVR_OPCODE_MESH_SET_SCALE,
	TVR_OPCODE_MESH_DESTROY,

	/* TEXTURE requests */

	TVR_OPCODE_TEXTURE_CREATE,
	TVR_OPCODE_TEXTURE_DESTROY,

	/* MATERIAL requests */

	TVR_OPCODE_MATERIAL_CREATE,
	TVR_OPCODE_MATERIAL_BIND_TEXTURE,
	TVR_OPCODE_MATERIAL_DESTROY,

	/* POV requests */

	TVR_OPCODE_POV_SET_LOC,
	TVR_OPCODE_POV_SET_ROT,
	TVR_OPCODE_POV_SET_FOV
};

/* Render passes */
enum
{
	/* Surface colour (Albedo) */
	TVR_PASS_ALBEDO = 0
};

#ifdef __cplusplus
extern "C" {
#endif

int tvr_open();
void tvr_close(int fd);

/* Vertex buffer functions */

int tvr_create_vert_buf(
	int fd,
	int32_t vb_id,
	uint64_t size,
	void *data
);

int tvr_destroy_vert_buf(
	int fd,
	int32_t vb_id
);

/* Index buffer functions */

int tvr_create_index_buf(
	int fd,
	int32_t ib_id,
	uint64_t size,
	void *data
);

int tvr_destroy_index_buf(
	int fd,
	int32_t ib_id
);

/* Mesh functions */

int tvr_create_mesh(
	int fd,
	int32_t mesh_id
);

int tvr_mesh_bind_vert_buf(
	int fd,
	int32_t mesh_id,
	int32_t vb_id
);

int tvr_mesh_bind_index_buf(
	int fd,
	int32_t mesh_id,
	int32_t ib_id
);

int tvr_mesh_bind_mat(
	int fd,
	int32_t mesh_id,
	int32_t mat_id
);

int tvr_mesh_set_loc(
	int fd,
	int32_t mesh_id,
	float x,
	float y,
	float z
);

int tvr_mesh_set_rot(
	int fd,
	int32_t mesh_id,
	float x,
	float y,
	float z
);

int tvr_mesh_set_scale(
	int fd,
	int32_t mesh_id,
	float x,
	float y,
	float z
);

int tvr_destroy_mesh(
	int fd,
	int32_t mesh_id
);

/* Texture functions */

int tvr_create_texture(
	int fd,
	int32_t tex_id,
	uint32_t width,
	uint32_t height,
	uint8_t channels,
	void *data
);

int tvr_destroy_texture(
	int fd,
	int32_t tex_id
);

/* Material functions */

int tvr_create_material(
	int fd,
	int32_t mat_id
);

int tvr_material_bind_texture(
	int fd,
	int32_t mat_id,
	int32_t tex_id,
	int8_t pass
);

int tvr_destroy_material(
	int fd, 
	int32_t mat_id
);

/* POV functions */

int tvr_pov_set_loc(
	int fd,
	float x,
	float y,
	float z
);

int tvr_pov_set_rot(
	int fd,
	float x,
	float y,
	float z
);

int tvr_pov_set_fov(
	int fd,
	float fov
);

#ifdef __cplusplus
}
#endif

#endif

