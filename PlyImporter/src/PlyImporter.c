#include "PlyImporter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable: 4996)

void plyLoadFile(const char* path, PlyFileData* ply) {
	
	FILE* stream = fopen(path, "r");

	if (stream == NULL) {
		return;
	}

	fseek(stream, 0, SEEK_END);
	uint32_t fileSize = ftell(stream);
	fseek(stream, 0, SEEK_SET);

	uint32_t headerSize = 0;

	if (stream != NULL) {

		//HEADER

		uint32_t lineCount = 0;
		char line[256];

		while (fgets(line, 256, stream) != NULL) {

			headerSize += strlen(line);
			
			// ELEMENT
			if (line[0] == 'e' && line[1] == 'l') {
				char* count_str = NULL;
				if (line[8] == 'v') {
					count_str = calloc(strlen(line) - 16, 1);
					if (count_str != NULL) {
						memcpy(count_str, &line[15], strlen(line) - 16);
						ply->vertexCount = atoi(count_str);
					}

				}

				else if (line[8] == 'f') {
					count_str = calloc(strlen(line) - 14, 1);
					if (count_str != NULL) {
						memcpy(count_str, &line[13], strlen(line) - 14);
						ply->faceCount = atoi(count_str);
					}
				}

				free(count_str);
				count_str = NULL;
			}

			// VERTEX PROPERTY
			else if (line[0] == 'p' && (line[9] == 'f' || line[9] == 'c' || line[9] == 'u' || line[9] == 's' || line[9] == 'i' || line[9] == 'f' || line[9] == 'd')) {
				ply->vertexStride++;
			} 
			lineCount++;
		}

		//BINARY

		fclose(stream);

		stream = fopen(path, "rb");
		if (stream == NULL) { return; }

		//read vertices
		ply->pVertices = calloc(ply->vertexCount * ply->vertexStride, sizeof(float));
		if (ply->pVertices == NULL) { exit(EXIT_FAILURE); }

		uint32_t offset = headerSize;
		fseek(stream, offset, SEEK_SET);
		fread(ply->pVertices, sizeof(float), ply->vertexCount * ply->vertexStride, stream);
		
		//read indices
		ply->pIndices = calloc(ply->faceCount * 3, sizeof(uint32_t));
		if (ply->pIndices == NULL) { exit(EXIT_FAILURE); }

		offset += ply->vertexCount * ply->vertexStride * sizeof(float);
		fseek(stream, offset, SEEK_SET);
		for (uint32_t i = 0; i < ply->vertexCount; i++) {
			offset += 1;
			fseek(stream, offset, SEEK_SET);
			fread(ply->pIndices, sizeof(uint32_t), ply->faceCount * 3, stream);
			offset += 3 * sizeof(uint32_t);
		}
		
		fclose(stream);

	} //if (stream != NULL)

	return ply;
}

void plyFree(PlyFileData* ply) {
	free(ply->pVertices);
	free(ply->pIndices);
	ply->pVertices = NULL;
	ply->pIndices  = NULL;
}