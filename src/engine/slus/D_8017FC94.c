#include "slus.h"

/*
 * per-map rectangle lists: each record is a tile rectangle (x0,y0)-(x1,y1) plus the encounter row,
 * kind, seed and picker flag the field code reads once the rectangle covers the party; D_80181164 selects
 * the first record of each list and the scan ends at the rectangle that covers the point.
 */
const EncounterZone g_AreaEncounterZones[MAP_ZONE_COUNT] = {
    /* list 0 */
    ENCOUNTER_ZONE(2, 2, 39, 38, 2, 0, 1, 1),
    ENCOUNTER_ZONE(1, 68, 12, 77, 0, 1, 1, 1),
    ENCOUNTER_ZONE(28, 66, 34, 77, 0, 2, 1, 1),
    ENCOUNTER_ZONE(50, 66, 61, 77, 0, 3, 1, 1),
    ENCOUNTER_ZONE(91, 68, 97, 77, 0, 4, 1, 1),
    ENCOUNTER_ZONE(91, 41, 97, 52, 0, 5, 1, 1),
    ENCOUNTER_ZONE(86, 13, 97, 22, 0, 6, 1, 1),
    ENCOUNTER_ZONE(52, 1, 63, 10, 0, 7, 1, 1),
    /* list 1 */
    ENCOUNTER_ZONE(1, 1, 57, 57, 0, 0, 110, 0),
    ENCOUNTER_ZONE(76, 50, 86, 59, 0, 1, 110, 0),
    ENCOUNTER_ZONE(76, 26, 86, 35, 0, 2, 110, 0),
    ENCOUNTER_ZONE(74, 2, 86, 11, 0, 3, 110, 0),
    /* list 2 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 0, 0, 2, 0),
    /* list 3 */
    ENCOUNTER_ZONE(2, 2, 56, 57, 2, 0, 5, 0),
    ENCOUNTER_ZONE(74, 49, 81, 56, 0, 1, 5, 0),
    ENCOUNTER_ZONE(72, 23, 84, 33, 0, 2, 5, 0),
    /* list 4 */
    ENCOUNTER_ZONE(1, 1, 37, 84, 0, 0, 8, 1),
    ENCOUNTER_ZONE(47, 47, 80, 76, 0, 1, 7, 1),
    ENCOUNTER_ZONE(47, 1, 82, 28, 0, 2, 7, 1),
    /* list 5 */
    ENCOUNTER_ZONE(1, 2, 59, 48, 2, 0, 7, 0),
    ENCOUNTER_ZONE(76, 32, 89, 42, 0, 1, 7, 0),
    ENCOUNTER_ZONE(77, 4, 88, 11, 0, 2, 7, 0),
    ENCOUNTER_ZONE(111, 27, 114, 44, 0, 3, 7, 0),
    ENCOUNTER_ZONE(104, 4, 114, 9, 0, 4, 7, 0),
    /* list 6 */
    ENCOUNTER_ZONE(1, 3, 87, 48, 2, 0, 5, 0),
    /* list 7 */
    ENCOUNTER_ZONE(2, 2, 39, 38, 2, 0, 0, 0),
    ENCOUNTER_ZONE(1, 68, 12, 77, 0, 1, 0, 0),
    ENCOUNTER_ZONE(28, 66, 34, 77, 0, 2, 0, 0),
    ENCOUNTER_ZONE(50, 66, 61, 77, 0, 3, 0, 0),
    ENCOUNTER_ZONE(91, 68, 97, 77, 0, 4, 0, 0),
    ENCOUNTER_ZONE(91, 41, 97, 52, 0, 5, 0, 0),
    ENCOUNTER_ZONE(86, 13, 97, 22, 0, 6, 0, 0),
    ENCOUNTER_ZONE(52, 1, 63, 10, 0, 7, 0, 0),
    /* list 8 */
    ENCOUNTER_ZONE(2, 2, 56, 57, 2, 0, 10, 0),
    ENCOUNTER_ZONE(74, 49, 81, 56, 0, 1, 10, 0),
    ENCOUNTER_ZONE(72, 23, 84, 33, 0, 2, 10, 0),
    /* list 9 */
    ENCOUNTER_ZONE(1, 3, 87, 48, 2, 0, 10, 0),
    /* list 10 */
    ENCOUNTER_ZONE(1, 2, 59, 47, 2, 0, 7, 0),
    ENCOUNTER_ZONE(78, 32, 89, 42, 0, 1, 7, 0),
    ENCOUNTER_ZONE(77, 4, 88, 11, 0, 2, 7, 0),
    ENCOUNTER_ZONE(93, 17, 97, 21, 0, 0, 7, 0),
    ENCOUNTER_ZONE(103, 3, 114, 9, 0, 3, 7, 0),
    ENCOUNTER_ZONE(111, 27, 114, 44, 0, 4, 7, 0),
    ENCOUNTER_ZONE(0, 0, 255, 255, 0, 0, 7, 0),
    /* list 11 */
    ENCOUNTER_ZONE(1, 2, 59, 48, 0, 0, 12, 0),
    ENCOUNTER_ZONE(76, 32, 89, 42, 0, 1, 12, 0),
    ENCOUNTER_ZONE(77, 4, 88, 11, 0, 2, 12, 0),
    ENCOUNTER_ZONE(111, 27, 114, 44, 0, 3, 12, 0),
    ENCOUNTER_ZONE(104, 4, 114, 9, 0, 4, 12, 0),
    /* list 12 */
    ENCOUNTER_ZONE(1, 2, 59, 48, 2, 0, 6, 1),
    ENCOUNTER_ZONE(76, 32, 89, 42, 0, 1, 6, 1),
    ENCOUNTER_ZONE(77, 4, 88, 11, 0, 2, 6, 1),
    ENCOUNTER_ZONE(111, 27, 114, 44, 0, 3, 6, 1),
    ENCOUNTER_ZONE(104, 4, 114, 9, 0, 4, 6, 1),
    /* list 13 */
    ENCOUNTER_ZONE(2, 3, 77, 65, 0, 0, 16, 0),
    ENCOUNTER_ZONE(4, 80, 12, 87, 0, 1, 16, 0),
    /* list 14 */
    ENCOUNTER_ZONE(2, 3, 77, 65, 0, 0, 16, 0),
    ENCOUNTER_ZONE(4, 80, 12, 87, 0, 1, 16, 0),
    /* list 15 */
    ENCOUNTER_ZONE(0, 0, 10, 12, 0, 1, 16, 0),
    ENCOUNTER_ZONE(0, 34, 17, 83, 2, 0, 16, 0),
    ENCOUNTER_ZONE(18, 0, 78, 83, 2, 0, 16, 0),
    /* list 16 */
    ENCOUNTER_ZONE(1, 1, 255, 255, 5, 0, 2, 1),
    /* list 17 */
    ENCOUNTER_ZONE(0, 0, 10, 12, 0, 1, 16, 0),
    ENCOUNTER_ZONE(0, 34, 17, 83, 0, 0, 16, 0),
    ENCOUNTER_ZONE(18, 0, 78, 83, 0, 0, 16, 0),
    /* list 18 */
    ENCOUNTER_ZONE(2, 3, 58, 77, 2, 0, 2, 1),
    /* list 19 */
    ENCOUNTER_ZONE(2, 3, 58, 77, 2, 0, 19, 0),
    /* list 20 */
    ENCOUNTER_ZONE(2, 2, 51, 51, 3, 0, 3, 1),
    /* list 21 */
    ENCOUNTER_ZONE(6, 8, 53, 46, 0, 0, 5, 1),
    ENCOUNTER_ZONE(64, 2, 77, 11, 0, 1, 5, 1),
    /* list 22 */
    ENCOUNTER_ZONE(1, 1, 34, 80, 3, 0, 24, 0),
    ENCOUNTER_ZONE(35, 1, 43, 49, 3, 0, 24, 0),
    ENCOUNTER_ZONE(51, 1, 71, 24, 0, 1, 24, 0),
    ENCOUNTER_ZONE(76, 1, 97, 32, 0, 2, 24, 0),
    ENCOUNTER_ZONE(36, 55, 49, 79, 3, 3, 24, 0),
    ENCOUNTER_ZONE(55, 37, 70, 73, 3, 4, 24, 0),
    ENCOUNTER_ZONE(73, 60, 100, 77, 3, 5, 24, 0),
    /* list 23 */
    ENCOUNTER_ZONE(1, 3, 42, 99, 2, 0, 27, 0),
    ENCOUNTER_ZONE(42, 34, 75, 100, 2, 0, 27, 0),
    ENCOUNTER_ZONE(69, 3, 77, 12, 0, 1, 27, 0),
    /* list 24 */
    ENCOUNTER_ZONE(0, 0, 73, 79, 0, 0, 255, 0),
    ENCOUNTER_ZONE(88, 1, 120, 34, 0, 1, 255, 0),
    ENCOUNTER_ZONE(132, 16, 160, 39, 0, 2, 255, 0),
    ENCOUNTER_ZONE(190, 0, 198, 16, 0, 3, 255, 0),
    ENCOUNTER_ZONE(160, 16, 188, 39, 0, 4, 255, 0),
    /* list 25 */
    ENCOUNTER_ZONE(5, 2, 21, 97, 0, 0, 255, 0),
    ENCOUNTER_ZONE(38, 2, 43, 97, 0, 1, 255, 0),
    /* list 26 */
    ENCOUNTER_ZONE(21, 1, 79, 94, 0, 0, 30, 0),
    ENCOUNTER_ZONE(2, 2, 13, 16, 0, 1, 30, 0),
    /* list 27 */
    ENCOUNTER_ZONE(2, 1, 41, 76, 2, 0, 33, 0),
    ENCOUNTER_ZONE(48, 1, 78, 37, 2, 1, 33, 0),
    ENCOUNTER_ZONE(48, 1, 78, 74, 2, 2, 33, 0),
    ENCOUNTER_ZONE(90, 3, 96, 10, 2, 3, 33, 0),
    ENCOUNTER_ZONE(90, 69, 96, 76, 0, 4, 33, 0),
    /* list 28 */
    ENCOUNTER_ZONE(2, 1, 78, 62, 2, 0, 38, 0),
    ENCOUNTER_ZONE(2, 85, 77, 97, 0, 1, 35, 0),
    /* list 29 */
    ENCOUNTER_ZONE(2, 2, 51, 51, 3, 0, 3, 1),
    /* list 30 */
    ENCOUNTER_ZONE(1, 1, 30, 70, 0, 0, 40, 0),
    /* list 31 */
    ENCOUNTER_ZONE(0, 0, 10, 210, 0, 0, 3, 0),
    /* list 32 */
    ENCOUNTER_ZONE(0, 0, 73, 79, 0, 0, 107, 0),
    ENCOUNTER_ZONE(88, 1, 120, 34, 0, 1, 107, 0),
    ENCOUNTER_ZONE(132, 16, 160, 39, 0, 2, 107, 0),
    ENCOUNTER_ZONE(190, 0, 198, 16, 0, 3, 107, 0),
    ENCOUNTER_ZONE(160, 16, 188, 39, 0, 4, 107, 0),
    ENCOUNTER_ZONE(1, 1, 255, 255, 0, 5, 255, 0),
    /* list 33 */
    ENCOUNTER_ZONE(1, 1, 255, 255, 5, 0, 19, 0),
    /* list 34 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 0, 0, 107, 0),
    /* list 35 */
    ENCOUNTER_ZONE(0, 0, 82, 84, 2, 0, 44, 0),
    /* list 36 */
    ENCOUNTER_ZONE(0, 0, 43, 43, 2, 0, 2, 1),
    ENCOUNTER_ZONE(62, 0, 77, 13, 2, 1, 2, 1),
    ENCOUNTER_ZONE(64, 28, 79, 43, 2, 2, 123, 0),
    /* list 37 */
    ENCOUNTER_ZONE(1, 1, 60, 67, 0, 0, 45, 0),
    ENCOUNTER_ZONE(75, 1, 86, 9, 0, 1, 45, 0),
    ENCOUNTER_ZONE(73, 24, 85, 30, 0, 2, 45, 0),
    ENCOUNTER_ZONE(75, 56, 87, 68, 0, 3, 45, 0),
    ENCOUNTER_ZONE(99, 1, 112, 13, 0, 4, 45, 0),
    ENCOUNTER_ZONE(100, 28, 112, 34, 0, 5, 45, 0),
    ENCOUNTER_ZONE(100, 48, 112, 55, 0, 6, 45, 0),
    ENCOUNTER_ZONE(100, 56, 112, 62, 0, 7, 45, 0),
    ENCOUNTER_ZONE(100, 63, 112, 68, 0, 8, 45, 0),
    /* list 38 */
    ENCOUNTER_ZONE(1, 1, 50, 59, 0, 0, 45, 0),
    ENCOUNTER_ZONE(63, 1, 73, 13, 0, 1, 45, 0),
    ENCOUNTER_ZONE(87, 1, 100, 19, 0, 2, 45, 0),
    ENCOUNTER_ZONE(115, 1, 128, 19, 0, 3, 45, 0),
    ENCOUNTER_ZONE(63, 25, 74, 36, 0, 4, 45, 0),
    ENCOUNTER_ZONE(85, 45, 97, 58, 0, 5, 45, 0),
    ENCOUNTER_ZONE(110, 40, 128, 58, 0, 6, 45, 0),
    /* list 39 */
    ENCOUNTER_ZONE(2, 1, 50, 78, 0, 0, 46, 0),
    ENCOUNTER_ZONE(63, 1, 74, 12, 0, 1, 46, 0),
    ENCOUNTER_ZONE(87, 12, 98, 23, 0, 2, 46, 0),
    ENCOUNTER_ZONE(63, 25, 74, 36, 0, 3, 46, 0),
    ENCOUNTER_ZONE(86, 37, 98, 53, 0, 4, 46, 0),
    ENCOUNTER_ZONE(62, 47, 72, 56, 0, 5, 46, 0),
    ENCOUNTER_ZONE(63, 68, 72, 78, 0, 6, 46, 0),
    ENCOUNTER_ZONE(86, 62, 98, 78, 0, 7, 46, 0),
    /* list 40 */
    ENCOUNTER_ZONE(2, 5, 35, 38, 3, 0, 48, 0),
    ENCOUNTER_ZONE(48, 1, 71, 20, 3, 1, 48, 0),
    ENCOUNTER_ZONE(75, 1, 90, 29, 3, 2, 48, 0),
    ENCOUNTER_ZONE(103, 1, 131, 37, 3, 3, 48, 0),
    ENCOUNTER_ZONE(144, 1, 152, 10, 3, 4, 48, 0),
    ENCOUNTER_ZONE(170, 1, 186, 17, 0, 5, 48, 0),
    ENCOUNTER_ZONE(144, 28, 154, 39, 0, 6, 48, 0),
    ENCOUNTER_ZONE(170, 30, 181, 38, 3, 7, 48, 0),
    /* list 41 */
    ENCOUNTER_ZONE(1, 1, 21, 24, 0, 0, 46, 0),
    ENCOUNTER_ZONE(26, 7, 45, 53, 0, 1, 49, 0),
    ENCOUNTER_ZONE(46, 7, 61, 18, 0, 1, 49, 0),
    ENCOUNTER_ZONE(61, 27, 97, 53, 0, 2, 46, 0),
    ENCOUNTER_ZONE(82, 1, 112, 13, 0, 3, 49, 0),
    ENCOUNTER_ZONE(127, 1, 143, 28, 0, 4, 46, 0),
    /* list 42 */
    ENCOUNTER_ZONE(1, 1, 47, 55, 2, 0, 64, 0),
    ENCOUNTER_ZONE(61, 1, 79, 34, 2, 1, 48, 0),
    ENCOUNTER_ZONE(64, 52, 71, 59, 2, 2, 48, 0),
    ENCOUNTER_ZONE(91, 48, 127, 58, 2, 3, 48, 0),
    /* list 43 */
    ENCOUNTER_ZONE(1, 1, 43, 36, 0, 0, 12, 1),
    ENCOUNTER_ZONE(57, 4, 80, 14, 0, 1, 12, 1),
    ENCOUNTER_ZONE(78, 28, 83, 35, 0, 2, 12, 1),
    /* list 44 */
    ENCOUNTER_ZONE(1, 1, 26, 33, 3, 0, 48, 0),
    ENCOUNTER_ZONE(40, 1, 69, 20, 3, 1, 48, 0),
    ENCOUNTER_ZONE(83, 1, 109, 16, 3, 2, 48, 0),
    ENCOUNTER_ZONE(129, 1, 134, 23, 3, 3, 48, 0),
    ENCOUNTER_ZONE(148, 1, 154, 21, 3, 4, 48, 0),
    ENCOUNTER_ZONE(83, 30, 93, 38, 3, 5, 48, 0),
    ENCOUNTER_ZONE(108, 29, 118, 38, 3, 6, 48, 0),
    ENCOUNTER_ZONE(170, 30, 179, 38, 3, 7, 48, 0),
    /* list 45 */
    ENCOUNTER_ZONE(1, 1, 255, 255, 5, 0, 2, 1),
    /* list 46 */
    ENCOUNTER_ZONE(1, 1, 37, 76, 0, 0, 2, 1),
    ENCOUNTER_ZONE(51, 10, 62, 29, 0, 1, 2, 1),
    ENCOUNTER_ZONE(51, 44, 61, 53, 0, 2, 2, 1),
    /* list 47 */
    ENCOUNTER_ZONE(1, 1, 47, 58, 0, 0, 2, 1),
    ENCOUNTER_ZONE(89, 1, 131, 23, 0, 1, 39, 0),
    ENCOUNTER_ZONE(123, 50, 131, 58, 0, 2, 46, 0),
    /* list 48 */
    ENCOUNTER_ZONE(1, 1, 30, 30, 0, 0, 48, 0),
    ENCOUNTER_ZONE(48, 2, 67, 19, 3, 1, 48, 0),
    ENCOUNTER_ZONE(94, 1, 107, 33, 3, 2, 48, 0),
    ENCOUNTER_ZONE(122, 1, 141, 20, 0, 3, 48, 0),
    ENCOUNTER_ZONE(1, 40, 9, 48, 3, 4, 48, 0),
    ENCOUNTER_ZONE(69, 27, 82, 46, 3, 5, 48, 0),
    /* list 49 */
    ENCOUNTER_ZONE(1, 1, 78, 70, 0, 0, 16, 0),
    ENCOUNTER_ZONE(2, 28, 20, 94, 0, 1, 16, 0),
    ENCOUNTER_ZONE(36, 82, 47, 92, 0, 2, 16, 0),
    ENCOUNTER_ZONE(63, 82, 84, 100, 0, 3, 16, 0),
    /* list 50 */
    ENCOUNTER_ZONE(1, 1, 48, 76, 0, 0, 52, 0),
    ENCOUNTER_ZONE(1, 91, 14, 103, 0, 1, 52, 0),
    ENCOUNTER_ZONE(33, 91, 46, 103, 0, 2, 52, 0),
    ENCOUNTER_ZONE(1, 117, 14, 129, 0, 3, 52, 0),
    ENCOUNTER_ZONE(33, 117, 46, 129, 0, 4, 52, 0),
    ENCOUNTER_ZONE(1, 143, 6, 151, 0, 5, 52, 0),
    ENCOUNTER_ZONE(21, 140, 26, 148, 0, 6, 52, 0),
    ENCOUNTER_ZONE(42, 149, 47, 157, 0, 7, 52, 0),
    /* list 51 */
    ENCOUNTER_ZONE(1, 1, 48, 77, 2, 0, 54, 0),
    /* list 52 */
    ENCOUNTER_ZONE(0, 8, 56, 41, 2, 0, 56, 0),
    ENCOUNTER_ZONE(56, 21, 75, 42, 2, 1, 56, 0),
    ENCOUNTER_ZONE(91, 1, 165, 37, 2, 2, 56, 0),
    /* list 53 */
    ENCOUNTER_ZONE(0, 0, 43, 47, 0, 0, 77, 0),
    ENCOUNTER_ZONE(55, 7, 68, 18, 0, 1, 77, 0),
    /* list 54 */
    ENCOUNTER_ZONE(0, 0, 53, 59, 2, 0, 76, 0),
    /* list 55 */
    ENCOUNTER_ZONE(0, 0, 59, 39, 2, 0, 121, 0),
    /* list 56 */
    ENCOUNTER_ZONE(1, 1, 54, 58, 2, 0, 24, 0),
    ENCOUNTER_ZONE(55, 1, 79, 40, 2, 1, 24, 0),
    ENCOUNTER_ZONE(79, 45, 85, 58, 2, 2, 24, 0),
    ENCOUNTER_ZONE(86, 1, 130, 58, 2, 2, 24, 0),
    ENCOUNTER_ZONE(138, 2, 157, 54, 2, 3, 24, 0),
    /* list 57 */
    ENCOUNTER_ZONE(1, 1, 53, 84, 2, 0, 66, 0),
    ENCOUNTER_ZONE(65, 0, 92, 16, 2, 1, 66, 0),
    ENCOUNTER_ZONE(63, 28, 73, 41, 2, 2, 66, 0),
    ENCOUNTER_ZONE(83, 28, 93, 41, 2, 3, 66, 0),
    ENCOUNTER_ZONE(71, 51, 80, 62, 2, 4, 66, 0),
    ENCOUNTER_ZONE(64, 73, 73, 83, 2, 5, 66, 0),
    ENCOUNTER_ZONE(83, 73, 92, 83, 2, 6, 66, 0),
    /* list 58 */
    ENCOUNTER_ZONE(1, 1, 43, 53, 2, 0, 131, 0),
    ENCOUNTER_ZONE(54, 2, 67, 20, 2, 1, 131, 0),
    ENCOUNTER_ZONE(79, 1, 91, 23, 2, 2, 131, 0),
    ENCOUNTER_ZONE(116, 1, 143, 18, 2, 3, 131, 0),
    ENCOUNTER_ZONE(56, 35, 69, 47, 2, 4, 131, 0),
    ENCOUNTER_ZONE(81, 34, 92, 47, 2, 5, 131, 0),
    ENCOUNTER_ZONE(116, 36, 143, 53, 2, 6, 131, 0),
    /* list 59 */
    ENCOUNTER_ZONE(0, 0, 56, 49, 2, 0, 2, 1),
    ENCOUNTER_ZONE(66, 0, 78, 11, 0, 1, 2, 1),
    ENCOUNTER_ZONE(64, 34, 79, 49, 0, 2, 123, 0),
    /* list 60 */
    ENCOUNTER_ZONE(0, 0, 69, 99, 2, 0, 120, 0),
    /* list 61 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 5, 0),
    /* list 62 */
    ENCOUNTER_ZONE(0, 0, 52, 55, 2, 0, 2, 1),
    ENCOUNTER_ZONE(62, 0, 78, 15, 2, 1, 2, 1),
    /* list 63 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 3, 0, 3, 1),
    /* list 64 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 3, 0, 3, 1),
    /* list 65 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 5, 0, 2, 1),
    /* list 66 */
    ENCOUNTER_ZONE(2, 2, 40, 45, 2, 0, 3, 1),
    ENCOUNTER_ZONE(54, 4, 69, 17, 2, 1, 3, 1),
    /* list 67 */
    ENCOUNTER_ZONE(1, 1, 63, 74, 0, 0, 68, 0),
    ENCOUNTER_ZONE(51, 85, 62, 97, 0, 1, 68, 0),
    /* list 68 */
    ENCOUNTER_ZONE(5, 4, 62, 63, 2, 0, 124, 0),
    ENCOUNTER_ZONE(9, 80, 34, 96, 2, 1, 124, 0),
    /* list 69 */
    ENCOUNTER_ZONE(1, 3, 59, 78, 2, 0, 2, 1),
    ENCOUNTER_ZONE(86, 1, 97, 11, 0, 1, 2, 1),
    /* list 70 */
    ENCOUNTER_ZONE(0, 0, 68, 79, 2, 0, 71, 0),
    ENCOUNTER_ZONE(78, 48, 95, 78, 2, 1, 71, 0),
    ENCOUNTER_ZONE(73, 0, 99, 38, 2, 2, 71, 0),
    /* list 71 */
    ENCOUNTER_ZONE(1, 57, 48, 148, 2, 0, 81, 0),
    ENCOUNTER_ZONE(2, 1, 20, 26, 2, 1, 81, 0),
    ENCOUNTER_ZONE(34, 3, 48, 22, 2, 2, 81, 0),
    ENCOUNTER_ZONE(9, 35, 20, 45, 2, 3, 81, 0),
    ENCOUNTER_ZONE(35, 40, 47, 51, 2, 4, 81, 0),
    /* list 72 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 3, 0, 3, 1),
    /* list 73 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 3, 0, 3, 1),
    /* list 74 */
    ENCOUNTER_ZONE(3, 3, 66, 43, 2, 0, 0, 0),
    ENCOUNTER_ZONE(86, 2, 96, 16, 2, 1, 0, 0),
    ENCOUNTER_ZONE(110, 1, 119, 17, 2, 2, 0, 0),
    ENCOUNTER_ZONE(131, 2, 141, 19, 2, 3, 0, 0),
    ENCOUNTER_ZONE(157, 1, 174, 19, 2, 4, 0, 0),
    ENCOUNTER_ZONE(86, 30, 94, 42, 2, 5, 0, 0),
    ENCOUNTER_ZONE(113, 31, 124, 41, 2, 6, 0, 0),
    /* list 75 */
    ENCOUNTER_ZONE(1, 1, 58, 75, 2, 0, 87, 0),
    ENCOUNTER_ZONE(1, 98, 32, 118, 2, 1, 87, 0),
    /* list 76 */
    ENCOUNTER_ZONE(0, 0, 79, 99, 2, 0, 89, 0),
    /* list 77 */
    ENCOUNTER_ZONE(0, 0, 71, 58, 2, 0, 91, 0),
    ENCOUNTER_ZONE(104, 0, 128, 29, 2, 1, 93, 0),
    ENCOUNTER_ZONE(88, 33, 103, 58, 0, 2, 91, 0),
    /* list 78 */
    ENCOUNTER_ZONE(1, 131, 27, 179, 2, 0, 74, 0),
    ENCOUNTER_ZONE(32, 169, 41, 177, 2, 1, 74, 0),
    ENCOUNTER_ZONE(30, 110, 43, 143, 2, 0, 74, 0),
    ENCOUNTER_ZONE(2, 72, 41, 94, 2, 3, 74, 0),
    ENCOUNTER_ZONE(2, 36, 41, 58, 2, 4, 74, 0),
    ENCOUNTER_ZONE(2, 1, 41, 23, 2, 5, 74, 0),
    /* list 79 */
    ENCOUNTER_ZONE(2, 1, 15, 25, 2, 0, 74, 0),
    ENCOUNTER_ZONE(29, 1, 36, 17, 2, 1, 74, 0),
    ENCOUNTER_ZONE(49, 1, 56, 13, 2, 2, 74, 0),
    ENCOUNTER_ZONE(68, 1, 74, 14, 2, 3, 74, 0),
    ENCOUNTER_ZONE(87, 1, 94, 17, 2, 4, 74, 0),
    ENCOUNTER_ZONE(126, 1, 132, 13, 2, 5, 74, 0),
    ENCOUNTER_ZONE(35, 26, 68, 33, 2, 6, 74, 0),
    ENCOUNTER_ZONE(81, 29, 107, 33, 2, 7, 74, 0),
    ENCOUNTER_ZONE(108, 14, 117, 33, 2, 7, 74, 0),
    ENCOUNTER_ZONE(131, 27, 157, 31, 2, 8, 74, 0),
    ENCOUNTER_ZONE(158, 11, 175, 34, 2, 8, 74, 0),
    ENCOUNTER_ZONE(180, 3, 219, 25, 2, 9, 74, 0),
    /* list 80 */
    ENCOUNTER_ZONE(2, 1, 15, 25, 2, 0, 74, 0),
    ENCOUNTER_ZONE(29, 1, 36, 17, 2, 1, 74, 0),
    ENCOUNTER_ZONE(49, 1, 56, 13, 2, 2, 74, 0),
    ENCOUNTER_ZONE(68, 1, 74, 14, 2, 3, 74, 0),
    ENCOUNTER_ZONE(87, 1, 94, 17, 2, 4, 74, 0),
    ENCOUNTER_ZONE(126, 1, 132, 13, 2, 5, 74, 0),
    ENCOUNTER_ZONE(35, 26, 68, 33, 2, 6, 74, 0),
    ENCOUNTER_ZONE(81, 29, 107, 13, 2, 7, 74, 0),
    ENCOUNTER_ZONE(108, 14, 117, 33, 2, 7, 74, 0),
    ENCOUNTER_ZONE(131, 27, 157, 31, 2, 8, 74, 0),
    ENCOUNTER_ZONE(158, 11, 175, 34, 2, 8, 74, 0),
    ENCOUNTER_ZONE(179, 0, 221, 28, 2, 9, 74, 0),
    /* list 81 */
    ENCOUNTER_ZONE(2, 1, 15, 25, 2, 0, 74, 0),
    ENCOUNTER_ZONE(29, 1, 36, 17, 2, 1, 74, 0),
    ENCOUNTER_ZONE(49, 1, 56, 13, 2, 2, 74, 0),
    ENCOUNTER_ZONE(68, 1, 74, 14, 2, 3, 74, 0),
    ENCOUNTER_ZONE(87, 1, 94, 17, 2, 4, 74, 0),
    ENCOUNTER_ZONE(126, 1, 132, 13, 2, 5, 74, 0),
    ENCOUNTER_ZONE(35, 26, 68, 33, 2, 6, 74, 0),
    ENCOUNTER_ZONE(81, 29, 107, 13, 2, 7, 74, 0),
    ENCOUNTER_ZONE(108, 14, 117, 33, 2, 7, 74, 0),
    ENCOUNTER_ZONE(131, 27, 157, 31, 2, 8, 74, 0),
    ENCOUNTER_ZONE(158, 11, 175, 34, 2, 8, 74, 0),
    ENCOUNTER_ZONE(180, 3, 219, 25, 2, 9, 74, 0),
    /* list 82 */
    ENCOUNTER_ZONE(1, 1, 81, 74, 2, 0, 62, 0),
    ENCOUNTER_ZONE(65, 79, 82, 93, 0, 1, 255, 0),
    /* list 83 */
    ENCOUNTER_ZONE(17, 45, 78, 98, 1, 0, 80, 0),
    ENCOUNTER_ZONE(1, 1, 49, 28, 2, 1, 80, 0),
    ENCOUNTER_ZONE(71, 1, 78, 23, 2, 2, 80, 0),
    /* list 84 */
    ENCOUNTER_ZONE(1, 1, 57, 31, 2, 0, 80, 0),
    ENCOUNTER_ZONE(7, 56, 23, 98, 2, 1, 80, 0),
    ENCOUNTER_ZONE(52, 50, 65, 83, 2, 2, 80, 0),
    ENCOUNTER_ZONE(53, 85, 65, 95, 0, 3, 80, 0),
    /* list 85 */
    ENCOUNTER_ZONE(1, 1, 78, 98, 0, 0, 80, 0),
    /* list 86 */
    ENCOUNTER_ZONE(1, 1, 68, 41, 2, 0, 91, 0),
    ENCOUNTER_ZONE(42, 55, 68, 67, 2, 1, 91, 0),
    /* list 87 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 5, 0, 2, 1),
    /* list 88 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 5, 0, 2, 1),
    /* list 89 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 40, 0),
    /* list 90 */
    ENCOUNTER_ZONE(0, 0, 43, 47, 0, 0, 13, 1),
    ENCOUNTER_ZONE(55, 7, 68, 18, 0, 1, 13, 1),
    /* list 91 */
    ENCOUNTER_ZONE(0, 0, 79, 64, 2, 0, 5, 0),
    /* list 92 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 60, 0),
    /* list 93 */
    ENCOUNTER_ZONE(0, 0, 49, 64, 2, 0, 2, 1),
    /* list 94 */
    ENCOUNTER_ZONE(0, 0, 99, 79, 2, 0, 66, 0),
    /* list 95 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 5, 0),
    /* list 96 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 5, 0),
    /* list 97 */
    ENCOUNTER_ZONE(1, 1, 83, 88, 2, 0, 54, 0),
    /* list 98 */
    ENCOUNTER_ZONE(27, 8, 85, 66, 2, 0, 67, 0),
    ENCOUNTER_ZONE(1, 1, 10, 22, 2, 1, 67, 0),
    /* list 99 */
    ENCOUNTER_ZONE(1, 101, 51, 179, 2, 0, 81, 0),
    ENCOUNTER_ZONE(32, 78, 47, 101, 0, 1, 81, 0),
    ENCOUNTER_ZONE(1, 30, 11, 42, 0, 2, 81, 0),
    ENCOUNTER_ZONE(1, 1, 13, 14, 0, 3, 81, 0),
    ENCOUNTER_ZONE(32, 1, 51, 20, 0, 4, 81, 0),
    ENCOUNTER_ZONE(0, 0, 255, 255, 0, 10, 81, 0),
    /* list 100 */
    ENCOUNTER_ZONE(0, 0, 57, 58, 2, 0, 2, 1),
    ENCOUNTER_ZONE(64, 0, 79, 14, 2, 1, 2, 1),
    ENCOUNTER_ZONE(72, 22, 79, 35, 2, 2, 46, 0),
    ENCOUNTER_ZONE(64, 45, 79, 59, 2, 3, 123, 0),
    /* list 101 */
    ENCOUNTER_ZONE(0, 0, 50, 46, 2, 0, 128, 0),
    ENCOUNTER_ZONE(64, 0, 77, 13, 2, 1, 129, 0),
    /* list 102 */
    ENCOUNTER_ZONE(1, 49, 47, 112, 2, 0, 90, 0),
    ENCOUNTER_ZONE(48, 79, 68, 112, 2, 0, 90, 0),
    ENCOUNTER_ZONE(1, 1, 39, 43, 2, 1, 90, 0),
    ENCOUNTER_ZONE(40, 1, 65, 24, 2, 1, 90, 0),
    ENCOUNTER_ZONE(48, 32, 68, 53, 2, 2, 90, 0),
    /* list 103 */
    ENCOUNTER_ZONE(20, 5, 97, 77, 2, 0, 90, 0),
    ENCOUNTER_ZONE(1, 1, 14, 27, 2, 1, 90, 0),
    /* list 104 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 9, 1),
    /* list 105 */
    ENCOUNTER_ZONE(0, 0, 29, 79, 2, 0, 24, 0),
    ENCOUNTER_ZONE(53, 0, 80, 60, 2, 1, 24, 0),
    /* list 106 */
    ENCOUNTER_ZONE(0, 0, 48, 49, 2, 0, 24, 0),
    ENCOUNTER_ZONE(69, 0, 99, 25, 2, 1, 24, 0),
    ENCOUNTER_ZONE(72, 60, 99, 76, 2, 2, 24, 0),
    /* list 107 */
    ENCOUNTER_ZONE(0, 0, 33, 90, 3, 0, 24, 0),
    ENCOUNTER_ZONE(33, 0, 43, 75, 3, 0, 24, 0),
    ENCOUNTER_ZONE(44, 0, 61, 40, 3, 0, 24, 0),
    ENCOUNTER_ZONE(28, 91, 65, 119, 2, 1, 24, 0),
    ENCOUNTER_ZONE(35, 76, 65, 90, 2, 1, 24, 0),
    ENCOUNTER_ZONE(44, 47, 65, 75, 2, 1, 24, 0),
    /* list 108 */
    ENCOUNTER_ZONE(0, 40, 68, 99, 2, 0, 107, 0),
    ENCOUNTER_ZONE(0, 2, 13, 17, 2, 1, 107, 0),
    ENCOUNTER_ZONE(34, 6, 53, 21, 0, 2, 107, 0),
    ENCOUNTER_ZONE(67, 0, 78, 12, 2, 3, 107, 0),
    /* list 109 */
    ENCOUNTER_ZONE(20, 0, 30, 9, 2, 0, 107, 0),
    ENCOUNTER_ZONE(49, 1, 78, 7, 2, 1, 107, 0),
    ENCOUNTER_ZONE(0, 5, 9, 43, 2, 2, 107, 0),
    ENCOUNTER_ZONE(10, 24, 37, 36, 2, 2, 107, 0),
    ENCOUNTER_ZONE(53, 25, 78, 32, 2, 3, 107, 0),
    ENCOUNTER_ZONE(16, 46, 36, 65, 2, 4, 107, 0),
    ENCOUNTER_ZONE(1, 70, 40, 98, 2, 5, 107, 0),
    ENCOUNTER_ZONE(46, 50, 78, 98, 2, 6, 107, 0),
    /* list 110 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 3, 0, 3, 1),
    /* list 111 */
    ENCOUNTER_ZONE(0, 212, 30, 248, 2, 0, 91, 0),
    ENCOUNTER_ZONE(0, 170, 29, 199, 0, 1, 91, 0),
    ENCOUNTER_ZONE(0, 127, 31, 156, 2, 2, 91, 0),
    ENCOUNTER_ZONE(0, 89, 20, 109, 2, 3, 91, 0),
    ENCOUNTER_ZONE(0, 44, 31, 67, 2, 4, 91, 0),
    ENCOUNTER_ZONE(0, 0, 22, 21, 2, 5, 91, 0),
    /* list 112 */
    ENCOUNTER_ZONE(0, 0, 40, 38, 0, 0, 91, 0),
    ENCOUNTER_ZONE(0, 57, 11, 66, 2, 1, 91, 0),
    ENCOUNTER_ZONE(26, 59, 35, 71, 2, 2, 91, 0),
    ENCOUNTER_ZONE(0, 75, 25, 99, 0, 3, 91, 0),
    ENCOUNTER_ZONE(43, 26, 79, 53, 2, 4, 91, 0),
    ENCOUNTER_ZONE(38, 54, 79, 99, 2, 4, 91, 0),
    ENCOUNTER_ZONE(47, 0, 79, 18, 2, 5, 91, 0),
    /* list 113 */
    ENCOUNTER_ZONE(0, 0, 59, 39, 2, 0, 93, 0),
    /* list 114 */
    ENCOUNTER_ZONE(0, 0, 55, 59, 2, 0, 2, 1),
    ENCOUNTER_ZONE(64, 0, 78, 13, 2, 1, 2, 1),
    /* list 115 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 5, 0, 2, 1),
    /* list 116 */
    ENCOUNTER_ZONE(0, 0, 51, 59, 2, 0, 2, 1),
    ENCOUNTER_ZONE(61, 0, 78, 13, 2, 1, 2, 1),
    ENCOUNTER_ZONE(65, 45, 79, 59, 2, 2, 123, 0),
    /* list 117 */
    ENCOUNTER_ZONE(1, 1, 45, 40, 2, 0, 97, 0),
    ENCOUNTER_ZONE(1, 66, 20, 78, 2, 1, 97, 0),
    ENCOUNTER_ZONE(60, 2, 69, 10, 2, 2, 97, 0),
    ENCOUNTER_ZONE(83, 6, 93, 16, 0, 3, 97, 0),
    ENCOUNTER_ZONE(77, 37, 97, 51, 2, 4, 97, 0),
    ENCOUNTER_ZONE(66, 73, 98, 78, 2, 5, 97, 0),
    /* list 118 */
    ENCOUNTER_ZONE(1, 1, 20, 32, 2, 0, 97, 0),
    ENCOUNTER_ZONE(27, 3, 41, 16, 2, 1, 97, 0),
    ENCOUNTER_ZONE(57, 2, 78, 29, 2, 2, 97, 0),
    ENCOUNTER_ZONE(1, 51, 19, 73, 2, 3, 97, 0),
    ENCOUNTER_ZONE(33, 63, 77, 98, 2, 4, 97, 0),
    /* list 119 */
    ENCOUNTER_ZONE(56, 43, 98, 78, 2, 0, 97, 0),
    ENCOUNTER_ZONE(1, 1, 18, 20, 0, 1, 97, 0),
    ENCOUNTER_ZONE(1, 45, 22, 58, 2, 2, 97, 0),
    /* list 120 */
    ENCOUNTER_ZONE(0, 0, 59, 32, 2, 0, 131, 0),
    ENCOUNTER_ZONE(0, 46, 13, 57, 2, 1, 131, 0),
    ENCOUNTER_ZONE(45, 46, 58, 57, 2, 2, 131, 0),
    ENCOUNTER_ZONE(0, 68, 22, 91, 2, 3, 131, 0),
    ENCOUNTER_ZONE(35, 68, 57, 91, 2, 4, 131, 0),
    ENCOUNTER_ZONE(23, 105, 49, 127, 2, 5, 10, 1),
    /* list 121 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 0, 0, 134, 0),
    /* list 122 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 121, 0),
    /* list 123 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 121, 0),
    /* list 124 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 3, 0, 3, 1),
    /* list 125 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 3, 0, 3, 1),
    /* list 126 */
    ENCOUNTER_ZONE(0, 0, 119, 59, 2, 0, 112, 0),
    /* list 127 */
    ENCOUNTER_ZONE(0, 0, 65, 84, 2, 0, 97, 0),
    ENCOUNTER_ZONE(77, 47, 90, 57, 2, 1, 97, 0),
    ENCOUNTER_ZONE(76, 71, 91, 83, 2, 2, 97, 0),
    /* list 128 */
    ENCOUNTER_ZONE(0, 0, 69, 78, 2, 0, 136, 0),
    ENCOUNTER_ZONE(84, 52, 94, 62, 2, 1, 11, 1),
    ENCOUNTER_ZONE(82, 28, 97, 38, 2, 2, 11, 1),
    ENCOUNTER_ZONE(76, 2, 97, 13, 2, 3, 11, 1),
    /* list 129 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 40, 0),
    /* list 130 */
    ENCOUNTER_ZONE(0, 0, 54, 65, 2, 0, 131, 0),
    ENCOUNTER_ZONE(0, 76, 14, 89, 2, 1, 131, 0),
    ENCOUNTER_ZONE(33, 76, 46, 91, 2, 2, 131, 0),
    ENCOUNTER_ZONE(0, 108, 13, 115, 2, 3, 131, 0),
    ENCOUNTER_ZONE(38, 103, 52, 116, 2, 4, 131, 0),
    ENCOUNTER_ZONE(0, 126, 16, 143, 2, 5, 131, 0),
    ENCOUNTER_ZONE(40, 129, 53, 143, 2, 6, 131, 0),
    /* list 131 */
    ENCOUNTER_ZONE(0, 0, 76, 60, 2, 0, 136, 0),
    ENCOUNTER_ZONE(1, 88, 10, 98, 2, 1, 11, 1),
    ENCOUNTER_ZONE(26, 88, 41, 98, 2, 2, 11, 1),
    ENCOUNTER_ZONE(56, 87, 74, 98, 2, 3, 11, 1),
    /* list 132 */
    ENCOUNTER_ZONE(0, 0, 99, 60, 2, 0, 136, 0),
    ENCOUNTER_ZONE(1, 65, 10, 75, 2, 1, 136, 0),
    ENCOUNTER_ZONE(23, 68, 38, 78, 2, 2, 136, 0),
    ENCOUNTER_ZONE(78, 67, 99, 78, 2, 3, 136, 0),
    /* list 133 */
    ENCOUNTER_ZONE(0, 0, 79, 61, 2, 0, 138, 0),
    ENCOUNTER_ZONE(1, 88, 10, 98, 2, 1, 138, 0),
    ENCOUNTER_ZONE(26, 88, 41, 98, 2, 2, 138, 0),
    ENCOUNTER_ZONE(56, 87, 74, 98, 2, 3, 138, 0),
    /* list 134 */
    ENCOUNTER_ZONE(0, 0, 119, 59, 2, 0, 119, 0),
    /* list 135 */
    ENCOUNTER_ZONE(0, 0, 49, 27, 0, 0, 139, 0),
    ENCOUNTER_ZONE(0, 34, 21, 46, 3, 1, 139, 0),
    ENCOUNTER_ZONE(0, 52, 8, 59, 3, 2, 139, 0),
    ENCOUNTER_ZONE(37, 38, 49, 65, 3, 3, 139, 0),
    ENCOUNTER_ZONE(0, 73, 28, 96, 3, 4, 139, 0),
    ENCOUNTER_ZONE(37, 78, 48, 90, 3, 5, 139, 0),
    ENCOUNTER_ZONE(0, 109, 24, 127, 3, 6, 139, 0),
    ENCOUNTER_ZONE(40, 104, 48, 119, 3, 7, 139, 0),
    ENCOUNTER_ZONE(0, 152, 19, 159, 3, 8, 139, 0),
    ENCOUNTER_ZONE(32, 137, 49, 159, 3, 9, 139, 0),
    /* list 136 */
    ENCOUNTER_ZONE(0, 0, 34, 24, 3, 0, 139, 0),
    ENCOUNTER_ZONE(0, 24, 14, 40, 3, 1, 139, 0),
    ENCOUNTER_ZONE(0, 58, 23, 68, 3, 2, 139, 0),
    ENCOUNTER_ZONE(40, 36, 57, 45, 3, 3, 139, 0),
    ENCOUNTER_ZONE(46, 60, 58, 76, 3, 4, 139, 0),
    ENCOUNTER_ZONE(0, 81, 15, 95, 0, 5, 139, 0),
    ENCOUNTER_ZONE(24, 119, 58, 126, 3, 6, 139, 0),
    /* list 137 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 139, 0),
    /* list 138 */
    ENCOUNTER_ZONE(0, 0, 66, 77, 2, 0, 91, 0),
    /* list 139 */
    ENCOUNTER_ZONE(0, 0, 53, 40, 2, 0, 91, 0),
    ENCOUNTER_ZONE(54, 0, 74, 15, 2, 0, 91, 0),
    ENCOUNTER_ZONE(68, 31, 89, 52, 2, 1, 91, 0),
    ENCOUNTER_ZONE(87, 2, 98, 21, 0, 2, 91, 0),
    ENCOUNTER_ZONE(55, 63, 71, 77, 0, 3, 91, 0),
    ENCOUNTER_ZONE(1, 66, 16, 79, 2, 4, 91, 0),
    ENCOUNTER_ZONE(29, 68, 41, 78, 2, 5, 91, 0),
    /* list 140 */
    ENCOUNTER_ZONE(0, 0, 99, 42, 2, 0, 91, 0),
    ENCOUNTER_ZONE(29, 43, 99, 79, 2, 1, 91, 0),
    ENCOUNTER_ZONE(0, 63, 14, 77, 2, 2, 91, 0),
    ENCOUNTER_ZONE(0, 0, 42, 11, 2, 3, 91, 0),
    /* list 141 */
    ENCOUNTER_ZONE(24, 0, 106, 20, 2, 0, 80, 0),
    ENCOUNTER_ZONE(24, 29, 106, 73, 2, 1, 80, 0),
    ENCOUNTER_ZONE(0, 3, 22, 61, 2, 2, 80, 0),
    /* list 142 */
    ENCOUNTER_ZONE(10, 9, 24, 63, 2, 1, 80, 0),
    ENCOUNTER_ZONE(53, 8, 84, 15, 2, 2, 80, 0),
    ENCOUNTER_ZONE(27, 30, 58, 46, 2, 3, 80, 0),
    ENCOUNTER_ZONE(0, 0, 99, 79, 2, 0, 80, 0),
    /* list 143 */
    ENCOUNTER_ZONE(0, 0, 68, 62, 2, 0, 111, 0),
    ENCOUNTER_ZONE(44, 90, 68, 111, 2, 1, 111, 0),
    ENCOUNTER_ZONE(1, 73, 15, 88, 2, 2, 111, 0),
    ENCOUNTER_ZONE(0, 98, 15, 112, 2, 3, 111, 0),
    ENCOUNTER_ZONE(28, 77, 37, 84, 2, 4, 111, 0),
    ENCOUNTER_ZONE(27, 103, 34, 112, 2, 5, 111, 0),
    /* list 144 */
    ENCOUNTER_ZONE(6, 55, 32, 72, 2, 0, 111, 0),
    ENCOUNTER_ZONE(0, 0, 10, 42, 2, 1, 111, 0),
    ENCOUNTER_ZONE(27, 22, 45, 37, 2, 2, 111, 0),
    ENCOUNTER_ZONE(18, 0, 40, 7, 2, 3, 111, 0),
    ENCOUNTER_ZONE(59, 0, 70, 11, 2, 4, 111, 0),
    ENCOUNTER_ZONE(65, 32, 75, 42, 2, 5, 111, 0),
    /* list 145 */
    ENCOUNTER_ZONE(0, 0, 71, 56, 2, 0, 91, 0),
    ENCOUNTER_ZONE(1, 57, 14, 78, 2, 1, 91, 0),
    ENCOUNTER_ZONE(28, 63, 40, 76, 2, 2, 91, 0),
    ENCOUNTER_ZONE(61, 61, 70, 74, 2, 3, 91, 0),
    ENCOUNTER_ZONE(0, 88, 22, 109, 2, 4, 91, 0),
    ENCOUNTER_ZONE(43, 90, 70, 108, 0, 5, 91, 0),
    /* list 146 */
    ENCOUNTER_ZONE(0, 0, 46, 59, 2, 0, 2, 1),
    ENCOUNTER_ZONE(62, 32, 78, 59, 2, 1, 2, 1),
    /* list 147 */
    ENCOUNTER_ZONE(0, 0, 63, 59, 2, 0, 140, 0),
    ENCOUNTER_ZONE(69, 0, 105, 13, 2, 1, 140, 0),
    ENCOUNTER_ZONE(115, 0, 132, 21, 2, 2, 140, 0),
    ENCOUNTER_ZONE(69, 23, 82, 35, 2, 3, 140, 0),
    ENCOUNTER_ZONE(93, 23, 106, 36, 2, 4, 140, 0),
    ENCOUNTER_ZONE(69, 45, 82, 58, 2, 5, 140, 0),
    ENCOUNTER_ZONE(100, 42, 132, 59, 2, 6, 140, 0),
    /* list 148 */
    ENCOUNTER_ZONE(0, 0, 54, 66, 2, 0, 140, 0),
    ENCOUNTER_ZONE(59, 0, 89, 41, 0, 1, 140, 0),
    ENCOUNTER_ZONE(90, 26, 105, 38, 0, 1, 140, 0),
    ENCOUNTER_ZONE(99, 0, 117, 17, 2, 2, 140, 0),
    ENCOUNTER_ZONE(68, 53, 79, 64, 0, 3, 140, 0),
    ENCOUNTER_ZONE(98, 46, 118, 66, 2, 4, 140, 0),
    /* list 149 */
    ENCOUNTER_ZONE(0, 0, 42, 49, 2, 0, 140, 0),
    /* list 150 */
    ENCOUNTER_ZONE(0, 0, 42, 65, 2, 0, 16, 0),
    ENCOUNTER_ZONE(54, 7, 66, 18, 2, 1, 16, 0),
    ENCOUNTER_ZONE(54, 29, 66, 40, 2, 2, 16, 0),
    ENCOUNTER_ZONE(54, 50, 66, 62, 2, 3, 16, 0),
    ENCOUNTER_ZONE(54, 74, 66, 86, 2, 4, 16, 0),
    /* list 151 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 5, 0, 2, 1),
    /* list 152 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 5, 0, 2, 1),
    /* list 153 */
    ENCOUNTER_ZONE(0, 0, 43, 47, 0, 0, 14, 1),
    ENCOUNTER_ZONE(55, 7, 68, 18, 0, 1, 14, 1),
    /* list 154 */
    ENCOUNTER_ZONE(0, 0, 43, 47, 0, 0, 14, 1),
    ENCOUNTER_ZONE(55, 7, 68, 18, 0, 1, 14, 1),
    /* list 155 */
    ENCOUNTER_ZONE(0, 0, 36, 71, 2, 0, 112, 0),
    ENCOUNTER_ZONE(37, 21, 70, 52, 2, 0, 112, 0),
    ENCOUNTER_ZONE(54, 0, 69, 13, 2, 1, 112, 0),
    ENCOUNTER_ZONE(81, 0, 98, 23, 2, 2, 112, 0),
    ENCOUNTER_ZONE(52, 65, 67, 78, 2, 3, 112, 0),
    ENCOUNTER_ZONE(81, 54, 98, 78, 2, 4, 112, 0),
    /* list 156 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 3, 1),
    /* list 157 */
    ENCOUNTER_ZONE(33, 17, 46, 22, 2, 1, 56, 0),
    ENCOUNTER_ZONE(41, 23, 46, 32, 2, 1, 56, 0),
    ENCOUNTER_ZONE(47, 17, 50, 24, 2, 2, 56, 0),
    ENCOUNTER_ZONE(19, 23, 32, 32, 2, 3, 56, 0),
    ENCOUNTER_ZONE(33, 23, 40, 32, 2, 4, 56, 0),
    ENCOUNTER_ZONE(15, 41, 24, 50, 2, 5, 56, 0),
    ENCOUNTER_ZONE(33, 33, 50, 50, 2, 6, 56, 0),
    ENCOUNTER_ZONE(25, 51, 32, 60, 2, 7, 56, 0),
    ENCOUNTER_ZONE(33, 51, 42, 56, 2, 8, 56, 0),
    ENCOUNTER_ZONE(13, 61, 32, 64, 2, 9, 56, 0),
    ENCOUNTER_ZONE(43, 61, 52, 67, 2, 10, 56, 0),
    ENCOUNTER_ZONE(0, 0, 79, 79, 2, 0, 56, 0),
    /* list 158 */
    ENCOUNTER_ZONE(1, 13, 14, 28, 2, 0, 56, 0),
    ENCOUNTER_ZONE(25, 1, 40, 13, 2, 1, 56, 0),
    /* list 159 */
    ENCOUNTER_ZONE(1, 13, 14, 28, 2, 0, 56, 0),
    ENCOUNTER_ZONE(27, 1, 42, 14, 2, 1, 56, 0),
    /* list 160 */
    ENCOUNTER_ZONE(1, 13, 14, 28, 2, 0, 56, 0),
    ENCOUNTER_ZONE(27, 1, 42, 14, 2, 1, 56, 0),
    /* list 161 */
    ENCOUNTER_ZONE(1, 13, 16, 28, 2, 0, 56, 0),
    ENCOUNTER_ZONE(29, 1, 42, 16, 2, 1, 56, 0),
    /* list 162 */
    ENCOUNTER_ZONE(1, 13, 16, 26, 2, 0, 56, 0),
    ENCOUNTER_ZONE(27, 1, 40, 16, 2, 1, 56, 0),
    /* list 163 */
    ENCOUNTER_ZONE(1, 13, 16, 26, 2, 0, 56, 0),
    ENCOUNTER_ZONE(27, 1, 42, 14, 2, 1, 56, 0),
    /* list 164 */
    ENCOUNTER_ZONE(1, 13, 15, 25, 2, 0, 56, 0),
    ENCOUNTER_ZONE(27, 1, 39, 15, 2, 1, 56, 0),
    /* list 165 */
    ENCOUNTER_ZONE(1, 13, 16, 26, 2, 0, 56, 0),
    ENCOUNTER_ZONE(27, 1, 42, 14, 2, 1, 56, 0),
    /* list 166 */
    ENCOUNTER_ZONE(1, 13, 13, 28, 2, 0, 56, 0),
    ENCOUNTER_ZONE(27, 1, 42, 14, 2, 1, 56, 0),
    ENCOUNTER_ZONE(59, 1, 74, 14, 2, 2, 56, 0),
    ENCOUNTER_ZONE(92, 2, 105, 17, 2, 3, 56, 0),
    /* list 167 */
    ENCOUNTER_ZONE(0, 59, 49, 123, 2, 0, 140, 0),
    ENCOUNTER_ZONE(0, 130, 49, 159, 2, 1, 140, 0),
    ENCOUNTER_ZONE(20, 1, 49, 20, 2, 2, 140, 0),
    ENCOUNTER_ZONE(4, 21, 49, 41, 2, 2, 140, 0),
    ENCOUNTER_ZONE(32, 46, 48, 57, 2, 3, 140, 0),
    ENCOUNTER_ZONE(0, 0, 5, 5, 2, 4, 140, 0),
    /* list 168 */
    ENCOUNTER_ZONE(0, 0, 53, 44, 2, 0, 140, 0),
    ENCOUNTER_ZONE(65, 0, 76, 15, 2, 1, 140, 0),
    ENCOUNTER_ZONE(65, 31, 80, 42, 2, 2, 140, 0),
    ENCOUNTER_ZONE(93, 23, 114, 43, 0, 3, 140, 0),
    ENCOUNTER_ZONE(121, 0, 133, 20, 2, 4, 140, 0),
    ENCOUNTER_ZONE(148, 12, 167, 35, 2, 5, 140, 0),
    ENCOUNTER_ZONE(131, 36, 167, 43, 2, 5, 140, 0),
    /* list 169 */
    ENCOUNTER_ZONE(0, 0, 32, 13, 2, 0, 140, 0),
    ENCOUNTER_ZONE(0, 27, 8, 35, 0, 1, 140, 0),
    ENCOUNTER_ZONE(26, 27, 35, 36, 2, 2, 140, 0),
    ENCOUNTER_ZONE(0, 52, 20, 61, 2, 3, 140, 0),
    /* list 170 */
    ENCOUNTER_ZONE(0, 0, 49, 28, 2, 0, 140, 0),
    ENCOUNTER_ZONE(21, 39, 48, 52, 2, 1, 140, 0),
    ENCOUNTER_ZONE(0, 57, 39, 79, 2, 2, 140, 0),
    ENCOUNTER_ZONE(10, 85, 46, 107, 2, 3, 140, 0),
    ENCOUNTER_ZONE(0, 110, 15, 134, 2, 4, 140, 0),
    ENCOUNTER_ZONE(0, 140, 41, 158, 2, 5, 140, 0),
    /* list 171 */
    ENCOUNTER_ZONE(0, 0, 25, 15, 2, 0, 140, 0),
    ENCOUNTER_ZONE(38, 0, 64, 16, 2, 1, 140, 0),
    ENCOUNTER_ZONE(0, 30, 9, 55, 2, 2, 140, 0),
    ENCOUNTER_ZONE(23, 33, 32, 44, 0, 3, 140, 0),
    ENCOUNTER_ZONE(52, 32, 61, 49, 2, 4, 140, 0),
    ENCOUNTER_ZONE(0, 72, 64, 119, 2, 5, 140, 0),
    /* list 172 */
    ENCOUNTER_ZONE(0, 23, 64, 83, 2, 0, 8, 0),
    ENCOUNTER_ZONE(0, 0, 34, 10, 2, 1, 140, 0),
    /* list 173 */
    ENCOUNTER_ZONE(0, 0, 59, 61, 2, 0, 140, 0),
    ENCOUNTER_ZONE(11, 63, 24, 97, 2, 1, 142, 0),
    ENCOUNTER_ZONE(19, 120, 39, 129, 2, 2, 142, 0),
    ENCOUNTER_ZONE(40, 91, 59, 129, 2, 2, 142, 0),
    /* list 174 */
    ENCOUNTER_ZONE(15, 0, 106, 72, 2, 0, 142, 0),
    ENCOUNTER_ZONE(0, 0, 14, 14, 2, 1, 142, 0),
    /* list 175 */
    ENCOUNTER_ZONE(0, 0, 77, 47, 2, 0, 4, 1),
    ENCOUNTER_ZONE(40, 88, 50, 98, 2, 1, 4, 1),
    /* list 176 */
    ENCOUNTER_ZONE(0, 0, 77, 47, 2, 0, 4, 1),
    ENCOUNTER_ZONE(40, 88, 50, 98, 2, 1, 4, 1),
    /* list 177 */
    ENCOUNTER_ZONE(0, 0, 77, 47, 2, 0, 4, 1),
    ENCOUNTER_ZONE(40, 88, 50, 98, 2, 1, 4, 1),
    ENCOUNTER_ZONE(0, 66, 25, 97, 2, 2, 4, 1),
    /* list 178 */
    ENCOUNTER_ZONE(0, 0, 77, 47, 2, 0, 4, 1),
    ENCOUNTER_ZONE(40, 88, 50, 98, 2, 1, 4, 1),
    ENCOUNTER_ZONE(0, 66, 25, 97, 2, 2, 4, 1),
    /* list 179 */
    ENCOUNTER_ZONE(0, 0, 77, 47, 2, 0, 4, 1),
    ENCOUNTER_ZONE(40, 88, 50, 98, 2, 1, 4, 1),
    ENCOUNTER_ZONE(0, 66, 25, 97, 2, 2, 4, 1),
    /* list 180 */
    ENCOUNTER_ZONE(0, 0, 77, 47, 2, 0, 4, 1),
    ENCOUNTER_ZONE(40, 88, 50, 98, 2, 1, 4, 1),
    ENCOUNTER_ZONE(0, 66, 25, 97, 2, 2, 4, 1),
    /* list 181 */
    ENCOUNTER_ZONE(0, 0, 77, 47, 2, 0, 4, 1),
    ENCOUNTER_ZONE(40, 88, 50, 98, 2, 1, 4, 1),
    ENCOUNTER_ZONE(0, 66, 25, 97, 2, 2, 4, 1),
    /* list 182 */
    ENCOUNTER_ZONE(0, 0, 77, 47, 2, 0, 4, 1),
    ENCOUNTER_ZONE(40, 88, 50, 98, 2, 1, 4, 1),
    ENCOUNTER_ZONE(0, 66, 25, 97, 2, 2, 4, 1),
    /* list 183 */
    ENCOUNTER_ZONE(0, 0, 77, 47, 2, 0, 4, 1),
    ENCOUNTER_ZONE(40, 88, 50, 98, 2, 1, 4, 1),
    ENCOUNTER_ZONE(0, 66, 25, 97, 2, 2, 4, 1),
    ENCOUNTER_ZONE(58, 62, 75, 91, 2, 3, 4, 1),
    /* list 184 */
    ENCOUNTER_ZONE(0, 0, 77, 47, 2, 0, 4, 1),
    ENCOUNTER_ZONE(40, 88, 50, 98, 2, 1, 4, 1),
    ENCOUNTER_ZONE(0, 66, 25, 97, 2, 2, 4, 1),
    ENCOUNTER_ZONE(58, 62, 75, 91, 2, 3, 4, 1),
    /* list 185 */
    ENCOUNTER_ZONE(0, 0, 77, 47, 2, 0, 4, 1),
    ENCOUNTER_ZONE(40, 88, 50, 98, 2, 1, 4, 1),
    ENCOUNTER_ZONE(0, 66, 25, 97, 2, 2, 4, 1),
    ENCOUNTER_ZONE(58, 62, 75, 91, 2, 3, 4, 1),
    /* list 186 */
    ENCOUNTER_ZONE(0, 0, 9, 240, 2, 0, 142, 0),
    /* list 187 */
    ENCOUNTER_ZONE(0, 0, 76, 60, 2, 0, 136, 0),
    ENCOUNTER_ZONE(1, 88, 10, 98, 2, 1, 137, 0),
    ENCOUNTER_ZONE(26, 88, 41, 98, 2, 2, 137, 0),
    ENCOUNTER_ZONE(56, 87, 74, 98, 2, 3, 137, 0),
    /* list 188 */
    ENCOUNTER_ZONE(0, 0, 34, 24, 3, 0, 139, 0),
    ENCOUNTER_ZONE(0, 24, 14, 40, 3, 1, 139, 0),
    ENCOUNTER_ZONE(0, 58, 23, 68, 3, 2, 139, 0),
    ENCOUNTER_ZONE(40, 36, 57, 45, 3, 3, 139, 0),
    ENCOUNTER_ZONE(46, 60, 58, 76, 3, 4, 139, 0),
    ENCOUNTER_ZONE(0, 81, 15, 95, 0, 5, 139, 0),
    ENCOUNTER_ZONE(24, 119, 58, 126, 3, 6, 139, 0),
    ENCOUNTER_ZONE(0, 0, 255, 255, 3, 0, 139, 0),
    /* list 189 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 145, 0),
    /* list 190 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 145, 0),
    /* list 191 */
    ENCOUNTER_ZONE(0, 0, 52, 46, 2, 0, 149, 0),
    ENCOUNTER_ZONE(67, 8, 78, 18, 2, 1, 149, 0),
    /* list 192 */
    ENCOUNTER_ZONE(0, 0, 40, 45, 2, 0, 14, 1),
    ENCOUNTER_ZONE(56, 8, 67, 18, 2, 1, 14, 1),
    /* list 193 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 149, 0),
    /* list 194 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 113, 0),
    /* list 195 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 54, 0),
    /* list 196 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 145, 0),
    /* list 197 */
    ENCOUNTER_ZONE(0, 0, 49, 28, 2, 0, 158, 0),
    ENCOUNTER_ZONE(21, 39, 48, 52, 2, 1, 158, 0),
    ENCOUNTER_ZONE(0, 57, 39, 79, 2, 2, 158, 0),
    ENCOUNTER_ZONE(10, 85, 46, 107, 2, 3, 158, 0),
    ENCOUNTER_ZONE(0, 110, 15, 134, 2, 4, 158, 0),
    ENCOUNTER_ZONE(0, 140, 41, 158, 2, 5, 158, 0),
    /* list 198 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 142, 0),
    /* list 199 */
    ENCOUNTER_ZONE(0, 0, 255, 255, 2, 0, 255, 0),
};
