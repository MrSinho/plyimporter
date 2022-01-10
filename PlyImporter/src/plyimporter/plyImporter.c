#include "plyimporter/plyImporter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable: 4996)

void plyGetPropertyTypes(const char* line, const uint32_t i, uint32_t* size) {

	switch (line[i]) {
	case 'c': *size = 1;	break;		//1 byte  char 
	case 's': *size = 2;	break;		//2 bytes short
	case 'i': *size = 4;	break;		//4 bytes int
	case 'f': *size = 4;	break;		//4 bytes float
	case 'd': *size = 8;	break;		//8 bytes double
	case 'u':
		switch (line[i + 1]) {
		case 'c': *size = 1;	break;	//1 byte  unsigned char
		case 's': *size = 2;	break;	//2 bytes unsigned short
		case 'i': *size = 4; 	break;	//4 bytes unsigned int
		case 'f': *size = 4;	break;	//4 bytes unsigned float
		case 'd': *size = 8;	break;	//8 bytes unsigned double
		};
	}

}

void plyGetPropertyTypenameSize(const char* line, const uint32_t i, uint32_t* size) {

	switch (line[i]) {
	case 'c': *size = 4; break;			//char
	case 's': *size = 5; break;			//short
	case 'i': *size = 3; break;			//int
	case 'f': *size = 5; break;			//float
	case 'd': *size = 6; break;			//double
	case 'u':
		switch (line[i + 1]) {
		case 'c': *size = 5; break;		//uchar
		case 's': *size = 6; break;		//ushort
		case 'i': *size = 4; break; 		//uint
		case 'f': *size = 6; break;		//ufloat
		case 'd': *size = 7; break;		//udouble
		};
	}
}

void plyLoadFile(const char* path, PlyFileData* ply, PlyLoadFlags flags) {

	FILE* stream = fopen(path, "r");

	if (stream == NULL) {
		return;
	}

	fseek(stream, 0, SEEK_END);
	uint32_t fileSize = ftell(stream);
	fseek(stream, 0, SEEK_SET);

	uint32_t headerSize = 0;

	if (stream == NULL) { return; }

	//HEADER
	uint32_t lineCount = 0;
	char line[256];

	while (fgets(line, 256, stream) != NULL) {

		headerSize += (uint32_t)strlen(line);
		if (line[0] == 'e' && line[1] == 'n' && line[2] == 'd') {
			break;
		}

		// ELEMENT
		if (line[0] == 'e' && line[1] == 'l') {
			char* count_str = NULL;

			// ELEMENT VERTEX
			if (line[8] == 'v') {
				count_str = (char*)calloc(strlen(line) - 16, 1);
				if (count_str != NULL) {
					memcpy(count_str, &line[15], strlen(line) - 16);
					ply->vertex_count = atoi(count_str);
				}

			}

			// ELEMENT FACE
			else if (line[8] == 'f') {
				count_str = (char*)calloc(strlen(line) - 14, 1);
				if (count_str != NULL) {
					memcpy(count_str, &line[13], strlen(line) - 14);
					ply->face_count = atoi(count_str);
				}
			}

			free(count_str);
			count_str = NULL;
		}

		// VERTEX PROPERTY
		else if (line[0] == 'p' && (line[9] == 'f' || line[9] == 'c' || line[9] == 'u' || line[9] == 's' || line[9] == 'i' || line[9] == 'f' || line[9] == 'd')) {
			plyGetPropertyTypes(line, 9, &ply->vertex_type_size);
			ply->vertex_stride++;
		}

		// PROPERTY LIST
		else if (line[0] == 'p' && line[9] == 'l') {
			plyGetPropertyTypes(line, 14, &ply->vertex_indices_list_type_size);
			uint32_t typename_size = 0;
			plyGetPropertyTypenameSize(line, 14, &typename_size);

			plyGetPropertyTypes(line, 14 + typename_size + 1, &ply->vertex_indices_type_size);
		}

		lineCount++;
	}
	ply->vertex_count *= ply->vertex_stride;
	//BINARY

	fclose(stream);

	stream = fopen(path, "rb");
	if (stream == NULL) { return; }

	//read vertices
	ply->p_vertices = (float*)calloc(ply->vertex_count, sizeof(float));
	if (ply->p_vertices == NULL) { exit(EXIT_FAILURE); }

	uint32_t offset = headerSize;
	fseek(stream, offset, SEEK_SET);
	size_t sz = fread(ply->p_vertices, ply->vertex_type_size, ply->vertex_count * ply->vertex_stride, stream);
	offset += ply->vertex_count * ply->vertex_stride * ply->vertex_type_size;

	//read indices

	ply->p_indices = (uint32_t*)calloc(ply->face_count * 4, sizeof(uint32_t));
	if (ply->p_indices == NULL) { exit(EXIT_FAILURE); }

	uint32_t index_count = 0;
	for (uint32_t i = 0; index_count < ply->face_count * 4; i += 0) {

		uint32_t list = 0;
		fseek(stream, offset, SEEK_SET);
		sz = fread(&list, ply->vertex_indices_list_type_size, 1, stream);
		offset += ply->vertex_indices_list_type_size;
		fseek(stream, offset, SEEK_SET);

		if (list == 3) {
			fseek(stream, offset, SEEK_SET);
			sz = fread(&ply->p_indices[i], ply->vertex_indices_type_size, 3, stream);
			offset += 3 * ply->vertex_indices_type_size;

			int _0 = ply->p_indices[i];
			int _1 = ply->p_indices[i + 1];
			int _2 = ply->p_indices[i + 2];

			index_count += 4;
			i += 3;
		}

		else if (list == 4) {
			ply->face_count += 1;

			size_t sz = fread(&ply->p_indices[i], ply->vertex_indices_type_size, 3, stream);
			fseek(stream, offset, SEEK_SET);

			sz = fread(&ply->p_indices[i + 3], ply->vertex_indices_type_size, 1, stream);
			offset += 2 * ply->vertex_indices_type_size;
			fseek(stream, offset, SEEK_SET);

			sz = fread(&ply->p_indices[i + 4], ply->vertex_indices_type_size, 2, stream);
			offset += 2 * ply->vertex_indices_type_size;
			fseek(stream, offset, SEEK_SET);

			int _0 = ply->p_indices[i];
			int _1 = ply->p_indices[i + 1];
			int _2 = ply->p_indices[i + 2];
			int _3 = ply->p_indices[i + 3];
			int _4 = ply->p_indices[i + 4];
			int _5 = ply->p_indices[i + 5];

			ply->index_count += 3;
			index_count += 8;
			i += 6;
		}
		ply->index_count += 3;
	}

	fclose(stream);

	if (flags & PLY_EXTRACT_VPOSITIONS_BIT) { plyExtractVPositions(ply); }
	if (flags & PLY_EXTRACT_UVS_BIT) { plyExtractUVs(ply); }
	if (flags & PLY_EXTRACT_VNORMALS_BIT) { plyExtractVertexNormals(ply); }

	return;
}

