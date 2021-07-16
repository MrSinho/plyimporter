#include <PlyImporter.h>

#include <stdio.h>
#include <string.h>

int main() {
	
	PlyFileData ply = { 0 };
	plyLoadFile("../Assets/triangle.ply", &ply);
	
	for (uint32_t i = 0; i < ply.vertexCount * ply.vertexStride; i++) {
		printf("%f\n", ply.pVertices[i]);
	}

	for (uint32_t i = 0; i < ply.faceCount * 4; i++) {
		printf("%i\n", ply.pIndices[i]);
	}

	plyFree(&ply);
}
