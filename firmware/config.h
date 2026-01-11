#pragma once

/* Key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* Key matrix pins */
#define MATRIX_ROW_PINS { GP29, GP6, GP7 }
#define MATRIX_COL_PINS { GP26, GP27, GP28 }

/* Diode direction */
#define DIODE_DIRECTION COL2ROW

/* Rotary encoder settings */
#define ENCODER_RESOLUTION 4

#define ENCODER_ENABLE_CUSTOM
#define NUM_ENCODERS 1