void plyExtractVPositions(PlyFileData* ply) {
	ply->p_vpositions = (float*)calloc(ply->vertex_count * 3, sizeof(float));
	if (ply->p_vpositions == NULL) { return; }
	uint32_t positionCount = 0;
	for (uint32_t i = 0; i < ply->vertex_count * ply->vertex_stride; i += ply->vertex_stride) {
		ply->p_vpositions[positionCount] = ply->p_vertices[i];
		ply->p_vpositions[positionCount + 1] = ply->p_vertices[i + 1];
		ply->p_vpositions[positionCount + 2] = ply->p_vertices[i + 2];
		positionCount += 3;
	}
}

void plyExtractUVs(PlyFileData* ply) {

	ply->p_uvs = (float*)calloc(ply->vertex_count * 2, sizeof(float));
	if (ply->p_uvs == NULL) { return; }
	uint32_t uvCount = 0;
	for (uint32_t i = 6; i < ply->vertex_count * ply->vertex_stride; i += ply->vertex_stride) {
		ply->p_uvs[uvCount] = ply->p_vertices[i];
		ply->p_uvs[uvCount + 1] = ply->p_vertices[i + 1];
		uvCount += 2;
	}

}

void plyExtractVertexNormals(PlyFileData* ply) {

	ply->p_vnormals = (float*)calloc(ply->vertex_count * 3, sizeof(float));
	if (ply->p_vnormals == NULL) { return; }
	uint32_t normalCount = 0;
	for (uint32_t i = 3; i < ply->vertex_count * ply->vertex_stride; i += ply->vertex_stride) {
		ply->p_vnormals[normalCount] = ply->p_vertices[i];
		ply->p_vnormals[normalCount + 1] = ply->p_vertices[i + 1];
		ply->p_vnormals[normalCount + 2] = ply->p_vertices[i + 2];
		normalCount += 3;
	}
}

void plyFree(PlyFileData* ply) {

	if (ply->p_vertices != NULL) { free(ply->p_vertices); ply->p_vertices = NULL; }
	if (ply->p_indices != NULL) { free(ply->p_indices);  ply->p_indices = NULL; }
	if (ply->p_uvs != NULL) { free(ply->p_uvs);      ply->p_uvs = NULL; }
	if (ply->p_vnormals != NULL) { free(ply->p_vnormals); ply->p_vnormals = NULL; }
}
