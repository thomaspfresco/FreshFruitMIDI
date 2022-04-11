#include <CapacitiveSensor.h>

//# define DEBUG 1
# define ATMEGA328 1

#ifdef ATMEGA328
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
#endif

byte note = 36;
byte midiCh = 1;

const int N = 8;

bool states[N];

CapacitiveSensor   cs_12_3 = CapacitiveSensor(12,3);       
CapacitiveSensor   cs_12_4 = CapacitiveSensor(12,4);        
CapacitiveSensor   cs_12_5 = CapacitiveSensor(12,5);    
CapacitiveSensor   cs_12_6 = CapacitiveSensor(12,6);    
CapacitiveSensor   cs_12_8 = CapacitiveSensor(12,8);     
CapacitiveSensor   cs_12_9 = CapacitiveSensor(12,9);        
CapacitiveSensor   cs_12_10 = CapacitiveSensor(12,10); 
CapacitiveSensor   cs_12_11 = CapacitiveSensor(12,11);   

CapacitiveSensor cs[N] = {cs_12_3,cs_12_4,cs_12_5,cs_12_6,cs_12_8,cs_12_9,cs_12_10,cs_12_11};

void setup() { 
  
  #ifdef ATMEGA328
  Serial.begin(115200);
  //MIDI.begin(MIDI_CHANNEL_OMNI);
  #elif DEBUG
  Serial.begin(9600);
  #endif

  pinMode(LED_BUILTIN, OUTPUT);

  for (int i = 0; i<N; i++) {
    states[i] = false;
    cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  }
}

void loop() {
  long touch;
  
  for (int i = 0; i<N; i++) {
    touch = cs[i].capacitiveSensor(1000);
    if (touch > 1000) {
      if (states[i]==false) {
      #ifdef ATMEGA328
        MIDI.sendNoteOn(note+i, 127, midiCh);
      #elif DEBUG
        Serial.print(i+1);
        Serial.println(": button on");
      #endif
      digitalWrite(LED_BUILTIN, HIGH);
      }
      
    states[i]=true;
    §   
    }else {
      
    if (states[i]==true) {
      #ifdef ATMEGA328
        MIDI.sendNoteOn(note+i, 0, midiCh);
      #elif DEBUG
        Serial.print(i+1);
        Serial.println(": button off");
    #endif
    digitalWrite(LED_BUILTIN, LOW);
    }
    states[i]=false;
  }
  }
}
 
