#ifndef PLY_IMPORTER_H
#define PLY_IMPORTER_H

#include <stdint.h>

typedef struct PlyFileData {

	uint32_t	vertexCount;
	uint32_t    vertexStride;
	float*		pVertices;

	int			faceCount;
	int*		pIndices;

} PlyFileData;



extern void plyLoadFile(const char* path, PlyFileData* ply);

extern void plyFree(PlyFileData* ply);

#endif