#include <Arduino.h>
#include <EEPROM.h>
#include <Bounce2.h>

#define LEFT_EYE    1
#define RIGHT_EYE   2
#define MOUTH_INNER 3
#define MOUTH_OUTER 4

#define PUSH 0

uint16_t eeprom_mode_address = 0;

Bounce push_button = Bounce();

void reset_LEDs();
void set_status_LED();

uint8_t get_mode();
uint8_t increment_mode();
void animate();

struct step_t{
	uint32_t d;   // Duration of this step
	uint8_t a[4]; // Bit sequence to show on this step
};

const uint8_t num_seqs = 5;
const uint8_t seq_steps = 8;

uint8_t curr_seq = 0;
uint32_t seq_lengths[num_seqs] = {0,0,0};

step_t seqs[num_seqs][seq_steps] = {
	{
		// Sequence 0 = occasional wink
		{4000, {1,1,1,1}},
		{150, {0,1,1,1}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}}
	},
	{
		// Sequence 1 = smiling up and down
		{0, {1,1,0,0}},
		{500, {1,1,1,0}},
		{500, {1,1,1,1}},
		{500, {1,1,1,0}},
		{500, {1,1,1,1}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}}
	},
	{
		// Sequence 2 = eyes flashing
		{250, {1,1,1,0}},
		{250, {0,0,1,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}}
	},
	{
		// Sequence 3 = spiral chase
		{65, {0,0,0,1}},
		{65, {0,0,1,1}},
		{65, {0,1,1,1}},
		{65, {1,1,1,1}},
		{65, {1,1,1,0}},
		{65, {1,1,0,0}},
		{65, {1,0,0,0}},
		{65, {0,0,0,0}}
	},
	{
		// Sequence 4 = off
		{1000, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}},
		{0, {0,0,0,0}}
	}
};

// On bootup
void setup() {
	// Setup pin defs
	pinMode(LEFT_EYE, 	OUTPUT);
	pinMode(RIGHT_EYE, 	OUTPUT);
	pinMode(MOUTH_INNER, OUTPUT);
	pinMode(MOUTH_OUTER, OUTPUT);
	push_button.attach(PUSH,INPUT_PULLUP);

	// Fetch the mode
  	curr_seq = get_mode();

	// Get animation lengths
	for(uint8_t i=0; i<num_seqs; i++){
		for(uint8_t j=0; j<seq_steps; j++){
			seq_lengths[i] += seqs[i][j].d;
		}
	}
  
}

// the loop function runs over and over again forever
void loop() {  

   // Handle button push to advance to next mode
	push_button.update(); 
   if(push_button.rose()) { 
		curr_seq = increment_mode();
   }

	animate();
}

// Simple animation looper
void animate(){
	uint32_t progress = millis() % seq_lengths[curr_seq];
	uint32_t tmp_counter = 0;

	for(uint8_t i=0; i<seq_steps; i++){
		tmp_counter += seqs[curr_seq][i].d;
		if(progress <= tmp_counter){
			digitalWrite(LEFT_EYE, 		seqs[curr_seq][i].a[0]);
			digitalWrite(RIGHT_EYE, 	seqs[curr_seq][i].a[1]);
			digitalWrite(MOUTH_INNER, 	seqs[curr_seq][i].a[2]);
			digitalWrite(MOUTH_OUTER, 	seqs[curr_seq][i].a[3]);
			break;
		}
	}
}


// Turn off everything
void reset_LEDs(){
  digitalWrite(LEFT_EYE, LOW);
  digitalWrite(RIGHT_EYE, LOW);
  digitalWrite(MOUTH_INNER, LOW);
  digitalWrite(MOUTH_OUTER, LOW);
}

// Save and restore the mode from EEPROM
uint8_t get_mode(){
	uint8_t new_mode;
	EEPROM.get(eeprom_mode_address, new_mode);
	if(new_mode >= num_seqs){
		new_mode = 0;
	}
	return new_mode;
}
uint8_t increment_mode(){
	uint8_t new_mode = curr_seq;
	new_mode++;
	if(new_mode >= num_seqs){
		new_mode = 0;
	}
	EEPROM.put(eeprom_mode_address, new_mode);
	return new_mode;
}
