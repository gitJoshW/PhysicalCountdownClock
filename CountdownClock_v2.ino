/* Heavily leveraged examples from Rui Santos & Sara Santos - Random Nerd Tutorials
*/

#include <SPI.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include <RTClib.h>
#include <image_small.h>
#include <planeOverShip.h>

RTC_DS3231 rtc;

TFT_eSPI tft = TFT_eSPI();

// Touchscreen pins
#define XPT2046_IRQ 35   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 34  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define FONT_SIZE 2

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

LV_IMAGE_DECLARE(planeOverShip);
LV_IMAGE_DECLARE(image_small);

lv_obj_t *img_bg;
lv_obj_t *label; 
int currentImgNum;

//Set Countdown Date
DateTime target = DateTime(2026, 2, 12, 0, 0, 0);

//Prevent screen from registering too many events per second
unsigned long previousMillis = 0;
const long interval = 500; // Update every half second

void draw_image(void) {
  img_bg = lv_image_create(lv_screen_active());
  lv_image_set_src(img_bg, &image_small);
  lv_obj_align(img_bg, LV_ALIGN_CENTER, 0, 0);
  
  //adding a label on the text
  label = lv_label_create(lv_screen_active());

  //style the label
  static lv_style_t style_label;
  lv_style_init(&style_label);
  lv_style_set_text_font(&style_label, &lv_font_montserrat_24); 
  lv_style_set_text_color(&style_label, lv_color_hex(0xFEFEFE));
  lv_obj_add_style(label, &style_label, LV_PART_MAIN);
  lv_style_set_bg_opa(&style_label, LV_OPA_TRANSP);

  lv_label_set_text(label, "");

  lv_obj_align(img_bg, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, -60);
  
}


void setup() {

  Serial.begin(115200);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  currentImgNum = 1;

  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);

  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
  touchscreen.setRotation(1);

  // Start the tft display
  tft.init();
  // Set the TFT display rotation in landscape mode
  tft.setRotation(1);


// Start LVGL
  lv_init();

  // Create a display object
  lv_display_t * disp;
  // Initialize the TFT display using the TFT_eSPI library
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);
    
  // Function to draw the image
  draw_image();

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

}

void updateBackground(int imageNum) {
  if(imageNum == 1) {
    lv_image_set_src(img_bg, &image_small);
    lv_obj_align(img_bg, LV_ALIGN_CENTER, 0, 0);
  }
  else if(imageNum == 2) {
    lv_image_set_src(img_bg, &planeOverShip);
    lv_obj_align(img_bg, LV_ALIGN_CENTER, 0, 0);    
  }
}

void loop() {

    unsigned long currentMillis = millis();    

    // Get the current time from the RTC
    DateTime now = rtc.now();

    //Trying to Compare difference in Dates
    TimeSpan ts = target - now;
    String difStr = String(ts.days());
    String difHoursStr = String(ts.hours());
    String difMinStr = String(ts.minutes());
    String difSecStr = String(ts.seconds());

    String formattedDif = "Only \n" + difStr + " days, \n" + difHoursStr + " hours, \n" + difMinStr + " minutes, \n" + difSecStr + " seconds until \n ARUBA!";

    if (touchscreen.tirqTouched() && touchscreen.touched()) {
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        if(currentImgNum == 1) {
          updateBackground(2);
          currentImgNum = 2;
        }
        else if(currentImgNum == 2) {
          updateBackground(1);
          currentImgNum = 1;
        }
      }
    }

    lv_label_set_text(label, formattedDif.c_str());
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_center(label);
    lv_task_handler();  // let the GUI do its work
    lv_tick_inc(5);     // tell LVGL how much time has passed
    delay(5);
}
