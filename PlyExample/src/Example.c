#include <PlyImporter.h>

#include <stdio.h>
#include <string.h>

int main() {
	
	PlyFileData ply = { 0 };
	plyLoadFile("../Assets/stanfordLucy.ply", &ply, PLY_EXTRACT_VPOSITIONS_BIT | PLY_EXTRACT_UVS_BIT | PLY_EXTRACT_VNORMALS_BIT);
	
	printf("vertex positions:\n");
	for (uint32_t i = 0; i < ply.vertexCount * 3; i += 3) {
		printf("{ %f, %f, %f }\n", ply.pvPositions[i], ply.pvPositions[i + 1], ply.pvPositions[i + 2]);
	}

	printf("vertex normals:\n");
	for (uint32_t i = 0; i < ply.vertexCount * 3; i += 3) {
		printf("{ %f, %f, %f }\n", ply.pvNormals[i], ply.pvNormals[i + 1], ply.pvNormals[i + 2]);
	}
	
	printf("uvs:\n");
	for (uint32_t i = 0; i < ply.vertexCount * 2; i += 2) {
		printf("{ %f, %f }\n", ply.pUvs[i], ply.pUvs[i + 1]);
	}

	printf("indices:\n");
	for (uint32_t i = 0; i < ply.faceCount * 3; i+=3) {
		printf("{ %i, %i, %i }\n", ply.pIndices[i], ply.pIndices[i + 1], ply.pIndices[i + 2]);
	}

	plyFree(&ply);
}
