#define REQUEST_MESSAGE_LENGTH			36

#define NORMAL_MODE_MESSAGE_YAW                             0
#define NORMAL_MODE_MESSAGE_PITCH							2
#define NORMAL_MODE_MESSAGE_MARCH							4
#define NORMAL_MODE_MESSAGE_LOG								6
#define NORMAL_MODE_MESSAGE_DEPTH							8
#define NORMAL_MODE_MESSAGE_GRUB1							10
#define NORMAL_MODE_MESSAGE_GRUB2							11
#define NORMAL_MODE_MESSAGE_LIGHT							12
#define NORMAL_MODE_MESSAGE_TILT							13
#define NORMAL_MODE_MESSAGE_DEV1							14
#define NORMAL_MODE_MESSAGE_DEV2							15
#define NORMAL_MODE_MESSAGE_FLAGS1                          16
#define NORMAL_MODE_MESSAGE_FLAGS2                          17
#define VTL_SPEED											18
#define VTR_SPEED											20
#define VBL_SPEED											22
#define VBR_SPEED											24
#define HTL_SPEED											26
#define HTR_SPEED											28
#define HBL_SPEED											30
#define HBR_SPEED											32
/* Коэффициенты на каждый винтомотор = 8 байт
 * Коэффициенты системы управления:
 *     - Глубина = 2 байта
 *     - Крен = 2 байта
 *     - Дифферент = 2 байта
 *     - Курс = 2 байта
 *
 *
 *
 *
 *
 *
 *
 *
 */


#define RESPONSE_MESSAGE_LENGTH                             70

#define NORMAL_MODE_RESPONSE_DEPTH							0
#define NORMAL_MODE_RESPONSE_ROLL							4
#define NORMAL_MODE_RESPONSE_YAW							8
#define NORMAL_MODE_RESPONSE_PITCH							12
#define NORMAL_MODE_RESPONSE_AX								16
#define NORMAL_MODE_RESPONSE_AY								20

#define NORMAL_MODE_RESPONSE_THRUSTER_VTL_SPEED             24	//Vertical Top Left
#define NORMAL_MODE_RESPONSE_THRUSTER_VTL_CURRENT           26
#define NORMAL_MODE_RESPONSE_THRUSTER_VTL_TEMP              27

#define NORMAL_MODE_RESPONSE_THRUSTER_VTR_SPEED             28	//Vertical Top Right
#define NORMAL_MODE_RESPONSE_THRUSTER_VTR_CURRENT           30
#define NORMAL_MODE_RESPONSE_THRUSTER_VTR_TEMP              31

#define NORMAL_MODE_RESPONSE_THRUSTER_VBL_SPEED             32	//Vertical Bottom Left
#define NORMAL_MODE_RESPONSE_THRUSTER_VBL_CURRENT           34
#define NORMAL_MODE_RESPONSE_THRUSTER_VBL_TEMP              35

#define NORMAL_MODE_RESPONSE_THRUSTER_VBR_SPEED             36	//Vertical Bottom Right
#define NORMAL_MODE_RESPONSE_THRUSTER_VBR_CURRENT           38
#define NORMAL_MODE_RESPONSE_THRUSTER_VBR_TEMP              39

#define NORMAL_MODE_RESPONSE_THRUSTER_HTL_SPEED             40	//Horizontal Top Left
#define NORMAL_MODE_RESPONSE_THRUSTER_HTL_CURRENT           42
#define NORMAL_MODE_RESPONSE_THRUSTER_HTL_TEMP              43

#define NORMAL_MODE_RESPONSE_THRUSTER_HTR_SPEED             44	//Horizontal Top Right
#define NORMAL_MODE_RESPONSE_THRUSTER_HTR_CURRENT           46
#define NORMAL_MODE_RESPONSE_THRUSTER_HTR_TEMP              47

#define NORMAL_MODE_RESPONSE_THRUSTER_HBL_SPEED             48	//Horizontal Bottom Left
#define NORMAL_MODE_RESPONSE_THRUSTER_HBL_CURRENT           50
#define NORMAL_MODE_RESPONSE_THRUSTER_HBL_TEMP              51

#define NORMAL_MODE_RESPONSE_THRUSTER_HBR_SPEED             52	//Horizontal Bottom Right
#define NORMAL_MODE_RESPONSE_THRUSTER_HBR_CURRENT           54
#define NORMAL_MODE_RESPONSE_THRUSTER_HBR_TEMP              55

#define NORMAL_MODE_RESPONSE_GRUB1_CURRENT					56
#define NORMAL_MODE_RESPONSE_GRUB2_CURRENT					57
#define NORMAL_MODE_RESPONSE_DEV1_CURRENT					58
#define NORMAL_MODE_RESPONSE_DEV2_CURRENT					59
#define NORMAL_MODE_RESPONSE_TILT_CURRENT					60
#define NORMAL_MODE_RESPONSE_LIGHT_CURRENT					61

#define NORMAL_MODE_RESPONSE_48V							62
#define NORMAL_MODE_RESPONSE_12V							63
#define NORMAL_MODE_RESPONSE_5V								64
#define NORMAL_MODE_RESPONSE_3V								65
#define NORMAL_MODE_RESPONSE_HUMIDITY						66

#define NORMAL_MODE_RESPONSE_THRUSTERS_FLAGS				67
