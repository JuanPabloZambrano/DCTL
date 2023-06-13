/* libDTColorMath
    --------------------------------------
    
      This was originally from Jed smith, but I added math functions for my DCTLS
*/



/* ##########################################################################
    Constants
    ---------------------------
*/

__CONSTANT__ float pi = 3.14159265358979323846f;
__CONSTANT__ float pi2 = 1.57079632679489661923f;
__CONSTANT__ float pi4 = 0.785398163397448309616f;



/* ##########################################################################
    Custom Structs
    ---------------------------
*/

// Custom 3x3 matrix struct float3x3
typedef struct {
  float3 x, y, z;
} float3x3;

// Struct to hold whitepoint normalization
typedef struct {
  float rec2020, p3d65, p3d60, p3dci, rec709, dcdm;
} wpnorm;


// Struct for chromaticity coordinates of color spaces
typedef struct {
  float2 red; float2 green; float2 blue; float2 white;
} Chromaticities;



/* ##########################################################################
    Color Conversion Matrices
    ---------------------------
*/


// Gamut conversion Matrices
//AP0, AP1 and P3D60 was changed to D65
#define identity_mtx make_float3x3(make_float3(1.0f, 0.0f, 0.0f), make_float3(0.0f, 1.0f, 0.0f), make_float3(0.0f, 0.0f, 1.0f))
#define matrix_ap0_to_xyz make_float3x3(make_float3(0.93863095f, -0.00574192f, 0.0175669f), make_float3(0.33809359f,0.7272139f, -0.0653075f), make_float3(0.00072312f, 0.00081844, 1.08751619f))
#define matrix_ap1_to_xyz make_float3x3(make_float3(0.65241872f, 0.12717993f, 0.17085728f), make_float3(0.26806406f, 0.67246448f, 0.05947146f), make_float3(-0.00546993f,0.0051828f, 1.08934488f))
#define matrix_p3d65_to_xyz make_float3x3(make_float3(0.486571133137f, 0.265667706728f, 0.198217317462f), make_float3(0.228974640369f, 0.691738605499f, 0.079286918044f), make_float3(-0.000000000000f, 0.045113388449, 1.043944478035f))
#define matrix_p3d60_to_xyz make_float3x3(make_float3(0.504949748516f, 0.264681518078f, 0.183015048504f), make_float3(0.237623393536f, 0.689170777798f, 0.073206014931f), make_float3(-0.000000000000f, 0.044945921749f, 0.963879227638f))
#define matrix_p3dci_to_xyz make_float3x3(make_float3(0.445170015097f, 0.277134418488f, 0.172282665968f), make_float3(0.209491759539f, 0.721595287323f, 0.068913064897f), make_float3(-0.000000000000f, 0.047060567886f, 0.907355427742f))
#define matrix_rec2020_to_xyz make_float3x3(make_float3(0.636958122253f, 0.144616916776f, 0.168880969286f), make_float3(0.262700229883f, 0.677998125553f, 0.059301715344f), make_float3(0.000000000000f, 0.028072696179, 1.060985088348f))
#define matrix_rec709_to_xyz make_float3x3(make_float3(0.412390917540f, 0.357584357262f, 0.180480793118f), make_float3(0.212639078498f, 0.715168714523f, 0.072192311287f), make_float3(0.019330825657f, 0.119194783270f, 0.950532138348f))
#define matrix_arriwg_to_xyz make_float3x3(make_float3(0.638007640839f, 0.214703813195f, 0.097744457424f), make_float3(0.291953772306f, 0.823840856552f, -0.115794822574f), make_float3(0.002798279049f, -0.067034222186, 1.153293848038f))
#define matrix_redwg_to_xyz make_float3x3(make_float3(0.735275208950f, 0.068609409034f, 0.146571278572f), make_float3(0.286694079638f, 0.842979073524f, -0.129673242569f), make_float3(-0.079680845141f, -0.347343206406, 1.516081929207f))
#define matrix_sonysgamut3 make_float3x3(make_float3(0.599083900452f, 0.248925492167f, 0.102446496487f), make_float3(0.215075820684f, 0.885068416595f, -0.100144319236f), make_float3(-0.032065849751f, -0.027658388019, 1.148782014847f))
#define matrix_egamut_to_xyz make_float3x3(make_float3(0.705396831036f, 0.164041340351f, 0.081017754972f), make_float3(0.280130714178f, 0.820206701756f, -0.100337378681f), make_float3(-0.103781513870f, -0.072907261550, 1.265746593475f))
#define matrix_davinciwg_to_xyz make_float3x3(make_float3(0.700622320175f, 0.148774802685f, 0.101058728993f), make_float3(0.274118483067f, 0.873631775379f, -0.147750422359f), make_float3(-0.098962903023f, -0.137895315886, 1.325916051865f))
#define matrix_blackmagicwg_to_xyz make_float3x3(make_float3(0.606538414955f, 0.220412746072f, 0.123504832387f), make_float3(0.267992943525f, 0.832748472691f, -0.100741356611f), make_float3(-0.029442556202f, -0.086612440646, 1.205112814903f))
#define matrix_canoncinema_to_xyz make_float3x3(make_float3(0.71604965f, 0.12968348f, 0.1047228f),make_float3(0.26126136f, 0.86964215f, -0.1309035f),make_float3(-0.00967635f, -0.23648164f, 1.33521573f))
#define matrix_arriwg4_to_xyz make_float3x3(make_float3(0.704858320407232064f,  0.129760295170463003f, 0.115837311473976537f),make_float3(0.254524176404027025f, 0.781477732712002049f, 0.036001909116029039f),make_float3(0.0f, 0.0f, 1.089057750759878429f))

