//////////Timer Kurulmasi icin Gerekli Ayarlar ////////////////
hw_timer_t * timer = NULL; 
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTimer();
int secondcounter=0; 
int minutecounter=0;
int cnt=0; 
int SendFlag=0;
#define SENDTIME  15  //(dakika)
void setup() {
 ///////// Timer Kurulumu ////////////////
  timer = timerBegin(0, 80, true); // Divider ayari
  timerAttachInterrupt(timer, &onTimer, true); // Timer interrupt fonksiyon kurulumu
  timerAlarmWrite(timer, 1000000, true); // Timer interrupt verme suresi (1 saniye)
  timerAlarmEnable(timer);              //timer enable

}

void loop() {
  

}
void IRAM_ATTR onTimer() {
  
  portENTER_CRITICAL_ISR(&timerMux);
  secondcounter++; // saniye sayaci
  cnt++;// Ekran guncellleme icin kullanılan sayac
  if(secondcounter>=60){secondcounter=0; minutecounter++;} // dakika sayaci
  if(minutecounter>=SENDTIME){secondcounter=0; minutecounter=0;SendFlag=1;} // RF yollama islemi icin flag verme 
  portEXIT_CRITICAL_ISR(&timerMux);
}
