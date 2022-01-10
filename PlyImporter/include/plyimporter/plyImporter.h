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
	uint32_t	vertex_count;					//the number of vertices
	uint32_t    vertex_stride;					//the number of vertex properties for each vertex
	float*		p_vertices;						//pointer to an array of size = vertex_count * vertex_stride

	uint32_t	vertex_indices_list_type_size;	//size in bytes of the first item in the property list 
	uint32_t	vertex_indices_type_size;		//size in bytes of the listed items in the property list 
	uint32_t	face_count;						//the number of faces
	uint32_t	index_count;					//the number of indices
	uint32_t*	p_indices;						//pointer to an array of size = face_count * vertex_indices_type_size

	float*		p_vpositions;					//pointer to an array of size = vertex_count * 3
	float*		p_vnormals;						//pointer to an array of size = vertex_count * 3
	float*		p_uvs;							//pointer to an array of size = vertex_count * 2

} PlyFileData;



extern void plyLoadFile(const char* path, PlyFileData* ply, PlyLoadFlags flags);

extern void plyGetPropertyTypes(const char* line, const uint32_t i, uint32_t* size);

extern void plyGetPropertyTypenameSize(const char* line, const uint32_t i, uint32_t* size);

extern void plyExtractVPositions(PlyFileData* ply);

extern void plyExtractUVs(PlyFileData* ply);

extern void plyExtractVertexNormals(PlyFileData* ply);

extern void plyFree(PlyFileData* ply);

#endif