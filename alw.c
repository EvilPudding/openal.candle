#include "alw.h"
#ifdef _WIN32
#include <windows.h>
#elif !defined(__EMSCRIPTEN__)
#include <unistd.h>
#include <dlfcn.h>
#endif
#include "../candle/systems/sauces.h"


void (*alwAuxiliaryEffectSlotf)(ALuint effectslot, ALenum param, ALfloat value);
void (*alwAuxiliaryEffectSlotfv)(ALuint effectslot, ALenum param, const ALfloat *pflValues);
void (*alwAuxiliaryEffectSloti)(ALuint effectslot, ALenum param, ALint iValue);
void (*alwAuxiliaryEffectSlotiv)(ALuint effectslot, ALenum param, const ALint *piValues);
void (*alwBuffer3f)(ALuint buffer, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
void (*alwBuffer3i)(ALuint buffer, ALenum param, ALint value1, ALint value2, ALint value3);
void (*alwBufferData)(ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei freq);
void (*alwBufferf)(ALuint buffer, ALenum param, ALfloat value);
void (*alwBufferfv)(ALuint buffer, ALenum param, const ALfloat *values);
void (*alwBufferi)(ALuint buffer, ALenum param, ALint value);
void (*alwBufferiv)(ALuint buffer, ALenum param, const ALint *values);
void (*alwDeleteAuxiliaryEffectSlots)(ALsizei n, const ALuint *effectslots);
void (*alwDeleteBuffers)(ALsizei n, const ALuint *buffers);
void (*alwDeleteEffects)(ALsizei n, const ALuint *effects);
void (*alwDeleteFilters)(ALsizei n, const ALuint *filters);
void (*alwDeleteSources)(ALsizei n, const ALuint *sources);
void (*alwDisable)(ALenum capability);
void (*alwDistanceModel)(ALenum distanceModel);
void (*alwDopplerFactor)(ALfloat value);
void (*alwDopplerVelocity)(ALfloat value);
void (*alwEffectf)(ALuint effect, ALenum param, ALfloat flValue);
void (*alwEffectfv)(ALuint effect, ALenum param, const ALfloat *pflValues);
void (*alwEffecti)(ALuint effect, ALenum param, ALint iValue);
void (*alwEffectiv)(ALuint effect, ALenum param, const ALint *piValues);
void (*alwEnable)(ALenum capability);
void (*alwFilterf)(ALuint filter, ALenum param, ALfloat flValue);
void (*alwFilterfv)(ALuint filter, ALenum param, const ALfloat *pflValues);
void (*alwFilteri)(ALuint filter, ALenum param, ALint iValue);
void (*alwFilteriv)(ALuint filter, ALenum param, const ALint *piValues);
void (*alwGenAuxiliaryEffectSlots)(ALsizei n, ALuint *effectslots);
void (*alwGenBuffers)(ALsizei n, ALuint *buffers);
void (*alwGenEffects)(ALsizei n, ALuint *effects);
void (*alwGenFilters)(ALsizei n, ALuint *filters);
void (*alwGenSources)(ALsizei n, ALuint *sources);
void (*alwGetAuxiliaryEffectSlotf)(ALuint effectslot, ALenum param, ALfloat *pflValue);
void (*alwGetAuxiliaryEffectSlotfv)(ALuint effectslot, ALenum param, ALfloat *pflValues);
void (*alwGetAuxiliaryEffectSloti)(ALuint effectslot, ALenum param, ALint *piValue);
void (*alwGetAuxiliaryEffectSlotiv)(ALuint effectslot, ALenum param, ALint *piValues);
ALboolean (*alwGetBoolean)(ALenum param);
void (*alwGetBooleanv)(ALenum param, ALboolean *values);
void (*alwGetBuffer3f)(ALuint buffer, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
void (*alwGetBuffer3i)(ALuint buffer, ALenum param, ALint *value1, ALint *value2, ALint *value3);
void (*alwGetBufferf)(ALuint buffer, ALenum param, ALfloat *value);
void (*alwGetBufferfv)(ALuint buffer, ALenum param, ALfloat *values);
void (*alwGetBufferi)(ALuint buffer, ALenum param, ALint *value);
void (*alwGetBufferiv)(ALuint buffer, ALenum param, ALint *values);
ALdouble (*alwGetDouble)(ALenum param);
void (*alwGetDoublev)(ALenum param, ALdouble *values);
void (*alwGetEffectf)(ALuint effect, ALenum param, ALfloat *pflValue);
void (*alwGetEffectfv)(ALuint effect, ALenum param, ALfloat *pflValues);
void (*alwGetEffecti)(ALuint effect, ALenum param, ALint *piValue);
void (*alwGetEffectiv)(ALuint effect, ALenum param, ALint *piValues);
ALenum (*alwGetEnumValue)(const ALchar *ename);
ALenum (*alwGetError)(void);
void (*alwGetFilterf)(ALuint filter, ALenum param, ALfloat *pflValue);
void (*alwGetFilterfv)(ALuint filter, ALenum param, ALfloat *pflValues);
void (*alwGetFilteri)(ALuint filter, ALenum param, ALint *piValue);
void (*alwGetFilteriv)(ALuint filter, ALenum param, ALint *piValues);
ALfloat (*alwGetFloat)(ALenum param);
void (*alwGetFloatv)(ALenum param, ALfloat *values);
ALint (*alwGetInteger)(ALenum param);
void (*alwGetIntegerv)(ALenum param, ALint *values);
void (*alwGetListener3f)(ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
void (*alwGetListener3i)(ALenum param, ALint *value1, ALint *value2, ALint *value3);
void (*alwGetListenerf)(ALenum param, ALfloat *value);
void (*alwGetListenerfv)(ALenum param, ALfloat *values);
void (*alwGetListeneri)(ALenum param, ALint *value);
void (*alwGetListeneriv)(ALenum param, ALint *values);
void* (*alwGetProcAddress)(const ALchar *fname);
void (*alwGetSource3f)(ALuint source, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
void (*alwGetSource3i)(ALuint source, ALenum param, ALint *value1, ALint *value2, ALint *value3);
void (*alwGetSourcef)(ALuint source, ALenum param, ALfloat *value);
void (*alwGetSourcefv)(ALuint source, ALenum param, ALfloat *values);
void (*alwGetSourcei)(ALuint source,  ALenum param, ALint *value);
void (*alwGetSourceiv)(ALuint source,  ALenum param, ALint *values);
const ALchar* (*alwGetString)(ALenum param);
ALboolean (*alwIsAuxiliaryEffectSlot)(ALuint effectslot);
ALboolean (*alwIsBuffer)(ALuint buffer);
ALboolean (*alwIsEffect)(ALuint effect);
ALboolean (*alwIsEnabled)(ALenum capability);
ALboolean (*alwIsExtensionPresent)(const ALchar *extname);
ALboolean (*alwIsFilter)(ALuint filter);
ALboolean (*alwIsSource)(ALuint source);
void (*alwListener3f)(ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
void (*alwListener3i)(ALenum param, ALint value1, ALint value2, ALint value3);
void (*alwListenerf)(ALenum param, ALfloat value);
void (*alwListenerfv)(ALenum param, const ALfloat *values);
void (*alwListeneri)(ALenum param, ALint value);
void (*alwListeneriv)(ALenum param, const ALint *values);
void (*alwSource3f)(ALuint source, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
void (*alwSource3i)(ALuint source, ALenum param, ALint value1, ALint value2, ALint value3);
void (*alwSourcePause)(ALuint source);
void (*alwSourcePausev)(ALsizei n, const ALuint *sources);
void (*alwSourcePlay)(ALuint source);
void (*alwSourcePlayv)(ALsizei n, const ALuint *sources);
void (*alwSourceQueueBuffers)(ALuint source, ALsizei nb, const ALuint *buffers);
void (*alwSourceRewind)(ALuint source);
void (*alwSourceRewindv)(ALsizei n, const ALuint *sources);
void (*alwSourceStop)(ALuint source);
void (*alwSourceStopv)(ALsizei n, const ALuint *sources);
void (*alwSourceUnqueueBuffers)(ALuint source, ALsizei nb, ALuint *buffers);
void (*alwSourcef)(ALuint source, ALenum param, ALfloat value);
void (*alwSourcefv)(ALuint source, ALenum param, const ALfloat *values);
void (*alwSourcei)(ALuint source, ALenum param, ALint value);
void (*alwSourceiv)(ALuint source, ALenum param, const ALint *values);
void (*alwSpeedOfSound)(ALfloat value);
ALCboolean (*alwcCaptureCloseDevice)(ALCdevice *device);
ALCdevice* (*alwcCaptureOpenDevice)(const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize);
void       (*alwcCaptureSamples)(ALCdevice *device, ALCvoid *buffer, ALCsizei samples);
void       (*alwcCaptureStart)(ALCdevice *device);
void       (*alwcCaptureStop)(ALCdevice *device);
ALCboolean (*alwcCloseDevice)(ALCdevice *device);
ALCcontext* (*alwcCreateContext)(ALCdevice *device, const ALCint *attrlist);
void        (*alwcDestroyContext)(ALCcontext *context);
ALCdevice*  (*alwcGetContextsDevice)(ALCcontext *context);
ALCcontext* (*alwcGetCurrentContext)(void);
ALCenum    (*alwcGetEnumValue)(ALCdevice *device, const ALCchar *enumname);
ALCenum (*alwcGetError)(ALCdevice *device);
void           (*alwcGetIntegerv)(ALCdevice *device, ALCenum param, ALCsizei size, ALCint *values);
ALCvoid*   (*alwcGetProcAddress)(ALCdevice *device, const ALCchar *funcname);
const ALCchar* (*alwcGetString)(ALCdevice *device, ALCenum param);
ALCboolean (*alwcIsExtensionPresent)(ALCdevice *device, const ALCchar *extname);
ALCboolean  (*alwcMakeContextCurrent)(ALCcontext *context);
ALCdevice* (*alwcOpenDevice)(const ALCchar *devicename);
void        (*alwcProcessContext)(ALCcontext *context);
void        (*alwcSuspendContext)(ALCcontext *context);
const ALCchar* (*alwcGetStringiSOFT)(ALCdevice *device, ALCenum paramName, ALCsizei index);
ALCboolean (*alwcResetDeviceSOFT)(ALCdevice *device, const ALCint *attribs);

void alw_init(void)
{
#ifdef _WIN32
#define allib(l) LoadLibrary(l)
#define alsym(v, type, l, s) v = (type)GetProcAddress(l, #s)
#define alclose(l)
#elif defined(__EMSCRIPTEN__)
#define allib(l)
#define alsym(v, type, l, s) v = (type)s
#define alclose(l)
#else
#define allib(l) dlopen(l, RTLD_NODELETE)
#define alsym(v, type, l, s) v = (type)dlsym(l, #s)
#define alclose(l)
#endif

	FILE *fp;
#ifdef _WIN32
	HINSTANCE oallib;
	char lib_filename[MAX_PATH];  
	strcpy(lib_filename, "OpenAL32.dll");
	fp = fopen(lib_filename, "r");
	if (fp == NULL)
	{
		char temp_path[MAX_PATH];
		HANDLE fd, file_map;
		LPVOID address;
		size_t bytes_num;

		resource_t *sauce = c_sauces_get_sauce(c_sauces(&SYS), sauce_handle(lib_filename));
		char *bytes = c_sauces_get_bytes(c_sauces(&SYS), sauce, &bytes_num);

		GetTempPath(MAX_PATH, temp_path);
		GetTempFileName(temp_path, TEXT("tempoal"), 0, lib_filename);

		fd = CreateFile(lib_filename, GENERIC_READ | GENERIC_WRITE, 0, NULL,
				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		file_map = CreateFileMapping(fd, NULL, PAGE_READWRITE, 0, bytes_num, NULL);	    
		address = MapViewOfFile(file_map, FILE_MAP_WRITE, 0, 0, 0);	    
		CopyMemory(address, bytes, bytes_num);	    
		UnmapViewOfFile(address);
		CloseHandle(file_map);
		CloseHandle(fd);
	}
	oallib = allib(lib_filename);
#elif !defined(__EMSCRIPTEN__)
	void *oallib;
	char lib_filename[PATH_MAX];  
	strcpy(lib_filename, "libopenal.so");
	fp = fopen(lib_filename, "r");
	if (fp == NULL)
	{
		char temp_name[] = "/tmp/XXXXXXX";
		int fd = mkstemp(temp_name);
		size_t bytes_num;

		resource_t *sauce = c_sauces_get_sauce(c_sauces(&SYS), sauce_handle(lib_filename));
		char *bytes = c_sauces_get_bytes(c_sauces(&SYS), sauce, &bytes_num);

		if (write(fd, bytes, bytes_num) == -1)
		{
			printf("Failed to write to al shared library temp file.\n");
			exit(1);
		}
		close(fd);
	}
	oallib = allib(lib_filename);
#else
	void *oallib;
#endif

	alsym(alwAuxiliaryEffectSlotf, void (*)(ALuint effectslot, ALenum param, ALfloat value), oallib, alAuxiliaryEffectSlotf);
	alsym(alwAuxiliaryEffectSlotfv, void (*)(ALuint effectslot, ALenum param, const ALfloat *pflValues), oallib, alAuxiliaryEffectSlotfv);
	alsym(alwAuxiliaryEffectSloti, void (*)(ALuint effectslot, ALenum param, ALint iValue), oallib, alAuxiliaryEffectSloti);
	alsym(alwAuxiliaryEffectSlotiv, void (*)(ALuint effectslot, ALenum param, const ALint *piValues), oallib, alAuxiliaryEffectSlotiv);
	alsym(alwBuffer3f, void (*)(ALuint buffer, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3), oallib, alBuffer3f);
	alsym(alwBuffer3i, void (*)(ALuint buffer, ALenum param, ALint value1, ALint value2, ALint value3), oallib, alBuffer3i);
	alsym(alwBufferData, void (*)(ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei freq), oallib, alBufferData);
	alsym(alwBufferf, void (*)(ALuint buffer, ALenum param, ALfloat value), oallib, alBufferf);
	alsym(alwBufferfv, void (*)(ALuint buffer, ALenum param, const ALfloat *values), oallib, alBufferfv);
	alsym(alwBufferi, void (*)(ALuint buffer, ALenum param, ALint value), oallib, alBufferi);
	alsym(alwBufferiv, void (*)(ALuint buffer, ALenum param, const ALint *values), oallib, alBufferiv);
	alsym(alwDeleteAuxiliaryEffectSlots, void (*)(ALsizei n, const ALuint *effectslots), oallib, alDeleteAuxiliaryEffectSlots);
	alsym(alwDeleteBuffers, void (*)(ALsizei n, const ALuint *buffers), oallib, alDeleteBuffers);
	alsym(alwDeleteEffects, void (*)(ALsizei n, const ALuint *effects), oallib, alDeleteEffects);
	alsym(alwDeleteFilters, void (*)(ALsizei n, const ALuint *filters), oallib, alDeleteFilters);
	alsym(alwDeleteSources, void (*)(ALsizei n, const ALuint *sources), oallib, alDeleteSources);
	alsym(alwDisable, void (*)(ALenum capability), oallib, alDisable);
	alsym(alwDistanceModel, void (*)(ALenum distanceModel), oallib, alDistanceModel);
	alsym(alwDopplerFactor, void (*)(ALfloat value), oallib, alDopplerFactor);
	alsym(alwDopplerVelocity, void (*)(ALfloat value), oallib, alDopplerVelocity);
	alsym(alwEffectf, void (*)(ALuint effect, ALenum param, ALfloat flValue), oallib, alEffectf);
	alsym(alwEffectfv, void (*)(ALuint effect, ALenum param, const ALfloat *pflValues), oallib, alEffectfv);
	alsym(alwEffecti, void (*)(ALuint effect, ALenum param, ALint iValue), oallib, alEffecti);
	alsym(alwEffectiv, void (*)(ALuint effect, ALenum param, const ALint *piValues), oallib, alEffectiv);
	alsym(alwEnable, void (*)(ALenum capability), oallib, alEnable);
	alsym(alwFilterf, void (*)(ALuint filter, ALenum param, ALfloat flValue), oallib, alFilterf);
	alsym(alwFilterfv, void (*)(ALuint filter, ALenum param, const ALfloat *pflValues), oallib, alFilterfv);
	alsym(alwFilteri, void (*)(ALuint filter, ALenum param, ALint iValue), oallib, alFilteri);
	alsym(alwFilteriv, void (*)(ALuint filter, ALenum param, const ALint *piValues), oallib, alFilteriv);
	alsym(alwGenAuxiliaryEffectSlots, void (*)(ALsizei n, ALuint *effectslots), oallib, alGenAuxiliaryEffectSlots);
	alsym(alwGenBuffers, void (*)(ALsizei n, ALuint *buffers), oallib, alGenBuffers);
	alsym(alwGenEffects, void (*)(ALsizei n, ALuint *effects), oallib, alGenEffects);
	alsym(alwGenFilters, void (*)(ALsizei n, ALuint *filters), oallib, alGenFilters);
	alsym(alwGenSources, void (*)(ALsizei n, ALuint *sources), oallib, alGenSources);
	alsym(alwGetAuxiliaryEffectSlotf, void (*)(ALuint effectslot, ALenum param, ALfloat *pflValue), oallib, alGetAuxiliaryEffectSlotf);
	alsym(alwGetAuxiliaryEffectSlotfv, void (*)(ALuint effectslot, ALenum param, ALfloat *pflValues), oallib, alGetAuxiliaryEffectSlotfv);
	alsym(alwGetAuxiliaryEffectSloti, void (*)(ALuint effectslot, ALenum param, ALint *piValue), oallib, alGetAuxiliaryEffectSloti);
	alsym(alwGetAuxiliaryEffectSlotiv, void (*)(ALuint effectslot, ALenum param, ALint *piValues), oallib, alGetAuxiliaryEffectSlotiv);
	alsym(alwGetBoolean, ALboolean (*)(ALenum param), oallib, alGetBoolean);
	alsym(alwGetBooleanv, void (*)(ALenum param, ALboolean *values), oallib, alGetBooleanv);
	alsym(alwGetBuffer3f, void (*)(ALuint buffer, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3), oallib, alGetBuffer3f);
	alsym(alwGetBuffer3i, void (*)(ALuint buffer, ALenum param, ALint *value1, ALint *value2, ALint *value3), oallib, alGetBuffer3i);
	alsym(alwGetBufferf, void (*)(ALuint buffer, ALenum param, ALfloat *value), oallib, alGetBufferf);
	alsym(alwGetBufferfv, void (*)(ALuint buffer, ALenum param, ALfloat *values), oallib, alGetBufferfv);
	alsym(alwGetBufferi, void (*)(ALuint buffer, ALenum param, ALint *value), oallib, alGetBufferi);
	alsym(alwGetBufferiv, void (*)(ALuint buffer, ALenum param, ALint *values), oallib, alGetBufferiv);
	alsym(alwGetDouble, ALdouble (*)(ALenum param), oallib, alGetDouble);
	alsym(alwGetDoublev, void (*)(ALenum param, ALdouble *values), oallib, alGetDoublev);
	alsym(alwGetEffectf, void (*)(ALuint effect, ALenum param, ALfloat *pflValue), oallib, alGetEffectf);
	alsym(alwGetEffectfv, void (*)(ALuint effect, ALenum param, ALfloat *pflValues), oallib, alGetEffectfv);
	alsym(alwGetEffecti, void (*)(ALuint effect, ALenum param, ALint *piValue), oallib, alGetEffecti);
	alsym(alwGetEffectiv, void (*)(ALuint effect, ALenum param, ALint *piValues), oallib, alGetEffectiv);
	alsym(alwGetEnumValue, ALenum (*)(const ALchar *ename), oallib, alGetEnumValue);
	alsym(alwGetError, ALenum (*)(void), oallib, alGetError);
	alsym(alwGetFilterf, void (*)(ALuint filter, ALenum param, ALfloat *pflValue), oallib, alGetFilterf);
	alsym(alwGetFilterfv, void (*)(ALuint filter, ALenum param, ALfloat *pflValues), oallib, alGetFilterfv);
	alsym(alwGetFilteri, void (*)(ALuint filter, ALenum param, ALint *piValue), oallib, alGetFilteri);
	alsym(alwGetFilteriv, void (*)(ALuint filter, ALenum param, ALint *piValues), oallib, alGetFilteriv);
	alsym(alwGetFloat, ALfloat (*)(ALenum param), oallib, alGetFloat);
	alsym(alwGetFloatv, void (*)(ALenum param, ALfloat *values), oallib, alGetFloatv);
	alsym(alwGetInteger, ALint (*)(ALenum param), oallib, alGetInteger);
	alsym(alwGetIntegerv, void (*)(ALenum param, ALint *values), oallib, alGetIntegerv);
	alsym(alwGetListener3f, void (*)(ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3), oallib, alGetListener3f);
	alsym(alwGetListener3i, void (*)(ALenum param, ALint *value1, ALint *value2, ALint *value3), oallib, alGetListener3i);
	alsym(alwGetListenerf, void (*)(ALenum param, ALfloat *value), oallib, alGetListenerf);
	alsym(alwGetListenerfv, void (*)(ALenum param, ALfloat *values), oallib, alGetListenerfv);
	alsym(alwGetListeneri, void (*)(ALenum param, ALint *value), oallib, alGetListeneri);
	alsym(alwGetListeneriv, void (*)(ALenum param, ALint *values), oallib, alGetListeneriv);
	alsym(alwGetProcAddress, void* (*)(const ALchar *fname), oallib, alGetProcAddress);
	alsym(alwGetSource3f, void (*)(ALuint source, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3), oallib, alGetSource3f);
	alsym(alwGetSource3i, void (*)(ALuint source, ALenum param, ALint *value1, ALint *value2, ALint *value3), oallib, alGetSource3i);
	alsym(alwGetSourcef, void (*)(ALuint source, ALenum param, ALfloat *value), oallib, alGetSourcef);
	alsym(alwGetSourcefv, void (*)(ALuint source, ALenum param, ALfloat *values), oallib, alGetSourcefv);
	alsym(alwGetSourcei, void (*)(ALuint source,  ALenum param, ALint *value), oallib, alGetSourcei);
	alsym(alwGetSourceiv, void (*)(ALuint source,  ALenum param, ALint *values), oallib, alGetSourceiv);
	alsym(alwGetString, const ALchar* (*)(ALenum param), oallib, alGetString);
	alsym(alwIsAuxiliaryEffectSlot, ALboolean (*)(ALuint effectslot), oallib, alIsAuxiliaryEffectSlot);
	alsym(alwIsBuffer, ALboolean (*)(ALuint buffer), oallib, alIsBuffer);
	alsym(alwIsEffect, ALboolean (*)(ALuint effect), oallib, alIsEffect);
	alsym(alwIsEnabled, ALboolean (*)(ALenum capability), oallib, alIsEnabled);
	alsym(alwIsExtensionPresent, ALboolean (*)(const ALchar *extname), oallib, alIsExtensionPresent);
	alsym(alwIsFilter, ALboolean (*)(ALuint filter), oallib, alIsFilter);
	alsym(alwIsSource, ALboolean (*)(ALuint source), oallib, alIsSource);
	alsym(alwListener3f, void (*)(ALenum param, ALfloat value1, ALfloat value2, ALfloat value3), oallib, alListener3f);
	alsym(alwListener3i, void (*)(ALenum param, ALint value1, ALint value2, ALint value3), oallib, alListener3i);
	alsym(alwListenerf, void (*)(ALenum param, ALfloat value), oallib, alListenerf);
	alsym(alwListenerfv, void (*)(ALenum param, const ALfloat *values), oallib, alListenerfv);
	alsym(alwListeneri, void (*)(ALenum param, ALint value), oallib, alListeneri);
	alsym(alwListeneriv, void (*)(ALenum param, const ALint *values), oallib, alListeneriv);
	alsym(alwSource3f, void (*)(ALuint source, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3), oallib, alSource3f);
	alsym(alwSource3i, void (*)(ALuint source, ALenum param, ALint value1, ALint value2, ALint value3), oallib, alSource3i);
	alsym(alwSourcePause, void (*)(ALuint source), oallib, alSourcePause);
	alsym(alwSourcePausev, void (*)(ALsizei n, const ALuint *sources), oallib, alSourcePausev);
	alsym(alwSourcePlay, void (*)(ALuint source), oallib, alSourcePlay);
	alsym(alwSourcePlayv, void (*)(ALsizei n, const ALuint *sources), oallib, alSourcePlayv);
	alsym(alwSourceQueueBuffers, void (*)(ALuint source, ALsizei nb, const ALuint *buffers), oallib, alSourceQueueBuffers);
	alsym(alwSourceRewind, void (*)(ALuint source), oallib, alSourceRewind);
	alsym(alwSourceRewindv, void (*)(ALsizei n, const ALuint *sources), oallib, alSourceRewindv);
	alsym(alwSourceStop, void (*)(ALuint source), oallib, alSourceStop);
	alsym(alwSourceStopv, void (*)(ALsizei n, const ALuint *sources), oallib, alSourceStopv);
	alsym(alwSourceUnqueueBuffers, void (*)(ALuint source, ALsizei nb, ALuint *buffers), oallib, alSourceUnqueueBuffers);
	alsym(alwSourcef, void (*)(ALuint source, ALenum param, ALfloat value), oallib, alSourcef);
	alsym(alwSourcefv, void (*)(ALuint source, ALenum param, const ALfloat *values), oallib, alSourcefv);
	alsym(alwSourcei, void (*)(ALuint source, ALenum param, ALint value), oallib, alSourcei);
	alsym(alwSourceiv, void (*)(ALuint source, ALenum param, const ALint *values), oallib, alSourceiv);
	alsym(alwSpeedOfSound, void (*)(ALfloat value), oallib, alSpeedOfSound);
	alsym(alwcCaptureCloseDevice, ALCboolean (*)(ALCdevice *device), oallib, alcCaptureCloseDevice);
	alsym(alwcCaptureOpenDevice, ALCdevice* (*)(const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize), oallib, alcCaptureOpenDevice);
	alsym(alwcCaptureSamples, void (*)(ALCdevice *device, ALCvoid *buffer, ALCsizei samples), oallib, alcCaptureSamples);
	alsym(alwcCaptureStart, void (*)(ALCdevice *device), oallib, alcCaptureStart);
	alsym(alwcCaptureStop, void (*)(ALCdevice *device), oallib, alcCaptureStop);
	alsym(alwcCloseDevice, ALCboolean (*)(ALCdevice *device), oallib, alcCloseDevice);
	alsym(alwcCreateContext, ALCcontext* (*)(ALCdevice *device, const ALCint *attrlist), oallib, alcCreateContext);
	alsym(alwcDestroyContext, void (*)(ALCcontext *context), oallib, alcDestroyContext);
	alsym(alwcGetContextsDevice, ALCdevice* (*)(ALCcontext *context), oallib, alcGetContextsDevice);
	alsym(alwcGetCurrentContext, ALCcontext* (*)(void), oallib, alcGetCurrentContext);
	alsym(alwcGetEnumValue, ALCenum (*)(ALCdevice *device, const ALCchar *enumname), oallib, alcGetEnumValue);
	alsym(alwcGetError, ALCenum (*)(ALCdevice *device), oallib, alcGetError);
	alsym(alwcGetIntegerv, void (*)(ALCdevice *device, ALCenum param, ALCsizei size, ALCint *values), oallib, alcGetIntegerv);
	alsym(alwcGetProcAddress, ALCvoid* (*)(ALCdevice *device, const ALCchar *funcname), oallib, alcGetProcAddress);
	alsym(alwcGetString, const ALCchar* (*)(ALCdevice *device, ALCenum param), oallib, alcGetString);
	alsym(alwcIsExtensionPresent, ALCboolean (*)(ALCdevice *device, const ALCchar *extname), oallib, alcIsExtensionPresent);
	alsym(alwcMakeContextCurrent, ALCboolean  (*)(ALCcontext *context), oallib, alcMakeContextCurrent);
	alsym(alwcOpenDevice, ALCdevice* (*)(const ALCchar *devicename), oallib, alcOpenDevice);
	alsym(alwcProcessContext, void (*)(ALCcontext *context), oallib, alcProcessContext);
	alsym(alwcSuspendContext, void (*)(ALCcontext *context), oallib, alcSuspendContext);
	alsym(alwcGetStringiSOFT, const ALCchar* (*)(ALCdevice *device, ALCenum paramName, ALCsizei index), oallib, alcGetStringiSOFT);
	alsym(alwcResetDeviceSOFT, ALCboolean (*)(ALCdevice *device, const ALCint *attribs), oallib, alcResetDeviceSOFT);
	alclose(oallib);

#undef allib
#undef alsym
}