// Color Spaces Coordinates
//AP0, AP1 and P3D60 was changed to D65
__CONSTANT__ Chromaticities AP0 =
{ {0.734771f, 0.264663f}, {-0.00795f, 1.006817f}, {0.016895f, -0.062809f}, {0.3127f, 0.3129f} };
//__CONSTANT__ Chromaticities AP0 =
//{ {0.7347f, 0.2653f}, {0.0f, 1.0f}, {0.0001f, -0.077f}, {0.32168f, 0.33767f} };
__CONSTANT__ Chromaticities AP1 =
{ {0.713016f, 0.292962f}, {0.158021f, 0.835539f}, {0.129469f, 0.045065f}, {0.3127f, 0.329f} };
//__CONSTANT__ Chromaticities AP1 =
//{ {0.713f, 0.293f}, {0.165f, 0.83f}, {0.128f, 0.044f}, {0.32168f, 0.33767f} };
__CONSTANT__ Chromaticities REC709_PRI =
{ {0.64f, 0.33f}, {0.3f, 0.6f}, {0.15f, 0.06f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities REC709_PRI_2012 =
{ {0.6366613f, 0.33388708f}, {0.33235734f, 0.57712478f}, { 0.13868026f, 0.1068737f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities P3D60_PRI =
{ {0.67912f, 0.32026f}, {0.25856f, 0.69172f}, {0.14946f, 0.05973f}, {0.3127, 0.329f} };
__CONSTANT__ Chromaticities P3D65_PRI =
{ {0.68f, 0.32f}, {0.265f, 0.69f}, {0.15f, 0.06f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities P3DCI_PRI =
{ {0.68f, 0.32f}, {0.265f, 0.69f}, {0.15f, 0.06f}, {0.314f, 0.351f} };
__CONSTANT__ Chromaticities ARRI_ALEXA_WG_PRI =
{ {0.684f, 0.313f}, {0.221f, 0.848f}, {0.0861f, -0.102f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities REC2020_PRI =
{ {0.708f, 0.292f}, {0.17f, 0.797f}, {0.131f, 0.046f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities REC2020_PRI_2012 =
{ {0.69977419f,  0.30022581f}, {0.22431866f, 0.76476346f}, {0.12136517f, 0.0961114f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities ARRI_ALEXA_WG4_PRI =
{ {0.7347f,  0.2653f}, {0.1424f, 0.8576f}, {0.0991f,-0.0308f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities SGAMUT3cine_PRI =
{ {0.766f,  0.275f}, {0.225f, 0.8f}, {0.089f, -0.087f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities SGAMUT3_PRI =
{ {0.73f,  0.28f}, {0.14f, 0.855f}, {0.01f, -0.05f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities EGAMUT_PRI =
{ {0.8f,  0.3177f}, {0.18f, 0.9f}, {0.065f, -0.0805f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities DWGINT_PRI =
{ {0.8f,  0.3130f}, {0.1682f, 0.9877f}, {0.079f, -0.1155f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities SONYA6000_PRI =
{ {0.709212f,  0.27432f}, {0.219737f, 0.961661f}, {0.023252f, -0.305702f}, {0.3127f, 0.329f} };
__CONSTANT__ Chromaticities CustomRec2020_PRI =
{ {0.676376f, 0.29496f}, {0.17f, 0.797f}, {0.131f, 0.046f}, {0.3127f, 0.329f} };




/* Matrix for conversion from CIE 1931 XYZ tristumulus to CIE 2006 LMS or "Truelight LMS", described in:
    "Chromaticity Coordinates for Graphic Arts Based on CIE 2006 LMS with Even Spacing of Munsell Colours" by Richard Kirk
    https://doi.org/10.2352/issn.2169-2629.2019.27.38
*/
#define matrix_xyz_to_truelightlms make_float3x3(make_float3(0.257085f, 0.859943f, -0.031061f), make_float3(-0.394427, 1.175800f, 0.106423f), make_float3(0.064856f, -0.07625f, 0.559067f))


// Whitepoint scaling factors for Truelight LMS
// eg: (1, 1, 1) in RGB (D65 whitepoint) -> XYZ -> TLMS /= catd65 *= catd55 -> XYZ -> Yxy == D65 white
#define catd50 make_float3(1.08221f, 0.883260f, 0.447579f)
#define catd55 make_float3(1.07730f, 0.896467f, 0.500927f)
#define catd60 make_float3(1.07344f, 0.907523f, 0.549381f)
#define catd65 make_float3(1.07046f, 0.916817f, 0.594251f)
#define catd75 make_float3(1.06600f, 0.931715f, 0.670839f)
#define catd93 make_float3(1.06098f, 0.950462f, 0.776150f)








/* ##########################################################################
    Functions
    ---------------------------------
*/
__DEVICE__ Chromaticities make_chromaticities( float2 A, float2 B, float2 C, float2 D) {
  Chromaticities E;
  E.red = A; E.green = B; E.blue = C; E.white = D;
  return E;
}


__DEVICE__ float _radians(float d) {return d * (pi / 180.0f);}
__DEVICE__ float _degrees(float r) {return r * (180.0f / pi);}

__DEVICE__ float3 sqrtf3(float3 a) {
  // For each component of float3 a, compute the square-root
  return make_float3(_sqrtf(a.x), _sqrtf(a.y), _sqrtf(a.z));
}

__DEVICE__ float3 clampf3(float3 a, float mn, float mx) { 
  // Clamp each component of float3 a to be between float mn and float mx
  return make_float3(
    _fminf(_fmaxf(a.x, mn), mx),
    _fminf(_fmaxf(a.y, mn), mx),
    _fminf(_fmaxf(a.z, mn), mx));
}

__DEVICE__ float3 maxf3(float b, float3 a) {
  // For each component of float3 a, return max of component and float b
  return make_float3(_fmaxf(a.x, b), _fmaxf(a.y, b), _fmaxf(a.z, b));
}

__DEVICE__ float3 minf3(float b, float3 a) { 
  // For each component of float3 a, return min of component and float b
  return make_float3(_fminf(a.x, b), _fminf(a.y, b), _fminf(a.z, b));
}


__DEVICE__ float _sign(float x) {
  // Return the sign of float x
  if (x > 0.0f) return 1.0f; 
  if (x < 0.0f) return -1.0f; 
  return 0.0f; 
}

__DEVICE__ float3 powf3(float3 a, float b) { 
  // Raise each component of float3 a to power b
  return make_float3(_powf(a.x, b), _powf(a.y, b), _powf(a.z, b));
}

__DEVICE__ float spowf(float a, float b) {
  // Compute "safe" power of float a, reflected over the origin
  
    a=_sign(a)*_powf(_fabs(a), b);
    return a;
    
}


__DEVICE__ float3 spowf3(float3 a, float b) {
  // Compute "safe" power of float3 a, reflected over the origin
  return make_float3(
    _sign(a.x)*_powf(_fabs(a.x), b), 
    _sign(a.y)*_powf(_fabs(a.y), b), 
    _sign(a.z)*_powf(_fabs(a.z), b));
}

__DEVICE__ float _mixf(float a, float b, float f) {
  // Linear interpolation between float a and float b by factor f. Extrapolates.
  return a * (1.0f - f) + b * f;
}

__DEVICE__ float3 _mixf3(float3 a, float3 b, float f) {
  // Linear interpolation between float3 a and float3 b by factor f. Extrapolates.
  return make_float3(_mixf(a.x, b.x, f), _mixf(a.y, b.y, f), _mixf(a.z, b.z, f));
}

__DEVICE__ float _smoothstepf(float e0, float e1, float x) {
  // return smoothstep of float x between e0 and e1
  x = _clampf((x - e0) / (e1 - e0), 0.0f, 1.0f);
  return x * x * (3.0f - 2.0f * x);
}

__DEVICE__ float3 _smoothstepf3(float e0, float e1, float3 x) {
  // return smoothstep of float3 x between e0 and e1
  return make_float3(_smoothstepf(e0, e1, x.x), _smoothstepf(e0, e1, x.y), _smoothstepf(e0, e1, x.z));
}



// Helper function to create a float3x3
__DEVICE__ float3x3 make_float3x3(float3 a, float3 b, float3 c) {
  float3x3 d;
  d.x = a, d.y = b, d.z = c;
  return d;
}


// Multiply float3 vector a and 3x3 matrix m
__DEVICE__ float3 mult_f3_f33(float3 a, float3x3 m) {
  return make_float3(
    m.x.x * a.x + m.x.y * a.y + m.x.z * a.z,
    m.y.x * a.x + m.y.y * a.y + m.y.z * a.z,
    m.z.x * a.x + m.z.y * a.y + m.z.z * a.z);
}



// Calculate inverse of 3x3 matrix: https://stackoverflow.com/questions/983999/simple-3x3-matrix-inverse-code-c
__DEVICE__ float3x3 inv_f33(float3x3 m) {
  float d = m.x.x * (m.y.y * m.z.z - m.z.y * m.y.z) -
            m.x.y * (m.y.x * m.z.z - m.y.z * m.z.x) +
            m.x.z * (m.y.x * m.z.y - m.y.y * m.z.x);
  float id = 1.0f / d;
  float3x3 c = identity_mtx;
  c.x.x = id * (m.y.y * m.z.z - m.z.y * m.y.z);
  c.x.y = id * (m.x.z * m.z.y - m.x.y * m.z.z);
  c.x.z = id * (m.x.y * m.y.z - m.x.z * m.y.y);
  c.y.x = id * (m.y.z * m.z.x - m.y.x * m.z.z);
  c.y.y = id * (m.x.x * m.z.z - m.x.z * m.z.x);
  c.y.z = id * (m.y.x * m.x.z - m.x.x * m.y.z);
  c.z.x = id * (m.y.x * m.z.y - m.z.x * m.y.y);
  c.z.y = id * (m.z.x * m.x.y - m.x.x * m.z.y);
  c.z.z = id * (m.x.x * m.y.y - m.y.x * m.x.y);
  return c;
}

__DEVICE__ float3x3 transpose_f33( float3x3 A) {

float3x3 B = A;
A.x=make_float3(B.x.x,B.y.x,B.z.x);
A.y=make_float3(B.x.y,B.y.y,B.z.y);
A.z=make_float3(B.x.z,B.y.z,B.z.z);

return A;

}

__DEVICE__ float3x3 mult_f33_f33( float3x3 A, float3x3 B) {
A = transpose_f33(A);
float3x3 C = B;
B.x= mult_f3_f33(A.x,C);
B.y= mult_f3_f33(A.y,C);
B.z= mult_f3_f33(A.z,C);
B = transpose_f33(B);

return B;

}



__DEVICE__ float3x3 RGBtoXYZ( Chromaticities N) {

float3x3 M = make_float3x3(make_float3(N.red.x/N.red.y,N.green.x/N.green.y,N.blue.x/N.blue.y),
make_float3(1.0,1.0,1.0), make_float3((1-N.red.x-N.red.y)/N.red.y,(1-N.green.x-N.green.y)/N.green.y,(1-N.blue.x-N.blue.y)/N.blue.y));
float3 wh = make_float3(N.white.x/N.white.y,1,(1-N.white.x-N.white.y)/N.white.y);
wh = mult_f3_f33(wh, inv_f33(M));
M = make_float3x3(make_float3(M.x.x*wh.x , M.x.y*wh.y , M.x.z*wh.z),
make_float3(M.y.x*wh.x , M.y.y*wh.y ,M.y.z*wh.z), make_float3(M.z.x*wh.x,M.z.y*wh.y,M.z.z*wh.z));
return M;

}

__DEVICE__ float3x3 XYZtoRGB( Chromaticities N) {
float3x3 M = inv_f33(RGBtoXYZ(N));
return M;
}



__DEVICE__ Chromaticities Insetcalc(Chromaticities N,float cpr,float cpg,float cpb){

  float3 scale = make_float3(1/_powf(1-cpr,2),1/_powf(1-cpg,2),1/_powf(1-cpb,2));

  Chromaticities adj = make_chromaticities(make_float2((N.red.x-N.white.x)*scale.x+N.white.x,(N.red.y-N.white.y)*scale.x+N.white.y),
    make_float2((N.green.x-N.white.x)*scale.y+N.white.x,(N.green.y-N.white.y)*scale.y+N.white.y),
    make_float2((N.blue.x-N.white.x)*scale.z+N.white.x,(N.blue.y-N.white.y)*scale.z+N.white.y),make_float2(N.white.x,N.white.y));

  return adj;
    
}



__DEVICE__ float3x3 Insetcalcmatrix(Chromaticities N,float cpr,float cpg,float cpb){

    float3 scale = make_float3(1/_powf(1-cpr,2),1/_powf(1-cpg,2),1/_powf(1-cpb,2));

    Chromaticities adj = make_chromaticities(make_float2((N.red.x-N.white.x)*scale.x+N.white.x,(N.red.y-N.white.y)*scale.x+N.white.y),
        make_float2((N.green.x-N.white.x)*scale.y+N.white.x,(N.green.y-N.white.y)*scale.y+N.white.y),
        make_float2((N.blue.x-N.white.x)*scale.z+N.white.x,(N.blue.y-N.white.y)*scale.z+N.white.y),make_float2(N.white.x,N.white.y));

    float3x3 In2XYZ = RGBtoXYZ(N);
    float3x3 XYZ2Adj = XYZtoRGB(adj);

    float3x3 RGBtoAdj = mult_f33_f33(In2XYZ,XYZ2Adj);

    return RGBtoAdj;
    
}

__DEVICE__ Chromaticities RotatePrimaries(Chromaticities N,float ored,float og,float ob)
{

  ored = _radians(ored);
  og =_radians(og);
  ob = _radians(ob);
  float2 Cred= make_float2(N.red.x-N.white.x,N.red.y-N.white.y);
  float2 Cgreen = make_float2(N.green.x-N.white.x,N.green.y-N.white.y);
  float2 Cblue = make_float2(N.blue.x-N.white.x,N.blue.y-N.white.y);
  float3 l = make_float3(_hypotf(Cred.x,Cred.y),_hypotf(Cgreen.x,Cgreen.y),_hypotf(Cblue.x,Cblue.y));
  float3 hue = make_float3( _atan2f(Cred.y,Cred.x), _atan2f(Cgreen.y,Cgreen.x), _atan2f(Cblue.y,Cblue.x));
  Chromaticities Nout = make_chromaticities(make_float2(l.x*_cosf(hue.x+ored),l.x*_sinf(hue.x+ored)),make_float2(l.x*_cosf(hue.y+og),l.x*_sinf(hue.y+og)),make_float2(l.x*_cosf(hue.z+ob),l.x*_sinf(hue.z+ob)),N.white);
  Nout.red.x= Nout.red.x+N.white.x;
  Nout.red.y=Nout.red.y+N.white.y;
  Nout.green.x=Nout.green.x+N.white.x;
  Nout.green.y=Nout.green.y+N.white.y;
  Nout.blue.x=Nout.blue.x+N.white.x;
  Nout.blue.y=Nout.blue.y+N.white.y;

  return Nout;

}


__DEVICE__ Chromaticities Primaries2Moment(Chromaticities N){

float2 momr = make_float2((N.red.x-N.white.x)/N.red.y,(N.red.y-N.white.y)/N.red.y);
float2 momg = make_float2((N.green.x-N.white.x)/N.green.y,(N.green.y-N.white.y)/N.green.y);
float2 momb = make_float2((N.blue.x-N.white.x)/N.blue.y,(N.blue.y-N.white.y)/N.blue.y);

Chromaticities M = make_chromaticities(momr,momg,momb,N.white);

return M;

}

__DEVICE__ Chromaticities CenterPrimaries(Chromaticities N){


N.red.x = N.red.x-N.white.x;
N.red.y = N.red.y-N.white.y;
N.green.x = N.green.x-N.white.x;
N.green.y = N.green.y-N.white.y;
N.blue.x = N.blue.x-N.white.x;
N.blue.y = N.blue.y-N.white.y;

return N;

}

__DEVICE__ Chromaticities DeCenterPrimaries(Chromaticities N){


N.red.x = N.red.x+N.white.x;
N.red.y = N.red.y+N.white.y;
N.green.x = N.green.x+N.white.x;
N.green.y = N.green.y+N.white.y;
N.blue.x = N.blue.x+N.white.x;
N.blue.y = N.blue.y+N.white.y;

return N;

}


__DEVICE__ Chromaticities ScalePrim(Chromaticities N,float rs,float gs,float bs){

    N = CenterPrimaries(N);

    N.red = make_float2(N.red.x*rs,N.red.y*rs);
    N.green = make_float2(N.green.x*gs,N.green.y*gs);
    N.blue = make_float2(N.blue.x*bs,N.blue.y*bs);

    N = DeCenterPrimaries(N);

    return N;

}

__DEVICE__ float2 cartesian_to_polar2(float2 a) {

    float2 b = a;
    b.y = _atan2f(a.y,a.x);

  return make_float2(_sqrtf(a.x*a.x+ a.y*a.y),b.y);
}


__DEVICE__ float2 polar_to_cartesian2(float2 a) {

  return make_float2(a.x * _cosf(a.y), a.x * _sinf(a.y));
}


__DEVICE__ Chromaticities RotatePrimary(Chromaticities N,float rrot,float grot,float brot){

//rotatation parameter excepted in degrees, but internally transformed to radians

    N = CenterPrimaries(N);
    N.red = cartesian_to_polar2(N.red);
    N.green = cartesian_to_polar2(N.green);
    N.blue = cartesian_to_polar2(N.blue);

    rrot = _radians(rrot);
    grot = _radians(grot);
    brot = _radians(brot);

    N.red.y = N.red.y + rrot;
    N.green.y = N.green.y + grot;
    N.blue.y = N.blue.y + brot;

    N.red = polar_to_cartesian2(N.red);
    N.green = polar_to_cartesian2(N.green);
    N.blue = polar_to_cartesian2(N.blue);

    N = DeCenterPrimaries(N);

    return N;

}

__DEVICE__ float2 Line_equation (float2 a,float2 b){

    float m = (b.y-a.y)/(b.x - a.x);
    float c = a.y - m*a.x;

    float2 line = make_float2(m,c);

    return line;

}



__DEVICE__ Chromaticities PrimariesLines(Chromaticities N){

    Chromaticities M = N;

    N.red = Line_equation(M.red,M.white);
    N.green = Line_equation(M.green,M.white);
    N.blue = Line_equation(M.blue,M.white);

    return N;

}

__DEVICE__ Chromaticities Polygon(Chromaticities N){


    Chromaticities M = N;

    N.red = Line_equation(M.red,M.green);
    N.green = Line_equation(M.red,M.blue);
    N.blue = Line_equation(M.blue,M.green);

    return N;


}


__DEVICE__ float2 intersection(float2 a,float2 b){

//Calculate the xy coordinates where 2 lines intersect
    
    float2 c = a;
    float2 d = b;

    a.x = (d.y-c.y)/(c.x-d.x);
    a.y = a.x*c.x+c.y;

    return a;

}

__DEVICE__ Chromaticities InsetPrimaries(Chromaticities N,float cpr,float cpg,float cpb,float ored,float og,float ob){

    Chromaticities M = N;
    N = ScalePrim(N,2.0,2.0,2.0);

    N = RotatePrimary(N,ored,og,ob);

    M= Polygon(M);
  
   float2 redline = ored>0? M.red:M.green;
   float2 greenline = og>0? M.blue:M.red;
   float2 blueline = ob>0? M.green:M.blue;

//this are the lines from wp to scaled, needed to find intersection with polygon
    N = PrimariesLines(N);


N.red = intersection(N.red,redline);
N.green = intersection(N.green,greenline);
N.blue = intersection(N.blue,blueline);

cpr = 1-cpr;
cpg = 1-cpg;
cpb = 1-cpb;

N = ScalePrim(N,cpr,cpg,cpb);

   return N;

}


__DEVICE__ Chromaticities MomentBoundary(Chromaticities N){
  
float2 momr = make_float2((N.red.x-N.white.x)/N.red.y,(N.red.y-N.white.y)/N.red.y);
float2 momg = make_float2((N.green.x-N.white.x)/N.green.y,(N.green.y-N.white.y)/N.green.y);
float2 momb = make_float2((N.blue.x-N.white.x)/N.blue.y,(N.blue.y-N.white.y)/N.blue.y);

float r2gslope = (momg.y-momr.y)/(momg.x-momr.x);
float r2gint = (momr.y-r2gslope*momr.x);
float r2bslope = (momb.y-momr.y)/(momb.x-momr.x);
float r2bint = (momr.y-r2bslope*momr.x);
float g2bslope = (momb.y-momg.y)/(momb.x-momg.x);
float g2bint = (momb.y-g2bslope*momb.x);

Chromaticities M = make_chromaticities(make_float2(r2gslope,r2gint),make_float2(r2bslope,r2bint),make_float2(g2bslope,g2bint),N.white);

  return M;
}



__DEVICE__ float3x3 RGBtoRGB(Chromaticities N,Chromaticities M){

  float3x3 In2XYZ = RGBtoXYZ(N);
  float3x3 XYZ2Out = XYZtoRGB(M);

  float3x3 rgbtorgb = mult_f33_f33(In2XYZ,XYZ2Out);

  return rgbtorgb;

}

__DEVICE__ float3x3 InsetMatrix(Chromaticities N,float cpr,float cpg,float cpb,float oRed,float og,float ob){

  Chromaticities In = Insetcalc(N,cpr,cpg,cpb);
  In=RotatePrimaries(In,oRed,og,ob);
  float3x3 Matrix = RGBtoRGB(N,In);

  return Matrix;


}

__DEVICE__ float3 XYZ_2_xyY( float3 XYZ) {
float3 xyY;
//float divisor = (_fabs(XYZ.x) + _fabs(XYZ.y) + _fabs(XYZ.z));
float divisor = ((XYZ.x) + XYZ.y + XYZ.z);
//if (divisor == 0.0f) divisor = 1e-10f;
xyY.x =divisor == 0.0f? 0.0f:(XYZ.x) / divisor;
xyY.y = divisor == 0.0f? 0.0f:(XYZ.y)/ divisor;
//xyY.z = _fabs(XYZ.y);
xyY.z = XYZ.y;
return xyY;
}

__DEVICE__ float3 xyY_2_XYZ( float3 xyY) {
float3 XYZ;
//XYZ.x = xyY.x * xyY.z / _fmaxf( xyY.y, 1e-10f);
XYZ.x = xyY.y==0.0f? 0.0f: xyY.x * xyY.z / xyY.y;
XYZ.y = xyY.z;
//XYZ.z = (1.0f - xyY.x - xyY.y) * xyY.z / _fmaxf( xyY.y, 1e-10f);
XYZ.z = xyY.y==0.0f? 0.0f: (1.0f - xyY.x - xyY.y) * xyY.z /( xyY.y);
return XYZ;
}


__DEVICE__ float3 RGB2HCL(Chromaticities Ingamut,float3 rgb){

Chromaticities RGBBoundaries = MomentBoundary(Ingamut);

float2 Gxy = make_float2(((-RGBBoundaries.blue.y + RGBBoundaries.red.y)/(-RGBBoundaries.red.x + RGBBoundaries.blue.x)),
  ((RGBBoundaries.blue.x*RGBBoundaries.red.y-RGBBoundaries.blue.y*RGBBoundaries.red.x)/(-RGBBoundaries.red.x+RGBBoundaries.blue.x)));
float2 Rxy = make_float2(((-RGBBoundaries.red.y + RGBBoundaries.green.y)/(-RGBBoundaries.green.x + RGBBoundaries.red.x)),
  ((RGBBoundaries.red.x*RGBBoundaries.green.y-RGBBoundaries.red.y*RGBBoundaries.green.x)/(-RGBBoundaries.green.x+RGBBoundaries.red.x)));
float2 Bxy = make_float2(((-RGBBoundaries.blue.y + RGBBoundaries.green.y)/(-RGBBoundaries.green.x + RGBBoundaries.blue.x)),
  ((RGBBoundaries.blue.x*RGBBoundaries.green.y-RGBBoundaries.blue.y*RGBBoundaries.green.x)/(-RGBBoundaries.green.x+RGBBoundaries.blue.x)));


float Gangle = _atan2f(Gxy.y,Gxy.x)<0?_atan2f(Gxy.y,Gxy.x)/(2*pi)+ 1:_atan2f(Gxy.y,Gxy.x)/(2*pi);
float Rangle = _atan2f(Rxy.y,Rxy.x)<0?_atan2f(Rxy.y,Rxy.x)/(2*pi)+ 1:_atan2f(Rxy.y,Rxy.x)/(2*pi);
float Bangle = _atan2f(Bxy.y,Bxy.x)<0?_atan2f(Bxy.y,Bxy.x)/(2*pi)+ 1:_atan2f(Bxy.y,Bxy.x)/(2*pi);

float Roffset = Rangle;


Rangle = Rangle - Roffset;
Gangle = Gangle - Roffset;
Gangle = Gangle<0?Gangle+1:Gangle;
Bangle = Bangle - Roffset;
Bangle = Bangle<0?Bangle+1:Bangle;
float2 whitepoint = Ingamut.white;
float3x3 In2XYZ = RGBtoXYZ(Ingamut);
float3x3 XYZ2In = inv_f33(In2XYZ);

float3 XYZ = mult_f3_f33(rgb,In2XYZ);


float fakeneg = _fmaxf(_fmaxf(XYZ.x,XYZ.y),XYZ.z);

XYZ = fakeneg<=0.0f?make_float3(0.0f,0.0f,0.0f):XYZ;


XYZ = XYZ_2_xyY(XYZ);
//float3 xyY = XYZ;


float3 XYZin = XYZ;


//Calculate Moment
//XYZin.y = XYZin.y == 0.0f ? 1e-10f : XYZin.y;

float cysign = _sign(XYZ.z);

XYZ.x = XYZ.y == 0.0f?0.0:(XYZin.x-whitepoint.x)/(XYZin.y);
XYZ.y =  XYZ.y == 0.0f?0.0:(XYZin.y-whitepoint.y)/(XYZin.y);
XYZ.x = cysign*XYZ.x;
XYZ.y = cysign*XYZ.y;
XYZ.z = XYZin.z;

float divxy = XYZ.x == 0.0?0.0: XYZ.y/XYZ.x;
float angle =  _atan2f(XYZ.y,XYZ.x)/(2*pi);
angle = rgb.x == rgb.y && rgb.y == rgb.z ? 0 : angle;
angle = angle<0.0f?angle + 1:angle;
angle = XYZ.x ==0.0f? 0.0f:angle;
angle = angle - Roffset;
angle = angle>1?angle - 1:angle<0?angle+1:angle;

float slope = angle > Gangle && angle <= Bangle ? RGBBoundaries.blue.x : angle > Bangle or angle <= Rangle ? RGBBoundaries.green.x : angle > Rangle && angle <= Gangle ? RGBBoundaries.red.x : 1;
float Bound = angle > Gangle && angle <= Bangle ? RGBBoundaries.blue.y : angle > Bangle or angle <= Rangle ? RGBBoundaries.green.y : angle > Rangle && angle <= Gangle ? RGBBoundaries.red.y: 1;

float interx = Bound/(divxy-slope);
float intery = interx*divxy;

float Cin = _sqrtf(XYZ.x * XYZ.x + XYZ.y * XYZ.y);
float Cnorm = _sqrtf(interx * interx + intery * intery);

Cin = Cnorm ==0?0: Cin/Cnorm;
angle = angle + Roffset;
angle = angle>1?angle - 1:angle<0?angle+1:angle;
angle = Cin == 0.0? 0.0:angle;


float3 Out = make_float3(angle,Cin,XYZ.z);

  return Out;


}



__DEVICE__ float3 HCL2RGB(Chromaticities Ingamut,float3 hcl){

Chromaticities RGBBoundaries = MomentBoundary(Ingamut);

//Find slope and intercept between each primary 

float2 Rxy = make_float2(((-RGBBoundaries.red.y + RGBBoundaries.green.y)/(-RGBBoundaries.green.x + RGBBoundaries.red.x)),
  ((RGBBoundaries.red.x*RGBBoundaries.green.y-RGBBoundaries.red.y*RGBBoundaries.green.x)/(-RGBBoundaries.green.x+RGBBoundaries.red.x)));
float2 Gxy = make_float2(((-RGBBoundaries.blue.y + RGBBoundaries.red.y)/(-RGBBoundaries.red.x + RGBBoundaries.blue.x)),
  ((RGBBoundaries.blue.x*RGBBoundaries.red.y-RGBBoundaries.blue.y*RGBBoundaries.red.x)/(-RGBBoundaries.red.x+RGBBoundaries.blue.x)));
float2 Bxy = make_float2(((-RGBBoundaries.blue.y + RGBBoundaries.green.y)/(-RGBBoundaries.green.x + RGBBoundaries.blue.x)),
  ((RGBBoundaries.blue.x*RGBBoundaries.green.y-RGBBoundaries.blue.y*RGBBoundaries.green.x)/(-RGBBoundaries.green.x+RGBBoundaries.blue.x)));

float Rangle = _atan2f(Rxy.y,Rxy.x)<0?_atan2f(Rxy.y,Rxy.x)/(2*pi)+ 1:_atan2f(Rxy.y,Rxy.x)/(2*pi);
float Gangle = _atan2f(Gxy.y,Gxy.x)<0?_atan2f(Gxy.y,Gxy.x)/(2*pi)+ 1:_atan2f(Gxy.y,Gxy.x)/(2*pi);
float Bangle = _atan2f(Bxy.y,Bxy.x)<0?_atan2f(Bxy.y,Bxy.x)/(2*pi)+ 1:_atan2f(Bxy.y,Bxy.x)/(2*pi);


float Roffset = Rangle;

Rangle = Rangle - Roffset;
Gangle = Gangle - Roffset;
Bangle = Bangle - Roffset;

Gangle = Gangle<0?Gangle+1:Gangle;
Bangle = Bangle<0?Bangle+1:Bangle;


float2 whitepoint = Ingamut.white;

float3x3 In2XYZ = RGBtoXYZ(Ingamut);
float3x3 XYZ2In = inv_f33(In2XYZ);


float angle = hcl.x;
angle = angle - Roffset;
angle = angle>1?angle - 1:angle<0?angle+1:angle;

float slope = angle > Gangle && angle <= Bangle ? RGBBoundaries.blue.x : angle > Bangle or angle <= Rangle ? RGBBoundaries.green.x : angle > Rangle && angle <= Gangle ? RGBBoundaries.red.x : 1;
float Bound = angle > Gangle && angle <= Bangle ? RGBBoundaries.blue.y : angle > Bangle or angle <= Rangle ? RGBBoundaries.green.y : angle > Rangle && angle <= Gangle ? RGBBoundaries.red.y: 1;

angle = angle + Roffset;
angle = angle>1?angle - 1:angle<0?angle+1:angle;
angle = angle*2*pi;

float chroma = hcl.y;
hcl.x = _cosf(angle);
hcl.y = _sinf(angle);

float divxy = hcl.y/hcl.x;
divxy = hcl.x == 0.0f ? 0.0f :divxy;

float interx = Bound/(divxy-slope);
float intery = interx*divxy;

angle = angle/(2*pi);
interx = angle == 0.25f? 0.0f :angle == 0.75f?0.0f:interx;
intery = angle == 0.75f? RGBBoundaries.green.y:angle==0.25f?RGBBoundaries.red.y:intery;


float Cnorm = _sqrtf(interx * interx + intery * intery);
chroma = chroma*Cnorm;


float cx = hcl.x*chroma;
float cy = hcl.y*chroma;

float sy = whitepoint.y/(1-cy);
float sx = whitepoint.x + cx*sy;

float3 xyY = make_float3(sx,sy,hcl.z);

float3 XYZ = xyY_2_XYZ(xyY);

float3 RGB = mult_f3_f33(XYZ,XYZ2In);


return RGB;


}


__DEVICE__ float3 HCL2HML(Chromaticities Ingamut,float3 hcl){



Chromaticities RGBBoundaries = MomentBoundary(Ingamut);

//Find slope and intercept between each primary 

float2 Rxy = make_float2(((-RGBBoundaries.red.y + RGBBoundaries.green.y)/(-RGBBoundaries.green.x + RGBBoundaries.red.x)),
  ((RGBBoundaries.red.x*RGBBoundaries.green.y-RGBBoundaries.red.y*RGBBoundaries.green.x)/(-RGBBoundaries.green.x+RGBBoundaries.red.x)));
float2 Gxy = make_float2(((-RGBBoundaries.blue.y + RGBBoundaries.red.y)/(-RGBBoundaries.red.x + RGBBoundaries.blue.x)),
  ((RGBBoundaries.blue.x*RGBBoundaries.red.y-RGBBoundaries.blue.y*RGBBoundaries.red.x)/(-RGBBoundaries.red.x+RGBBoundaries.blue.x)));
float2 Bxy = make_float2(((-RGBBoundaries.blue.y + RGBBoundaries.green.y)/(-RGBBoundaries.green.x + RGBBoundaries.blue.x)),
  ((RGBBoundaries.blue.x*RGBBoundaries.green.y-RGBBoundaries.blue.y*RGBBoundaries.green.x)/(-RGBBoundaries.green.x+RGBBoundaries.blue.x)));

float Rangle = _atan2f(Rxy.y,Rxy.x)<0?_atan2f(Rxy.y,Rxy.x)/(2*pi)+ 1:_atan2f(Rxy.y,Rxy.x)/(2*pi);
float Gangle = _atan2f(Gxy.y,Gxy.x)<0?_atan2f(Gxy.y,Gxy.x)/(2*pi)+ 1:_atan2f(Gxy.y,Gxy.x)/(2*pi);
float Bangle = _atan2f(Bxy.y,Bxy.x)<0?_atan2f(Bxy.y,Bxy.x)/(2*pi)+ 1:_atan2f(Bxy.y,Bxy.x)/(2*pi);


float Roffset = Rangle;

Rangle = Rangle - Roffset;
Gangle = Gangle - Roffset;
Bangle = Bangle - Roffset;

Gangle = Gangle<0?Gangle+1:Gangle;
Bangle = Bangle<0?Bangle+1:Bangle;


//float2 whitepoint = Ingamut.white;

float3x3 In2XYZ = RGBtoXYZ(Ingamut);
float3x3 XYZ2In = inv_f33(In2XYZ);


float angle = hcl.x;
angle = angle - Roffset;
angle = angle>1?angle - 1:angle<0?angle+1:angle;

float slope = angle > Gangle && angle <= Bangle ? RGBBoundaries.blue.x : angle > Bangle or angle <= Rangle ? RGBBoundaries.green.x : angle > Rangle && angle <= Gangle ? RGBBoundaries.red.x : 1;
float Bound = angle > Gangle && angle <= Bangle ? RGBBoundaries.blue.y : angle > Bangle or angle <= Rangle ? RGBBoundaries.green.y : angle > Rangle && angle <= Gangle ? RGBBoundaries.red.y: 1;

angle = angle + Roffset;
angle = angle>1?angle - 1:angle<0?angle+1:angle;
angle = angle*2*pi;


float chroma = hcl.y;
hcl.x = _cosf(angle);
hcl.y = _sinf(angle);

float divxy = hcl.y/hcl.x;
divxy = hcl.x == 0.0f ? 0.0f :divxy;

float interx = Bound/(divxy-slope);
float intery = interx*divxy;

angle = angle/(2*pi);
interx = angle == 0.25f? 0.0f :angle == 0.75f?0.0f:interx;
intery = angle == 0.75f? RGBBoundaries.green.y:angle==0.25f?RGBBoundaries.red.y:intery;

float Cnorm = _sqrtf(interx * interx + intery * intery);
chroma = chroma*Cnorm;

float3 RGB = make_float3(angle,chroma,hcl.z);
//RGB = make_float3(interx,intery,angle);

return RGB;
}





/* ##########################################################################
    Transfer Functions
    ---------------------------------
*/



__DEVICE__ float3 lin2log(float3 rgb, int tf) {
  if (tf == 0) return rgb;
  else if (tf == 1) { // ACEScct
    rgb.x = rgb.x > 0.0078125f ? (_log2f(rgb.x) + 9.72f) / 17.52f : 10.5402377416545f * rgb.x + 0.0729055341958355f;
    rgb.y = rgb.y > 0.0078125f ? (_log2f(rgb.y) + 9.72f) / 17.52f : 10.5402377416545f * rgb.y + 0.0729055341958355f;
    rgb.z = rgb.z > 0.0078125f ? (_log2f(rgb.z) + 9.72f) / 17.52f : 10.5402377416545f * rgb.z + 0.0729055341958355f;
  } else if (tf == 2) { // Arri V3 LogC EI 800
    rgb.x = rgb.x > 0.010591f ? 0.24719f * _log10f(5.555556f * rgb.x + 0.052272f) + 0.385537f : 5.367655f * rgb.x + 0.092809f;
    rgb.y = rgb.y > 0.010591f ? 0.24719f * _log10f(5.555556f * rgb.y + 0.052272f) + 0.385537f : 5.367655f * rgb.y + 0.092809f;
    rgb.z = rgb.z > 0.010591f ? 0.24719f * _log10f(5.555556f * rgb.z + 0.052272f) + 0.385537f : 5.367655f * rgb.z + 0.092809f;
  } else if (tf == 3) { // Red Log3G10
    rgb.x = rgb.x > -0.01f ? 0.224282f * _log10f(((rgb.x + 0.01f) * 155.975327f) + 1.0f) : (rgb.x + 0.01f) * 15.1927f;
    rgb.y = rgb.y > -0.01f ? 0.224282f * _log10f(((rgb.y + 0.01f) * 155.975327f) + 1.0f) : (rgb.y + 0.01f) * 15.1927f;
    rgb.z = rgb.z > -0.01f ? 0.224282f * _log10f(((rgb.z + 0.01f) * 155.975327f) + 1.0f) : (rgb.z + 0.01f) * 15.1927f;
  } else if (tf == 4) { // Sony SLog3
    rgb.x = rgb.x >= 0.01125f ? (420.0f + _log10f((rgb.x + 0.01f) / (0.18f + 0.01f)) * 261.5f) / 1023.0f : (rgb.x * (171.2102946929f - 95.0f) / 0.01125000f + 95.0f) / 1023.0f;
    rgb.y = rgb.y >= 0.01125f ? (420.0f + _log10f((rgb.y + 0.01f) / (0.18f + 0.01f)) * 261.5f) / 1023.0f : (rgb.y * (171.2102946929f - 95.0f) / 0.01125000f + 95.0f) / 1023.0f;
    rgb.z = rgb.z >= 0.01125f ? (420.0f + _log10f((rgb.z + 0.01f) / (0.18f + 0.01f)) * 261.5f) / 1023.0f : (rgb.z * (171.2102946929f - 95.0f) / 0.01125000f + 95.0f) / 1023.0f;
  } else if (tf == 5) { // Filmlight T-Log
    rgb.x = rgb.x < 0.0f ? 16.18437649f * rgb.x + 0.075f : _logf(rgb.x + 0.00570482f) * 0.09232903f + 0.55201266f;
    rgb.y = rgb.y < 0.0f ? 16.18437649f * rgb.y + 0.075f : _logf(rgb.y + 0.00570482f) * 0.09232903f + 0.55201266f;
    rgb.z = rgb.z < 0.0f ? 16.18437649f * rgb.z + 0.075f : _logf(rgb.z + 0.00570482f) * 0.09232903f + 0.55201266f;
  } else if (tf == 6) { // DaVinci Intermediate
    rgb.x = rgb.x <= 0.00262409f ? rgb.x * 10.44426855f : (_log2f(rgb.x + 0.0075f) + 7.0f) * 0.07329248f;
    rgb.y = rgb.y <= 0.00262409f ? rgb.y * 10.44426855f : (_log2f(rgb.y + 0.0075f) + 7.0f) * 0.07329248f;
    rgb.z = rgb.z <= 0.00262409f ? rgb.z * 10.44426855f : (_log2f(rgb.z + 0.0075f) + 7.0f) * 0.07329248f;
  } else if (tf == 7) { // Blackmagic Film Gen5
    rgb.x = rgb.x < 0.005f ? rgb.x * 8.283605932402494f : 0.08692876065491224f * _log2f(rgb.x + 0.005494072432257808f) + 0.5300133392291939f;
    rgb.y = rgb.y < 0.005f ? rgb.y * 8.283605932402494f : 0.08692876065491224f * _log2f(rgb.y + 0.005494072432257808f) + 0.5300133392291939f;
    rgb.z = rgb.z < 0.005f ? rgb.z * 8.283605932402494f : 0.08692876065491224f * _log2f(rgb.z + 0.005494072432257808f) + 0.5300133392291939f;
  }
  else if (tf == 8) { // CanonLog3
    rgb.x = rgb.x/0.9f ;
    rgb.y = rgb.y/0.9f ;
    rgb.z = rgb.z/0.9f ;
    rgb.x = rgb.x < -0.014f ? -0.36726845f * _log10f( 1.0f - 14.98325f * rgb.x ) + 0.12783901f: -0.014f <= rgb.x && rgb.x <= 0.014f?1.9754798f * rgb.x + 0.12512219f:0.36726845f * _log10f( 14.98325f * rgb.x + 1.0f ) + 0.12240537f;
    rgb.y = rgb.y < -0.014f ? -0.36726845f * _log10f( 1.0f - 14.98325f * rgb.y ) + 0.12783901f: -0.014f <= rgb.y && rgb.y <= 0.014f?1.9754798f * rgb.y + 0.12512219f:0.36726845f * _log10f( 14.98325f * rgb.y + 1.0f ) + 0.12240537f;
    rgb.z = rgb.z < -0.014f ? -0.36726845f * _log10f( 1.0f - 14.98325f * rgb.z ) + 0.12783901f: -0.014f <= rgb.z && rgb.z <= 0.014f?1.9754798f * rgb.z + 0.12512219f:0.36726845f * _log10f( 14.98325f * rgb.z + 1.0f ) + 0.12240537f;
  }
  else if (tf == 9){  // Arri LogC 4
  const float a = (_powf(2.0f, 18.0f) - 16.0f) / 117.45f;
  const float b = (1023.0f - 95.0f) / 1023.0f;
  const float c = 95.0f / 1023.f;
  const float s = (7.f * _logf(2.0f) * _powf(2.0f, 7.0f - 14.0f * c / b)) / (a * b);
  const float t = (_powf(2.0f, 14.0f * ((-1.0f * c) / b) + 6.0f) - 64.0f) / a;

  
  rgb.x = rgb.x >= t ? ((_log2f(a * rgb.x + 64.f) - 6.f) / 14.f) * b + c : (rgb.x - t) / s;
  rgb.y = rgb.y >= t ? ((_log2f(a * rgb.y + 64.f) - 6.f) / 14.f) * b + c : (rgb.y - t) / s;
  rgb.z = rgb.z >= t ? ((_log2f(a * rgb.z + 64.f) - 6.f) / 14.f) * b + c : (rgb.z - t) / s;

  }
  else if (tf == 10) { // CanonLog2
    rgb.x = rgb.x/0.9f ;
    rgb.y = rgb.y/0.9f ;
    rgb.z = rgb.z/0.9f ;
    rgb.x = rgb.x<0?-0.24136077f * _log10f( 1.0f - 87.099375f * rgb.x ) + 0.092864125f : 0.24136077f * _log10f( 87.099375f * rgb.x + 1.0f ) + 0.092864125f;
    rgb.y = rgb.y<0?-0.24136077f * _log10f( 1.0f - 87.099375f * rgb.y ) + 0.092864125f : 0.24136077f * _log10f( 87.099375f * rgb.y + 1.0f ) + 0.092864125f;
    rgb.z = rgb.z<0?-0.24136077f * _log10f( 1.0f - 87.099375f * rgb.z ) + 0.092864125f : 0.24136077f * _log10f( 87.099375f * rgb.z + 1.0f ) + 0.092864125f;
  }
 else if (tf == 11){  // Flog2
    const float a = 5.555556f;
    const float b = 0.064829f;
    const float c = 0.245281f;
    const float d = 0.384316f;
    const float e = 8.799461f;
    const float f = 0.092864f;
    const float cut1 = 0.000889f; // Should be equal to ((cut2 - f) / e)
    //const float cut2 = 0.100686685370811f; // should be equal to (e * cut1 + f)

    rgb.x = rgb.x>=cut1?(c * _log10f(a * rgb.x + b) + d):(e * rgb.x + f);
    rgb.y = rgb.y>=cut1?(c * _log10f(a * rgb.y + b) + d):(e * rgb.y + f);
    rgb.z = rgb.z>=cut1?(c * _log10f(a * rgb.z + b) + d):(e * rgb.z + f);
}

  return rgb;
}

__DEVICE__ float3 log2lin(float3 rgb, int tf) {
  if (tf == 0) return rgb;
  else if (tf == 1) { // ACEScct
    rgb.x = rgb.x > 0.155251141552511f ? _powf(2.0f, rgb.x * 17.52f - 9.72f) : (rgb.x - 0.0729055341958355f) / 10.5402377416545f;
    rgb.y = rgb.y > 0.155251141552511f ? _powf(2.0f, rgb.y * 17.52f - 9.72f) : (rgb.y - 0.0729055341958355f) / 10.5402377416545f;
    rgb.z = rgb.z > 0.155251141552511f ? _powf(2.0f, rgb.z * 17.52f - 9.72f) : (rgb.z - 0.0729055341958355f) / 10.5402377416545f;
  } else if (tf == 2) { // Arri V3 LogC EI 800
    rgb.x = rgb.x > 0.149658f ? (_powf(10.0f, (rgb.x - 0.385537f) / 0.24719f) - 0.052272f) / 5.555556f : (rgb.x - 0.092809f) / 5.367655f;
    rgb.y = rgb.y > 0.149658f ? (_powf(10.0f, (rgb.y - 0.385537f) / 0.24719f) - 0.052272f) / 5.555556f : (rgb.y - 0.092809f) / 5.367655f;
    rgb.z = rgb.z > 0.149658f ? (_powf(10.0f, (rgb.z - 0.385537f) / 0.24719f) - 0.052272f) / 5.555556f : (rgb.z - 0.092809f) / 5.367655f;
  } else if (tf == 3) { // Red Log3G10
    rgb.x = rgb.x > 0.0f ? (_powf(10.0f, rgb.x / 0.224282f) - 1.0f) / 155.975327f - 0.01f : (rgb.x / 15.1927f) - 0.01f;
    rgb.y = rgb.y > 0.0f ? (_powf(10.0f, rgb.y / 0.224282f) - 1.0f) / 155.975327f - 0.01f : (rgb.y / 15.1927f) - 0.01f;
    rgb.z = rgb.z > 0.0f ? (_powf(10.0f, rgb.z / 0.224282f) - 1.0f) / 155.975327f - 0.01f : (rgb.z / 15.1927f) - 0.01f;
  } else if (tf == 4) { // Sony SLog3
    rgb.x = rgb.x >= 171.2102946929f / 1023.0f ? _powf(10.0f, ((rgb.x * 1023.0f - 420.0f) / 261.5f)) * (0.18f + 0.01f) - 0.01f : (rgb.x * 1023.0f - 95.0f) * 0.01125000f / (171.2102946929f - 95.0f);
    rgb.y = rgb.y >= 171.2102946929f / 1023.0f ? _powf(10.0f, ((rgb.y * 1023.0f - 420.0f) / 261.5f)) * (0.18f + 0.01f) - 0.01f : (rgb.y * 1023.0f - 95.0f) * 0.01125000f / (171.2102946929f - 95.0f);
    rgb.z = rgb.z >= 171.2102946929f / 1023.0f ? _powf(10.0f, ((rgb.z * 1023.0f - 420.0f) / 261.5f)) * (0.18f + 0.01f) - 0.01f : (rgb.z * 1023.0f - 95.0f) * 0.01125000f / (171.2102946929f - 95.0f);
  } else if (tf == 5) { // Filmlight T-Log
    rgb.x = rgb.x < 0.075f ? (rgb.x - 0.075f) / 16.18437649f : _expf((rgb.x - 0.55201266f) / 0.09232903f) - 0.00570482f;
    rgb.y = rgb.y < 0.075f ? (rgb.y - 0.075f) / 16.18437649f : _expf((rgb.y - 0.55201266f) / 0.09232903f) - 0.00570482f;
    rgb.z = rgb.z < 0.075f ? (rgb.z - 0.075f) / 16.18437649f : _expf((rgb.z - 0.55201266f) / 0.09232903f) - 0.00570482f;
  } else if (tf == 6) { // DaVinci Intermediate
    rgb.x = rgb.x <= 0.02740668f ? rgb.x / 10.44426855f : _powf(2.0f, (rgb.x / 0.07329248f) - 7.0f) - 0.0075f;
    rgb.y = rgb.y <= 0.02740668f ? rgb.y / 10.44426855f : _powf(2.0f, (rgb.y / 0.07329248f) - 7.0f) - 0.0075f;
    rgb.z = rgb.z <= 0.02740668f ? rgb.z / 10.44426855f : _powf(2.0f, (rgb.z / 0.07329248f) - 7.0f) - 0.0075f;
  } else if (tf == 7) { // Blackmagic Film Gen5
    rgb.x = rgb.x < 0.13388378f ? (rgb.x - 0.09246575342465753f) / 8.283605932402494f : _expf((rgb.x - 0.5300133392291939f) / 0.08692876065491224f) - 0.005494072432257808f;
    rgb.y = rgb.y < 0.13388378f ? (rgb.y - 0.09246575342465753f) / 8.283605932402494f : _expf((rgb.y - 0.5300133392291939f) / 0.08692876065491224f) - 0.005494072432257808f;
    rgb.z = rgb.z < 0.13388378f ? (rgb.z - 0.09246575342465753f) / 8.283605932402494f : _expf((rgb.z - 0.5300133392291939f) / 0.08692876065491224f) - 0.005494072432257808f;
  }
  else if (tf == 8) { // CanonLog3
    rgb.x = rgb.x < 0.097465473f ?-( _powf( 10.0f, ( 0.12783901f - rgb.x ) / 0.36726845f ) - 1.0f ) / 14.98325f : 0.097465473f <= rgb.x && rgb.x <= 0.15277891f?(rgb.x - 0.12512219f) / 1.9754798f:( _powf( 10.0f, ( rgb.x - 0.12240537f ) / 0.36726845f ) - 1.0f ) / 14.98325f;
    rgb.y = rgb.y < 0.097465473f ?-( _powf( 10.0f, ( 0.12783901f - rgb.y ) / 0.36726845f ) - 1.0f ) / 14.98325f : 0.097465473f <= rgb.y && rgb.y <= 0.15277891f?(rgb.y - 0.12512219f) / 1.9754798f:( _powf( 10.0f, ( rgb.y - 0.12240537f ) / 0.36726845f ) - 1.0f ) / 14.98325f;
    rgb.z = rgb.z < 0.097465473f ?-( _powf( 10.0f, ( 0.12783901f - rgb.z ) / 0.36726845f ) - 1.0f ) / 14.98325f : 0.097465473f <= rgb.z && rgb.z <= 0.15277891f?(rgb.z - 0.12512219f) / 1.9754798f:( _powf( 10.0f, ( rgb.z - 0.12240537f ) / 0.36726845f ) - 1.0f ) / 14.98325f;
    rgb.x = rgb.x*0.9f;
    rgb.y = rgb.y*0.9f;
    rgb.z = rgb.z*0.9f;
  }

  else if (tf == 9){  // Arri LogC 4
  const float a = (_powf(2.0f, 18.0f) - 16.0f) / 117.45f;
  const float b = (1023.0f - 95.0f) / 1023.0f;
  const float c = 95.0f / 1023.f;
  const float s = (7.f * _logf(2.0f) * _powf(2.0f, 7.0f - 14.0f * c / b)) / (a * b);
  const float t = (_powf(2.0f, 14.0f * ((-1.0f * c) / b) + 6.0f) - 64.0f) / a;

  rgb.x = rgb.x < 0.0f ? rgb.x * s + t : (_powf(2.0f, (14.0f * (rgb.x - c) / b + 6.0f)) - 64.0f) / a;
  rgb.y = rgb.y < 0.0f ? rgb.y * s + t : (_powf(2.0f, (14.0f * (rgb.y - c) / b + 6.0f)) - 64.0f) / a;
  rgb.z = rgb.z < 0.0f ? rgb.z * s + t : (_powf(2.0f, (14.0f * (rgb.z - c) / b + 6.0f)) - 64.0f) / a;
  }
  
  else if (tf == 10){ //PureLog2 -10 stop under 0.18 and 6.5 over
    float mx = 6.5;
    float mn = -10;

    rgb.x = 0.18*_powf(2,(rgb.x*(mx-mn)+mn));
    rgb.y = 0.18*_powf(2,(rgb.y*(mx-mn)+mn));
    rgb.z = 0.18*_powf(2,(rgb.z*(mx-mn)+mn));

  }
  else if (tf == 11){  // Flog2
    const float a = 5.555556f;
    const float b = 0.064829f;
    const float c = 0.245281f;
    const float d = 0.384316f;
    const float e = 8.799461f;
    const float f = 0.092864f;
    //const float cut1 = 0.000889f; // Should be equal to ((cut2 - f) / e)
    const float cut2 = 0.100686685370811f; // should be equal to (e * cut1 + f)

    rgb.x = rgb.x>=cut2?((_exp10f((rgb.x - d) / c) - b) / a):((rgb.x - f) / e);
    rgb.y = rgb.y>=cut2?((_exp10f((rgb.y - d) / c) - b) / a):((rgb.y - f) / e);
    rgb.z = rgb.z>=cut2?((_exp10f((rgb.z - d) / c) - b) / a):((rgb.z - f) / e);
}
  else if (tf == 12){  // BMFilm
    const float p1 = 0.06031746;
    const float p2 = 0.00712130;
    const float p3 = 0.20123443;
    const float p4 = 0.72309772;
    const float p5 = 0.42929868;
    const float p6 = 0.02476426;
    const float p7 = 0.76154283;


    rgb.x = rgb.x<=p1?rgb.x*p3-p2:(spowf(10,(rgb.x-p4)/p5)-p6)/p7;
    rgb.y = rgb.y<=p1?rgb.y*p3-p2:(spowf(10,(rgb.y-p4)/p5)-p6)/p7;
    rgb.z = rgb.z<=p1?rgb.z*p3-p2:(spowf(10,(rgb.z-p4)/p5)-p6)/p7;
}
  return rgb;
}



//LogZ

  __DEVICE__ float log2linz(float in,float mn,float mx) {
    
    float a = _powf(2,mn);
    float m2 = _log2f(mx/a+1)+mn;

    float out = in<0?in/(1/(_logf(2)*(m2-mn)*a)):_powf(2,in*(m2-mn)+mn)-a;
    
    return out;
}

__DEVICE__ float lin2logz(float in,float mn,float mx) {
    
    float a = _powf(2,mn);
    float m2 = _log2f(mx/a+1)+mn;

    float out = in<0?in/(_logf(2)*(m2-mn)*a):(_log2f(in+a)-mn)/(m2-mn);
    
    return out;
}


__DEVICE__ float ShoulderSigmoid(float in,float sp,float Pslength,float slx){
  
  float px =  0.5;
  float py =  0.5;
  float tlx = 0.0;
  float tly = 0.0;
  float sly = 1.0;

  float stx = Pslength/_sqrtf(2) + px;
  float sty = stx;

  float ss = spowf(((spowf((slx-stx)/(sly-sty),sp)-1)*spowf(slx-stx,-sp)),-1/sp);

  float sx = (in-stx)/ss;
  float fs = sx/spowf(1+spowf(sx,sp),1/sp);

  float fss = ss*fs + sty;

  float Out = in > stx ? fss : in;

  return Out;

}




__DEVICE__ float3 desaturate(float3 in,Chromaticities N,float sat)
{
  
  float3x3 mat = RGBtoXYZ(N);
  float lumr = mat.y.x;
  float lumg = mat.y.y;
  float lumb = mat.y.z;

  float Y =  in.x*(lumr)+in.y*(lumg)+in.z*(lumb);

  in.x = (in.x-Y)*sat+Y;
  in.y = (in.y-Y)*sat+Y;
  in.z = (in.z-Y)*sat+Y;

  return in;

}


__DEVICE__ float3 eotf_hlg(float3 rgb, int inverse) {
  // Aply the HLG Forward or Inverse EOTF. Implements the full ambient surround illumination model
  // ITU-R Rec BT.2100-2 https://www.itu.int/rec/R-REC-BT.2100
  // ITU-R Rep BT.2390-8: https://www.itu.int/pub/R-REP-BT.2390
  // Perceptual Quantiser (PQ) to Hybrid Log-Gamma (HLG) Transcoding: https://www.bbc.co.uk/rd/sites/50335ff370b5c262af000004/assets/592eea8006d63e5e5200f90d/BBC_HDRTV_PQ_HLG_Transcode_v2.pdf

  const float HLG_Lw = 1000.0f;
//   const float HLG_Lb = 0.0f;
  const float HLG_Ls = 5.0f;
  const float h_a = 0.17883277f;
  const float h_b = 1.0f - 4.0f * 0.17883277f;
  const float h_c = 0.5f - h_a * _logf(4.0f * h_a);
  const float h_g = 1.2f * _powf(1.111f, _log2f(HLG_Lw / 1000.0f)) * _powf(0.98f, _log2f(_fmaxf(1e-6f, HLG_Ls) / 5.0f));
  if (inverse == 1) {
    float Yd = 0.2627f * rgb.x + 0.6780f * rgb.y + 0.0593f * rgb.z;
    // HLG Inverse OOTF
    rgb = rgb * _powf(Yd, (1.0f - h_g) / h_g);
    // HLG OETF
    rgb.x = rgb.x <= 1.0f / 12.0f ? _sqrtf(3.0f * rgb.x) : h_a * _logf(12.0f * rgb.x - h_b) + h_c;
    rgb.y = rgb.y <= 1.0f / 12.0f ? _sqrtf(3.0f * rgb.y) : h_a * _logf(12.0f * rgb.y - h_b) + h_c;
    rgb.z = rgb.z <= 1.0f / 12.0f ? _sqrtf(3.0f * rgb.z) : h_a * _logf(12.0f * rgb.z - h_b) + h_c;
  } else {
    // HLG Inverse OETF
    rgb.x = rgb.x <= 0.5f ? rgb.x * rgb.x / 3.0f : (_expf((rgb.x - h_c) / h_a) + h_b) / 12.0f;
    rgb.y = rgb.y <= 0.5f ? rgb.y * rgb.y / 3.0f : (_expf((rgb.y - h_c) / h_a) + h_b) / 12.0f;
    rgb.z = rgb.z <= 0.5f ? rgb.z * rgb.z / 3.0f : (_expf((rgb.z - h_c) / h_a) + h_b) / 12.0f;
    // HLG OOTF
    float Ys = 0.2627f * rgb.x + 0.6780f * rgb.y + 0.0593f * rgb.z;
    rgb = rgb * _powf(Ys, h_g - 1.0f);
  }
  return rgb;
}


__DEVICE__ float3 eotf_pq(float3 rgb, int inverse, int jz) {
  // Apply the ST-2084 PQ Forward or Inverse EOTF
  // Normalized such that input display linear light code value 1.0 equals 10,000 nits
  // ITU-R Rec BT.2100-2 https://www.itu.int/rec/R-REC-BT.2100
  // ITU-R Rep BT.2390-9 https://www.itu.int/pub/R-REP-BT.2390
  
  float Lp = 1.0f; // We normalize for hdr peak display luminance elsewhere.
  const float m1 = 2610.0f / 16384.0f;
  float m2 = 2523.0f / 32.0f;
  const float c1 = 107.0f / 128.0f;
  const float c2 = 2413.0f / 128.0f;
  const float c3 = 2392.0f / 128.0f;

  // Custom values for JzAzBz colorspace
  if (jz == 1) {
    m2 *= 1.7f;
    Lp = 10000.0f;
  }

  if (inverse == 1) {
    rgb /= Lp;
    rgb = spowf3(rgb, m1);
    // Prevent shitting of the bed when there are negatives, for JzAzBz conversion
    rgb.x = _sign(rgb.x) * _powf((c1 + c2 * _fabs(rgb.x)) / (1.0f + c3 * _fabs(rgb.x)), m2);
    rgb.y = _sign(rgb.y) * _powf((c1 + c2 * _fabs(rgb.y)) / (1.0f + c3 * _fabs(rgb.y)), m2);
    rgb.z = _sign(rgb.z) * _powf((c1 + c2 * _fabs(rgb.z)) / (1.0f + c3 * _fabs(rgb.z)), m2);
  } else {
    rgb = spowf3(rgb, 1.0f / m2);
    rgb.x = _sign(rgb.x) * _powf((_fabs(rgb.x) - c1) / (c2 - c3 * _fabs(rgb.x)), 1.0f / m1) * Lp;
    rgb.y = _sign(rgb.y) * _powf((_fabs(rgb.y) - c1) / (c2 - c3 * _fabs(rgb.y)), 1.0f / m1) * Lp;
    rgb.z = _sign(rgb.z) * _powf((_fabs(rgb.z) - c1) / (c2 - c3 * _fabs(rgb.z)), 1.0f / m1) * Lp;
  }
  return rgb;
}


/* ########################################################################## 
    Color Models
    ---------------------------------
*/





/* ########################################################################## 
    Utility Functions 
    --------------------
*/

__DEVICE__ float compress_parabolic(float x, float t0, float x0, float y0) {
  /* Parabolic Compression Function
      Threshold
        Only values above threshold point (t0, t0) will be compressed.
      Intersection constraint
        The coordinate (x0, y0) specifies the compression function intersection
        constraint. The input x value x0 is compressed to the output y value y0.
      https://www.desmos.com/calculator/khowxlu6xh
  */
  const float s = (y0 - t0)/_sqrtf(x0 - y0);
  const float ox = t0 - s * s / 4.0f;
  const float oy = t0 - s * sqrt(s * s / 4.0f);

  return (x < t0 ? x : s * _sqrtf(x - ox) + oy);
}

__DEVICE__ float3 gamut_compress_rgb(float3 xyz, float th, float ds, int av) {
  // Chromaticity-linear gamut compression, given threshold th and distance ds.
  // if av==1, average of rgb will be used as achromatic axis instead of max of rgb
  
  float3 rgb = mult_f3_f33(xyz, inv_f33(matrix_rec2020_to_xyz));

  float mx = _fmaxf(rgb.x, _fmaxf(rgb.y, rgb.z));
  float mn = _fminf(rgb.x, _fminf(rgb.y, rgb.z));
  float ch = mx == 0.0f ? 0.0f : (mx - mn) / mx; // classic chroma
  float ch_c = compress_parabolic(ch, th, ds, 1.0f);
  float f = ch == 0.0f ? 0.0f : ch_c / ch;

  // Gamut compress
  if (av == 0) {
    rgb = mx * (1.0f - f) + rgb * f;
  } else {
    float mean = (rgb.x + rgb.y + rgb.z) / 3.0f;
    rgb = mean * (1.0f - f) + rgb * f;
  }

  rgb = mult_f3_f33(rgb, matrix_rec2020_to_xyz);

  return rgb;
}