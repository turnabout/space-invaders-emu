#include <stdint.h>

enum SoundEffects {
	SFX_UFO, // Repeats
	SFX_Shot,
	SFX_Player_Die,
	SFX_Invader_Die,
	SFX_Fleet_Movement_1,
	SFX_Fleet_Movement_2,
	SFX_Fleet_Movement_3,
	SFX_Fleet_Movement_4,
	SFX_UFO_Hit,
	SFX_AMOUNT
};

// Play sound effect corresponding to a sound effect specified in the 
// SoundEffects enum
void Play_Sound(uint8_t sfxN);

// Stop sound effect
void Stop_Sound(uint8_t sfxN);

// Initialize the sound player, making it usable
void Init_Sound_Player();