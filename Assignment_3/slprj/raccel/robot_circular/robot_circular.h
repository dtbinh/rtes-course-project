#include "__cf_robot_circular.h"
#ifndef RTW_HEADER_robot_circular_h_
#define RTW_HEADER_robot_circular_h_
#ifndef robot_circular_COMMON_INCLUDES_
#define robot_circular_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#endif
#include "robot_circular_types.h"
#define MODEL_NAME robot_circular
#define NSAMPLE_TIMES (1) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (98) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (0)   
#elif NCSTATES != 0
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (NULL)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)
#endif
typedef struct { real_T nonm5g4o4k ; real_T mnknpq2c4s ; real_T ptf05qfh23 ;
real_T pi4pgrzjdg ; real_T axilp3tz0a [ 6 ] ; real_T kvwcbei2yp ; real_T
bdqwapvmep ; real_T cp0i2hcsha ; real_T fywryl4tfe ; real_T c15poiyb0k [ 12 ]
; real_T iccfft1fyi [ 16 ] ; real_T oodqxyey5l [ 16 ] ; real_T bh3kreoxfr ;
real_T cgc5dx5go3 [ 3 ] ; real_T mtf5exy1d5 [ 3 ] ; real_T olcy3pu40b [ 6 ] ;
real_T c0j5gjznxd [ 3 ] ; real_T l2ybfmwenl [ 3 ] ; real_T itpoecacsw [ 3 ] ;
real_T pxwhdnbs3a [ 6 ] ; real_T fapc3wzhgp [ 3 ] ; real_T c54mpsjpxe [ 3 ] ;
real_T izceacj0o4 [ 3 ] ; real_T ncii3n04xe [ 6 ] ; real_T lns4a50jfv [ 3 ] ;
real_T kds4a0jgsi [ 3 ] ; real_T pswhok3m0h [ 3 ] ; real_T nxcjgubfup [ 3 ] ;
real_T bg0w5wujyw [ 3 ] ; real_T plwhzf40d5 [ 6 ] ; real_T i2h1htfzsc [ 6 ] ;
real_T d24dsjjt3o [ 36 ] ; real_T jeci4qlpkk [ 6 ] ; real_T hlkmo5q05f [ 6 ]
; real_T fq3r53l3l1 [ 6 ] ; real_T d2p52y2le0 ; real_T bawsajx3qj ; real_T
bqksmtmspn [ 4 ] ; real_T icbou04qgh [ 16 ] ; real_T oq001gqp2p ; real_T
mvjjykwlqc ; real_T pbi3or4c0k ; real_T goeguqncgp ; real_T m214sy2azr ;
real_T p50j15qoex ; real_T f1rqrj0gds [ 16 ] ; real_T lo2unisv3r [ 16 ] ;
real_T gelfrxwjrs [ 16 ] ; real_T k5iuwdqmdv ; real_T kcmz2bstxf ; real_T
melahpcxwo ; real_T gio2vjw2fw ; real_T hw4qs5maxi ; real_T jqxwm2tpmb ;
real_T euoqqrdkql ; real_T cgye2zz4fs ; real_T bkktt4qysn ; real_T i1y4akvdkd
; real_T nz5gddymwa ; real_T ilrbulvgek ; real_T e0q3brqdgq ; real_T
buky4qjekz ; real_T figg1nrpod ; real_T kua0xnsh0o ; real_T mdd1nwwlps ;
real_T itobk2hvgd ; real_T iguaipqyek ; real_T ecxpi3bkcd ; real_T fng0duekef
; real_T b402h2idnm [ 3 ] ; real_T dz4xjznsqf [ 6 ] ; real_T amgmrxskq1 [ 36
] ; real_T pv0zwy4ism [ 30 ] ; real_T nwvxmcftuf [ 24 ] ; real_T j2wxn3cjv4 [
18 ] ; real_T fxrx2jteos [ 12 ] ; real_T hyyj3phdcl [ 6 ] ; real_T nu3lqck3bd
; real_T jyrzcculwp [ 4 ] ; real_T jzztlkosp1 [ 16 ] ; real_T fr13pf2yrk [ 16
] ; real_T ddxq2ghec0 ; real_T kjnhuvsnqx ; real_T pje1rdxv2r ; real_T
oogxhdfgdu ; real_T dv0esmlgu1 ; real_T jweiksj5ax ; real_T izlcklrx3a [ 16 ]
; real_T ltq0doaugx [ 16 ] ; real_T kx1y0wb3wk [ 16 ] ; real_T ap0z031w0t ;
real_T ptpimknh2x ; real_T gdlwb53cjz [ 2 ] ; real_T f3y1rdetlc ; real_T
lfg0s2opgm ; real_T ln4kdqr0me [ 2 ] ; int32_T kbqerzvazr ; int32_T
ozqlu4h43q ; } B ; typedef struct { real_T eeux2ti3uv ; real_T g5wnsipe0f [ 6
] ; real_T aj0tywjzak [ 9 ] ; real_T ak2swym2hr [ 36 ] ; real_T bvnna42qnw [
36 ] ; real_T asjef53ye4 [ 36 ] ; real_T dhfl3cl5td ; real_T p3s2khgxd4 [ 16
] ; real_T mwz1nxvmic [ 16 ] ; struct { void * LoggedData ; } ltrljuz1h5 ;
struct { void * LoggedData ; } dyrjcbme1i ; int32_T hq2ynfxh5b [ 6 ] ; int8_T
cteqqy32ya ; int8_T luwwjirqvw ; int8_T j2qrq44urz ; int8_T coupmxhajs ;
int8_T ijfh0nhbll ; int8_T gvrqqxide3 ; } DW ; typedef struct { const real_T
hmrko55v3c [ 3 ] ; const real_T anjizy1ltz ; const real_T fxwr3ekv2x ; const
real_T bjom1eompn [ 3 ] ; const real_T jnsmoo3nox ; const real_T pvrrhdkgkf [
3 ] ; const real_T gpohrx52hz [ 9 ] ; const real_T ljsbn43v2p ; const real_T
duojv0ocrr ; const real_T fck3zvlzga ; const real_T j15weosm4g [ 3 ] ; const
real_T pqdwlv0a32 [ 3 ] ; const real_T izintugdk0 [ 3 ] ; const real_T
mighrtapsy [ 9 ] ; const real_T oawzhrjrrp ; const real_T gndnvqc2t0 ; const
real_T lxg4ocsdrm [ 3 ] ; const real_T kvokgld4fo ; const real_T ewe2xzipt2 [
3 ] ; const real_T ghrlntl5yl [ 3 ] ; const real_T ihk2igpyqb [ 9 ] ; const
real_T epj5vednng [ 9 ] ; const real_T islcc2b2k1 [ 12 ] ; const real_T
lilszzzwzx [ 16 ] ; } ConstB ; typedef struct { real_T iphb2gkf32 [ 16 ] ;
real_T nrgwfwwnxs [ 6 ] ; real_T d2pk3t4xwc [ 9 ] ; } ConstP ; extern const
ConstB rtrtC ; extern const ConstP rtConstP ; extern const char *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern DW rtDW ; extern SimStruct
* const rtS ; extern const int_T gblNumToFiles ; extern const int_T
gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern rtInportTUtable
* gblInportTUtables ; extern const char * gblInportFileName ; extern const
int_T gblNumRootInportBlks ; extern const int_T gblNumModelInputs ; extern
const int_T gblInportDataTypeIdx [ ] ; extern const int_T gblInportDims [ ] ;
extern const int_T gblInportComplex [ ] ; extern const int_T
gblInportInterpoFlag [ ] ; extern const int_T gblInportContinuous [ ] ;
#endif
