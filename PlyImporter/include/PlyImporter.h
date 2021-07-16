#ifndef PLY_IMPORTER_H
#define PLY_IMPORTER_H

#include <stdint.h>

typedef enum PlyLoadFlags {

	PLY_EXTRACT_VPOSITIONS_BIT	= 0x0001,
	PLY_EXTRACT_UVS_BIT			= 0x0002,
	PLY_EXTRACT_VNORMALS_BIT	= 0x0004,

} PlyLoadFlags;

typedef struct PlyFileData {

	uint32_t	vertex_type_size;				//size in bytes of every single vertex property
	uint32_t	vertexCount;					//the number of vertices
	uint32_t    vertexStride;					//the number of vertex properties for each vertex
	float*		pVertices;						//pointer to an array of size = vertexCount * vertexStride

	uint32_t	vertex_indices_list_type_size;	//size in bytes of the first item in the property list 
	uint32_t	vertex_indices_type_size;		//size in bytes of the listed items in the property list 
	int			faceCount;						//the number of faces
	int*		pIndices;						//pointer to an array of size = faceCount * vertex_indices_type_size

	float*		pvPositions;
	float*		pUvs;
	float*		pvNormals;

} PlyFileData;



extern void plyLoadFile(const char* path, PlyFileData* ply, PlyLoadFlags flags);

extern void plyGetPropertyTypes(const char* line, const uint32_t i, uint32_t* size);

extern void plyGetPropertyTypenameSize(const char* line, const uint32_t i, uint32_t* size);

extern void plyExtractVPositions(PlyFileData* ply);

extern void plyExtractUVs(PlyFileData* ply);

extern void plyExtractVertexNormals(PlyFileData* ply);

extern void plyFree(PlyFileData* ply);

#endif