// based on https://github.com/qmk/qmk_firmware/blob/master/keyboards/kyria/keymaps/j-inc/keymap.c

// In your rules.mk make sure you have:
// OLED_DRIVER_ENABLE = yes
// WPM_ENABLE = yes

// WPM-responsive animation stuff here
#    define IDLE_FRAMES 5
#    define IDLE_SPEED 15  // below this wpm value your animation will idle

// #define PREP_FRAMES 1 // uncomment if >1

#    define TAP_FRAMES 2
#    define TAP_SPEED 30  // above this wpm value typing animation to trigger

#    define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
#    define ANIM_SIZE 636  // number of bytes in array, minimize for adequate firmware size, max is 1024

uint32_t anim_timer         = 0;
uint32_t anim_sleep         = 0;
uint8_t  current_idle_frame = 0;
// uint8_t current_prep_frame = 0; // uncomment if PREP_FRAMES >1
uint8_t current_tap_frame = 0;

// Code containing pixel art, contains:
// 5 idle frames, 1 prep frame, and 2 tap frames

// To make your own pixel art:
// save a png/jpeg of an 128x32 image (resource: https://www.pixilart.com/draw )
// follow this guide up to and including "CONVERT YOUR IMAGE" https://docs.splitkb.com/hc/en-us/articles/360013811280-How-do-I-convert-an-image-for-use-on-an-OLED-display-
// replace numbers in brackets with your own
// if you start getting errors when compiling make sure you didn't accedentally delete a bracket
static void render_anim(void) {
    static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x20, 0x18, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc1, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x80, 0x80, 0x40, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x18, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x83, 0x83, 0x40, 0x40, 0x40, 0x40, 0x20, 0x21, 0x21, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x30, 0x40, 0x80, 0x80, 0x00, 0x00, 0x01, 0x86, 0x98, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x0f, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x41, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                                                              {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc1, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x86, 0x86, 0x40, 0x40, 0x40, 0x40, 0x21, 0x22, 0x22, 0x20, 0x11, 0x11, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x30, 0x40, 0x80, 0x80, 0x00, 0x00, 0x01, 0x86, 0x98, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x0f, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x41, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                                                              {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x82, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x60, 0x60, 0x00, 0x01, 0x01, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x86, 0x86, 0x40, 0x40, 0x40, 0x40, 0x21, 0x22, 0x22, 0x20, 0x11, 0x11, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x30, 0x40, 0x80, 0x80, 0x00, 0x00, 0x01, 0x86, 0x98, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x0f, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x41, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                                                              {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x34, 0xc4, 0x04, 0x04, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x80, 0x80, 0x40, 0x00, 0x00, 0x30, 0x30, 0x00, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x18, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x83, 0x83, 0x40, 0x40, 0x40, 0x40, 0x20, 0x21, 0x21, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x30, 0x40, 0x80, 0x80, 0x00, 0x00, 0x01, 0x86, 0x98, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x0f, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x41, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                                                              {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x20, 0x18, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0d, 0x31, 0xc1, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x80, 0x80, 0x40, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x18, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x83, 0x83, 0x40, 0x40, 0x40, 0x40, 0x20, 0x21, 0x21, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x30, 0x40, 0x80, 0x80, 0x00, 0x00, 0x01, 0x86, 0x98, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x0f, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x41, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
    static const char PROGMEM prep[][ANIM_SIZE]            = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc1, 0x01, 0x01, 0x02, 0x02, 0x04, 0x84, 0x44, 0x44, 0x42, 0x82, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x80, 0x80, 0x40, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x64, 0x18, 0x04, 0x12, 0xc2, 0xca, 0x24, 0x88, 0xf0, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x18, 0x06, 0x01, 0x00, 0x00, 0x0c, 0x03, 0x00, 0x02, 0x18, 0x19, 0x00, 0x05, 0xfe, 0x80, 0x83, 0x83, 0x40, 0x40, 0x40, 0x40, 0x20, 0x21, 0x21, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x0f, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
    static const char PROGMEM tap[TAP_FRAMES][ANIM_SIZE]   = {
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc1, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x80, 0x80, 0x40, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x64, 0x18, 0x04, 0x12, 0xc2, 0xca, 0x24, 0x88, 0xf0, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x18, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x83, 0x83, 0x40, 0x40, 0x40, 0x40, 0x20, 0x21, 0x21, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x0f, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x41, 0x42, 0x24, 0x98, 0xc0, 0x88, 0x88, 0x8c, 0x9c, 0x1c, 0x1e, 0x0e, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc1, 0x01, 0x01, 0x02, 0x02, 0x04, 0x84, 0x44, 0x44, 0x42, 0x82, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x80, 0x80, 0x40, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x18, 0x06, 0x01, 0x00, 0x00, 0x0c, 0x03, 0x00, 0x02, 0x18, 0x19, 0x00, 0x05, 0xfe, 0x80, 0x83, 0x83, 0x40, 0x40, 0x40, 0x40, 0x20, 0x21, 0x21, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x30, 0x40, 0x80, 0x80, 0x00, 0x00, 0x01, 0x86, 0x98, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x0f, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0f, 0x0f, 0x07, 0x03, 0x03, 0x61, 0xf0, 0xf8, 0xfc, 0x60, 0x01, 0x01, 0x01, 0x3c, 0x78, 0xf8, 0xf0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    };

    // assumes 1 frame prep stage
    void animation_phase(void) {
        if (get_current_wpm() <= IDLE_SPEED) {
            current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
            oled_write_raw_P(idle[abs((IDLE_FRAMES - 1) - current_idle_frame)], ANIM_SIZE);
        }
        if (get_current_wpm() > IDLE_SPEED && get_current_wpm() < TAP_SPEED) {
            // oled_write_raw_P(prep[abs((PREP_FRAMES-1)-current_prep_frame)], ANIM_SIZE); // uncomment if IDLE_FRAMES >1
            oled_write_raw_P(prep[0], ANIM_SIZE);  // remove if IDLE_FRAMES >1
        }
        if (get_current_wpm() >= TAP_SPEED) {
            current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
            oled_write_raw_P(tap[abs((TAP_FRAMES - 1) - current_tap_frame)], ANIM_SIZE);
        }
    }
    if (get_current_wpm() != 000) {
        oled_on();  // not essential but turns on animation OLED with any alpha keypress
        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}