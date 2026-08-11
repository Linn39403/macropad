#include "lock_screen.h"

#define LOCK_AUTO_LOCK_TIMEOUT_MS      (2000UL * 60UL * 60UL)
#define LOCK_SUCCESS_DISPLAY_TIME_MS    500UL
#define LOCK_SHAKE_OFFSET_PX            8
#define LOCK_SHAKE_STEP_TIME_MS         70U
#define LOCK_SHAKE_REPEAT_COUNT         3U

typedef enum {
    LOCK_enReady,
    LOCK_enFailureAnimation,
    LOCK_enSuccessAnimation,
} LOCK_teEntryState;

/*
 * This record is flash-resident and 256-byte aligned so the host UF2 tool can
 * locate and patch it inside one UF2 payload block. The all-zero PIN is invalid.
 */
static const volatile LOCK_tsPinRecord LOCK__stPinRecord
    __attribute__((used, section(".rodata.lock_pin"), aligned(256))) = {
        .m_au8Magic = LOCK_PIN_MAGIC_BYTES,
        .m_u8Version = LOCK_PIN_VERSION,
        .m_au8Pin = {0, 0, 0, 0},
        .m_u8Checksum = 0,
        .m_au8Guard = {LOCK_PIN_GUARD_0, LOCK_PIN_GUARD_1, LOCK_PIN_GUARD_2},
    };

static const uint16_t LOCK__au16PhysicalKeys[20] = {
    LOCK_KEY_0, LOCK_KEY_1, LOCK_KEY_2, LOCK_KEY_3,
    LOCK_KEY_4, LOCK_KEY_5, LOCK_KEY_6, LOCK_KEY_7,
    LOCK_KEY_8, LOCK_KEY_9, LOCK_KEY_10, LOCK_KEY_11,
    LOCK_KEY_12, LOCK_KEY_13, LOCK_KEY_14, LOCK_KEY_15,
    LOCK_KEY_16, LOCK_KEY_17, LOCK_KEY_18, LOCK_KEY_19,
};

static lv_obj_t *LOCK__spLockLabel;
static lv_obj_t *LOCK__aspPinLabels[LOCK_PIN_LENGTH];
static uint8_t LOCK__au8EnteredPin[LOCK_PIN_LENGTH];
static uint8_t LOCK__u8EnteredPinLength;
static uint32_t LOCK__u32SuccessTimer;
static uint32_t LOCK__u32AutoLockTimer;
static LOCK_teEntryState LOCK__enEntryState = LOCK_enReady;

void SCREEN_vSetLock(void);
void SCREEN_vSetUnLock(void);
bool SCREEN_boIsLock(void);
void SCREEN_vChangeLayer(uint8_t u8Layer);

static uint8_t LOCK__u8PinChecksum(const volatile uint8_t *pu8Pin)
{
    uint8_t u8Checksum = 0xA5U;
    for (uint8_t u8Index = 0; u8Index < LOCK_PIN_LENGTH; u8Index++) {
        u8Checksum = (uint8_t)((u8Checksum << 1) | (u8Checksum >> 7));
        u8Checksum ^= pu8Pin[u8Index];
    }
    return u8Checksum;
}

static bool LOCK__boPinRecordIsValid(void)
{
    uint8_t u8Difference = 0;
    u8Difference |= LOCK__stPinRecord.m_u8Version ^ LOCK_PIN_VERSION;
    u8Difference |= LOCK__stPinRecord.m_au8Guard[0] ^ LOCK_PIN_GUARD_0;
    u8Difference |= LOCK__stPinRecord.m_au8Guard[1] ^ LOCK_PIN_GUARD_1;
    u8Difference |= LOCK__stPinRecord.m_au8Guard[2] ^ LOCK_PIN_GUARD_2;

    for (uint8_t u8Index = 0; u8Index < LOCK_PIN_LENGTH; u8Index++) {
        if (LOCK__stPinRecord.m_au8Pin[u8Index] < 1U || LOCK__stPinRecord.m_au8Pin[u8Index] > 20U) {
            return false;
        }
    }
    return u8Difference == 0U && LOCK__u8PinChecksum(LOCK__stPinRecord.m_au8Pin) == LOCK__stPinRecord.m_u8Checksum;
}

