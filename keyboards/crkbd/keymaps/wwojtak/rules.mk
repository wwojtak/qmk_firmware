RGBLIGHT_ENABLE    = no
RGB_MATRIX_ENABLE  = WS2812
NKRO_ENABLE        = yes
OLED_DRIVER_ENABLE = yes
TAP_DANCE_ENABLE = no
EXTRAKEY_ENABLE = yes

BOOTMAGIC_ENABLE           = no  # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE            = no  # Mouse keys(+4700)
CONSOLE_ENABLE             = no  # Console for debug(+400)
COMMAND_ENABLE             = no  # Commands for debug and configuration
RAW_ENABLE = yes

CFLAGS += -flto
