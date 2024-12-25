xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 344;
 -10.00000;12.00000;-49.00000;,
 -10.00000;12.00000;-55.00000;,
 -10.00000;-17.00000;-55.00000;,
 -10.00000;-17.00000;-49.00000;,
 -10.00000;12.00000;-55.00000;,
 10.00000;12.00000;-55.00000;,
 10.00000;-17.00000;-55.00000;,
 -10.00000;-17.00000;-55.00000;,
 10.00000;12.00000;-55.00000;,
 10.00000;12.00000;-49.00000;,
 10.00000;-17.00000;-49.00000;,
 10.00000;-17.00000;-55.00000;,
 10.00000;12.00000;-49.00000;,
 -10.00000;12.00000;-49.00000;,
 -10.00000;-17.00000;-49.00000;,
 10.00000;-17.00000;-49.00000;,
 -10.00000;12.00000;-55.00000;,
 -10.00000;12.00000;-49.00000;,
 -10.00000;-17.00000;-49.00000;,
 -10.00000;-17.00000;-55.00000;,
 -10.00000;12.00000;55.00000;,
 -10.00000;12.00000;49.00000;,
 -10.00000;-17.00000;49.00000;,
 -10.00000;-17.00000;55.00000;,
 -10.00000;12.00000;49.00000;,
 10.00000;12.00000;49.00000;,
 10.00000;-17.00000;49.00000;,
 -10.00000;-17.00000;49.00000;,
 10.00000;12.00000;49.00000;,
 10.00000;12.00000;55.00000;,
 10.00000;-17.00000;55.00000;,
 10.00000;-17.00000;49.00000;,
 10.00000;12.00000;55.00000;,
 -10.00000;12.00000;55.00000;,
 -10.00000;-17.00000;55.00000;,
 10.00000;-17.00000;55.00000;,
 -10.00000;12.00000;49.00000;,
 -10.00000;12.00000;55.00000;,
 -10.00000;-17.00000;55.00000;,
 -10.00000;-17.00000;49.00000;,
 -49.00000;12.00000;10.00000;,
 -55.00000;12.00000;10.00000;,
 -55.00000;-17.00000;10.00000;,
 -49.00000;-17.00000;10.00000;,
 -55.00000;12.00000;10.00000;,
 -55.00000;12.00000;-10.00000;,
 -55.00000;-17.00000;-10.00000;,
 -55.00000;-17.00000;10.00000;,
 -55.00000;12.00000;-10.00000;,
 -49.00000;12.00000;-10.00000;,
 -49.00000;-17.00000;-10.00000;,
 -55.00000;-17.00000;-10.00000;,
 -49.00000;12.00000;-10.00000;,
 -49.00000;12.00000;10.00000;,
 -49.00000;-17.00000;10.00000;,
 -49.00000;-17.00000;-10.00000;,
 -55.00000;12.00000;10.00000;,
 -49.00000;12.00000;10.00000;,
 -49.00000;-17.00000;10.00000;,
 -55.00000;-17.00000;10.00000;,
 55.00000;12.00000;10.00000;,
 49.00000;12.00000;10.00000;,
 49.00000;-17.00000;10.00000;,
 55.00000;-17.00000;10.00000;,
 49.00000;12.00000;10.00000;,
 49.00000;12.00000;-10.00000;,
 49.00000;-17.00000;-10.00000;,
 49.00000;-17.00000;10.00000;,
 49.00000;12.00000;-10.00000;,
 55.00000;12.00000;-10.00000;,
 55.00000;-17.00000;-10.00000;,
 49.00000;-17.00000;-10.00000;,
 55.00000;12.00000;-10.00000;,
 55.00000;12.00000;10.00000;,
 55.00000;-17.00000;10.00000;,
 55.00000;-17.00000;-10.00000;,
 49.00000;12.00000;10.00000;,
 55.00000;12.00000;10.00000;,
 55.00000;-17.00000;10.00000;,
 49.00000;-17.00000;10.00000;,
 -10.00000;12.00000;-51.00000;,
 -10.00000;9.00000;-51.00000;,
 -10.00000;9.00000;51.00000;,
 -10.00000;12.00000;51.00000;,
 -10.00000;9.00000;-51.00000;,
 10.00000;9.00000;-51.00000;,
 10.00000;9.00000;51.00000;,
 -10.00000;9.00000;51.00000;,
 10.00000;9.00000;-51.00000;,
 10.00000;12.00000;-51.00000;,
 10.00000;12.00000;51.00000;,
 10.00000;9.00000;51.00000;,
 10.00000;12.00000;-51.00000;,
 -10.00000;12.00000;-51.00000;,
 -10.00000;12.00000;51.00000;,
 10.00000;12.00000;51.00000;,
 -10.00000;9.00000;-51.00000;,
 -10.00000;12.00000;-51.00000;,
 -10.00000;12.00000;51.00000;,
 -10.00000;9.00000;51.00000;,
 -51.00000;12.00000;10.00000;,
 -51.00000;9.00000;10.00000;,
 51.00000;9.00000;10.00000;,
 51.00000;12.00000;10.00000;,
 -51.00000;9.00000;10.00000;,
 -51.00000;9.00000;-10.00000;,
 51.00000;9.00000;-10.00000;,
 51.00000;9.00000;10.00000;,
 -51.00000;9.00000;-10.00000;,
 -51.00000;12.00000;-10.00000;,
 51.00000;12.00000;-10.00000;,
 51.00000;9.00000;-10.00000;,
 -51.00000;12.00000;-10.00000;,
 -51.00000;12.00000;10.00000;,
 51.00000;12.00000;10.00000;,
 51.00000;12.00000;-10.00000;,
 -51.00000;9.00000;10.00000;,
 -51.00000;12.00000;10.00000;,
 51.00000;12.00000;10.00000;,
 51.00000;9.00000;10.00000;,
 12.00000;31.00000;-10.00000;,
 1.33974;25.00000;-10.00000;,
 1.33975;25.00000;10.00000;,
 12.00000;31.00000;10.00000;,
 3.07180;24.00000;-10.00000;,
 12.00000;29.00000;-10.00000;,
 12.00000;29.00000;10.00000;,
 3.07180;24.00000;10.00000;,
 1.33974;12.00000;-10.00000;,
 1.33975;12.00000;10.00000;,
 3.07180;13.00000;-10.00000;,
 3.07180;13.00000;10.00000;,
 10.00000;7.00000;-10.00000;,
 10.00000;7.00000;10.00000;,
 10.00000;9.00000;-10.00000;,
 10.00000;9.00000;10.00000;,
 23.66025;12.00000;-10.00000;,
 23.66025;12.00000;10.00000;,
 21.92820;13.00000;-10.00000;,
 21.92820;13.00000;10.00000;,
 25.66025;25.00000;-10.00000;,
 25.66025;25.00000;10.00000;,
 23.92820;24.00000;-10.00000;,
 23.92820;24.00000;10.00000;,
 12.00000;31.00000;-10.00000;,
 12.00000;31.00000;10.00000;,
 12.00000;29.00000;-10.00000;,
 12.00000;29.00000;10.00000;,
 3.07180;24.00000;-10.00000;,
 1.33974;25.00000;-10.00000;,
 12.00000;31.00000;10.00000;,
 1.33975;25.00000;10.00000;,
 3.07180;24.00000;10.00000;,
 12.00000;29.00000;10.00000;,
 3.07180;13.00000;-10.00000;,
 1.33974;12.00000;-10.00000;,
 1.33975;12.00000;10.00000;,
 3.07180;13.00000;10.00000;,
 10.00000;9.00000;-10.00000;,
 10.00000;7.00000;-10.00000;,
 10.00000;7.00000;10.00000;,
 10.00000;9.00000;10.00000;,
 21.92820;13.00000;-10.00000;,
 23.66025;12.00000;-10.00000;,
 23.66025;12.00000;10.00000;,
 21.92820;13.00000;10.00000;,
 23.92820;24.00000;-10.00000;,
 25.66025;25.00000;-10.00000;,
 25.66025;25.00000;10.00000;,
 23.92820;24.00000;10.00000;,
 -10.00000;31.00000;10.00000;,
 1.66026;25.00000;10.00000;,
 1.66025;25.00000;-10.00000;,
 -10.00000;31.00000;-10.00000;,
 -0.07180;24.00000;10.00000;,
 -10.00000;29.00000;10.00000;,
 -10.00000;29.00000;-10.00000;,
 -0.07180;24.00000;-10.00000;,
 1.66026;12.00000;10.00000;,
 1.66025;12.00000;-10.00000;,
 -0.07180;13.00000;10.00000;,
 -0.07180;13.00000;-10.00000;,
 -7.00000;7.00000;10.00000;,
 -7.00000;7.00000;-10.00000;,
 -7.00000;9.00000;10.00000;,
 -7.00000;9.00000;-10.00000;,
 -20.66025;12.00000;10.00000;,
 -20.66025;12.00000;-10.00000;,
 -18.92820;13.00000;10.00000;,
 -18.92820;13.00000;-10.00000;,
 -22.66025;25.00000;10.00000;,
 -22.66025;25.00000;-10.00000;,
 -20.92820;24.00000;10.00000;,
 -20.92820;24.00000;-10.00000;,
 -10.00000;31.00000;10.00000;,
 -10.00000;31.00000;-10.00000;,
 -10.00000;29.00000;10.00000;,
 -10.00000;29.00000;-10.00000;,
 -0.07180;24.00000;10.00000;,
 1.66026;25.00000;10.00000;,
 -10.00000;31.00000;-10.00000;,
 1.66025;25.00000;-10.00000;,
 -0.07180;24.00000;-10.00000;,
 -10.00000;29.00000;-10.00000;,
 -0.07180;13.00000;10.00000;,
 1.66026;12.00000;10.00000;,
 1.66025;12.00000;-10.00000;,
 -0.07180;13.00000;-10.00000;,
 -7.00000;9.00000;10.00000;,
 -7.00000;7.00000;10.00000;,
 -7.00000;7.00000;-10.00000;,
 -7.00000;9.00000;-10.00000;,
 -18.92820;13.00000;10.00000;,
 -20.66025;12.00000;10.00000;,
 -20.66025;12.00000;-10.00000;,
 -18.92820;13.00000;-10.00000;,
 -20.92820;24.00000;10.00000;,
 -22.66025;25.00000;10.00000;,
 -22.66025;25.00000;-10.00000;,
 -20.92820;24.00000;-10.00000;,
 0.00000;10.00000;-55.00000;,
 32.32819;10.00000;-44.49594;,
 32.32819;-5.00000;-44.49594;,
 0.00000;-5.00000;-55.00000;,
 28.44881;10.00000;-39.15643;,
 0.00000;10.00000;-48.40000;,
 0.00000;-5.00000;-48.40000;,
 28.44881;-5.00000;-39.15643;,
 52.30811;10.00000;-16.99593;,
 52.30811;-5.00000;-16.99593;,
 46.03114;10.00000;-14.95642;,
 46.03114;-5.00000;-14.95642;,
 52.30811;10.00000;16.99594;,
 52.30811;-5.00000;16.99594;,
 46.03114;10.00000;14.95643;,
 46.03114;-5.00000;14.95643;,
 32.32818;10.00000;44.49594;,
 32.32818;-5.00000;44.49594;,
 28.44880;10.00000;39.15643;,
 28.44880;-5.00000;39.15643;,
 -0.00000;10.00000;55.00000;,
 -0.00000;-5.00000;55.00000;,
 -0.00000;10.00000;48.40000;,
 -0.00000;-5.00000;48.40000;,
 -32.32820;10.00000;44.49594;,
 -32.32820;-5.00000;44.49594;,
 -28.44881;10.00000;39.15642;,
 -28.44881;-5.00000;39.15642;,
 -52.30811;10.00000;16.99594;,
 -52.30811;-5.00000;16.99594;,
 -46.03114;10.00000;14.95643;,
 -46.03114;-5.00000;14.95643;,
 -52.30811;10.00000;-16.99594;,
 -52.30811;-5.00000;-16.99594;,
 -46.03114;10.00000;-14.95643;,
 -46.03114;-5.00000;-14.95643;,
 -32.32817;10.00000;-44.49595;,
 -32.32817;-5.00000;-44.49595;,
 -28.44879;10.00000;-39.15643;,
 -28.44879;-5.00000;-39.15643;,
 0.00000;10.00000;-55.00000;,
 0.00000;-5.00000;-55.00000;,
 0.00000;10.00000;-48.40000;,
 0.00000;-5.00000;-48.40000;,
 28.44881;10.00000;-39.15643;,
 32.32819;10.00000;-44.49594;,
 0.00000;-5.00000;-55.00000;,
 32.32819;-5.00000;-44.49594;,
 28.44881;-5.00000;-39.15643;,
 0.00000;-5.00000;-48.40000;,
 46.03114;10.00000;-14.95642;,
 52.30811;10.00000;-16.99593;,
 52.30811;-5.00000;-16.99593;,
 46.03114;-5.00000;-14.95642;,
 46.03114;10.00000;14.95643;,
 52.30811;10.00000;16.99594;,
 52.30811;-5.00000;16.99594;,
 46.03114;-5.00000;14.95643;,
 28.44880;10.00000;39.15643;,
 32.32818;10.00000;44.49594;,
 32.32818;-5.00000;44.49594;,
 28.44880;-5.00000;39.15643;,
 -0.00000;10.00000;48.40000;,
 -0.00000;10.00000;55.00000;,
 -0.00000;-5.00000;55.00000;,
 -0.00000;-5.00000;48.40000;,
 -28.44881;10.00000;39.15642;,
 -32.32820;10.00000;44.49594;,
 -32.32820;-5.00000;44.49594;,
 -28.44881;-5.00000;39.15642;,
 -46.03114;10.00000;14.95643;,
 -52.30811;10.00000;16.99594;,
 -52.30811;-5.00000;16.99594;,
 -46.03114;-5.00000;14.95643;,
 -46.03114;10.00000;-14.95643;,
 -52.30811;10.00000;-16.99594;,
 -52.30811;-5.00000;-16.99594;,
 -46.03114;-5.00000;-14.95643;,
 -28.44879;10.00000;-39.15643;,
 -32.32817;10.00000;-44.49595;,
 -32.32817;-5.00000;-44.49595;,
 -28.44879;-5.00000;-39.15643;,
 0.00000;10.00000;-50.00000;,
 29.38926;10.00000;-40.45085;,
 29.38926;0.00000;-40.45085;,
 0.00000;0.00000;-50.00000;,
 47.55283;10.00000;-15.45085;,
 47.55283;0.00000;-15.45085;,
 47.55283;10.00000;15.45085;,
 47.55283;0.00000;15.45085;,
 29.38926;10.00000;40.45085;,
 29.38926;0.00000;40.45085;,
 -0.00000;10.00000;50.00000;,
 -0.00000;0.00000;50.00000;,
 -29.38927;10.00000;40.45085;,
 -29.38927;0.00000;40.45085;,
 -47.55283;10.00000;15.45085;,
 -47.55283;0.00000;15.45085;,
 -47.55282;10.00000;-15.45086;,
 -47.55282;0.00000;-15.45086;,
 -29.38925;10.00000;-40.45086;,
 -29.38925;0.00000;-40.45086;,
 0.00000;10.00000;-50.00000;,
 0.00000;0.00000;-50.00000;,
 0.00000;10.00000;0.00000;,
 0.00000;10.00000;0.00000;,
 0.00000;10.00000;0.00000;,
 0.00000;10.00000;0.00000;,
 0.00000;10.00000;0.00000;,
 0.00000;10.00000;0.00000;,
 0.00000;10.00000;0.00000;,
 0.00000;10.00000;0.00000;,
 0.00000;10.00000;0.00000;,
 0.00000;10.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;;
 
 154;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;121,128,129,122;,
 4;130,124,127,131;,
 4;128,132,133,129;,
 4;134,130,131,135;,
 4;132,136,137,133;,
 4;138,134,135,139;,
 4;136,140,141,137;,
 4;142,138,139,143;,
 4;140,144,145,141;,
 4;146,142,143,147;,
 4;120,125,148,149;,
 4;150,151,152,153;,
 4;149,148,154,155;,
 4;151,156,157,152;,
 4;155,154,158,159;,
 4;156,160,161,157;,
 4;159,158,162,163;,
 4;160,164,165,161;,
 4;163,162,166,167;,
 4;164,168,169,165;,
 4;167,166,125,120;,
 4;168,150,153,169;,
 4;170,171,172,173;,
 4;174,175,176,177;,
 4;171,178,179,172;,
 4;180,174,177,181;,
 4;178,182,183,179;,
 4;184,180,181,185;,
 4;182,186,187,183;,
 4;188,184,185,189;,
 4;186,190,191,187;,
 4;192,188,189,193;,
 4;190,194,195,191;,
 4;196,192,193,197;,
 4;170,175,198,199;,
 4;200,201,202,203;,
 4;199,198,204,205;,
 4;201,206,207,202;,
 4;205,204,208,209;,
 4;206,210,211,207;,
 4;209,208,212,213;,
 4;210,214,215,211;,
 4;213,212,216,217;,
 4;214,218,219,215;,
 4;217,216,175,170;,
 4;218,200,203,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;221,228,229,222;,
 4;230,224,227,231;,
 4;228,232,233,229;,
 4;234,230,231,235;,
 4;232,236,237,233;,
 4;238,234,235,239;,
 4;236,240,241,237;,
 4;242,238,239,243;,
 4;240,244,245,241;,
 4;246,242,243,247;,
 4;244,248,249,245;,
 4;250,246,247,251;,
 4;248,252,253,249;,
 4;254,250,251,255;,
 4;252,256,257,253;,
 4;258,254,255,259;,
 4;256,260,261,257;,
 4;262,258,259,263;,
 4;220,225,264,265;,
 4;266,267,268,269;,
 4;265,264,270,271;,
 4;267,272,273,268;,
 4;271,270,274,275;,
 4;272,276,277,273;,
 4;275,274,278,279;,
 4;276,280,281,277;,
 4;279,278,282,283;,
 4;280,284,285,281;,
 4;283,282,286,287;,
 4;284,288,289,285;,
 4;287,286,290,291;,
 4;288,292,293,289;,
 4;291,290,294,295;,
 4;292,296,297,293;,
 4;295,294,298,299;,
 4;296,300,301,297;,
 4;299,298,225,220;,
 4;300,266,269,301;,
 4;302,303,304,305;,
 4;303,306,307,304;,
 4;306,308,309,307;,
 4;308,310,311,309;,
 4;310,312,313,311;,
 4;312,314,315,313;,
 4;314,316,317,315;,
 4;316,318,319,317;,
 4;318,320,321,319;,
 4;320,322,323,321;,
 3;324,303,302;,
 3;325,306,303;,
 3;326,308,306;,
 3;327,310,308;,
 3;328,312,310;,
 3;329,314,312;,
 3;330,316,314;,
 3;331,318,316;,
 3;332,320,318;,
 3;333,322,320;,
 3;334,305,304;,
 3;335,304,307;,
 3;336,307,309;,
 3;337,309,311;,
 3;338,311,313;,
 3;339,313,315;,
 3;340,315,317;,
 3;341,317,319;,
 3;342,319,321;,
 3;343,321,323;;
 
 MeshMaterialList {
  2;
  154;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  93;
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  -0.049372;0.998780;0.000000;,
  -0.490485;0.871450;0.000000;,
  -1.000000;0.000000;0.000001;,
  -0.086252;-0.996273;0.000000;,
  0.343724;-0.939071;-0.000000;,
  0.988372;-0.152057;-0.000000;,
  0.056759;-0.998388;-0.000000;,
  0.488619;-0.872497;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.099855;0.995002;0.000000;,
  -0.317939;0.948111;0.000000;,
  -0.983870;0.178885;0.000000;,
  -0.500000;-0.866025;0.000000;,
  0.500000;0.866025;0.000000;,
  0.402148;0.915575;0.000000;,
  -0.386585;-0.922254;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.016331;0.999867;-0.000000;,
  0.457547;0.889185;-0.000000;,
  1.000000;0.000000;-0.000000;,
  0.086252;-0.996273;-0.000000;,
  -0.343724;-0.939071;0.000000;,
  -0.988372;-0.152057;0.000000;,
  -0.018717;-0.999825;0.000000;,
  -0.449795;-0.893132;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.099855;0.995002;0.000000;,
  0.317939;0.948111;0.000000;,
  0.983870;0.178885;0.000000;,
  0.500000;-0.866025;-0.000000;,
  -0.500000;0.866025;0.000000;,
  -0.428264;0.903654;0.000000;,
  0.416052;-0.909341;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.587785;0.000000;-0.809017;,
  0.951057;0.000000;-0.309017;,
  0.951056;0.000000;0.309017;,
  0.587785;0.000000;0.809017;,
  -0.000000;0.000000;1.000000;,
  -0.587785;0.000000;0.809017;,
  -0.951057;0.000000;0.309017;,
  -0.951056;0.000000;-0.309017;,
  -0.587785;0.000000;-0.809017;,
  -0.000000;0.000000;1.000000;,
  -0.587785;0.000000;0.809017;,
  -0.951057;0.000000;0.309017;,
  -0.951057;0.000000;-0.309017;,
  -0.587785;0.000000;-0.809017;,
  0.000000;0.000000;-1.000000;,
  0.951057;0.000000;-0.309017;,
  0.951056;0.000000;0.309017;,
  0.587785;0.000000;0.809017;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.587785;0.000000;-0.809017;,
  0.951057;0.000000;-0.309017;,
  0.951057;0.000000;0.309017;,
  0.587785;0.000000;0.809017;,
  -0.000000;0.000000;1.000000;,
  -0.587785;0.000000;0.809017;,
  -0.951057;0.000000;0.309017;,
  -0.951056;0.000000;-0.309017;,
  -0.587785;0.000000;-0.809017;,
  0.000000;-1.000000;-0.000000;;
  154;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;23,23,23,23;,
  4;22,22,22,22;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;19,19,19,19;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;20,20,20,20;,
  4;24,25,25,24;,
  4;31,30,30,31;,
  4;26,26,26,26;,
  4;32,32,32,32;,
  4;36,27,27,36;,
  4;33,37,37,33;,
  4;27,28,28,27;,
  4;34,33,33,34;,
  4;29,29,29,29;,
  4;35,35,35,35;,
  4;38,24,24,38;,
  4;30,39,39,30;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,43,43,42;,
  4;49,48,48,49;,
  4;44,44,44,44;,
  4;50,50,50,50;,
  4;54,45,45,54;,
  4;51,55,55,51;,
  4;45,46,46,45;,
  4;52,51,51,52;,
  4;47,47,47,47;,
  4;53,53,53,53;,
  4;56,42,42,56;,
  4;48,57,57,48;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,61,61,60;,
  4;71,70,70,71;,
  4;61,62,62,61;,
  4;72,71,71,72;,
  4;62,63,63,62;,
  4;73,72,72,73;,
  4;63,64,64,63;,
  4;74,73,73,74;,
  4;64,65,65,64;,
  4;75,74,74,75;,
  4;65,66,66,65;,
  4;61,75,75,61;,
  4;66,67,67,66;,
  4;76,61,61,76;,
  4;67,68,68,67;,
  4;77,76,76,77;,
  4;68,69,69,68;,
  4;78,77,77,78;,
  4;69,60,60,69;,
  4;70,78,78,70;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;82,83,83,82;,
  4;83,84,84,83;,
  4;84,85,85,84;,
  4;85,86,86,85;,
  4;86,87,87,86;,
  4;87,88,88,87;,
  4;88,89,89,88;,
  4;89,90,90,89;,
  4;90,91,91,90;,
  4;91,82,82,91;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;;
 }
 MeshTextureCoords {
  344;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.166670;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.166670;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.100000;0.000000;,
  0.100000;1.000000;,
  0.000000;1.000000;,
  0.100000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.100000;1.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.300000;0.000000;,
  0.300000;1.000000;,
  0.300000;0.000000;,
  0.300000;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.700000;0.000000;,
  0.700000;1.000000;,
  0.700000;0.000000;,
  0.700000;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  0.900000;0.000000;,
  0.900000;1.000000;,
  0.900000;0.000000;,
  0.900000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.100000;0.000000;,
  0.100000;1.000000;,
  0.000000;1.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.300000;0.000000;,
  0.300000;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.700000;0.000000;,
  0.700000;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  0.900000;0.000000;,
  0.900000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.050000;0.000000;,
  0.150000;0.000000;,
  0.250000;0.000000;,
  0.350000;0.000000;,
  0.450000;0.000000;,
  0.550000;0.000000;,
  0.650000;0.000000;,
  0.750000;0.000000;,
  0.850000;0.000000;,
  0.950000;0.000000;,
  0.050000;1.000000;,
  0.150000;1.000000;,
  0.250000;1.000000;,
  0.350000;1.000000;,
  0.450000;1.000000;,
  0.550000;1.000000;,
  0.650000;1.000000;,
  0.750000;1.000000;,
  0.850000;1.000000;,
  0.950000;1.000000;;
 }
}