static uint8_t LOCK__u8PhysicalKeyNumber(uint16_t u16KeyCode)
{
    for (uint8_t u8Index = 0; u8Index < ARRAY_SIZE(LOCK__au16PhysicalKeys); u8Index++) {
        if (LOCK__au16PhysicalKeys[u8Index] == u16KeyCode) {
            return u8Index + 1U;
        }
    }
    return 0U;
}

static void LOCK__vClearPinSlots(void)
{
    LOCK__u8EnteredPinLength = 0U;
    for (uint8_t u8Index = 0; u8Index < LOCK_PIN_LENGTH; u8Index++) {
        lv_label_set_text(LOCK__aspPinLabels[u8Index], "");
    }
}

static void LOCK__vResetLockedUi(void)
{
    LOCK__vClearPinSlots();
    LOCK__enEntryState = LOCK_enReady;
    lv_label_set_text(LOCK__spLockLabel, FA_LOCK_CODE);
    lv_obj_set_style_text_color(LOCK__spLockLabel, lv_color_hex(0xFF0000), LV_PART_MAIN);
    lv_obj_set_style_translate_x(LOCK__spLockLabel, 0, LV_PART_MAIN);
}

static bool LOCK__boEnteredPinMatches(void)
{
    uint8_t u8Difference = 0;
    if (!LOCK__boPinRecordIsValid()) {
        return false;
    }
    for (uint8_t u8Index = 0; u8Index < LOCK_PIN_LENGTH; u8Index++) {
        u8Difference |= LOCK__au8EnteredPin[u8Index] ^ LOCK__stPinRecord.m_au8Pin[u8Index];
    }
    return u8Difference == 0U;
}

static void LOCK__vSetIconTranslateX(void *pvObject, int32_t i32Offset)
{
    lv_obj_set_style_translate_x((lv_obj_t *)pvObject, i32Offset, LV_PART_MAIN);
}

static void LOCK__vFailureAnimationReady(lv_anim_t *pstAnimation)
{
    (void)pstAnimation;
    LOCK__vResetLockedUi();
}

static void LOCK__vStartFailureAnimation(void)
{
    lv_anim_t stAnimation;

    LOCK__enEntryState = LOCK_enFailureAnimation;
    lv_obj_set_style_text_color(LOCK__spLockLabel, lv_color_hex(0xFF3030), LV_PART_MAIN);
    lv_anim_init(&stAnimation);
    lv_anim_set_var(&stAnimation, LOCK__spLockLabel);
    lv_anim_set_exec_cb(&stAnimation, LOCK__vSetIconTranslateX);
    lv_anim_set_values(&stAnimation, -LOCK_SHAKE_OFFSET_PX, LOCK_SHAKE_OFFSET_PX);
    lv_anim_set_time(&stAnimation, LOCK_SHAKE_STEP_TIME_MS);
    lv_anim_set_playback_time(&stAnimation, LOCK_SHAKE_STEP_TIME_MS);
    lv_anim_set_repeat_count(&stAnimation, LOCK_SHAKE_REPEAT_COUNT);
    lv_anim_set_path_cb(&stAnimation, lv_anim_path_ease_in_out);
    lv_anim_set_ready_cb(&stAnimation, LOCK__vFailureAnimationReady);
    lv_anim_start(&stAnimation);
}

static void LOCK__vUnlock(void)
{
    SCREEN_vSetUnLock();
    LOCK__enEntryState = LOCK_enSuccessAnimation;
    LOCK__u32SuccessTimer = timer_read32();
    LOCK__u32AutoLockTimer = LOCK__u32SuccessTimer;
    lv_label_set_text(LOCK__spLockLabel, FA_UNLOCK_CODE);
    lv_obj_set_style_text_color(LOCK__spLockLabel, lv_color_hex(0x00FF00), LV_PART_MAIN);
}

