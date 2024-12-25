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
 244;
 -51.00000;101.00000;-10.00000;,
 -45.00000;101.00000;-10.00000;,
 -45.00000;-1.00000;-10.00000;,
 -51.00000;-1.00000;-10.00000;,
 -45.00000;101.00000;-10.00000;,
 -45.00000;101.00000;10.00000;,
 -45.00000;-1.00000;10.00000;,
 -45.00000;-1.00000;-10.00000;,
 -45.00000;101.00000;10.00000;,
 -51.00000;101.00000;10.00000;,
 -51.00000;-1.00000;10.00000;,
 -45.00000;-1.00000;10.00000;,
 -51.00000;101.00000;10.00000;,
 -51.00000;101.00000;-10.00000;,
 -51.00000;-1.00000;-10.00000;,
 -51.00000;-1.00000;10.00000;,
 -45.00000;101.00000;-10.00000;,
 -51.00000;101.00000;-10.00000;,
 -51.00000;-1.00000;-10.00000;,
 -45.00000;-1.00000;-10.00000;,
 45.00000;101.00000;-10.00000;,
 51.00000;101.00000;-10.00000;,
 51.00000;-1.00000;-10.00000;,
 45.00000;-1.00000;-10.00000;,
 51.00000;101.00000;-10.00000;,
 51.00000;101.00000;10.00000;,
 51.00000;-1.00000;10.00000;,
 51.00000;-1.00000;-10.00000;,
 51.00000;101.00000;10.00000;,
 45.00000;101.00000;10.00000;,
 45.00000;-1.00000;10.00000;,
 51.00000;-1.00000;10.00000;,
 45.00000;101.00000;10.00000;,
 45.00000;101.00000;-10.00000;,
 45.00000;-1.00000;-10.00000;,
 45.00000;-1.00000;10.00000;,
 51.00000;101.00000;-10.00000;,
 45.00000;101.00000;-10.00000;,
 45.00000;-1.00000;-10.00000;,
 51.00000;-1.00000;-10.00000;,
 -10.00000;101.00000;51.00000;,
 -10.00000;101.00000;45.00000;,
 -10.00000;-1.00000;45.00000;,
 -10.00000;-1.00000;51.00000;,
 -10.00000;101.00000;45.00000;,
 10.00000;101.00000;45.00000;,
 10.00000;-1.00000;45.00000;,
 -10.00000;-1.00000;45.00000;,
 10.00000;101.00000;45.00000;,
 10.00000;101.00000;51.00000;,
 10.00000;-1.00000;51.00000;,
 10.00000;-1.00000;45.00000;,
 10.00000;101.00000;51.00000;,
 -10.00000;101.00000;51.00000;,
 -10.00000;-1.00000;51.00000;,
 10.00000;-1.00000;51.00000;,
 -10.00000;101.00000;45.00000;,
 -10.00000;101.00000;51.00000;,
 -10.00000;-1.00000;51.00000;,
 -10.00000;-1.00000;45.00000;,
 51.00000;5.00000;-10.00000;,
 51.00000;-1.00000;-10.00000;,
 -51.00000;-1.00000;-10.00000;,
 -51.00000;5.00000;-10.00000;,
 51.00000;-1.00000;-10.00000;,
 51.00000;-1.00000;10.00000;,
 -51.00000;-1.00000;10.00000;,
 -51.00000;-1.00000;-10.00000;,
 51.00000;-1.00000;10.00000;,
 51.00000;5.00000;10.00000;,
 -51.00000;5.00000;10.00000;,
 -51.00000;-1.00000;10.00000;,
 51.00000;5.00000;10.00000;,
 51.00000;5.00000;-10.00000;,
 -51.00000;5.00000;-10.00000;,
 -51.00000;5.00000;10.00000;,
 51.00000;-1.00000;-10.00000;,
 51.00000;5.00000;-10.00000;,
 -51.00000;5.00000;-10.00000;,
 -51.00000;-1.00000;-10.00000;,
 -10.00000;5.00000;-51.00000;,
 -10.00000;-1.00000;-51.00000;,
 -10.00000;-1.00000;51.00000;,
 -10.00000;5.00000;51.00000;,
 -10.00000;-1.00000;-51.00000;,
 10.00000;-1.00000;-51.00000;,
 10.00000;-1.00000;51.00000;,
 -10.00000;-1.00000;51.00000;,
 10.00000;-1.00000;-51.00000;,
 10.00000;5.00000;-51.00000;,
 10.00000;5.00000;51.00000;,
 10.00000;-1.00000;51.00000;,
 10.00000;5.00000;-51.00000;,
 -10.00000;5.00000;-51.00000;,
 -10.00000;5.00000;51.00000;,
 10.00000;5.00000;51.00000;,
 -10.00000;-1.00000;-51.00000;,
 -10.00000;5.00000;-51.00000;,
 -10.00000;5.00000;51.00000;,
 -10.00000;-1.00000;51.00000;,
 -10.00000;101.00000;-45.00000;,
 -10.00000;101.00000;-51.00000;,
 -10.00000;-1.00000;-51.00000;,
 -10.00000;-1.00000;-45.00000;,
 -10.00000;101.00000;-51.00000;,
 10.00000;101.00000;-51.00000;,
 10.00000;-1.00000;-51.00000;,
 -10.00000;-1.00000;-51.00000;,
 10.00000;101.00000;-51.00000;,
 10.00000;101.00000;-45.00000;,
 10.00000;-1.00000;-45.00000;,
 10.00000;-1.00000;-51.00000;,
 10.00000;101.00000;-45.00000;,
 -10.00000;101.00000;-45.00000;,
 -10.00000;-1.00000;-45.00000;,
 10.00000;-1.00000;-45.00000;,
 -10.00000;101.00000;-51.00000;,
 -10.00000;101.00000;-45.00000;,
 -10.00000;-1.00000;-45.00000;,
 -10.00000;-1.00000;-51.00000;,
 0.00000;100.00000;-50.00000;,
 29.38926;100.00000;-40.45085;,
 29.38926;0.00000;-40.45085;,
 0.00000;0.00000;-50.00000;,
 23.51141;100.00000;-32.36068;,
 0.00000;100.00000;-40.00000;,
 0.00000;0.00000;-40.00000;,
 23.51141;0.00000;-32.36068;,
 47.55283;100.00000;-15.45085;,
 47.55283;0.00000;-15.45085;,
 38.04226;100.00000;-12.36068;,
 38.04226;0.00000;-12.36068;,
 47.55283;100.00000;15.45085;,
 47.55283;0.00000;15.45085;,
 38.04226;100.00000;12.36068;,
 38.04226;0.00000;12.36068;,
 29.38926;100.00000;40.45085;,
 29.38926;0.00000;40.45085;,
 23.51141;100.00000;32.36068;,
 23.51141;0.00000;32.36068;,
 -0.00000;100.00000;50.00000;,
 -0.00000;0.00000;50.00000;,
 -0.00000;100.00000;40.00000;,
 -0.00000;0.00000;40.00000;,
 -29.38927;100.00000;40.45085;,
 -29.38927;0.00000;40.45085;,
 -23.51141;100.00000;32.36068;,
 -23.51141;0.00000;32.36068;,
 -47.55283;100.00000;15.45085;,
 -47.55283;0.00000;15.45085;,
 -38.04226;100.00000;12.36068;,
 -38.04226;0.00000;12.36068;,
 -47.55282;100.00000;-15.45086;,
 -47.55282;0.00000;-15.45086;,
 -38.04226;100.00000;-12.36069;,
 -38.04226;0.00000;-12.36069;,
 -29.38925;100.00000;-40.45086;,
 -29.38925;0.00000;-40.45086;,
 -23.51140;100.00000;-32.36069;,
 -23.51140;0.00000;-32.36069;,
 0.00000;100.00000;-50.00000;,
 0.00000;0.00000;-50.00000;,
 0.00000;100.00000;-40.00000;,
 0.00000;0.00000;-40.00000;,
 23.51141;100.00000;-32.36068;,
 29.38926;100.00000;-40.45085;,
 0.00000;0.00000;-50.00000;,
 29.38926;0.00000;-40.45085;,
 23.51141;0.00000;-32.36068;,
 0.00000;0.00000;-40.00000;,
 38.04226;100.00000;-12.36068;,
 47.55283;100.00000;-15.45085;,
 47.55283;0.00000;-15.45085;,
 38.04226;0.00000;-12.36068;,
 38.04226;100.00000;12.36068;,
 47.55283;100.00000;15.45085;,
 47.55283;0.00000;15.45085;,
 38.04226;0.00000;12.36068;,
 23.51141;100.00000;32.36068;,
 29.38926;100.00000;40.45085;,
 29.38926;0.00000;40.45085;,
 23.51141;0.00000;32.36068;,
 -0.00000;100.00000;40.00000;,
 -0.00000;100.00000;50.00000;,
 -0.00000;0.00000;50.00000;,
 -0.00000;0.00000;40.00000;,
 -23.51141;100.00000;32.36068;,
 -29.38927;100.00000;40.45085;,
 -29.38927;0.00000;40.45085;,
 -23.51141;0.00000;32.36068;,
 -38.04226;100.00000;12.36068;,
 -47.55283;100.00000;15.45085;,
 -47.55283;0.00000;15.45085;,
 -38.04226;0.00000;12.36068;,
 -38.04226;100.00000;-12.36069;,
 -47.55282;100.00000;-15.45086;,
 -47.55282;0.00000;-15.45086;,
 -38.04226;0.00000;-12.36069;,
 -23.51140;100.00000;-32.36069;,
 -29.38925;100.00000;-40.45086;,
 -29.38925;0.00000;-40.45086;,
 -23.51140;0.00000;-32.36069;,
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
 
 106;
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
 4;144,148,149,145;,
 4;150,146,147,151;,
 4;148,152,153,149;,
 4;154,150,151,155;,
 4;152,156,157,153;,
 4;158,154,155,159;,
 4;156,160,161,157;,
 4;162,158,159,163;,
 4;120,125,164,165;,
 4;166,167,168,169;,
 4;165,164,170,171;,
 4;167,172,173,168;,
 4;171,170,174,175;,
 4;172,176,177,173;,
 4;175,174,178,179;,
 4;176,180,181,177;,
 4;179,178,182,183;,
 4;180,184,185,181;,
 4;183,182,186,187;,
 4;184,188,189,185;,
 4;187,186,190,191;,
 4;188,192,193,189;,
 4;191,190,194,195;,
 4;192,196,197,193;,
 4;195,194,198,199;,
 4;196,200,201,197;,
 4;199,198,125,120;,
 4;200,166,169,201;,
 4;202,203,204,205;,
 4;203,206,207,204;,
 4;206,208,209,207;,
 4;208,210,211,209;,
 4;210,212,213,211;,
 4;212,214,215,213;,
 4;214,216,217,215;,
 4;216,218,219,217;,
 4;218,220,221,219;,
 4;220,222,223,221;,
 3;224,203,202;,
 3;225,206,203;,
 3;226,208,206;,
 3;227,210,208;,
 3;228,212,210;,
 3;229,214,212;,
 3;230,216,214;,
 3;231,218,216;,
 3;232,220,218;,
 3;233,222,220;,
 3;234,205,204;,
 3;235,204,207;,
 3;236,207,209;,
 3;237,209,211;,
 3;238,211,213;,
 3;239,213,215;,
 3;240,215,217;,
 3;241,217,219;,
 3;242,219,221;,
 3;243,221,223;;
 
 MeshMaterialList {
  2;
  106;
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
   0.800000;0.000000;0.800000;1.000000;;
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
  69;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
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
  106;
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
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,37,37,36;,
  4;47,46,46,47;,
  4;37,38,38,37;,
  4;48,47,47,48;,
  4;38,39,39,38;,
  4;49,48,48,49;,
  4;39,40,40,39;,
  4;50,49,49,50;,
  4;40,41,41,40;,
  4;51,50,50,51;,
  4;41,42,42,41;,
  4;37,51,51,37;,
  4;42,43,43,42;,
  4;52,37,37,52;,
  4;43,44,44,43;,
  4;53,52,52,53;,
  4;44,45,45,44;,
  4;54,53,53,54;,
  4;45,36,36,45;,
  4;46,54,54,46;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,58,58,67;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;;
 }
 MeshTextureCoords {
  244;
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
