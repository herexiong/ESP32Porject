// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void showScanResult_Animation(lv_obj_t * TargetObject, int delay);


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Screen1Spinner1;
lv_obj_t * ui_Screen1Panel1;
void ui_event_Screen1Switch1(lv_event_t * e);
lv_obj_t * ui_Screen1Switch1;
lv_obj_t * ui_Screen1Label1;
lv_obj_t * ui_Screen1ContainerScanResult;
void ui_event_ResultContainer1(lv_event_t * e);
lv_obj_t * ui_ResultContainer1;
lv_obj_t * ui_ResultLabel1;
void ui_event_ResultContainer2(lv_event_t * e);
lv_obj_t * ui_ResultContainer2;
lv_obj_t * ui_ResultLabel2;
void ui_event_ResultContainer3(lv_event_t * e);
lv_obj_t * ui_ResultContainer3;
lv_obj_t * ui_ResultLabel3;
void ui_event_ResultContainer4(lv_event_t * e);
lv_obj_t * ui_ResultContainer4;
lv_obj_t * ui_ResultLabel4;
void ui_event_ResultContainer5(lv_event_t * e);
lv_obj_t * ui_ResultContainer5;
lv_obj_t * ui_ResultLabel5;
void ui_event_ResultContainer6(lv_event_t * e);
lv_obj_t * ui_ResultContainer6;
lv_obj_t * ui_ResultLabel6;
void ui_event_ResultContainer7(lv_event_t * e);
lv_obj_t * ui_ResultContainer7;
lv_obj_t * ui_ResultLabel7;
void ui_event_ResultContainer8(lv_event_t * e);
lv_obj_t * ui_ResultContainer8;
lv_obj_t * ui_ResultLabel8;
void ui_event_ResultContainer9(lv_event_t * e);
lv_obj_t * ui_ResultContainer9;
lv_obj_t * ui_ResultLabel9;
void ui_event_ResultContainer10(lv_event_t * e);
lv_obj_t * ui_ResultContainer10;
lv_obj_t * ui_ResultLabel10;


// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
lv_obj_t * ui_Screen2;
lv_obj_t * ui_Keyboard1;
lv_obj_t * ui_Screen2SSIDLabel;
lv_obj_t * ui_Screen2PWDTextArea;
void ui_event_Screen2ConnectBTN(lv_event_t * e);
lv_obj_t * ui_Screen2ConnectBTN;
lv_obj_t * ui_Screen2BTNLabel;


// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
lv_obj_t * ui_Screen3;
lv_obj_t * ui_Screen3Spinner1;
lv_obj_t * ui_Screen3ResultBTN1;
void ui_event_Srceen3BTNLabel1(lv_event_t * e);
lv_obj_t * ui_Srceen3BTNLabel1;
lv_obj_t * ui_Screen3WiFiInfoPanel;
lv_obj_t * ui_Screen3WiFiSSID;
lv_obj_t * ui_Screen3WiFiPWD;
lv_obj_t * ui_Screen3WiFiINFOLabel1;
lv_obj_t * ui_Screen3WiFiINFOLabel2;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void showScanResult_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 800);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 430, 40);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_Screen1Switch1(lv_event_t * e)//wifi开关回调函数
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _ui_flag_modify(ui_Screen1Spinner1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        wifi_open(e);
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _ui_flag_modify(ui_Screen1Spinner1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        lv_obj_add_flag(ui_Screen1ContainerScanResult, LV_OBJ_FLAG_HIDDEN);     /// Flags
        lv_obj_add_flag(ui_ResultContainer1, LV_OBJ_FLAG_HIDDEN);     /// Flags
        lv_obj_add_flag(ui_ResultContainer2, LV_OBJ_FLAG_HIDDEN);     /// Flags
        lv_obj_add_flag(ui_ResultContainer3, LV_OBJ_FLAG_HIDDEN);     /// Flags
        lv_obj_add_flag(ui_ResultContainer4, LV_OBJ_FLAG_HIDDEN);     /// Flags
        lv_obj_add_flag(ui_ResultContainer5, LV_OBJ_FLAG_HIDDEN);     /// Flags
        lv_obj_add_flag(ui_ResultContainer6, LV_OBJ_FLAG_HIDDEN);     /// Flags
        lv_obj_add_flag(ui_ResultContainer7, LV_OBJ_FLAG_HIDDEN);     /// Flags
        lv_obj_add_flag(ui_ResultContainer8, LV_OBJ_FLAG_HIDDEN);     /// Flags
        lv_obj_add_flag(ui_ResultContainer9, LV_OBJ_FLAG_HIDDEN);     /// Flags
        lv_obj_add_flag(ui_ResultContainer10, LV_OBJ_FLAG_HIDDEN);    /// Flags
        wifi_close(e);
    }
}
void ui_event_ResultContainer1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Screen1WiFiBTN(e);
    }
}
void ui_event_ResultContainer2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Screen1WiFiBTN(e);
    }
}
void ui_event_ResultContainer3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Screen1WiFiBTN(e);
    }
}
void ui_event_ResultContainer4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Screen1WiFiBTN(e);
    }
}
void ui_event_ResultContainer5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Screen1WiFiBTN(e);
    }
}
void ui_event_ResultContainer6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Screen1WiFiBTN(e);
    }
}
void ui_event_ResultContainer7(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Screen1WiFiBTN(e);
    }
}
void ui_event_ResultContainer8(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Screen1WiFiBTN(e);
    }
}
void ui_event_ResultContainer9(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Screen1WiFiBTN(e);
    }
}
void ui_event_ResultContainer10(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Screen1WiFiBTN(e);
    }
}

//存储SSID和PassWord用于第三屏显示
char WIFI_SSID[50];
char PASSWORD[50];
char IPV4ADDR[20];
char GATEWAY[20];
char RSSI[10];//信号强度

extern int wifi_connected;

void screen3_reset(void){
    lv_obj_add_flag(ui_Screen3WiFiInfoPanel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Screen3ResultBTN1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Screen3Spinner1, LV_OBJ_FLAG_HIDDEN);
}

void ui_event_Screen2ConnectBTN(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        //连接wifi
        //获取ssid
        strcpy(WIFI_SSID,lv_label_get_text(ui_Screen2SSIDLabel));
        strcpy(PASSWORD,lv_textarea_get_text(ui_Screen2PWDTextArea));        
        printf("Text in ui_Screen2PWDTextArea: %s\n", PASSWORD);
        //断开WiFi
        if (wifi_connected)
        {
            esp_wifi_disconnect();
            wifi_connected = 0; 
            // vTaskDelay(1000 / portTICK_PERIOD_MS); // 延迟1秒

        }

        // WiFi 配置
        wifi_config_t wifi_config = {
            .sta = {
                .ssid = {0},
                .password = {0},
                .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            },
        };
        // 拷贝 SSID 和密码到配置结构体中
        strncpy((char *)wifi_config.sta.ssid, WIFI_SSID, sizeof(wifi_config.sta.ssid));
        strncpy((char *)wifi_config.sta.password, PASSWORD, sizeof(wifi_config.sta.password)); 
        esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
        
        esp_wifi_connect();
        screen3_reset();
        _ui_screen_change(&ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen3_screen_init);
    }
}

void ui_event_Srceen3BTNLabel1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    printf("ui_event_Srceen3BTNLabel1");
    if(event_code == LV_EVENT_CLICKED) {
        Screen3BTNEvent(e);
        printf("ui_event_Srceen3BTNLabel1 called");
        _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, &ui_Screen1_screen_init);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    ui_Screen3_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}