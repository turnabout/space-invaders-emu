#include <windows.h>
#include <xaudio2.h>
#include <stdio.h>
#pragma comment(lib, "xaudio2.lib")

extern "C" {
	#include "Sound_Player.h"
}

// Reverse due to little-endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'

HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset);
void Init_Lists(uint8_t sfxN);

// Base sfxN file path - # is replaced by audio num
static char soundFilePath[] = "SI_Audio/#.wav";

// Index in soundFilePath that represents audio num
static const uint8_t pathNumIndex = 9;

// XAudio2 engine instance
static IXAudio2 *pXAudio2 = NULL;

// Master/Source Voices
static IXAudio2MasteringVoice *pMasterVoice = NULL;
static IXAudio2SourceVoice *pSourceVoices[SFX_AMOUNT];

// Lists of XAUDIO2_BUFFERs and WAVEFORMATEXTENSIBLEs for each sound
XAUDIO2_BUFFER bufferList[SFX_AMOUNT];

void Play_Sound(uint8_t sfxN)
{
	Stop_Sound(sfxN);

	// Submit appropriate XAUDIO2_BUFFER structure to the source voice
	if (FAILED(pSourceVoices[sfxN]->SubmitSourceBuffer(&bufferList[sfxN])))
	{
		printf("Submitting source buffer failed!\n");
	}

	// Actually play the sound
	pSourceVoices[sfxN]->Start();
}

void Stop_Sound(uint8_t sfxN)
{
	pSourceVoices[sfxN]->Stop();
}

void Init_Sound_Player()
{
	// XAudio2 instance
	XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);

	// Master voice instance
	pXAudio2->CreateMasteringVoice(&pMasterVoice);

	// Populate SFX XAUDIO2_BUFFER and Source Voice lists
	for (int i = 0; i < SFX_AMOUNT; i++)
	{
		Init_Lists(i);
	}
}

void Init_Lists(uint8_t sfxN)
{
	HANDLE hFile;
	DWORD dwChunkPos = 0;
	DWORD dwChunkSize;
	WAVEFORMATEXTENSIBLE wfx = { 0 };

	// Set audio file path number
	soundFilePath[pathNumIndex] = (char)('0' + sfxN);

	// Open the audio file
	hFile = CreateFile(
		soundFilePath,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("INVALID HANDLE VALUE\n");
	}

	// Locate fmt chunk and fill out WAVEFORMATEXTENSIBLE structure
	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPos);
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPos);

	// Locate data chunk, read its contents into a buffer
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPos);
	BYTE *pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPos);

	// Populate this SFX's XAUDIO2_BUFFER structure
	bufferList[sfxN].AudioBytes = dwChunkSize;
	bufferList[sfxN].pAudioData = pDataBuffer;
	bufferList[sfxN].Flags = XAUDIO2_END_OF_STREAM;

	// Make SFX UFO loop until stopped
	if (sfxN == SFX_UFO)
	{
		bufferList[sfxN].LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	// Create source voice
	if (FAILED(pXAudio2->CreateSourceVoice(&pSourceVoices[sfxN], (WAVEFORMATEX*)&wfx)))
	{
		printf("Creating source voice failed!\n");
	}
}

HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD &dwChunkSize, DWORD &dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;

		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}

		dwOffset += sizeof(DWORD)* 2;

		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}

	}

	return S_OK;
}

HRESULT ReadChunkData(HANDLE hFile, void *buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
	}
	return hr;
}