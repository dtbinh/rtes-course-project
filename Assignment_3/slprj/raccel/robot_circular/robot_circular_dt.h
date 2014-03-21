#include "__cf_robot_circular.h"
#include "ext_types.h"
static uint_T rtDataTypeSizes [ ] = { sizeof ( real_T ) , sizeof ( real32_T )
, sizeof ( int8_T ) , sizeof ( uint8_T ) , sizeof ( int16_T ) , sizeof (
uint16_T ) , sizeof ( int32_T ) , sizeof ( uint32_T ) , sizeof ( boolean_T )
, sizeof ( fcn_call_T ) , sizeof ( int_T ) , sizeof ( pointer_T ) , sizeof (
action_T ) , 2 * sizeof ( uint32_T ) } ; static const char_T *
rtDataTypeNames [ ] = { "real_T" , "real32_T" , "int8_T" , "uint8_T" ,
"int16_T" , "uint16_T" , "int32_T" , "uint32_T" , "boolean_T" , "fcn_call_T"
, "int_T" , "pointer_T" , "action_T" , "timer_uint32_pair_T" } ; static
DataTypeTransition rtBTransitions [ ] = { { ( char_T * ) ( & rtB . nonm5g4o4k
) , 0 , 0 , 513 } , { ( char_T * ) ( & rtB . kbqerzvazr ) , 6 , 0 , 2 } , { (
char_T * ) ( & rtDW . eeux2ti3uv ) , 0 , 0 , 157 } , { ( char_T * ) ( & rtDW
. ltrljuz1h5 . LoggedData ) , 11 , 0 , 2 } , { ( char_T * ) ( & rtDW .
hq2ynfxh5b [ 0 ] ) , 6 , 0 , 6 } , { ( char_T * ) ( & rtDW . cteqqy32ya ) , 2
, 0 , 6 } } ; static DataTypeTransitionTable rtBTransTable = { 6U ,
rtBTransitions } ;
