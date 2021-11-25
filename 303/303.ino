#include <MozziGuts.h>

#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/saw2048_int8.h>
#include <tables/square_no_alias_2048_int8.h>
#include <tables/triangle_dist_cubed_2048_int8.h>
#include <EventDelay.h>
#include <ADSR.h>
#include <LowPassFilter.h>
#include "pitches.h"
#include "pins.h"

#include <PinButton.h>

#include <mozzi_rand.h>

#define CONTROL_RATE 256

Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSaw(SAW2048_DATA);
Oscil <SQUARE_NO_ALIAS_2048_NUM_CELLS, AUDIO_RATE> aSquare(SQUARE_NO_ALIAS_2048_DATA);
Oscil <TRIANGLE_DIST_CUBED_2048_NUM_CELLS, AUDIO_RATE> aTriangle(TRIANGLE_DIST_CUBED_2048_DATA);

Oscil <2048, AUDIO_RATE> aOsc;

enum OscType {
  saw,
  squareWave,
  triangle
};
/*
enum State {
  stopped,
  play,
  recording
};
*/
enum OscType oscType = saw;

// enum State state = stopped;

EventDelay noteChange;
LowPassFilter lpf;
ADSR <CONTROL_RATE, CONTROL_RATE> envelope;

PinButton oscToggle(WAVEFORM_PIN);
PinButton playButton(PLAY_PIN);
PinButton recordButton(RECORD_PIN);

PinButton buttons[2] = {
  oscToggle,
  playButton
};

boolean playing = true;
boolean recording = false;
boolean led = false;

int pattern[8] = {0, 0, 3, 5, 0, 7, 0, 12};
int patternIndex = 0;
int oct = 2;
int freq = 440;
int tempo = 80;
int key = 0;
int attack_level, attack, decay_level, decay, sustain, release_ms, cutoff, resonance, gain;
uint16_t cutoff_freq;

void setup() {
  pinMode(PLAY_PIN, INPUT_PULLUP);
  pinMode(WAVEFORM_PIN, INPUT_PULLUP);
  pinMode(RECORD_PIN, INPUT_PULLUP);
  pinMode(RECORD_LED, OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  startMozzi(CONTROL_RATE);
  noteChange.set(200);
  randSeed();
  aOsc = aSaw;
  aOsc.setFreq(PITCHES[oct][pattern[patternIndex]]);
}


void updateControl() {

  playButton.update();
  oscToggle.update();
  recordButton.update();
  
  if (playButton.isClick() || playButton.isSingleClick()) {
    ledEvent();
    playing = !playing;
  }

  if (oscToggle.isClick() || oscToggle.isSingleClick()) {
    ledEvent();
    
    if (oscType == saw) {
      aOsc = aSquare;
      oscType = squareWave;
    } else if (oscType == squareWave) {
      aOsc = aTriangle;
      oscType = triangle;
    } else if (oscType == triangle) {
      aOsc = aSaw;
      oscType = saw;
    }
  }

  if (recordButton.isClick() || recordButton.isSingleClick()) {
    recording = !recording;
    if (recording) {
      digitalWrite(RECORD_LED, HIGH);
      playing = false;
      patternIndex = 0;
    } else {
      digitalWrite(RECORD_LED, LOW);
    }
  }

  tempo = map(mozziAnalogRead(TEMPO_PIN), 0, 1024, 80, 220);
  oct = map(mozziAnalogRead(OCT_PIN), 0, 1024, 0, 3);
  cutoff = map(mozziAnalogRead(CUTOFF_PIN), 0, 1024, 10, 255);
  resonance = map(mozziAnalogRead(RESONANCE_PIN), 0, 1024, 0, 255);
  attack_level = map(mozziAnalogRead(ATTACK_PIN), 0, 1024, 0, 255);
  decay_level = map(mozziAnalogRead(DECAY_PIN), 0, 1024, 0, 255);
  
  tempo = 60000/(tempo<<1);

  if (recording) {
    key = mozziAnalogRead(KEYS_PIN);
    for (int i=0; i < 13; i++) {
      if (KEYS[i] == key) {
        pattern[patternIndex] = i;
        patternIndex++;
        break;
      }
    }

    if (patternIndex == 8) {
      digitalWrite(RECORD_LED, LOW);
      patternIndex = 0;
      recording = false;  
    }
  }

  
  if (noteChange.ready() && playing) {

    // ADSR
    envelope.setADLevels(attack_level, decay_level);
    attack = map(attack_level, 0, 255, 0, 100);
    decay = map(decay_level, 0, 255, 0, 200);
    sustain = 10;
    release_ms = 0;

    envelope.setTimes(attack, decay, sustain, release_ms);
    envelope.noteOn();

    // Oscillator Frequency
    freq = PITCHES[oct][pattern[patternIndex]];
    patternIndex++;
    if (patternIndex > 7) {
      patternIndex = 0;
    }
    aOsc.setFreq(freq);

    // NoteDelay
    noteChange.set(tempo);
    noteChange.start();
  }

  lpf.setCutoffFreqAndResonance(cutoff, resonance);

  envelope.update();
  gain = envelope.next();
}

AudioOutput_t updateAudio() {
  if (playing) {
    int asig = lpf.next(aOsc.next()>>2)>>1;
    return MonoOutput::from16Bit((int) (gain * asig));  
  }
  
}

void loop() {
  audioHook();
}

void updateButtons() {
  for (int i=0; i < (sizeof(buttons) / sizeof(buttons[0])); i++) {
    buttons[i].update();
  }
}

void ledEvent() {
  Serial.println("click");
  led = !led;
  digitalWrite(LED_BUILTIN, led);
}
