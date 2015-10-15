#include "music_defs.h"

static note_t note_a4 = { .length = 74, .samples = { 2048, 2221, 2394, 2564, 2730, 2891, 3046, 3194, 3334, 3465, 3585, 3694, 3791, 3876, 3948, 4006, 4050, 4079, 4094, 4094, 4079, 4050, 4006, 3948, 3876, 3791, 3694, 3585, 3465, 3334, 3194, 3046, 2891, 2730, 2564, 2394, 2221, 2048, 1874, 1701, 1531, 1365, 1204, 1049, 901, 761, 630, 510, 401, 304, 219, 147, 89, 45, 16, 1, 1, 16, 45, 89, 147, 219, 304, 401, 510, 630, 761, 901, 1049, 1204, 1365, 1531, 1701, 1874 } };
static note_t note_bflat = { .length = 70, .samples = { 2048, 2231, 2413, 2592, 2767, 2936, 3098, 3251, 3395, 3528, 3649, 3757, 3851, 3931, 3995, 4044, 4077, 4093, 4093, 4077, 4044, 3995, 3931, 3851, 3757, 3649, 3528, 3395, 3251, 3098, 2936, 2767, 2592, 2413, 2231, 2048, 1864, 1682, 1503, 1328, 1159, 997, 844, 700, 567, 446, 338, 244, 164, 100, 51, 18, 2, 2, 18, 51, 100, 164, 244, 338, 446, 567, 700, 844, 997, 1159, 1328, 1503, 1682, 1864 } };
static note_t note_b = { .length = 66, .samples = { 2048, 2242, 2435, 2624, 2809, 2986, 3155, 3313, 3461, 3595, 3716, 3821, 3910, 3983, 4038, 4075, 4093, 4093, 4075, 4038, 3983, 3910, 3821, 3716, 3595, 3461, 3313, 3155, 2986, 2809, 2624, 2435, 2242, 2048, 1853, 1660, 1471, 1286, 1109, 940, 782, 634, 500, 379, 274, 185, 112, 57, 20, 2, 2, 20, 57, 112, 185, 274, 379, 500, 634, 782, 940, 1109, 1286, 1471, 1660, 1853 } };
static note_t note_c = { .length = 62, .samples = { 2048, 2255, 2460, 2661, 2855, 3041, 3217, 3382, 3532, 3667, 3786, 3886, 3968, 4030, 4072, 4093, 4093, 4072, 4030, 3968, 3886, 3786, 3667, 3532, 3382, 3217, 3041, 2855, 2661, 2460, 2255, 2048, 1840, 1635, 1434, 1240, 1054, 878, 713, 563, 428, 309, 209, 127, 65, 23, 2, 2, 23, 65, 127, 209, 309, 428, 563, 713, 878, 1054, 1240, 1434, 1635, 1840 } };static note_t note_csharp = { .length = 59, .samples = { 2048, 2265, 2480, 2691, 2894, 3087, 3269, 3437, 3589, 3723, 3839, 3934, 4008, 4060, 4089, 4095, 4077, 4037, 3974, 3889, 3784, 3658, 3515, 3355, 3180, 2992, 2793, 2586, 2373, 2156, 1939, 1722, 1509, 1302, 1103, 915, 740, 580, 437, 311, 206, 121, 58, 18, 0, 6, 35, 87, 161, 256, 372, 506, 658, 826, 1008, 1201, 1404, 1615, 1830 } };
static note_t note_d = { .length = 55, .samples = { 2048, 2281, 2511, 2736, 2951, 3155, 3344, 3516, 3669, 3801, 3910, 3995, 4055, 4088, 4095, 4075, 4028, 3956, 3859, 3738, 3595, 3432, 3251, 3055, 2845, 2624, 2397, 2164, 1931, 1698, 1471, 1250, 1040, 844, 663, 500, 357, 236, 139, 67, 20, 0, 7, 40, 100, 185, 294, 426, 579, 751, 940, 1144, 1359, 1584, 1814 } };
static note_t note_dsharp = { .length = 52, .samples = { 2048, 2294, 2538, 2774, 2999, 3211, 3406, 3580, 3733, 3861, 3962, 4036, 4081, 4096, 4081, 4036, 3962, 3861, 3733, 3580, 3406, 3211, 2999, 2774, 2538, 2294, 2048, 1801, 1557, 1321, 1096, 884, 689, 515, 362, 234, 133, 59, 14, 0, 14, 59, 133, 234, 362, 515, 689, 884, 1096, 1321, 1557, 1801 } };
static note_t note_e = { .length = 49, .samples = { 2048, 2309, 2567, 2816, 3052, 3272, 3472, 3649, 3799, 3920, 4011, 4069, 4094, 4086, 4044, 3969, 3863, 3727, 3564, 3375, 3165, 2936, 2693, 2439, 2179, 1916, 1656, 1402, 1159, 930, 720, 531, 368, 232, 126, 51, 9, 1, 26, 84, 175, 296, 446, 623, 823, 1043, 1279, 1528, 1786 } };
static note_t note_f = { .length = 46, .samples = { 2048, 2326, 2600, 2863, 3112, 3340, 3544, 3721, 3866, 3977, 4053, 4091, 4091, 4053, 3977, 3866, 3721, 3544, 3340, 3112, 2863, 2600, 2326, 2048, 1769, 1495, 1232, 983, 755, 551, 374, 229, 118, 42, 4, 4, 42, 118, 229, 374, 551, 755, 983, 1232, 1495, 1769 } };
static note_t note_fsharp = { .length = 44, .samples = { 2048, 2339, 2624, 2898, 3155, 3389, 3595, 3770, 3910, 4013, 4075, 4096, 4075, 4013, 3910, 3770, 3595, 3389, 3155, 2898, 2624, 2339, 2048, 1756, 1471, 1197, 940, 706, 500, 325, 185, 82, 20, 0, 20, 82, 185, 325, 500, 706, 940, 1197, 1471, 1756 } };
static note_t note_g = { .length = 41, .samples = { 2048, 2360, 2665, 2956, 3226, 3468, 3676, 3847, 3975, 4058, 4094, 4082, 4022, 3916, 3767, 3576, 3351, 3094, 2813, 2514, 2204, 1891, 1581, 1282, 1001, 744, 519, 328, 179, 73, 13, 1, 37, 120, 248, 419, 627, 869, 1139, 1430, 1735 } };
static note_t note_aflat = { .length = 39, .samples = { 2048, 2376, 2696, 2999, 3278, 3525, 3733, 3898, 4015, 4081, 4094, 4054, 3962, 3821, 3634, 3406, 3142, 2850, 2538, 2212, 1883, 1557, 1245, 953, 689, 461, 274, 133, 41, 1, 14, 80, 197, 362, 570, 817, 1096, 1399, 1719 } };
static note_t note_a5 = { .length = 37, .samples = { 2048, 2394, 2730, 3046, 3334, 3585, 3791, 3948, 4050, 4094, 4079, 4006, 3876, 3694, 3465, 3194, 2891, 2564, 2221, 1874, 1531, 1204, 901, 630, 401, 219, 89, 16, 1, 45, 147, 304, 510, 761, 1049, 1365, 1701 } };

song_t scale = {
    .length = 13,
    .parts = {
        { .duration = 8192, .note = &note_a4 },
        { .duration = 8192, .note = &note_b },
        { .duration = 8192, .note = &note_bflat },
        { .duration = 8192, .note = &note_c },
        { .duration = 8192, .note = &note_csharp },
        { .duration = 8192, .note = &note_d },
        { .duration = 8192, .note = &note_dsharp },
        { .duration = 8192, .note = &note_e },
        { .duration = 8192, .note = &note_f },
        { .duration = 8192, .note = &note_fsharp },
        { .duration = 8192, .note = &note_g },
        { .duration = 8192, .note = &note_aflat },
        { .duration = 8192, .note = &note_a5 },
    }
};