void LOCK_vScreenCreate(lv_obj_t *spParentScreen)
{
    LOCK__spLockLabel = lv_label_create(spParentScreen);
    lv_label_set_text(LOCK__spLockLabel, FA_LOCK_CODE);
    lv_obj_set_style_text_font(LOCK__spLockLabel, &fa_lock_unlock, LV_PART_MAIN);
    lv_obj_set_style_text_color(LOCK__spLockLabel, lv_color_hex(0xFF0000), LV_PART_MAIN);
    lv_obj_align(LOCK__spLockLabel, LV_ALIGN_CENTER, 0, -32);

    for (uint8_t u8Index = 0; u8Index < LOCK_PIN_LENGTH; u8Index++) {
        lv_obj_t *spSlot = lv_obj_create(spParentScreen);
        int16_t i16OffsetX = ((int16_t)u8Index - 1) * 50 - 25;
        lv_obj_set_size(spSlot, 34, 34);
        lv_obj_align(spSlot, LV_ALIGN_CENTER, i16OffsetX, 44);
        lv_obj_set_style_bg_opa(spSlot, LV_OPA_TRANSP, LV_PART_MAIN);
        lv_obj_set_style_border_width(spSlot, 2, LV_PART_MAIN);
        lv_obj_set_style_border_color(spSlot, lv_color_hex(0xFF0000), LV_PART_MAIN);
        lv_obj_set_style_radius(spSlot, 4, LV_PART_MAIN);
        lv_obj_clear_flag(spSlot, LV_OBJ_FLAG_SCROLLABLE);

        LOCK__aspPinLabels[u8Index] = lv_label_create(spSlot);
        lv_obj_set_style_text_font(LOCK__aspPinLabels[u8Index], &lv_font_montserrat_24, LV_PART_MAIN);
        lv_obj_set_style_text_color(LOCK__aspPinLabels[u8Index], lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        lv_obj_center(LOCK__aspPinLabels[u8Index]);
    }
    LOCK__vResetLockedUi();
}

bool LOCK_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    uint8_t u8PhysicalKey = LOCK__u8PhysicalKeyNumber(u16KeyCode);

    if (!SCREEN_boIsLock() || LOCK__enEntryState != LOCK_enReady || u8PhysicalKey == 0U) {
        return false;
    }

    LOCK__au8EnteredPin[LOCK__u8EnteredPinLength] = u8PhysicalKey;
    lv_label_set_text(LOCK__aspPinLabels[LOCK__u8EnteredPinLength], "*");
    LOCK__u8EnteredPinLength++;

    if (LOCK__u8EnteredPinLength == LOCK_PIN_LENGTH) {
        if (LOCK__boEnteredPinMatches()) {
            LOCK__vUnlock();
        } else {
            LOCK__vStartFailureAnimation();
        }
    }
    return false;
}

bool LOCK_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    (void)u16KeyCode;
    return false;
}

void LOCK_vRotaryCallBackFunction(bool boClockwise)
{
    (void)boClockwise;
}

void LOCK_vRotaryButtonPressedCallBackFunction(void)
{
}

void LOCK_vHouseKeeping(void)
{
}

void LOCK_vLockTimerCheck(void)
{
    if (LOCK__enEntryState == LOCK_enSuccessAnimation &&
        timer_elapsed32(LOCK__u32SuccessTimer) >= LOCK_SUCCESS_DISPLAY_TIME_MS) {
        LOCK__enEntryState = LOCK_enReady;
        SCREEN_vChangeLayer(1);
    }

    if (!SCREEN_boIsLock() && LOCK__u32AutoLockTimer != 0U &&
        timer_elapsed32(LOCK__u32AutoLockTimer) >= LOCK_AUTO_LOCK_TIMEOUT_MS) {
        SCREEN_vSetLock();
        LOCK__u32AutoLockTimer = 0U;
        LOCK__vResetLockedUi();
        SCREEN_vChangeLayer(0);
    }
}
