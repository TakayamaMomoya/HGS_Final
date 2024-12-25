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
 295;
 -0.88858;33.87353;-61.91890;,
 29.78566;33.87353;-61.91890;,
 29.78566;21.87282;-66.87103;,
 -0.88858;21.87282;-66.87103;,
 29.78566;33.87353;91.54783;,
 -0.88858;33.87353;91.54783;,
 -0.88858;9.65682;91.54783;,
 29.78566;9.65682;91.54783;,
 29.78566;33.87353;-37.26079;,
 29.78566;11.38735;-59.83816;,
 -0.88858;33.87353;-35.76882;,
 -0.88858;33.87353;-61.91890;,
 -0.88858;21.87282;-66.87103;,
 -0.88858;11.27478;-58.34617;,
 -0.88858;9.65682;91.54783;,
 -0.88858;33.87353;91.54783;,
 -0.88858;33.87353;-35.76882;,
 -0.88858;11.27478;-58.34617;,
 -29.78566;21.87282;-66.87103;,
 -29.78566;33.87353;-61.91890;,
 -29.78566;9.65682;91.54783;,
 -29.78566;33.87353;91.54783;,
 -29.78566;11.38735;-59.83816;,
 -29.78566;33.87353;-37.26079;,
 -29.78566;33.87353;-61.91890;,
 -29.78566;21.87282;-66.87103;,
 -29.78566;11.38735;-59.83816;,
 -29.78566;33.87353;-37.26079;,
 29.67760;24.56045;-65.97367;,
 47.24293;24.56045;-65.97367;,
 47.24293;21.67878;-65.97367;,
 29.67760;21.67878;-65.97367;,
 47.24293;25.22333;90.22344;,
 29.67760;25.22333;90.22344;,
 29.67760;22.34166;90.22344;,
 47.24293;22.34166;90.22344;,
 47.24293;33.49849;74.53894;,
 47.24293;30.61685;74.49649;,
 47.24293;31.71956;-57.72064;,
 47.24293;34.60123;-57.60004;,
 29.67760;30.61685;74.90841;,
 29.67760;33.49849;74.95076;,
 29.67760;34.60123;-56.69571;,
 29.67760;31.71956;-56.81649;,
 29.67760;33.49849;74.95076;,
 29.67760;34.60123;-56.69571;,
 29.67760;30.61685;74.90841;,
 29.67760;31.71956;-56.81649;,
 47.24293;28.70441;-62.58406;,
 47.24293;30.36130;-63.53749;,
 29.67760;29.56355;-63.87522;,
 29.67760;24.56045;-65.97367;,
 29.67760;21.67878;-65.97367;,
 29.67760;27.82601;-62.87551;,
 29.67760;29.56355;-63.87522;,
 29.67760;27.82601;-62.87551;,
 29.67760;21.67878;-65.97367;,
 47.24293;21.67878;-65.97367;,
 47.24293;28.70441;-62.58406;,
 47.24293;31.71956;-57.72064;,
 29.67760;31.71956;-56.81649;,
 47.24293;31.59091;85.63599;,
 47.24293;29.11339;84.84539;,
 29.67760;28.80897;85.64887;,
 29.67760;22.34166;90.22344;,
 29.67760;25.22333;90.22344;,
 29.67760;31.27644;86.43627;,
 29.67760;31.27644;86.43627;,
 29.67760;28.80897;85.64887;,
 -29.67760;21.67878;-65.97367;,
 -47.24293;21.67878;-65.97367;,
 -47.24293;24.56045;-65.97367;,
 -29.67760;24.56045;-65.97367;,
 -47.24293;22.34166;90.22344;,
 -29.67760;22.34166;90.22344;,
 -29.67760;25.22333;90.22344;,
 -47.24293;25.22333;90.22344;,
 -47.24293;34.60123;-57.60004;,
 -47.24293;31.71956;-57.72064;,
 -47.24293;30.61685;74.49649;,
 -47.24293;33.49849;74.53894;,
 -29.67760;31.71956;-56.81649;,
 -29.67760;34.60123;-56.69571;,
 -29.67760;33.49849;74.95076;,
 -29.67760;30.61685;74.90841;,
 -29.67760;34.60123;-56.69571;,
 -29.67760;33.49849;74.95076;,
 -29.67760;31.71956;-56.81649;,
 -29.67760;30.61685;74.90841;,
 -47.24293;30.36130;-63.53749;,
 -47.24293;24.56045;-65.97367;,
 -47.24293;21.67878;-65.97367;,
 -47.24293;28.70441;-62.58406;,
 -47.24293;31.71956;-57.72064;,
 -47.24293;34.60123;-57.60004;,
 -29.67760;27.82601;-62.87551;,
 -29.67760;21.67878;-65.97367;,
 -29.67760;24.56045;-65.97367;,
 -29.67760;29.56355;-63.87522;,
 -29.67760;29.56355;-63.87522;,
 -47.24293;30.36130;-63.53749;,
 -47.24293;28.70441;-62.58406;,
 -47.24293;21.67878;-65.97367;,
 -29.67760;21.67878;-65.97367;,
 -29.67760;27.82601;-62.87551;,
 -29.67760;31.71956;-56.81649;,
 -47.24293;31.71956;-57.72064;,
 -47.24293;29.11339;84.84539;,
 -47.24293;31.59091;85.63599;,
 -29.67760;31.27644;86.43627;,
 -29.67760;25.22333;90.22344;,
 -29.67760;22.34166;90.22344;,
 -29.67760;28.80897;85.64887;,
 -29.67760;31.27644;86.43627;,
 -29.67760;28.80897;85.64887;,
 -47.24293;22.34166;90.22344;,
 -47.24293;29.11339;84.84539;,
 -47.24293;30.61685;74.49649;,
 -29.67760;30.61685;74.90841;,
 31.14679;30.08696;75.07480;,
 46.34091;30.08696;75.07480;,
 46.34091;30.08696;-57.05763;,
 31.14679;30.08696;-57.05763;,
 31.14679;0.13262;-54.04850;,
 46.34091;0.13262;-54.04850;,
 46.34091;-0.31873;75.07480;,
 31.14679;-0.31873;75.07480;,
 46.34091;20.11960;-63.54486;,
 31.14679;20.11293;-63.54486;,
 46.34091;24.97202;82.27244;,
 46.34091;20.11960;-63.54486;,
 46.34091;30.08696;-57.05763;,
 46.34091;30.08696;75.07480;,
 31.14679;24.96545;82.27244;,
 46.34091;24.97202;82.27244;,
 31.14679;20.11293;-63.54486;,
 31.14679;24.96545;82.27244;,
 31.14679;30.08696;75.07480;,
 31.14679;30.08696;-57.05763;,
 46.34091;10.68018;-64.77667;,
 31.14679;10.49077;-64.77667;,
 46.34091;15.14820;84.85157;,
 46.34091;-0.31873;75.07480;,
 46.34091;0.13262;-54.04850;,
 46.34091;10.68018;-64.77667;,
 31.14679;14.95870;84.85157;,
 46.34091;15.14820;84.85157;,
 31.14679;10.49077;-64.77667;,
 31.14679;0.13262;-54.04850;,
 31.14679;-0.31873;75.07480;,
 31.14679;14.95870;84.85157;,
 -31.14679;30.08696;-57.05763;,
 -46.34091;30.08696;-57.05763;,
 -46.34091;30.08696;75.07480;,
 -31.14679;30.08696;75.07480;,
 -31.14679;-0.31873;75.07480;,
 -46.34091;-0.31873;75.07480;,
 -46.34091;0.13262;-54.04850;,
 -31.14679;0.13262;-54.04850;,
 -31.14679;20.11293;-63.54486;,
 -46.34091;20.11960;-63.54486;,
 -46.34091;30.08696;75.07480;,
 -46.34091;30.08696;-57.05763;,
 -46.34091;20.11960;-63.54486;,
 -46.34091;24.97202;82.27244;,
 -46.34091;24.97202;82.27244;,
 -31.14679;24.96545;82.27244;,
 -31.14679;30.08696;-57.05763;,
 -31.14679;30.08696;75.07480;,
 -31.14679;24.96545;82.27244;,
 -31.14679;20.11293;-63.54486;,
 -31.14679;10.49077;-64.77667;,
 -46.34091;10.68018;-64.77667;,
 -46.34091;10.68018;-64.77667;,
 -46.34091;0.13262;-54.04850;,
 -46.34091;-0.31873;75.07480;,
 -46.34091;15.14820;84.85157;,
 -46.34091;15.14820;84.85157;,
 -31.14679;14.95870;84.85157;,
 -31.14679;14.95870;84.85157;,
 -31.14679;-0.31873;75.07480;,
 -31.14679;0.13262;-54.04850;,
 -31.14679;10.49077;-64.77667;,
 7.01122;61.02452;-28.25443;,
 26.83975;61.02452;-20.69746;,
 26.83975;33.49666;-20.69746;,
 7.01122;33.49666;-28.25443;,
 29.00173;61.02452;20.58910;,
 29.00173;33.49666;20.58910;,
 28.81300;61.02452;38.52075;,
 28.81300;33.49666;38.52075;,
 28.81300;61.02452;38.52075;,
 7.01122;61.02452;45.96249;,
 7.01122;33.49666;45.96249;,
 28.81300;33.49666;38.52075;,
 7.01122;61.02452;20.58910;,
 7.01122;61.02452;45.96249;,
 7.01122;33.49666;20.58910;,
 7.01122;33.49666;-28.25443;,
 26.83975;33.49666;-20.69746;,
 7.01122;33.49666;20.58910;,
 29.00173;33.49666;20.58910;,
 7.01122;33.49666;20.58910;,
 7.01122;33.49666;20.58910;,
 -7.01122;33.49666;-28.25443;,
 -26.83975;33.49666;-20.69746;,
 -26.83975;61.02452;-20.69746;,
 -7.01122;61.02452;-28.25443;,
 -29.00173;33.49666;20.58910;,
 -29.00173;61.02452;20.58910;,
 -28.81300;33.49666;38.52075;,
 -28.81300;61.02452;38.52075;,
 -7.01122;33.49666;45.96249;,
 -7.01122;61.02452;45.96249;,
 -7.01122;61.02452;20.58910;,
 -26.83975;33.49666;-20.69746;,
 -7.01122;33.49666;-28.25443;,
 -7.01122;33.49666;20.58910;,
 -29.00173;33.49666;20.58910;,
 -7.01122;33.49666;20.58910;,
 -28.81300;33.49666;38.52075;,
 -7.01122;33.49666;20.58910;,
 -7.01122;33.49666;45.96249;,
 -7.01122;33.49666;20.58910;,
 7.01122;33.49666;45.96249;,
 0.00000;56.08796;-38.09730;,
 14.19114;56.08796;-38.09730;,
 14.19114;39.49578;-38.09730;,
 0.00000;39.49578;-38.09730;,
 14.19114;56.08796;-23.79840;,
 14.19114;39.49578;-23.79840;,
 14.19114;56.08796;-23.79840;,
 0.00000;56.08796;-23.79840;,
 0.00000;39.49578;-23.79840;,
 14.19114;39.49578;-23.79840;,
 0.00000;56.08796;-23.79840;,
 0.00000;56.08796;-38.09730;,
 0.00000;39.49578;-38.09730;,
 0.00000;39.49578;-23.79840;,
 0.00000;56.08796;-23.79840;,
 0.00000;39.49578;-38.09730;,
 14.19114;39.49578;-38.09730;,
 14.19114;39.49578;-23.79840;,
 -14.19114;39.49578;-38.09730;,
 -14.19114;56.08796;-38.09730;,
 -14.19114;39.49578;-23.79840;,
 -14.19114;56.08796;-23.79840;,
 -14.19114;39.49578;-23.79840;,
 -14.19114;56.08796;-23.79840;,
 -14.19114;39.49578;-23.79840;,
 -14.19114;39.49578;-38.09730;,
 0.18504;50.03990;-37.17914;,
 2.25814;49.21884;-37.17914;,
 2.25814;49.21884;-92.95209;,
 0.18504;50.03990;-92.95209;,
 3.11691;47.23665;-37.17914;,
 3.11691;47.23665;-92.95209;,
 2.25814;45.25449;-37.17914;,
 2.25814;45.25449;-92.95209;,
 0.18504;44.43346;-37.17914;,
 0.18504;44.43346;-92.95209;,
 0.18504;47.23665;-37.17914;,
 2.25814;49.21884;-37.17914;,
 0.18504;50.03990;-37.17914;,
 0.18504;47.23665;-37.17914;,
 3.11691;47.23665;-37.17914;,
 0.18504;47.23665;-37.17914;,
 2.25814;45.25449;-37.17914;,
 0.18504;47.23665;-37.17914;,
 0.18504;44.43346;-37.17914;,
 0.18504;47.23665;-92.95209;,
 -0.18504;50.03990;-92.95209;,
 -2.25814;49.21884;-92.95209;,
 -2.25814;49.21884;-37.17914;,
 -0.18504;50.03990;-37.17914;,
 -2.25814;49.21884;-92.95209;,
 -3.11691;47.23665;-92.95209;,
 -3.11691;47.23665;-37.17914;,
 -2.25814;49.21884;-37.17914;,
 -3.11691;47.23665;-92.95209;,
 -2.25814;45.25449;-92.95209;,
 -2.25814;45.25449;-37.17914;,
 -3.11691;47.23665;-37.17914;,
 -0.18504;44.43346;-92.95209;,
 -0.18504;44.43346;-37.17914;,
 -0.18504;50.03990;-37.17914;,
 -0.18504;47.23665;-37.17914;,
 -0.18504;47.23665;-37.17914;,
 -2.25814;45.25449;-37.17914;,
 -0.18504;47.23665;-37.17914;,
 -0.18504;44.43346;-37.17914;,
 -0.18504;47.23665;-37.17914;,
 -0.18504;47.23665;-92.95209;,
 0.18504;50.03990;-92.95209;,
 -0.18504;50.03990;-92.95209;;
 
 164;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,4,7,9;,
 4;8,9,2,1;,
 4;10,11,12,13;,
 4;10,13,14,15;,
 4;8,1,0,16;,
 4;8,16,5,4;,
 4;9,7,6,17;,
 4;9,17,3,2;,
 4;3,18,19,0;,
 4;20,6,5,21;,
 4;22,20,21,23;,
 4;24,25,26,27;,
 4;13,12,11,10;,
 4;15,14,13,10;,
 4;16,0,19,23;,
 4;21,5,16,23;,
 4;17,6,20,22;,
 4;18,3,17,22;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,36,39,45;,
 4;37,46,47,38;,
 4;48,30,29,49;,
 4;48,49,39,38;,
 4;50,51,52,53;,
 4;50,53,43,42;,
 4;49,29,28,54;,
 4;49,54,45,39;,
 4;55,56,57,58;,
 4;55,58,59,60;,
 4;61,32,35,62;,
 4;61,62,37,36;,
 4;63,64,65,66;,
 4;63,66,41,40;,
 4;67,33,32,61;,
 4;67,61,36,44;,
 4;62,35,34,68;,
 4;62,68,46,37;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,78,79,80;,
 4;81,82,83,84;,
 4;85,77,80,86;,
 4;78,87,88,79;,
 4;89,90,91,92;,
 4;93,94,89,92;,
 4;95,96,97,98;,
 4;82,81,95,98;,
 4;99,72,71,100;,
 4;77,85,99,100;,
 4;101,102,103,104;,
 4;105,106,101,104;,
 4;107,73,76,108;,
 4;80,79,107,108;,
 4;109,110,111,112;,
 4;84,83,109,112;,
 4;108,76,75,113;,
 4;86,80,108,113;,
 4;114,111,115,116;,
 4;117,118,114,116;,
 4;119,120,121,122;,
 4;123,124,125,126;,
 4;127,128,122,121;,
 4;129,130,131,132;,
 4;133,134,120,119;,
 4;135,136,137,138;,
 4;139,124,123,140;,
 4;139,140,128,127;,
 4;141,142,143,144;,
 4;141,144,130,129;,
 4;145,126,125,146;,
 4;145,146,134,133;,
 4;147,148,149,150;,
 4;147,150,136,135;,
 4;151,152,153,154;,
 4;155,156,157,158;,
 4;152,151,159,160;,
 4;161,162,163,164;,
 4;154,153,165,166;,
 4;167,168,169,170;,
 4;171,158,157,172;,
 4;160,159,171,172;,
 4;173,174,175,176;,
 4;164,163,173,176;,
 4;177,156,155,178;,
 4;166,165,177,178;,
 4;179,180,181,182;,
 4;170,169,179,182;,
 4;183,184,185,186;,
 4;184,187,188,185;,
 4;187,189,190,188;,
 4;191,192,193,194;,
 3;195,184,183;,
 3;195,187,184;,
 3;195,189,187;,
 3;195,196,189;,
 3;197,198,199;,
 3;200,199,201;,
 3;202,201,194;,
 3;203,194,193;,
 4;204,205,206,207;,
 4;205,208,209,206;,
 4;208,210,211,209;,
 4;210,212,213,211;,
 3;207,206,214;,
 3;206,209,214;,
 3;209,211,214;,
 3;211,213,214;,
 3;215,216,217;,
 3;218,215,219;,
 3;220,218,221;,
 3;222,220,223;,
 4;186,204,207,183;,
 4;196,213,212,224;,
 4;183,207,214,195;,
 4;195,214,213,196;,
 4;197,217,216,198;,
 4;193,222,223,203;,
 4;225,226,227,228;,
 4;226,229,230,227;,
 4;231,232,233,234;,
 4;235,236,237,238;,
 4;239,229,226,225;,
 4;240,241,242,238;,
 4;228,243,244,225;,
 4;243,245,246,244;,
 4;247,233,232,248;,
 4;238,237,236,235;,
 4;225,244,246,239;,
 4;238,249,250,240;,
 4;251,252,253,254;,
 4;252,255,256,253;,
 4;255,257,258,256;,
 4;257,259,260,258;,
 3;261,262,263;,
 3;264,265,262;,
 3;266,267,265;,
 3;268,269,267;,
 3;270,254,253;,
 3;270,253,256;,
 3;270,256,258;,
 3;270,258,260;,
 4;271,272,273,274;,
 4;275,276,277,278;,
 4;279,280,281,282;,
 4;280,283,284,281;,
 3;285,278,286;,
 3;278,277,287;,
 3;277,288,289;,
 3;288,290,291;,
 3;272,271,292;,
 3;279,272,292;,
 3;280,279,292;,
 3;283,280,292;,
 4;293,294,285,263;,
 4;259,284,283,260;,
 4;263,285,286,261;,
 4;268,291,290,269;,
 4;270,292,271,254;,
 4;260,283,292,270;;
 
 MeshMaterialList {
  4;
  164;
  2,
  2,
  2,
  2,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  2,
  2,
  2,
  3,
  3,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  0,
  1,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  0,
  1,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  2,
  2,
  3,
  3,
  2,
  3,
  2,
  2,
  3,
  3,
  2,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  0,
  0,
  0,
  0,
  2,
  2,
  3,
  3,
  0,
  0;;
  Material {
   0.075200;0.075200;0.075200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\Ver.3.0-20221027T000251Z-001\\Ver.3.0\\data\\TEXTURE\\track.jpg";
   }
  }
  Material {
   0.091200;0.483200;0.009600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\Ver.3.0-20221027T000251Z-001\\Ver.3.0\\data\\TEXTURE\\armor.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  96;
  0.000000;0.381452;-0.924389;,
  0.000314;-0.121018;-0.992650;,
  0.000000;0.381452;-0.924389;,
  -0.010218;-0.121015;-0.992598;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.381452;-0.924389;,
  0.010846;-0.121008;-0.992592;,
  0.000000;1.000000;0.000000;,
  -0.009081;-0.889773;-0.456313;,
  0.001557;-0.999937;-0.011112;,
  -0.000048;-0.999938;-0.011112;,
  0.000279;-0.889811;-0.456330;,
  -0.001653;-0.999937;-0.011112;,
  0.009639;-0.889770;-0.456307;,
  0.000036;0.197382;-0.980327;,
  0.000000;0.000000;-1.000000;,
  0.006928;0.291527;0.956537;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.000042;0.197382;-0.980327;,
  -0.006928;0.291527;0.956537;,
  -0.001085;0.995536;0.094375;,
  -0.014373;0.954123;-0.299071;,
  0.001379;-0.996644;-0.081843;,
  0.015879;-0.961681;0.273711;,
  -0.014354;0.625641;-0.779979;,
  0.017754;-0.668914;0.743128;,
  0.003393;-0.442312;0.896855;,
  0.005850;0.836518;0.547908;,
  -0.005105;-0.856958;-0.515361;,
  -0.012523;-0.599878;-0.799994;,
  0.014373;0.954123;-0.299071;,
  0.001085;0.995536;0.094375;,
  -0.015879;-0.961681;0.273711;,
  -0.001379;-0.996644;-0.081843;,
  0.014348;0.625641;-0.779979;,
  -0.017754;-0.668914;0.743128;,
  -0.003393;-0.442312;0.896855;,
  -0.005850;0.836518;0.547908;,
  0.005105;-0.856958;-0.515361;,
  0.012523;-0.599878;-0.799994;,
  -0.000068;0.879022;-0.476781;,
  0.002397;-0.925689;-0.378278;,
  -0.000092;0.952618;0.304170;,
  0.001902;-0.877386;0.479781;,
  -0.000482;0.345415;-0.938450;,
  1.000000;0.000000;0.000000;,
  -0.000951;0.567593;0.823309;,
  0.002026;-0.328705;-0.944430;,
  0.000938;-0.155362;0.987857;,
  0.000068;0.879022;-0.476781;,
  -0.002397;-0.925689;-0.378278;,
  0.000092;0.952618;0.304170;,
  -0.001902;-0.877386;0.479781;,
  0.000482;0.345415;-0.938450;,
  -1.000000;0.000000;0.000000;,
  0.000951;0.567593;0.823309;,
  -0.002026;-0.328705;-0.944430;,
  -0.000938;-0.155362;0.987857;,
  0.000000;1.000000;0.000000;,
  0.181057;0.000000;-0.983473;,
  0.356129;0.000000;-0.934437;,
  0.999782;0.000000;-0.020895;,
  0.999945;0.000000;0.010524;,
  0.163728;0.000000;0.986506;,
  0.000000;-1.000000;-0.000000;,
  -0.181057;0.000000;-0.983473;,
  -0.356129;0.000000;-0.934437;,
  -0.999782;0.000000;-0.020895;,
  -0.999945;0.000000;0.010524;,
  -0.163728;0.000000;0.986506;,
  0.998632;0.000000;-0.052294;,
  0.323036;0.000000;0.946387;,
  -0.998632;0.000000;-0.052294;,
  -0.323036;0.000000;0.946387;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.187435;0.982277;0.000000;,
  0.695801;0.718235;0.000000;,
  1.000000;-0.000002;-0.000000;,
  0.695794;-0.718241;-0.000000;,
  0.187428;-0.982278;-0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.187435;0.982277;0.000000;,
  -0.695801;0.718235;0.000000;,
  -1.000000;-0.000002;0.000000;,
  -0.695794;-0.718241;0.000000;,
  -0.187428;-0.982278;0.000000;;
  164;
  4;0,2,3,1;,
  4;4,4,4,4;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;10,11,12,13;,
  4;10,13,1,3;,
  4;1,8,7,0;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;13,12,14,15;,
  4;8,1,13,15;,
  4;16,16,17,17;,
  4;18,18,19,19;,
  4;21,21,21,21;,
  4;20,20,20,20;,
  4;24,24,25,25;,
  4;26,26,27,27;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;28,16,16,28;,
  4;28,28,25,25;,
  4;29,30,30,29;,
  4;29,29,27,27;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;31,18,18,31;,
  4;31,31,24,24;,
  4;32,33,33,32;,
  4;32,32,26,26;,
  4;17,17,22,22;,
  4;19,19,23,23;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;34,34,35,35;,
  4;36,36,37,37;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;38,22,22,38;,
  4;34,34,38,38;,
  4;39,40,40,39;,
  4;36,36,39,39;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;41,23,23,41;,
  4;35,35,41,41;,
  4;42,43,43,42;,
  4;37,37,42,42;,
  4;46,46,44,44;,
  4;45,45,47,47;,
  4;48,48,44,44;,
  4;49,49,49,49;,
  4;50,50,46,46;,
  4;58,58,58,58;,
  4;51,45,45,51;,
  4;51,51,48,48;,
  4;49,49,49,49;,
  4;49,49,49,49;,
  4;52,47,47,52;,
  4;52,52,50,50;,
  4;58,58,58,58;,
  4;58,58,58,58;,
  4;53,53,55,55;,
  4;56,56,54,54;,
  4;53,53,57,57;,
  4;58,58,58,58;,
  4;55,55,59,59;,
  4;49,49,49,49;,
  4;60,54,54,60;,
  4;57,57,60,60;,
  4;58,58,58,58;,
  4;58,58,58,58;,
  4;61,56,56,61;,
  4;59,59,61,61;,
  4;49,49,49,49;,
  4;49,49,49,49;,
  4;63,64,64,63;,
  4;74,65,65,74;,
  4;65,66,66,65;,
  4;75,67,67,75;,
  3;62,62,62;,
  3;62,62,62;,
  3;62,62,62;,
  3;62,62,62;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  4;69,70,70,69;,
  4;76,71,71,76;,
  4;71,72,72,71;,
  4;77,73,73,77;,
  3;62,62,62;,
  3;62,62,62;,
  3;62,62,62;,
  3;62,62,62;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  4;63,69,69,63;,
  4;67,73,73,67;,
  4;62,62,62,62;,
  4;62,62,62,62;,
  4;68,68,68,68;,
  4;68,68,68,68;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;78,78,78,78;,
  4;81,81,81,81;,
  4;80,80,80,80;,
  4;79,79,79,79;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;85,86,86,85;,
  4;86,87,87,86;,
  4;87,88,88,87;,
  4;88,89,89,88;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  3;90,90,90;,
  3;90,90,90;,
  3;90,90,90;,
  3;90,90,90;,
  4;91,92,92,91;,
  4;92,93,93,92;,
  4;93,94,94,93;,
  4;94,95,95,94;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  3;90,90,90;,
  3;90,90,90;,
  3;90,90,90;,
  3;90,90,90;,
  4;85,91,91,85;,
  4;89,95,95,89;,
  4;84,84,84,84;,
  4;84,84,84,84;,
  4;90,90,90,90;,
  4;90,90,90,90;;
 }
 MeshTextureCoords {
  295;
  0.500020;0.649750;,
  0.653990;0.649720;,
  0.653990;0.690030;,
  0.500030;0.690060;,
  0.653830;-0.118290;,
  0.499870;-0.118260;,
  0.499870;-0.086920;,
  0.653830;-0.086950;,
  0.653960;0.526320;,
  0.653990;0.668410;,
  0.890920;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.819110;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.518880;,
  0.500020;0.661120;,
  0.346070;0.690090;,
  0.346060;0.649780;,
  0.345900;-0.086890;,
  0.345900;-0.118230;,
  0.346060;0.668470;,
  0.346040;0.526380;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.175170;1.000000;,
  0.102860;0.000000;,
  0.653430;0.682060;,
  0.744230;0.682040;,
  0.744230;0.685770;,
  0.653430;0.685790;,
  0.744070;-0.100490;,
  0.653270;-0.100470;,
  0.653270;-0.096740;,
  0.744070;-0.096760;,
  0.744090;-0.032710;,
  0.744090;-0.028760;,
  0.744220;0.631480;,
  0.744220;0.627140;,
  0.099630;1.000000;,
  0.099370;0.000000;,
  0.928850;0.000000;,
  0.929580;1.000000;,
  0.653290;-0.034750;,
  0.653420;0.622640;,
  0.653290;-0.030810;,
  0.653420;0.626970;,
  0.744230;0.659720;,
  0.744230;0.662340;,
  0.974230;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.966470;1.000000;,
  0.653430;0.665090;,
  0.000000;0.033530;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.036600;,
  1.000000;0.064940;,
  0.000000;0.070420;,
  0.744080;-0.085770;,
  0.744080;-0.078610;,
  0.054390;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.049270;0.000000;,
  0.653280;-0.089350;,
  0.653280;-0.082220;,
  0.346620;0.685850;,
  0.255830;0.685870;,
  0.255830;0.682140;,
  0.346620;0.682120;,
  0.255670;-0.096660;,
  0.346460;-0.096680;,
  0.346460;-0.100410;,
  0.255670;-0.100390;,
  0.255820;0.627240;,
  0.255820;0.631570;,
  0.255680;-0.028670;,
  0.255680;-0.032610;,
  0.929580;1.000000;,
  0.928850;0.000000;,
  0.099370;0.000000;,
  0.099630;1.000000;,
  0.346610;0.622700;,
  0.346480;-0.034690;,
  0.346610;0.627030;,
  0.346480;-0.030750;,
  0.029000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.036600;1.000000;,
  0.064940;1.000000;,
  0.065670;0.000000;,
  0.966470;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.974230;0.000000;,
  0.346620;0.665140;,
  0.255820;0.662440;,
  1.000000;0.036600;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.033530;,
  0.000000;0.070420;,
  1.000000;0.064940;,
  0.255670;-0.078510;,
  0.255670;-0.085680;,
  0.049270;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.054390;1.000000;,
  0.346470;-0.089290;,
  0.000000;0.945610;,
  1.000000;1.000000;,
  1.000000;0.940490;,
  1.000000;0.897880;,
  0.000000;0.900370;,
  0.848730;-0.189780;,
  0.850840;-0.528410;,
  0.924440;-0.528980;,
  0.922320;-0.190350;,
  0.442980;-0.196160;,
  0.445100;-0.534800;,
  0.365980;-0.534330;,
  0.363870;-0.195690;,
  0.769110;-0.530950;,
  0.766890;-0.192320;,
  1.000000;0.167680;,
  0.000000;0.150480;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.763050;-0.190740;,
  0.765270;-0.529380;,
  1.000000;0.150700;,
  0.000000;0.167900;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.619270;-0.532790;,
  0.614130;-0.194190;,
  1.000000;0.489730;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.498260;,
  0.602040;-0.192680;,
  0.607180;-0.531280;,
  1.000000;0.504470;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.495940;,
  0.913660;1.197990;,
  0.911540;1.536630;,
  0.837950;1.537200;,
  0.840060;1.198560;,
  0.355200;1.192650;,
  0.353090;1.531280;,
  0.432200;1.530810;,
  0.434320;1.192180;,
  0.758220;1.196030;,
  0.756210;1.534660;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.150480;,
  1.000000;0.167680;,
  0.752370;1.536230;,
  0.754380;1.197600;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.167900;,
  1.000000;0.150700;,
  0.605470;1.194150;,
  0.606370;1.532820;,
  0.000000;0.498260;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.489730;,
  0.594280;1.534330;,
  0.593380;1.195660;,
  0.000000;0.495940;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.504470;,
  0.536230;0.456200;,
  0.638720;0.418360;,
  0.638720;0.443120;,
  0.536230;0.480960;,
  0.649850;0.211740;,
  0.649850;0.236500;,
  0.648860;0.122010;,
  0.648860;0.146760;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.375000;1.000000;,
  0.536180;0.211770;,
  0.536160;0.084790;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.463750;0.480970;,
  0.361250;0.443170;,
  0.361250;0.418410;,
  0.463750;0.456210;,
  0.350030;0.236560;,
  0.350030;0.211800;,
  0.350980;0.146820;,
  0.350980;0.122070;,
  0.463670;0.109560;,
  0.463670;0.084800;,
  0.463700;0.211780;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.062500;1.000000;,
  0.250000;1.000000;,
  0.187500;1.000000;,
  0.375000;1.000000;,
  0.312500;1.000000;,
  0.500000;1.000000;,
  0.437500;1.000000;,
  0.536160;0.109540;,
  0.500000;0.509900;,
  0.573360;0.509890;,
  0.573360;0.524810;,
  0.500000;0.524820;,
  0.573340;0.438330;,
  0.573340;0.453250;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.499990;0.438350;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.426650;0.524840;,
  0.426650;0.509920;,
  0.426630;0.453280;,
  0.426630;0.438360;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.500960;0.516460;,
  0.511670;0.517520;,
  0.511730;0.796630;,
  0.501010;0.795570;,
  0.516110;0.520090;,
  0.516170;0.799200;,
  0.511670;0.522650;,
  0.511730;0.801760;,
  0.500960;0.523720;,
  0.501010;0.802830;,
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.501010;0.799200;,
  0.499100;0.795570;,
  0.488390;0.796640;,
  0.488330;0.517520;,
  0.499040;0.516460;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.125000;0.000000;,
  0.483950;0.799200;,
  0.488390;0.801770;,
  0.488330;0.522660;,
  0.483890;0.520090;,
  0.499100;0.802830;,
  0.499040;0.523720;,
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.375000;0.000000;,
  0.312500;0.000000;,
  0.500000;0.000000;,
  0.437500;0.000000;,
  0.499100;0.799200;,
  0.000000;1.000000;,
  0.000000;1.000000;;
 }
}
