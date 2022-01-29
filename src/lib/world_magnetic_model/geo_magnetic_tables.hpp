/****************************************************************************
 *
 *   Copyright (c) 2020-2021 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdint.h>

static constexpr float SAMPLING_RES = 10;
static constexpr float SAMPLING_MIN_LAT = -90;
static constexpr float SAMPLING_MAX_LAT = 90;
static constexpr float SAMPLING_MIN_LON = -180;
static constexpr float SAMPLING_MAX_LON = 180;

static constexpr int LAT_DIM = 19;
static constexpr int LON_DIM = 37;


// *INDENT-OFF*
// Magnetic declination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2022.0767,
static constexpr const int16_t declination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ {  25999, 24253, 22508, 20763, 19017, 17272, 15527, 13781, 12036, 10291,  8545,  6800,  5055,  3310,  1564,  -181, -1926, -3672, -5417, -7162, -8907,-10653,-12398,-14143,-15889,-17634,-19379,-21125,-22870,-24616,-26361,-28106,-29852, 31235, 29489, 27744, 25999, },
	/* LAT: -80 */ {  22566, 20433, 18491, 16716, 15075, 13536, 12072, 10660,  9284,  7934,  6602,  5283,  3974,  2669,  1362,    43, -1298, -2669, -4078, -5528, -7022, -8557,-10134,-11752,-13415,-15132,-16917,-18788,-20770,-22887,-25160,-27594,-30163, 30028, 27408, 24899, 22566, },
	/* LAT: -70 */ {  14972, 13575, 12451, 11491, 10624,  9794,  8953,  8067,  7115,  6096,  5026,  3932,  2846,  1790,   768,  -243, -1279, -2383, -3581, -4878, -6257, -7685, -9131,-10572,-11997,-13412,-14840,-16324,-17945,-19853,-22365,-26151, 30762, 24166, 19625, 16845, 14972, },
	/* LAT: -60 */ {   8401,  8159,  7882,  7612,  7361,  7111,  6805,  6375,  5762,  4944,  3944,  2832,  1711,   681,  -204,  -964, -1693, -2513, -3513, -4705, -6031, -7398, -8718, -9928,-10994,-11894,-12611,-13106,-13278,-12829,-10734, -3546,  4848,  7617,  8399,  8531,  8401, },
	/* LAT: -50 */ {   5470,  5508,  5455,  5368,  5297,  5263,  5230,  5106,  4765,  4105,  3097,  1826,   484,  -701, -1578, -2148, -2547, -2986, -3664, -4669, -5906, -7179, -8320, -9224, -9826,-10070, -9881, -9129, -7625, -5267, -2364,   383,  2492,  3916,  4790,  5265,  5470, },
	/* LAT: -40 */ {   3943,  4037,  4047,  4005,  3948,  3916,  3923,  3913,  3742,  3212,  2193,   755,  -810, -2130, -3001, -3460, -3649, -3711, -3875, -4432, -5398, -6470, -7357, -7901, -8015, -7645, -6762, -5380, -3668, -1963,  -501,   721,  1764,  2628,  3282,  3712,  3943, },
	/* LAT: -30 */ {   2974,  3061,  3094,  3082,  3027,  2950,  2892,  2860,  2735,  2261,  1232,  -283, -1892, -3151, -3899, -4252, -4338, -4135, -3703, -3469, -3817, -4559, -5260, -5617, -5499, -4919, -3964, -2756, -1544,  -596,    84,   684,  1307,  1907,  2415,  2775,  2974, },
	/* LAT: -20 */ {   2331,  2378,  2399,  2404,  2365,  2273,  2168,  2093,  1948,  1457,   407, -1077, -2557, -3626, -4168, -4292, -4096, -3546, -2688, -1883, -1593, -1939, -2587, -3061, -3104, -2750, -2117, -1299,  -520,   -27,   237,   539,   979,  1454,  1874,  2180,  2331, },
	/* LAT: -10 */ {   1938,  1933,  1914,  1915,  1890,  1809,  1701,  1612,  1429,   882,  -175, -1549, -2825, -3663, -3941, -3722, -3153, -2375, -1528,  -770,  -298,  -322,  -788, -1295, -1513, -1426, -1114,  -614,  -114,   129,   180,   341,   710,  1144,  1535,  1820,  1938, },
	/* LAT:   0 */ {   1725,  1692,  1640,  1634,  1626,  1560,  1459,  1348,  1095,   477,  -560, -1786, -2844, -3440, -3449, -2957, -2193, -1410,  -756,  -217,   199,   316,    42,  -375,  -632,  -690,  -592,  -329,   -37,    54,    -4,    85,   425,   863,  1280,  1597,  1725, },
	/* LAT:  10 */ {   1590,  1599,  1559,  1579,  1607,  1561,  1443,  1260,   885,   169,  -850, -1927, -2760, -3108, -2913, -2313, -1538,  -824,  -305,    77,   404,   556,   398,    77,  -160,  -268,  -290,  -208,  -103,  -142,  -280,  -252,    47,   498,   977,  1382,  1590, },
	/* LAT:  20 */ {   1409,  1558,  1621,  1715,  1804,  1786,  1635,  1336,   793,   -63, -1106, -2061, -2664, -2781, -2460, -1862, -1152,  -500,   -37,   275,   534,   683,   595,   352,   152,    34,   -56,  -119,  -197,  -386,  -621,  -680,  -448,    -3,   536,  1053,  1409, },
	/* LAT:  30 */ {   1112,  1479,  1740,  1965,  2126,  2139,  1954,  1534,   808,  -221, -1341, -2223, -2645, -2590, -2195, -1618,  -963,  -344,   122,   430,   663,   811,   793,   645,   495,   371,   216,     7,  -273,  -647, -1015, -1176, -1018,  -594,   -18,   591,  1112, },
	/* LAT:  40 */ {    759,  1346,  1840,  2233,  2482,  2527,  2313,  1782,   871,  -357, -1600, -2474, -2801, -2654, -2210, -1619,  -966,  -335,   177,   544,   817,  1017,  1114,  1104,  1028,   880,   614,   207,  -329,  -935, -1457, -1703, -1588, -1173,  -575,    99,   759, },
	/* LAT:  50 */ {    474,  1222,  1902,  2459,  2826,  2932,  2703,  2050,   907,  -593, -2023, -2945, -3244, -3056, -2567, -1921, -1211,  -512,   107,   615,  1035,  1393,  1675,  1848,  1868,  1683,  1242,   538,  -353, -1255, -1937, -2226, -2104, -1663, -1027,  -292,   474, },
	/* LAT:  60 */ {    285,  1139,  1945,  2640,  3143,  3354,  3139,  2325,   805, -1164, -2890, -3876, -4131, -3871, -3298, -2551, -1724,  -881,   -71,   683,  1377,  2010,  2555,  2954,  3117,  2935,  2302,  1192,  -219, -1541, -2414, -2727, -2563, -2068, -1372,  -567,   285, },
	/* LAT:  70 */ {     64,  1002,  1901,  2700,  3313,  3605,  3348,  2203,   -56, -2791, -4752, -5576, -5580, -5093, -4319, -3381, -2353, -1285,  -207,   855,  1882,  2851,  3721,  4431,  4882,  4921,  4320,  2859,   675, -1434, -2738, -3186, -3027, -2493, -1740,  -866,    64, },
	/* LAT:  80 */ {   -596,   328,  1182,  1875,  2259,  2068,   841, -1831, -5098, -7224, -7958, -7813, -7173, -6246, -5148, -3944, -2674, -1364,   -37,  1293,  2609,  3893,  5122,  6261,  7258,  8019,  8366,  7932,  6039,  2325, -1250, -2980, -3359, -3039, -2367, -1519,  -596, },
	/* LAT:  90 */ { -30016,-28271,-26525,-24780,-23035,-21289,-19544,-17799,-16053,-14308,-12563,-10818, -9072, -7327, -5582, -3837, -2092,  -347,  1399,  3144,  4889,  6634,  8379, 10125, 11870, 13615, 15361, 17106, 18852, 20597, 22343, 24088, 25834, 27579, 29325, 31070,-30016, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2022.0767,
static constexpr const int16_t inclination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ { -12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574,-12574, },
	/* LAT: -80 */ { -13660,-13526,-13366,-13185,-12991,-12790,-12585,-12385,-12194,-12017,-11860,-11726,-11616,-11529,-11466,-11425,-11405,-11407,-11435,-11489,-11572,-11686,-11831,-12004,-12202,-12419,-12648,-12881,-13109,-13322,-13509,-13659,-13763,-13815,-13812,-13758,-13660, },
	/* LAT: -70 */ { -14109,-13791,-13471,-13148,-12816,-12472,-12116,-11759,-11415,-11106,-10852,-10668,-10555,-10502,-10489,-10493,-10501,-10511,-10535,-10591,-10699,-10872,-11118,-11431,-11803,-12220,-12668,-13132,-13598,-14051,-14469,-14815,-15005,-14953,-14723,-14425,-14109, },
	/* LAT: -60 */ { -13520,-13168,-12830,-12497,-12154,-11781,-11366,-10911,-10443,-10011, -9680, -9502, -9497, -9633, -9838,-10032,-10159,-10205,-10195,-10181,-10227,-10384,-10672,-11078,-11575,-12130,-12716,-13312,-13900,-14462,-14958,-15249,-15075,-14692,-14286,-13893,-13520, },
	/* LAT: -50 */ { -12497,-12155,-11825,-11503,-11180,-10833,-10434, -9962, -9432, -8909, -8517, -8388, -8585, -9044, -9608,-10122,-10485,-10653,-10627,-10478,-10336,-10339,-10556,-10968,-11508,-12100,-12686,-13226,-13673,-13972,-14080,-14008,-13804,-13521,-13193,-12846,-12497, },
	/* LAT: -40 */ { -11240,-10892,-10546,-10201, -9862, -9523, -9162, -8736, -8215, -7648, -7219, -7171, -7626, -8446, -9368,-10200,-10862,-11302,-11449,-11288,-10948,-10673,-10661,-10938,-11397,-11901,-12348,-12673,-12833,-12839,-12749,-12611,-12431,-12199,-11913,-11585,-11240, },
	/* LAT: -30 */ {  -9601, -9225, -8847, -8458, -8065, -7689, -7332, -6940, -6426, -5814, -5358, -5433, -6193, -7392, -8643, -9741,-10659,-11374,-11780,-11779,-11412,-10905,-10567,-10563,-10811,-11133,-11391,-11506,-11445,-11270,-11094,-10959,-10811,-10604,-10323, -9978, -9601, },
	/* LAT: -20 */ {  -7370, -6934, -6519, -6092, -5648, -5217, -4825, -4409, -3842, -3155, -2702, -2953, -4053, -5660, -7290, -8664, -9735,-10516,-10961,-11003,-10645,-10034, -9475, -9227, -9273, -9435, -9577, -9597, -9426, -9153, -8958, -8869, -8763, -8554, -8237, -7826, -7370, },
	/* LAT: -10 */ {  -4414, -3883, -3433, -2998, -2541, -2090, -1674, -1217,  -587,   119,   487,    70, -1248, -3160, -5137, -6752, -7857, -8497, -8768, -8710, -8306, -7626, -6962, -6613, -6572, -6665, -6783, -6808, -6621, -6325, -6168, -6174, -6131, -5913, -5529, -5003, -4414, },
	/* LAT:   0 */ {   -905,  -287,   173,   574,   991,  1409,  1800,  2248,  2836,  3417,  3625,  3138,  1852,   -52, -2097, -3755, -4772, -5208, -5271, -5104, -4668, -3957, -3252, -2878, -2817, -2887, -3013, -3087, -2958, -2722, -2665, -2804, -2862, -2673, -2249, -1622,  -905, },
	/* LAT:  10 */ {   2563,  3183,  3614,  3952,  4307,  4674,  5028,  5419,  5875,  6248,  6289,  5807,  4732,  3171,  1480,    99,  -713,  -967,  -880,  -646,  -238,   397,  1029,  1368,  1431,  1385,  1283,  1192,  1235,  1339,  1266,  1004,   816,   891,  1243,  1843,  2563, },
	/* LAT:  20 */ {   5417,  5941,  6318,  6612,  6925,  7268,  7613,  7963,  8300,  8503,  8419,  7961,  7130,  6037,  4911,  3999,  3465,  3342,  3488,  3730,  4059,  4522,  4981,  5237,  5293,  5274,  5224,  5167,  5157,  5140,  4968,  4639,  4345,  4257,  4429,  4850,  5417, },
	/* LAT:  30 */ {   7569,  7940,  8256,  8538,  8847,  9194,  9553,  9896, 10176, 10292, 10150,  9731,  9104,  8394,  7732,  7219,  6925,  6880,  7020,  7229,  7475,  7773,  8061,  8234,  8291,  8302,  8304,  8294,  8273,  8192,  7972,  7622,  7268,  7049,  7033,  7226,  7569, },
	/* LAT:  40 */ {   9266,  9486,  9742, 10027, 10353, 10715, 11084, 11424, 11678, 11762, 11615, 11256, 10784, 10310,  9913,  9628,  9478,  9472,  9580,  9740,  9915, 10098, 10269, 10394, 10472, 10531, 10585, 10618, 10603, 10494, 10254,  9905,  9539,  9255,  9112,  9124,  9266, },
	/* LAT:  50 */ {  10801, 10923, 11124, 11394, 11718, 12073, 12428, 12746, 12969, 13029, 12891, 12594, 12229, 11883, 11607, 11419, 11325, 11320, 11385, 11487, 11600, 11715, 11831, 11947, 12064, 12186, 12299, 12371, 12363, 12240, 11995, 11668, 11329, 11044, 10855, 10775, 10801, },
	/* LAT:  60 */ {  12319, 12392, 12543, 12762, 13033, 13334, 13637, 13904, 14081, 14109, 13973, 13724, 13434, 13162, 12941, 12784, 12692, 12660, 12675, 12722, 12789, 12873, 12979, 13110, 13269, 13444, 13609, 13718, 13726, 13607, 13383, 13105, 12826, 12589, 12418, 12327, 12319, },
	/* LAT:  70 */ {  13758, 13802, 13898, 14041, 14221, 14426, 14635, 14816, 14921, 14900, 14762, 14560, 14341, 14137, 13963, 13828, 13733, 13678, 13658, 13671, 13712, 13784, 13886, 14022, 14189, 14375, 14559, 14701, 14748, 14677, 14516, 14318, 14123, 13958, 13838, 13770, 13758, },
	/* LAT:  80 */ {  14999, 15012, 15051, 15111, 15188, 15274, 15353, 15399, 15379, 15299, 15185, 15060, 14937, 14823, 14723, 14640, 14578, 14537, 14518, 14522, 14548, 14597, 14668, 14761, 14872, 14999, 15134, 15266, 15373, 15418, 15380, 15295, 15200, 15116, 15052, 15013, 14999, },
	/* LAT:  90 */ {  15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, 15394, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2022.0767,
static constexpr const int16_t strength_table[19][37] {
	//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
	/* LAT: -90 */ {  5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, 5454, },
	/* LAT: -80 */ {  6060, 5997, 5919, 5827, 5724, 5613, 5495, 5373, 5251, 5131, 5017, 4911, 4817, 4738, 4674, 4629, 4605, 4602, 4624, 4669, 4740, 4833, 4948, 5079, 5223, 5372, 5522, 5665, 5796, 5910, 6003, 6072, 6116, 6136, 6132, 6106, 6060, },
	/* LAT: -70 */ {  6305, 6172, 6023, 5858, 5680, 5488, 5283, 5068, 4849, 4634, 4431, 4248, 4090, 3959, 3855, 3778, 3731, 3718, 3746, 3822, 3949, 4129, 4356, 4624, 4918, 5226, 5529, 5813, 6063, 6267, 6418, 6514, 6556, 6549, 6500, 6416, 6305, },
	/* LAT: -60 */ {  6190, 5999, 5798, 5589, 5371, 5137, 4880, 4602, 4310, 4020, 3752, 3525, 3345, 3210, 3111, 3037, 2987, 2966, 2992, 3082, 3249, 3500, 3826, 4211, 4633, 5067, 5488, 5872, 6197, 6446, 6610, 6689, 6691, 6629, 6516, 6366, 6190, },
	/* LAT: -50 */ {  5846, 5617, 5386, 5156, 4924, 4679, 4409, 4106, 3777, 3445, 3142, 2902, 2740, 2648, 2600, 2565, 2532, 2506, 2511, 2583, 2755, 3043, 3438, 3908, 4414, 4920, 5395, 5815, 6154, 6396, 6535, 6576, 6534, 6425, 6263, 6066, 5846, },
	/* LAT: -40 */ {  5395, 5150, 4905, 4666, 4432, 4196, 3941, 3657, 3343, 3017, 2718, 2495, 2377, 2350, 2370, 2391, 2397, 2386, 2374, 2402, 2530, 2803, 3218, 3730, 4277, 4801, 5269, 5658, 5951, 6139, 6228, 6231, 6162, 6032, 5851, 5633, 5395, },
	/* LAT: -30 */ {  4880, 4639, 4401, 4167, 3941, 3723, 3504, 3273, 3017, 2742, 2484, 2301, 2229, 2253, 2320, 2392, 2458, 2509, 2532, 2545, 2610, 2806, 3165, 3651, 4182, 4680, 5100, 5418, 5621, 5722, 5748, 5722, 5643, 5511, 5332, 5116, 4880, },
	/* LAT: -20 */ {  4322, 4110, 3902, 3697, 3501, 3319, 3151, 2987, 2810, 2612, 2422, 2287, 2244, 2286, 2375, 2486, 2614, 2743, 2833, 2871, 2895, 2989, 3225, 3606, 4056, 4483, 4833, 5070, 5176, 5184, 5154, 5107, 5024, 4897, 4731, 4534, 4322, },
	/* LAT: -10 */ {  3790, 3630, 3478, 3332, 3196, 3076, 2973, 2882, 2785, 2671, 2550, 2450, 2403, 2425, 2510, 2638, 2794, 2954, 3079, 3143, 3157, 3183, 3304, 3553, 3878, 4200, 4466, 4630, 4667, 4615, 4547, 4483, 4394, 4270, 4121, 3957, 3790, },
	/* LAT:   0 */ {  3412, 3320, 3236, 3164, 3109, 3071, 3045, 3027, 3004, 2956, 2878, 2783, 2701, 2668, 2708, 2810, 2942, 3078, 3194, 3270, 3302, 3323, 3397, 3552, 3760, 3973, 4154, 4261, 4268, 4201, 4113, 4020, 3908, 3777, 3643, 3519, 3412, },
	/* LAT:  10 */ {  3283, 3252, 3232, 3229, 3254, 3302, 3358, 3412, 3448, 3439, 3370, 3256, 3128, 3032, 3003, 3043, 3123, 3222, 3322, 3407, 3471, 3533, 3621, 3738, 3872, 4010, 4130, 4201, 4204, 4143, 4033, 3890, 3729, 3570, 3434, 3338, 3283, },
	/* LAT:  20 */ {  3400, 3403, 3430, 3485, 3577, 3699, 3828, 3946, 4028, 4041, 3968, 3826, 3658, 3517, 3439, 3425, 3459, 3531, 3627, 3724, 3815, 3913, 4023, 4134, 4243, 4353, 4455, 4521, 4533, 4475, 4339, 4137, 3910, 3701, 3538, 3438, 3400, },
	/* LAT:  30 */ {  3723, 3731, 3786, 3886, 4030, 4202, 4378, 4535, 4644, 4670, 4598, 4442, 4252, 4086, 3979, 3932, 3934, 3984, 4070, 4168, 4265, 4370, 4486, 4604, 4723, 4849, 4969, 5055, 5082, 5026, 4870, 4631, 4358, 4104, 3904, 3777, 3723, },
	/* LAT:  40 */ {  4222, 4222, 4288, 4413, 4580, 4768, 4952, 5109, 5214, 5240, 5171, 5022, 4834, 4659, 4529, 4453, 4426, 4447, 4506, 4585, 4671, 4767, 4882, 5015, 5166, 5327, 5479, 5589, 5629, 5576, 5421, 5184, 4910, 4650, 4440, 4295, 4222, },
	/* LAT:  50 */ {  4832, 4826, 4883, 4994, 5141, 5301, 5451, 5572, 5645, 5654, 5591, 5463, 5299, 5135, 4996, 4898, 4842, 4830, 4854, 4903, 4972, 5062, 5181, 5331, 5506, 5690, 5857, 5975, 6020, 5977, 5847, 5651, 5426, 5210, 5030, 4901, 4832, },
	/* LAT:  60 */ {  5392, 5381, 5411, 5475, 5561, 5656, 5742, 5808, 5841, 5831, 5777, 5682, 5561, 5432, 5312, 5215, 5148, 5114, 5111, 5138, 5194, 5280, 5398, 5545, 5711, 5880, 6028, 6132, 6177, 6155, 6073, 5947, 5800, 5657, 5534, 5444, 5392, },
	/* LAT:  70 */ {  5726, 5707, 5705, 5718, 5741, 5767, 5790, 5805, 5804, 5784, 5744, 5686, 5615, 5539, 5465, 5400, 5352, 5324, 5319, 5338, 5383, 5452, 5543, 5652, 5769, 5884, 5983, 6056, 6096, 6100, 6071, 6017, 5950, 5880, 5815, 5762, 5726, },
	/* LAT:  80 */ {  5789, 5772, 5758, 5746, 5736, 5727, 5717, 5705, 5690, 5671, 5649, 5624, 5596, 5569, 5544, 5523, 5509, 5504, 5508, 5524, 5549, 5584, 5627, 5675, 5725, 5773, 5815, 5850, 5874, 5888, 5890, 5883, 5869, 5850, 5829, 5809, 5789, },
	/* LAT:  90 */ {  5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, },
};
