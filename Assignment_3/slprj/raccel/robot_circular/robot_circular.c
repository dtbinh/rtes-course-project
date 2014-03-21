#include "__cf_robot_circular.h"
#include <math.h>
#include "robot_circular.h"
#include "robot_circular_private.h"
#include "robot_circular_dt.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
const boolean_T gbl_raccel_isMultitasking = 1 ;
#else
const boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
const boolean_T gbl_raccel_tid01eq = 0 ; const int_T gbl_raccel_NumST = 1 ;
const char_T * gbl_raccel_Version = "8.5 (R2013b) 08-Aug-2013" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#endif
} const char * gblSlvrJacPatternFileName =
"slprj//raccel//robot_circular//robot_circular_Jpattern.mat" ; const int_T
gblNumRootInportBlks = 0 ; const int_T gblNumModelInputs = 0 ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
const int_T gblInportDataTypeIdx [ ] = { - 1 } ; const int_T gblInportDims [
] = { - 1 } ; const int_T gblInportComplex [ ] = { - 1 } ; const int_T
gblInportInterpoFlag [ ] = { - 1 } ; const int_T gblInportContinuous [ ] = {
- 1 } ;
#include "simstruc.h"
#include "fixedpoint.h"
B rtB ; DW rtDW ; static SimStruct model_S ; SimStruct * const rtS = &
model_S ; void rt_invd6x6_snf ( const real_T u [ 36 ] , real_T y [ 36 ] ) {
real_T u_p [ 36 ] ; int8_T p [ 6 ] ; real_T B_p [ 36 ] ; int8_T ipiv [ 6 ] ;
int32_T mmj ; int32_T jj ; int32_T jp1j ; int32_T jpiv_offset ; int32_T j ;
int32_T ix ; real_T smax ; real_T s ; int32_T pipk ; int32_T k ; boolean_T
p_p ; int32_T jBcol ; int32_T kAcol ; int32_T i ; int32_T c ; real_T y_p ;
for ( k = 0 ; k < 36 ; k ++ ) { s = u [ k ] ; y [ k ] = 0.0 ; u_p [ k ] = s ;
} for ( k = 0 ; k < 6 ; k ++ ) { ipiv [ k ] = ( int8_T ) ( 1 + k ) ; } for (
j = 0 ; j < 5 ; j ++ ) { jBcol = j ; mmj = 5 - j ; c = jBcol * 7 ; jj = 1 + c
; jp1j = jj + 1 ; c = mmj + 1 ; for ( k = 0 ; k < 36 ; k ++ ) { s = u_p [ k ]
; B_p [ k ] = s ; } pipk = 1 ; ix = jj - 1 ; s = B_p [ jj - 1 ] ; y_p =
muDoubleScalarAbs ( s ) ; smax = y_p ; for ( k = 2 ; k <= c ; k ++ ) { ix ++
; s = B_p [ ix ] ; y_p = muDoubleScalarAbs ( s ) ; s = y_p ; if ( s > smax )
{ pipk = k ; smax = s ; } } jpiv_offset = pipk - 1 ; kAcol = ( jj +
jpiv_offset ) - 1 ; if ( u_p [ kAcol ] != 0.0 ) { if ( jpiv_offset != 0 ) { c
= ( j + jpiv_offset ) + 1 ; ipiv [ j ] = ( int8_T ) c ; pipk = jBcol ; kAcol
= pipk + jpiv_offset ; for ( k = 0 ; k < 6 ; k ++ ) { s = u_p [ pipk ] ; u_p
[ pipk ] = u_p [ kAcol ] ; u_p [ kAcol ] = s ; pipk += 6 ; kAcol += 6 ; } } c
= mmj - 1 ; k = jp1j + c ; for ( i = jp1j - 1 ; i + 1 <= k ; i ++ ) { s = u_p
[ i ] ; y_p = u_p [ jj - 1 ] ; s /= y_p ; u_p [ i ] = s ; } } c = 5 - j ;
jBcol = jj + 5 ; ix = jj + 7 ; pipk = ix - 1 ; for ( kAcol = 1 ; kAcol <= c ;
kAcol ++ ) { s = u_p [ jBcol ] ; if ( s != 0.0 ) { s = - s ; ix = jp1j - 1 ;
jpiv_offset = pipk ; k = mmj + pipk ; while ( jpiv_offset + 1 <= k ) { u_p [
jpiv_offset ] += u_p [ ix ] * s ; ix ++ ; jpiv_offset ++ ; } } jBcol += 6 ;
pipk += 6 ; } } for ( k = 0 ; k < 6 ; k ++ ) { p [ k ] = ( int8_T ) ( 1 + k )
; } for ( k = 0 ; k < 5 ; k ++ ) { s = 1.0 + ( real_T ) k ; kAcol = ipiv [ (
int32_T ) s - 1 ] - 1 ; p_p = ( kAcol + 1 > ( int32_T ) s ) ; if ( p_p ) {
pipk = p [ kAcol ] ; p [ kAcol ] = p [ ( int32_T ) s - 1 ] ; p [ ( int32_T )
s - 1 ] = ( int8_T ) pipk ; } } for ( k = 0 ; k < 6 ; k ++ ) { c = p [ k ] -
1 ; y [ k + 6 * c ] = 1.0 ; for ( j = k ; j + 1 < 7 ; j ++ ) { if ( y [ 6 * c
+ j ] != 0.0 ) { for ( i = j + 1 ; i + 1 < 7 ; i ++ ) { y_p = y [ 6 * c + j ]
; s = u_p [ 6 * j + i ] ; y_p *= s ; y [ i + 6 * c ] -= y_p ; } } } } for ( k
= 0 ; k < 36 ; k ++ ) { y_p = y [ k ] ; y [ k ] = y_p ; } for ( j = 0 ; j < 6
; j ++ ) { c = j ; c *= 6 ; jBcol = c ; for ( k = 5 ; k >= 0 ; k += - 1 ) { c
= k ; c *= 6 ; kAcol = c ; c = k + jBcol ; if ( y [ c ] != 0.0 ) { c = k +
jBcol ; ix = k + jBcol ; pipk = k + kAcol ; s = y [ ix ] ; y_p = u_p [ pipk ]
; s /= y_p ; y [ c ] = s ; for ( i = 1 ; i <= k ; i ++ ) { c = ( i + jBcol )
- 1 ; ix = ( i + jBcol ) - 1 ; pipk = k + jBcol ; jpiv_offset = ( i + kAcol )
- 1 ; y [ c ] = y [ ix ] - y [ pipk ] * u_p [ jpiv_offset ] ; } } } } } void
MdlInitialize ( void ) { int32_T i ; rtDW . eeux2ti3uv = 0.0 ; for ( i = 0 ;
i < 6 ; i ++ ) { rtDW . g5wnsipe0f [ i ] = rtConstP . nrgwfwwnxs [ i ] ; } }
void MdlStart ( void ) { int32_T i ; { RTWLogSignalInfo rt_ScopeSignalInfo ;
static int_T rt_ScopeSignalWidths [ ] = { 1 } ; static int_T
rt_ScopeSignalNumDimensions [ ] = { 2 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 1 , 1 } ; static void * rt_ScopeCurrSigDims
[ ] = { ( NULL ) , ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = {
4 , 4 } ; static const char_T * rt_ScopeSignalLabels [ ] = { "" } ; static
char_T rt_ScopeSignalTitles [ ] = "" ; static int_T
rt_ScopeSignalTitleLengths [ ] = { 0 } ; static boolean_T
rt_ScopeSignalIsVarDims [ ] = { 0 } ; static int_T rt_ScopeSignalPlotStyles [
] = { 1 } ; BuiltInDTypeId dTypes [ 1 ] = { SS_DOUBLE } ; static char_T
rt_ScopeBlockName [ ] = "robot_circular/controller/Scope" ;
rt_ScopeSignalInfo . numSignals = 1 ; rt_ScopeSignalInfo . numCols =
rt_ScopeSignalWidths ; rt_ScopeSignalInfo . numDims =
rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . ltrljuz1h5 .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) ,
"ScopeData1" , 1 , 5000 , 1 , 0.1 , & rt_ScopeSignalInfo , rt_ScopeBlockName
) ; if ( rtDW . ltrljuz1h5 . LoggedData == ( NULL ) ) return ; } for ( i = 0
; i < 16 ; i ++ ) { rtDW . mwz1nxvmic [ i ] = rtConstP . iphb2gkf32 [ i ] ;
rtDW . p3s2khgxd4 [ i ] = rtConstP . iphb2gkf32 [ i ] ; } MdlInitialize ( ) ;
} void MdlOutputs ( int_T tid ) { real_T u [ 16 ] ; real_T u_p [ 16 ] ;
real_T u_e [ 36 ] ; real_T u_i [ 6 ] ; int32_T s8_iter ; int32_T i ; int32_T
i_p ; srClearBC ( rtDW . cteqqy32ya ) ; srClearBC ( rtDW . luwwjirqvw ) ;
srClearBC ( rtDW . j2qrq44urz ) ; srClearBC ( rtDW . coupmxhajs ) ; srClearBC
( rtDW . ijfh0nhbll ) ; srClearBC ( rtDW . gvrqqxide3 ) ; rtB . nonm5g4o4k =
rtDW . eeux2ti3uv ; rtB . mnknpq2c4s = rtB . nonm5g4o4k + 1.0 ; rtB .
ptf05qfh23 = rtB . mnknpq2c4s / 30.0 ; rtB . pi4pgrzjdg = 0.1 *
muDoubleScalarCos ( rtB . ptf05qfh23 ) + 0.5 ; for ( i = 0 ; i < 6 ; i ++ ) {
rtB . axilp3tz0a [ i ] = rtDW . g5wnsipe0f [ i ] ; } for ( s8_iter = 1 ;
s8_iter <= 6 ; s8_iter ++ ) { rtB . ozqlu4h43q = s8_iter ; switch ( rtB .
ozqlu4h43q ) { case 1 : rtB . nu3lqck3bd = rtB . axilp3tz0a [ 0 ] ; break ;
case 2 : rtB . nu3lqck3bd = rtB . axilp3tz0a [ 1 ] ; break ; case 3 : rtB .
nu3lqck3bd = rtB . axilp3tz0a [ 2 ] ; break ; case 4 : rtB . nu3lqck3bd = rtB
. axilp3tz0a [ 3 ] ; break ; case 5 : rtB . nu3lqck3bd = rtB . axilp3tz0a [ 4
] ; break ; default : rtB . nu3lqck3bd = rtB . axilp3tz0a [ 5 ] ; break ; }
switch ( rtB . ozqlu4h43q ) { case 1 : rtB . jyrzcculwp [ 0 ] =
1.5707963267948966 ; rtB . jyrzcculwp [ 1 ] = 0.0 ; rtB . jyrzcculwp [ 2 ] =
1.5707963267948966 ; rtB . jyrzcculwp [ 3 ] = 0.0 ; break ; case 2 : rtB .
jyrzcculwp [ 0 ] = 0.0 ; rtB . jyrzcculwp [ 1 ] = 0.404 ; rtB . jyrzcculwp [
2 ] = 1.5707963267948966 ; rtB . jyrzcculwp [ 3 ] = 0.0 ; break ; case 3 :
rtB . jyrzcculwp [ 0 ] = ( - 1.5707963267948966 ) ; rtB . jyrzcculwp [ 1 ] =
0.0 ; rtB . jyrzcculwp [ 2 ] = 0.0 ; rtB . jyrzcculwp [ 3 ] = 0.0 ; break ;
case 4 : rtB . jyrzcculwp [ 0 ] = 1.5707963267948966 ; rtB . jyrzcculwp [ 1 ]
= 0.025 ; rtB . jyrzcculwp [ 2 ] = 0.0 ; rtB . jyrzcculwp [ 3 ] = 0.405 ;
break ; case 5 : rtB . jyrzcculwp [ 0 ] = 1.5707963267948966 ; rtB .
jyrzcculwp [ 1 ] = 0.0 ; rtB . jyrzcculwp [ 2 ] = 1.5707963267948966 ; rtB .
jyrzcculwp [ 3 ] = 0.0 ; break ; default : rtB . jyrzcculwp [ 0 ] = 0.0 ; rtB
. jyrzcculwp [ 1 ] = 0.0 ; rtB . jyrzcculwp [ 2 ] = 1.5707963267948966 ; rtB
. jyrzcculwp [ 3 ] = 0.0 ; break ; } rtB . ddxq2ghec0 = muDoubleScalarCos (
rtB . nu3lqck3bd ) ; rtB . izlcklrx3a [ 0 ] = rtB . ddxq2ghec0 ; rtB .
kjnhuvsnqx = muDoubleScalarSin ( rtB . nu3lqck3bd ) ; rtB . izlcklrx3a [ 1 ]
= rtB . kjnhuvsnqx ; rtB . izlcklrx3a [ 2 ] = 0.0 ; rtB . izlcklrx3a [ 3 ] =
0.0 ; rtB . pje1rdxv2r = ( - 1.0 ) * rtB . kjnhuvsnqx ; rtB . oogxhdfgdu =
muDoubleScalarCos ( rtB . jyrzcculwp [ 0 ] ) ; rtB . izlcklrx3a [ 4 ] = rtB .
pje1rdxv2r * rtB . oogxhdfgdu ; rtB . izlcklrx3a [ 5 ] = rtB . ddxq2ghec0 *
rtB . oogxhdfgdu ; rtB . dv0esmlgu1 = muDoubleScalarSin ( rtB . jyrzcculwp [
0 ] ) ; rtB . izlcklrx3a [ 6 ] = rtB . dv0esmlgu1 ; rtB . izlcklrx3a [ 7 ] =
0.0 ; rtB . izlcklrx3a [ 8 ] = rtB . kjnhuvsnqx * rtB . dv0esmlgu1 ; rtB .
jweiksj5ax = ( - 1.0 ) * rtB . ddxq2ghec0 ; rtB . izlcklrx3a [ 9 ] = rtB .
jweiksj5ax * rtB . dv0esmlgu1 ; rtB . izlcklrx3a [ 10 ] = rtB . oogxhdfgdu ;
rtB . izlcklrx3a [ 11 ] = 0.0 ; rtB . izlcklrx3a [ 12 ] = rtB . jyrzcculwp [
1 ] * rtB . ddxq2ghec0 ; rtB . izlcklrx3a [ 13 ] = rtB . jyrzcculwp [ 1 ] *
rtB . kjnhuvsnqx ; rtB . izlcklrx3a [ 14 ] = rtB . jyrzcculwp [ 3 ] ; rtB .
izlcklrx3a [ 15 ] = 1.0 ; for ( i = 0 ; i < 16 ; i ++ ) { rtB . jzztlkosp1 [
i ] = rtDW . mwz1nxvmic [ i ] ; if ( rtB . ozqlu4h43q > 1 ) { rtB .
fr13pf2yrk [ i ] = rtB . jzztlkosp1 [ i ] ; } else { rtB . fr13pf2yrk [ i ] =
rtConstP . iphb2gkf32 [ i ] ; } u [ i ] = rtB . fr13pf2yrk [ i ] ; u_p [ i ]
= rtB . izlcklrx3a [ i ] ; } for ( i = 0 ; i < 4 ; i ++ ) { for ( i_p = 0 ;
i_p < 4 ; i_p ++ ) { rtB . ltq0doaugx [ i + ( i_p << 2 ) ] = 0.0 ; rtB .
ltq0doaugx [ i + ( i_p << 2 ) ] += u_p [ i_p << 2 ] * u [ i ] ; rtB .
ltq0doaugx [ i + ( i_p << 2 ) ] += u_p [ ( i_p << 2 ) + 1 ] * u [ i + 4 ] ;
rtB . ltq0doaugx [ i + ( i_p << 2 ) ] += u_p [ ( i_p << 2 ) + 2 ] * u [ i + 8
] ; rtB . ltq0doaugx [ i + ( i_p << 2 ) ] += u_p [ ( i_p << 2 ) + 3 ] * u [ i
+ 12 ] ; } } for ( i = 0 ; i < 16 ; i ++ ) { u [ i ] = rtB . ltq0doaugx [ i ]
; u_p [ i ] = rtConstP . iphb2gkf32 [ i ] ; } for ( i = 0 ; i < 4 ; i ++ ) {
for ( i_p = 0 ; i_p < 4 ; i_p ++ ) { rtB . kx1y0wb3wk [ i + ( i_p << 2 ) ] =
0.0 ; rtB . kx1y0wb3wk [ i + ( i_p << 2 ) ] += u_p [ i_p << 2 ] * u [ i ] ;
rtB . kx1y0wb3wk [ i + ( i_p << 2 ) ] += u_p [ ( i_p << 2 ) + 1 ] * u [ i + 4
] ; rtB . kx1y0wb3wk [ i + ( i_p << 2 ) ] += u_p [ ( i_p << 2 ) + 2 ] * u [ i
+ 8 ] ; rtB . kx1y0wb3wk [ i + ( i_p << 2 ) ] += u_p [ ( i_p << 2 ) + 3 ] * u
[ i + 12 ] ; } } memcpy ( & rtDW . mwz1nxvmic [ 0 ] , & rtB . ltq0doaugx [ 0
] , sizeof ( real_T ) << 4U ) ; } rtB . kvwcbei2yp = rtB . kx1y0wb3wk [ 12 ]
; rtB . bdqwapvmep = rtB . pi4pgrzjdg - rtB . kvwcbei2yp ; if (
ssGetLogOutput ( rtS ) ) { StructLogVar * svar = ( StructLogVar * ) rtDW .
ltrljuz1h5 . LoggedData ; LogVar * var = svar -> signals . values ; { double
locTime = ssGetT ( rtS ) ; rt_UpdateLogVar ( ( LogVar * ) svar -> time , &
locTime , 0 ) ; } { real_T up0 [ 1 ] ; up0 [ 0 ] = rtB . bdqwapvmep ;
rt_UpdateLogVar ( ( LogVar * ) var , up0 , 0 ) ; } } rtB . cp0i2hcsha = 0.1 *
muDoubleScalarSin ( rtB . ptf05qfh23 ) ; rtB . fywryl4tfe = rtB . kx1y0wb3wk
[ 13 ] ; memcpy ( & rtB . c15poiyb0k [ 0 ] , rtConstP . d2pk3t4xwc , 9U *
sizeof ( real_T ) ) ; rtB . c15poiyb0k [ 9 ] = rtB . pi4pgrzjdg ; rtB .
c15poiyb0k [ 10 ] = rtB . cp0i2hcsha ; rtB . c15poiyb0k [ 11 ] = 0.0 ; for (
i = 0 ; i < 4 ; i ++ ) { rtB . iccfft1fyi [ i << 2 ] = rtB . c15poiyb0k [ 3 *
i ] ; rtB . iccfft1fyi [ 1 + ( i << 2 ) ] = rtB . c15poiyb0k [ 3 * i + 1 ] ;
rtB . iccfft1fyi [ 2 + ( i << 2 ) ] = rtB . c15poiyb0k [ 3 * i + 2 ] ; } rtB
. iccfft1fyi [ 3 ] = 0.0 ; rtB . iccfft1fyi [ 7 ] = 0.0 ; rtB . iccfft1fyi [
11 ] = 0.0 ; rtB . iccfft1fyi [ 15 ] = 1.0 ; for ( i = 0 ; i < 16 ; i ++ ) {
u [ i ] = rtB . iccfft1fyi [ i ] ; u_p [ i ] = rtrtC . lilszzzwzx [ i ] ; }
for ( i = 0 ; i < 4 ; i ++ ) { for ( i_p = 0 ; i_p < 4 ; i_p ++ ) { rtB .
oodqxyey5l [ i + ( i_p << 2 ) ] = 0.0 ; rtB . oodqxyey5l [ i + ( i_p << 2 ) ]
+= u_p [ i_p << 2 ] * u [ i ] ; rtB . oodqxyey5l [ i + ( i_p << 2 ) ] += u_p
[ ( i_p << 2 ) + 1 ] * u [ i + 4 ] ; rtB . oodqxyey5l [ i + ( i_p << 2 ) ] +=
u_p [ ( i_p << 2 ) + 2 ] * u [ i + 8 ] ; rtB . oodqxyey5l [ i + ( i_p << 2 )
] += u_p [ ( i_p << 2 ) + 3 ] * u [ i + 12 ] ; } } rtB . bh3kreoxfr = rtB .
kx1y0wb3wk [ 14 ] ; rtB . cgc5dx5go3 [ 0 ] = rtB . kx1y0wb3wk [ 0 ] ; rtB .
cgc5dx5go3 [ 1 ] = rtB . kx1y0wb3wk [ 1 ] ; rtB . cgc5dx5go3 [ 2 ] = rtB .
kx1y0wb3wk [ 2 ] ; rtB . mtf5exy1d5 [ 0 ] = rtB . oodqxyey5l [ 0 ] ; rtB .
mtf5exy1d5 [ 1 ] = rtB . oodqxyey5l [ 1 ] ; rtB . mtf5exy1d5 [ 2 ] = rtB .
oodqxyey5l [ 2 ] ; rtB . olcy3pu40b [ 0 ] = rtB . cgc5dx5go3 [ 1 ] * rtB .
mtf5exy1d5 [ 2 ] ; rtB . olcy3pu40b [ 1 ] = rtB . cgc5dx5go3 [ 2 ] * rtB .
mtf5exy1d5 [ 0 ] ; rtB . olcy3pu40b [ 2 ] = rtB . cgc5dx5go3 [ 0 ] * rtB .
mtf5exy1d5 [ 1 ] ; rtB . olcy3pu40b [ 3 ] = rtB . cgc5dx5go3 [ 2 ] * rtB .
mtf5exy1d5 [ 1 ] ; rtB . olcy3pu40b [ 4 ] = rtB . cgc5dx5go3 [ 0 ] * rtB .
mtf5exy1d5 [ 2 ] ; rtB . olcy3pu40b [ 5 ] = rtB . cgc5dx5go3 [ 1 ] * rtB .
mtf5exy1d5 [ 0 ] ; rtB . c0j5gjznxd [ 0 ] = rtB . olcy3pu40b [ 0 ] - rtB .
olcy3pu40b [ 3 ] ; rtB . c0j5gjznxd [ 1 ] = rtB . olcy3pu40b [ 1 ] - rtB .
olcy3pu40b [ 4 ] ; rtB . c0j5gjznxd [ 2 ] = rtB . olcy3pu40b [ 2 ] - rtB .
olcy3pu40b [ 5 ] ; rtB . l2ybfmwenl [ 0 ] = rtB . kx1y0wb3wk [ 4 ] ; rtB .
l2ybfmwenl [ 1 ] = rtB . kx1y0wb3wk [ 5 ] ; rtB . l2ybfmwenl [ 2 ] = rtB .
kx1y0wb3wk [ 6 ] ; rtB . itpoecacsw [ 0 ] = rtB . oodqxyey5l [ 4 ] ; rtB .
itpoecacsw [ 1 ] = rtB . oodqxyey5l [ 5 ] ; rtB . itpoecacsw [ 2 ] = rtB .
oodqxyey5l [ 6 ] ; rtB . pxwhdnbs3a [ 0 ] = rtB . l2ybfmwenl [ 1 ] * rtB .
itpoecacsw [ 2 ] ; rtB . pxwhdnbs3a [ 1 ] = rtB . l2ybfmwenl [ 2 ] * rtB .
itpoecacsw [ 0 ] ; rtB . pxwhdnbs3a [ 2 ] = rtB . l2ybfmwenl [ 0 ] * rtB .
itpoecacsw [ 1 ] ; rtB . pxwhdnbs3a [ 3 ] = rtB . l2ybfmwenl [ 2 ] * rtB .
itpoecacsw [ 1 ] ; rtB . pxwhdnbs3a [ 4 ] = rtB . l2ybfmwenl [ 0 ] * rtB .
itpoecacsw [ 2 ] ; rtB . pxwhdnbs3a [ 5 ] = rtB . l2ybfmwenl [ 1 ] * rtB .
itpoecacsw [ 0 ] ; rtB . fapc3wzhgp [ 0 ] = rtB . pxwhdnbs3a [ 0 ] - rtB .
pxwhdnbs3a [ 3 ] ; rtB . fapc3wzhgp [ 1 ] = rtB . pxwhdnbs3a [ 1 ] - rtB .
pxwhdnbs3a [ 4 ] ; rtB . fapc3wzhgp [ 2 ] = rtB . pxwhdnbs3a [ 2 ] - rtB .
pxwhdnbs3a [ 5 ] ; rtB . c54mpsjpxe [ 0 ] = rtB . kx1y0wb3wk [ 8 ] ; rtB .
c54mpsjpxe [ 1 ] = rtB . kx1y0wb3wk [ 9 ] ; rtB . c54mpsjpxe [ 2 ] = rtB .
kx1y0wb3wk [ 10 ] ; rtB . izceacj0o4 [ 0 ] = rtB . oodqxyey5l [ 8 ] ; rtB .
izceacj0o4 [ 1 ] = rtB . oodqxyey5l [ 9 ] ; rtB . izceacj0o4 [ 2 ] = rtB .
oodqxyey5l [ 10 ] ; rtB . ncii3n04xe [ 0 ] = rtB . c54mpsjpxe [ 1 ] * rtB .
izceacj0o4 [ 2 ] ; rtB . ncii3n04xe [ 1 ] = rtB . c54mpsjpxe [ 2 ] * rtB .
izceacj0o4 [ 0 ] ; rtB . ncii3n04xe [ 2 ] = rtB . c54mpsjpxe [ 0 ] * rtB .
izceacj0o4 [ 1 ] ; rtB . ncii3n04xe [ 3 ] = rtB . c54mpsjpxe [ 2 ] * rtB .
izceacj0o4 [ 1 ] ; rtB . ncii3n04xe [ 4 ] = rtB . c54mpsjpxe [ 0 ] * rtB .
izceacj0o4 [ 2 ] ; rtB . ncii3n04xe [ 5 ] = rtB . c54mpsjpxe [ 1 ] * rtB .
izceacj0o4 [ 0 ] ; rtB . lns4a50jfv [ 0 ] = rtB . ncii3n04xe [ 0 ] - rtB .
ncii3n04xe [ 3 ] ; rtB . lns4a50jfv [ 1 ] = rtB . ncii3n04xe [ 1 ] - rtB .
ncii3n04xe [ 4 ] ; rtB . lns4a50jfv [ 2 ] = rtB . ncii3n04xe [ 2 ] - rtB .
ncii3n04xe [ 5 ] ; rtB . kds4a0jgsi [ 0 ] = ( rtB . c0j5gjznxd [ 0 ] + rtB .
fapc3wzhgp [ 0 ] ) + rtB . lns4a50jfv [ 0 ] ; rtB . kds4a0jgsi [ 1 ] = ( rtB
. c0j5gjznxd [ 1 ] + rtB . fapc3wzhgp [ 1 ] ) + rtB . lns4a50jfv [ 1 ] ; rtB
. kds4a0jgsi [ 2 ] = ( rtB . c0j5gjznxd [ 2 ] + rtB . fapc3wzhgp [ 2 ] ) +
rtB . lns4a50jfv [ 2 ] ; rtB . pswhok3m0h [ 0 ] = rtB . oodqxyey5l [ 12 ] ;
rtB . pswhok3m0h [ 1 ] = rtB . oodqxyey5l [ 13 ] ; rtB . pswhok3m0h [ 2 ] =
rtB . oodqxyey5l [ 14 ] ; rtB . nxcjgubfup [ 0 ] = rtB . kx1y0wb3wk [ 12 ] ;
rtB . nxcjgubfup [ 1 ] = rtB . kx1y0wb3wk [ 13 ] ; rtB . nxcjgubfup [ 2 ] =
rtB . kx1y0wb3wk [ 14 ] ; rtB . bg0w5wujyw [ 0 ] = rtB . pswhok3m0h [ 0 ] -
rtB . nxcjgubfup [ 0 ] ; rtB . bg0w5wujyw [ 1 ] = rtB . pswhok3m0h [ 1 ] -
rtB . nxcjgubfup [ 1 ] ; rtB . bg0w5wujyw [ 2 ] = rtB . pswhok3m0h [ 2 ] -
rtB . nxcjgubfup [ 2 ] ; rtB . plwhzf40d5 [ 0 ] = rtB . bg0w5wujyw [ 0 ] ;
rtB . plwhzf40d5 [ 1 ] = rtB . bg0w5wujyw [ 1 ] ; rtB . plwhzf40d5 [ 2 ] =
rtB . bg0w5wujyw [ 2 ] ; rtB . plwhzf40d5 [ 3 ] = 0.5 * rtB . kds4a0jgsi [ 0
] ; rtB . plwhzf40d5 [ 4 ] = 0.5 * rtB . kds4a0jgsi [ 1 ] ; rtB . plwhzf40d5
[ 5 ] = 0.5 * rtB . kds4a0jgsi [ 2 ] ; for ( s8_iter = 1 ; s8_iter <= 6 ;
s8_iter ++ ) { rtB . kbqerzvazr = s8_iter ; rtB . d2p52y2le0 = 6.0 - ( real_T
) rtB . kbqerzvazr ; switch ( ( int32_T ) rtB . d2p52y2le0 ) { case 0 : rtB .
bawsajx3qj = rtB . axilp3tz0a [ 0 ] ; break ; case 1 : rtB . bawsajx3qj = rtB
. axilp3tz0a [ 1 ] ; break ; case 2 : rtB . bawsajx3qj = rtB . axilp3tz0a [ 2
] ; break ; case 3 : rtB . bawsajx3qj = rtB . axilp3tz0a [ 3 ] ; break ; case
4 : rtB . bawsajx3qj = rtB . axilp3tz0a [ 4 ] ; break ; default : rtB .
bawsajx3qj = rtB . axilp3tz0a [ 5 ] ; break ; } switch ( ( int32_T ) rtB .
d2p52y2le0 ) { case 0 : rtB . bqksmtmspn [ 0 ] = 1.5707963267948966 ; rtB .
bqksmtmspn [ 1 ] = 0.0 ; rtB . bqksmtmspn [ 2 ] = 1.5707963267948966 ; rtB .
bqksmtmspn [ 3 ] = 0.0 ; break ; case 1 : rtB . bqksmtmspn [ 0 ] = 0.0 ; rtB
. bqksmtmspn [ 1 ] = 0.404 ; rtB . bqksmtmspn [ 2 ] = 1.5707963267948966 ;
rtB . bqksmtmspn [ 3 ] = 0.0 ; break ; case 2 : rtB . bqksmtmspn [ 0 ] = ( -
1.5707963267948966 ) ; rtB . bqksmtmspn [ 1 ] = 0.0 ; rtB . bqksmtmspn [ 2 ]
= 0.0 ; rtB . bqksmtmspn [ 3 ] = 0.0 ; break ; case 3 : rtB . bqksmtmspn [ 0
] = 1.5707963267948966 ; rtB . bqksmtmspn [ 1 ] = 0.025 ; rtB . bqksmtmspn [
2 ] = 0.0 ; rtB . bqksmtmspn [ 3 ] = 0.405 ; break ; case 4 : rtB .
bqksmtmspn [ 0 ] = 1.5707963267948966 ; rtB . bqksmtmspn [ 1 ] = 0.0 ; rtB .
bqksmtmspn [ 2 ] = 1.5707963267948966 ; rtB . bqksmtmspn [ 3 ] = 0.0 ; break
; default : rtB . bqksmtmspn [ 0 ] = 0.0 ; rtB . bqksmtmspn [ 1 ] = 0.0 ; rtB
. bqksmtmspn [ 2 ] = 1.5707963267948966 ; rtB . bqksmtmspn [ 3 ] = 0.0 ;
break ; } rtB . oq001gqp2p = muDoubleScalarCos ( rtB . bawsajx3qj ) ; rtB .
f1rqrj0gds [ 0 ] = rtB . oq001gqp2p ; rtB . mvjjykwlqc = muDoubleScalarSin (
rtB . bawsajx3qj ) ; rtB . f1rqrj0gds [ 1 ] = rtB . mvjjykwlqc ; rtB .
f1rqrj0gds [ 2 ] = 0.0 ; rtB . f1rqrj0gds [ 3 ] = 0.0 ; rtB . pbi3or4c0k = (
- 1.0 ) * rtB . mvjjykwlqc ; rtB . goeguqncgp = muDoubleScalarCos ( rtB .
bqksmtmspn [ 0 ] ) ; rtB . f1rqrj0gds [ 4 ] = rtB . pbi3or4c0k * rtB .
goeguqncgp ; rtB . f1rqrj0gds [ 5 ] = rtB . oq001gqp2p * rtB . goeguqncgp ;
rtB . m214sy2azr = muDoubleScalarSin ( rtB . bqksmtmspn [ 0 ] ) ; rtB .
f1rqrj0gds [ 6 ] = rtB . m214sy2azr ; rtB . f1rqrj0gds [ 7 ] = 0.0 ; rtB .
f1rqrj0gds [ 8 ] = rtB . mvjjykwlqc * rtB . m214sy2azr ; rtB . p50j15qoex = (
- 1.0 ) * rtB . oq001gqp2p ; rtB . f1rqrj0gds [ 9 ] = rtB . p50j15qoex * rtB
. m214sy2azr ; rtB . f1rqrj0gds [ 10 ] = rtB . goeguqncgp ; rtB . f1rqrj0gds
[ 11 ] = 0.0 ; rtB . f1rqrj0gds [ 12 ] = rtB . bqksmtmspn [ 1 ] * rtB .
oq001gqp2p ; rtB . f1rqrj0gds [ 13 ] = rtB . bqksmtmspn [ 1 ] * rtB .
mvjjykwlqc ; rtB . f1rqrj0gds [ 14 ] = rtB . bqksmtmspn [ 3 ] ; rtB .
f1rqrj0gds [ 15 ] = 1.0 ; for ( i = 0 ; i < 16 ; i ++ ) { rtB . icbou04qgh [
i ] = rtDW . p3s2khgxd4 [ i ] ; if ( rtB . kbqerzvazr >= 1 ) { rtB .
lo2unisv3r [ i ] = rtB . icbou04qgh [ i ] ; } else { rtB . lo2unisv3r [ i ] =
rtConstP . iphb2gkf32 [ i ] ; } u [ i ] = rtB . f1rqrj0gds [ i ] ; u_p [ i ]
= rtB . lo2unisv3r [ i ] ; } for ( i = 0 ; i < 4 ; i ++ ) { for ( i_p = 0 ;
i_p < 4 ; i_p ++ ) { rtB . gelfrxwjrs [ i + ( i_p << 2 ) ] = 0.0 ; rtB .
gelfrxwjrs [ i + ( i_p << 2 ) ] += u_p [ i_p << 2 ] * u [ i ] ; rtB .
gelfrxwjrs [ i + ( i_p << 2 ) ] += u_p [ ( i_p << 2 ) + 1 ] * u [ i + 4 ] ;
rtB . gelfrxwjrs [ i + ( i_p << 2 ) ] += u_p [ ( i_p << 2 ) + 2 ] * u [ i + 8
] ; rtB . gelfrxwjrs [ i + ( i_p << 2 ) ] += u_p [ ( i_p << 2 ) + 3 ] * u [ i
+ 12 ] ; } } rtB . k5iuwdqmdv = rtB . gelfrxwjrs [ 0 ] ; rtB . kcmz2bstxf = (
- 1.0 ) * rtB . k5iuwdqmdv ; rtB . melahpcxwo = rtB . gelfrxwjrs [ 13 ] ; rtB
. gio2vjw2fw = rtB . kcmz2bstxf * rtB . melahpcxwo ; rtB . hw4qs5maxi = rtB .
gelfrxwjrs [ 1 ] ; rtB . jqxwm2tpmb = rtB . gelfrxwjrs [ 12 ] ; rtB .
euoqqrdkql = rtB . hw4qs5maxi * rtB . jqxwm2tpmb ; rtB . dz4xjznsqf [ 0 ] =
rtB . gio2vjw2fw + rtB . euoqqrdkql ; rtB . cgye2zz4fs = rtB . gelfrxwjrs [ 4
] ; rtB . bkktt4qysn = ( - 1.0 ) * rtB . cgye2zz4fs ; rtB . i1y4akvdkd = rtB
. gelfrxwjrs [ 13 ] ; rtB . nz5gddymwa = rtB . bkktt4qysn * rtB . i1y4akvdkd
; rtB . ilrbulvgek = rtB . gelfrxwjrs [ 5 ] ; rtB . e0q3brqdgq = rtB .
gelfrxwjrs [ 12 ] ; rtB . buky4qjekz = rtB . ilrbulvgek * rtB . e0q3brqdgq ;
rtB . dz4xjznsqf [ 1 ] = rtB . nz5gddymwa + rtB . buky4qjekz ; rtB .
figg1nrpod = rtB . gelfrxwjrs [ 8 ] ; rtB . kua0xnsh0o = ( - 1.0 ) * rtB .
figg1nrpod ; rtB . mdd1nwwlps = rtB . gelfrxwjrs [ 13 ] ; rtB . itobk2hvgd =
rtB . kua0xnsh0o * rtB . mdd1nwwlps ; rtB . iguaipqyek = rtB . gelfrxwjrs [ 9
] ; rtB . ecxpi3bkcd = rtB . gelfrxwjrs [ 12 ] ; rtB . fng0duekef = rtB .
iguaipqyek * rtB . ecxpi3bkcd ; rtB . dz4xjznsqf [ 2 ] = rtB . itobk2hvgd +
rtB . fng0duekef ; rtB . b402h2idnm [ 0 ] = rtB . gelfrxwjrs [ 2 ] ; rtB .
b402h2idnm [ 1 ] = rtB . gelfrxwjrs [ 6 ] ; rtB . b402h2idnm [ 2 ] = rtB .
gelfrxwjrs [ 10 ] ; rtB . dz4xjznsqf [ 3 ] = rtB . b402h2idnm [ 0 ] ; rtB .
dz4xjznsqf [ 4 ] = rtB . b402h2idnm [ 1 ] ; rtB . dz4xjznsqf [ 5 ] = rtB .
b402h2idnm [ 2 ] ; switch ( rtB . kbqerzvazr ) { case 1 : for ( i = 0 ; i < 6
; i ++ ) { rtB . hyyj3phdcl [ i ] = rtB . dz4xjznsqf [ i ] ; } rtDW .
cteqqy32ya = 4 ; break ; case 2 : for ( i = 0 ; i < 6 ; i ++ ) { rtB .
fxrx2jteos [ i ] = rtB . dz4xjznsqf [ i ] ; } for ( i = 0 ; i < 6 ; i ++ ) {
rtB . fxrx2jteos [ i + 6 ] = rtB . hyyj3phdcl [ i ] ; } rtDW . luwwjirqvw = 4
; break ; case 3 : for ( i = 0 ; i < 6 ; i ++ ) { rtB . j2wxn3cjv4 [ i ] =
rtB . dz4xjznsqf [ i ] ; } memcpy ( & rtB . j2wxn3cjv4 [ 6 ] , & rtB .
fxrx2jteos [ 0 ] , 12U * sizeof ( real_T ) ) ; rtDW . j2qrq44urz = 4 ; break
; case 4 : for ( i = 0 ; i < 6 ; i ++ ) { rtB . nwvxmcftuf [ i ] = rtB .
dz4xjznsqf [ i ] ; } memcpy ( & rtB . nwvxmcftuf [ 6 ] , & rtB . j2wxn3cjv4 [
0 ] , 18U * sizeof ( real_T ) ) ; rtDW . coupmxhajs = 4 ; break ; case 5 :
for ( i = 0 ; i < 6 ; i ++ ) { rtB . pv0zwy4ism [ i ] = rtB . dz4xjznsqf [ i
] ; } memcpy ( & rtB . pv0zwy4ism [ 6 ] , & rtB . nwvxmcftuf [ 0 ] , 24U *
sizeof ( real_T ) ) ; rtDW . ijfh0nhbll = 4 ; break ; case 6 : for ( i = 0 ;
i < 6 ; i ++ ) { rtB . amgmrxskq1 [ i ] = rtB . dz4xjznsqf [ i ] ; } memcpy (
& rtB . amgmrxskq1 [ 6 ] , & rtB . pv0zwy4ism [ 0 ] , 30U * sizeof ( real_T )
) ; rtDW . gvrqqxide3 = 4 ; break ; } memcpy ( & rtDW . p3s2khgxd4 [ 0 ] , &
rtB . gelfrxwjrs [ 0 ] , sizeof ( real_T ) << 4U ) ; } rt_invd6x6_snf ( rtB .
amgmrxskq1 , rtB . d24dsjjt3o ) ; memcpy ( & u_e [ 0 ] , & rtB . d24dsjjt3o [
0 ] , 36U * sizeof ( real_T ) ) ; for ( i = 0 ; i < 6 ; i ++ ) { u_i [ i ] =
rtB . i2h1htfzsc [ i ] ; } for ( i = 0 ; i < 6 ; i ++ ) { rtB . jeci4qlpkk [
i ] = 0.0 ; for ( i_p = 0 ; i_p < 6 ; i_p ++ ) { rtB . jeci4qlpkk [ i ] +=
u_e [ 6 * i_p + i ] * u_i [ i_p ] ; } rtB . hlkmo5q05f [ i ] = 0.1 * rtB .
jeci4qlpkk [ i ] ; } for ( i = 0 ; i < 6 ; i ++ ) { rtB . fq3r53l3l1 [ i ] =
rtB . hlkmo5q05f [ i ] + rtB . axilp3tz0a [ i ] ; } UNUSED_PARAMETER ( tid )
; } void MdlUpdate ( int_T tid ) { int32_T i ; rtDW . eeux2ti3uv = rtB .
mnknpq2c4s ; for ( i = 0 ; i < 6 ; i ++ ) { rtDW . g5wnsipe0f [ i ] = rtB .
fq3r53l3l1 [ i ] ; } UNUSED_PARAMETER ( tid ) ; } void MdlTerminate ( void )
{ } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 0 ) ;
ssSetNumY ( rtS , 0 ) ; ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS
, 0 ) ; ssSetNumSampleTimes ( rtS , 1 ) ; ssSetNumBlocks ( rtS , 277 ) ;
ssSetNumBlockIO ( rtS , 98 ) ; } void MdlInitializeSampleTimes ( void ) {
ssSetSampleTime ( rtS , 0 , 0.1 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ; }
void raccel_set_checksum ( SimStruct * rtS ) { ssSetChecksumVal ( rtS , 0 ,
2928393357U ) ; ssSetChecksumVal ( rtS , 1 , 2934841979U ) ; ssSetChecksumVal
( rtS , 2 , 1865750830U ) ; ssSetChecksumVal ( rtS , 3 , 3543056207U ) ; }
SimStruct * raccel_register_model ( void ) { static struct _ssMdlInfo mdlInfo
; ( void ) memset ( ( char * ) rtS , 0 , sizeof ( SimStruct ) ) ; ( void )
memset ( ( char * ) & mdlInfo , 0 , sizeof ( struct _ssMdlInfo ) ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { void * dwork = ( void * ) & rtDW ; ssSetRootDWork ( rtS , dwork
) ; ( void ) memset ( dwork , 0 , sizeof ( DW ) ) ; } { static
DataTypeTransInfo dtInfo ; ( void ) memset ( ( char_T * ) & dtInfo , 0 ,
sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS , & dtInfo ) ; dtInfo .
numDataTypes = 14 ; dtInfo . dataTypeSizes = & rtDataTypeSizes [ 0 ] ; dtInfo
. dataTypeNames = & rtDataTypeNames [ 0 ] ; dtInfo . B = & rtBTransTable ; }
ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2 ) ;
ssSetModelName ( rtS , "robot_circular" ) ; ssSetPath ( rtS ,
"robot_circular" ) ; ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal ( rtS , 100.0 )
; ssSetStepSize ( rtS , 0.1 ) ; ssSetFixedStepSize ( rtS , 0.1 ) ; { static
RTWLogInfo rt_DataLoggingInfo ; ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo
) ; } { rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogXSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; rtliSetLogT (
ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX ( ssGetRTWLogInfo ( rtS ) ,
"" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetSigLog (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo
( rtS ) , "none" ) ; rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 0 ) ;
rtliSetLogMaxRows ( ssGetRTWLogInfo ( rtS ) , 1000 ) ; rtliSetLogDecimation (
ssGetRTWLogInfo ( rtS ) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" )
; rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
ssSolverInfo slvrInfo ; ssSetSolverInfo ( rtS , & slvrInfo ) ;
ssSetSolverName ( rtS , "FixedStepDiscrete" ) ; ssSetVariableStepSolver ( rtS
, 0 ) ; ssSetSolverConsistencyChecking ( rtS , 0 ) ;
ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ; ssSetSolverRobustResetMethod (
rtS , 0 ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelLogData ( rtS , rt_UpdateTXYLogVars ) ; ssSetModelUpdate ( rtS
, MdlUpdate ) ; ssSetTNextTid ( rtS , INT_MIN ) ; ssSetTNext ( rtS ,
rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ; ssSetNumNonsampledZCs ( rtS ,
0 ) ; } ssSetChecksumVal ( rtS , 0 , 2928393357U ) ; ssSetChecksumVal ( rtS ,
1 , 2934841979U ) ; ssSetChecksumVal ( rtS , 2 , 1865750830U ) ;
ssSetChecksumVal ( rtS , 3 , 3543056207U ) ; { static const sysRanDType
rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo
; static const sysRanDType * systemRan [ 11 ] ; ssSetRTWExtModeInfo ( rtS , &
rt_ExtModeInfo ) ; rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo ,
systemRan ) ; systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = &
rtAlwaysEnabled ; systemRan [ 2 ] = & rtAlwaysEnabled ; systemRan [ 3 ] = &
rtAlwaysEnabled ; systemRan [ 4 ] = ( sysRanDType * ) & rtDW . cteqqy32ya ;
systemRan [ 5 ] = ( sysRanDType * ) & rtDW . luwwjirqvw ; systemRan [ 6 ] = (
sysRanDType * ) & rtDW . j2qrq44urz ; systemRan [ 7 ] = ( sysRanDType * ) &
rtDW . coupmxhajs ; systemRan [ 8 ] = ( sysRanDType * ) & rtDW . ijfh0nhbll ;
systemRan [ 9 ] = ( sysRanDType * ) & rtDW . gvrqqxide3 ; systemRan [ 10 ] =
& rtAlwaysEnabled ; rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS )
, & ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr (
ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr (
ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; } return rtS ; }
