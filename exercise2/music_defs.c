#include "music_defs.h"

static note_t note_silence = { .length = 1, .samples = { 0 } };

static note_t note_c5 = { .length = 62, .samples = { 2048, 2255, 2460, 2661, 2855, 3041, 3217, 3382, 3532, 3667, 3786, 3886, 3968, 4030, 4072, 4093, 4093, 4072, 4030, 3968, 3886, 3786, 3667, 3532, 3382, 3217, 3041, 2855, 2661, 2460, 2255, 2048, 1840, 1635, 1434, 1240, 1054, 878, 713, 563, 428, 309, 209, 127, 65, 23, 2, 2, 23, 65, 127, 209, 309, 428, 563, 713, 878, 1054, 1240, 1434, 1635, 1840 } };

static note_t note_d5 = { .length = 55, .samples = { 2048, 2281, 2511, 2736, 2951, 3155, 3344, 3516, 3669, 3801, 3910, 3995, 4055, 4088, 4095, 4075, 4028, 3956, 3859, 3738, 3595, 3432, 3251, 3055, 2845, 2624, 2397, 2164, 1931, 1698, 1471, 1250, 1040, 844, 663, 500, 357, 236, 139, 67, 20, 0, 7, 40, 100, 185, 294, 426, 579, 751, 940, 1144, 1359, 1584, 1814 } };

static note_t note_e5 = { .length = 49, .samples = { 2048, 2309, 2567, 2816, 3052, 3272, 3472, 3649, 3799, 3920, 4011, 4069, 4094, 4086, 4044, 3969, 3863, 3727, 3564, 3375, 3165, 2936, 2693, 2439, 2179, 1916, 1656, 1402, 1159, 930, 720, 531, 368, 232, 126, 51, 9, 1, 26, 84, 175, 296, 446, 623, 823, 1043, 1279, 1528, 1786 } };

static note_t note_f5 = { .length = 46, .samples = { 2048, 2326, 2600, 2863, 3112, 3340, 3544, 3721, 3866, 3977, 4053, 4091, 4091, 4053, 3977, 3866, 3721, 3544, 3340, 3112, 2863, 2600, 2326, 2048, 1769, 1495, 1232, 983, 755, 551, 374, 229, 118, 42, 4, 4, 42, 118, 229, 374, 551, 755, 983, 1232, 1495, 1769 } };

static note_t note_g5 = { .length = 41, .samples = { 2048, 2360, 2665, 2956, 3226, 3468, 3676, 3847, 3975, 4058, 4094, 4082, 4022, 3916, 3767, 3576, 3351, 3094, 2813, 2514, 2204, 1891, 1581, 1282, 1001, 744, 519, 328, 179, 73, 13, 1, 37, 120, 248, 419, 627, 869, 1139, 1430, 1735 } };

static note_t note_a5 = { .length = 37, .samples = { 2048, 2394, 2730, 3046, 3334, 3585, 3791, 3948, 4050, 4094, 4079, 4006, 3876, 3694, 3465, 3194, 2891, 2564, 2221, 1874, 1531, 1204, 901, 630, 401, 219, 89, 16, 1, 45, 147, 304, 510, 761, 1049, 1365, 1701 } };

song_t lisa_gikk_til_skolen = {
    .length = 37,
    .parts = {
        { .duration = 16384, .note = &note_c5 },
        { .duration = 16384, .note = &note_d5 },
        { .duration = 16384, .note = &note_e5 },
        { .duration = 16384, .note = &note_f5 },
        { .duration = 31129, .note = &note_g5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 31129, .note = &note_g5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_a5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_a5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_a5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_a5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 63897, .note = &note_g5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_f5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_f5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_f5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_f5 },
        { .duration = 31129, .note = &note_e5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 31129, .note = &note_e5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_d5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_d5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_d5 },
        { .duration = 1638, .note = &note_silence },
        { .duration = 14745, .note = &note_d5 },
        { .duration = 65536, .note = &note_c5 },
    }
};

