#include "../libtvrender/tvr_core.h"

#include <stdio.h> /* printf and perror */
#include <string.h> /* strncpy */
#include <sys/socket.h> /* socket and connect*/
#include <sys/un.h> /* sockaddr_un */
#include <unistd.h> /* sleep */
#include <stdlib.h> /* getenv */

int tvr_open()
{
	/* TVrender display socket */

	/* Socket path */
	const char *path;

	/* Socket descriptor */
	int fd;

	/* Address */
	struct sockaddr_un tmp_addr;

	const int opcode = TVR_OPCODE_SET_VERSION;
	const int version = TVRENDER_VERSION;

	/* ------------------- */

	/* Create socket */
	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd == -1)
	{
		perror("libtvrender failed to create socket");
		return -1;
	}

	path = getenv("TVR_DISPLAY");

	if (!path)
	{
		printf("Could not find environment var 'TVR_DISPLAY'.\n");
		return -1;
	}


	tmp_addr.sun_family = AF_UNIX;
	strncpy(tmp_addr.sun_path, path, sizeof(tmp_addr.sun_path));

	if (connect(fd, (struct sockaddr*)&tmp_addr, sizeof(tmp_addr)) == -1)
	{
		perror("libtvrender failed to connect to server");
		return -1;
	}

	/* Announce tvrender protocol version to server */
	/* P1: Opcode */
	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}
	/* P2: Version ID (1) */
	if (send(fd, &version, 4, 0) == -1)
	{
		return -1;
	}

	return fd;
}

void tvr_close(int fd)
{
	close(fd);
}

/* Vertex buffer functions */

int tvr_create_vert_buf(
	int fd,
	int32_t vb_id,
	uint64_t size,
	void *data
)
{
	const int opcode = TVR_OPCODE_VERTEX_BUFFER_CREATE;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &vb_id, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &size, 8, 0) == -1)
	{
		return -1;
	}

	if (send(fd, data, size, 0) == -1)
	{
		return -1;
	}

	return 0;
}

int tvr_destroy_vert_buf(
	int fd,
	int32_t vb_id
)
{
	const int opcode = TVR_OPCODE_VERTEX_BUFFER_DESTROY;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &vb_id, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

/* Index buffer functions */

int tvr_create_index_buf(
	int fd,
	int32_t ib_id,
	uint64_t size,
	void *data
)
{
	const int opcode = TVR_OPCODE_INDEX_BUFFER_CREATE;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &ib_id, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &size, 8, 0) == -1)
	{
		return -1;
	}

	if (send(fd, data, size, 0) == -1)
	{
		return -1;
	}


	return 0;
}

int tvr_destroy_index_buf(
	int fd,
	int32_t ib_id
)
{
	const int opcode = TVR_OPCODE_INDEX_BUFFER_DESTROY;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &ib_id, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

/* Mesh functions */

int tvr_create_mesh(
	int fd,
	int32_t mesh_id,
	int32_t mesh_vb_id,
	int32_t mesh_ib_id
)
{
	const int opcode = TVR_OPCODE_MESH_CREATE;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &mesh_id, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &mesh_vb_id, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &mesh_ib_id, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

int tvr_mesh_bind_mat(
	int fd,
	int32_t mesh_id,
	int32_t mat_id
)
{
	const int opcode = TVR_OPCODE_MESH_BIND_MAT;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &mesh_id, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &mat_id, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

int tvr_mesh_set_loc(
	int fd,
	int32_t mesh_id,
	float x,
	float y,
	float z
)
{
	const int opcode = TVR_OPCODE_MESH_SET_LOC;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &mesh_id, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &x, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &y, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &z, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

int tvr_mesh_set_rot(
	int fd,
	int32_t mesh_id,
	float x,
	float y,
	float z
)
{
	const int opcode = TVR_OPCODE_MESH_SET_ROT;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &mesh_id, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &x, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &y, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &z, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

int tvr_mesh_set_scale(
	int fd,
	int32_t mesh_id,
	float x,
	float y,
	float z
)
{
	const int opcode = TVR_OPCODE_MESH_SET_SCALE;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &mesh_id, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &x, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &y, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &z, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

int tvr_destroy_mesh(
	int fd,
	int32_t mesh_id
)
{
	const int opcode = TVR_OPCODE_MESH_DESTROY;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &mesh_id, 4, 0) == -1)
	{
		return -1;
	}


	return 0;
}

/* Texture functions */

int tvr_create_texture(
	int fd,
	int32_t tex_id,
	uint32_t width,
	uint32_t height,
	uint8_t channels,
	void *data
)
{
	size_t img_size;
	const int opcode = TVR_OPCODE_TEXTURE_CREATE;
	
	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &tex_id, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &width, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &height, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &channels, 1, 0) == -1)
	{
		return -1;
	}

	img_size = width * height * channels;

	if (send(fd, data, img_size, 0) == -1)
	{
		return -1;
	}

	return 0;
}

int tvr_destroy_texture(
	int fd,
	int32_t tex_id
)
{
	const int opcode = TVR_OPCODE_TEXTURE_DESTROY;
	
	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &tex_id, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

/* Material functions */

int tvr_create_material(
	int fd,
	int32_t mat_id
)
{
	const int opcode = TVR_OPCODE_MATERIAL_CREATE;
	
	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &mat_id, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

int tvr_material_bind_texture(
	int fd,
	int32_t mat_id,
	int32_t tex_id,
	int8_t pass
)
{
	const int opcode = TVR_OPCODE_MATERIAL_BIND_TEXTURE;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &mat_id, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &tex_id, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &pass, 1, 0) == -1)
	{
		return -1;
	}

	return 0;
}

int tvr_destroy_material(
	int fd, 
	int32_t mat_id
)
{
	const int opcode = TVR_OPCODE_MATERIAL_DESTROY;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}
	
	if (send(fd, &mat_id, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

/* POV functions */

int tvr_pov_set_loc(
	int fd,
	float x,
	float y,
	float z
)
{
	const int opcode = TVR_OPCODE_POV_SET_LOC;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &x, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &y, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &z, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

int tvr_pov_set_rot(
	int fd,
	float x,
	float y,
	float z
)
{
	const int opcode = TVR_OPCODE_POV_SET_ROT;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &x, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &y, 4, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &z, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

int tvr_pov_set_fov(
	int fd,
	float fov
)
{
	const int opcode = TVR_OPCODE_POV_SET_FOV;

	if (send(fd, &opcode, 2, 0) == -1)
	{
		return -1;
	}

	if (send(fd, &fov, 4, 0) == -1)
	{
		return -1;
	}

	return 0;
}

