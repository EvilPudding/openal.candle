CC = cc
LD = cc
AR = ar

emscripten: CC = emcc
emscripten: LD = emcc
emscripten: AR = emar

DIR = build

SRCS = openal.c sound.c speaker.c listener.c

DEPS = -lopenal
DEPS_EMS = -lopenal

PLUGIN_SAUCES = speaker.png

OBJS_REL = $(patsubst %.c, $(DIR)/%.o, $(SRCS))
OBJS_DEB = $(patsubst %.c, $(DIR)/%.debug.o, $(SRCS))
OBJS_EMS = $(patsubst %.c, $(DIR)/%.emscripten.o, $(SRCS))

CFLAGS = $(shell pkg-config openal --cflags) -I../candle \
		 -Wuninitialized -Wno-unused-function $(PARENTCFLAGS)

CFLAGS_REL = $(CFLAGS) -O3 -DTHREADED

CFLAGS_DEB = $(CFLAGS) -g3 -DTHREADED

CFLAGS_EMS = $(CFLAGS) -s USE_GLFW=3 -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 \
		      -s FULL_ES3=1 -s EMULATE_FUNCTION_POINTER_CASTS=1 \
		      -s WASM=1 -s ASSERTIONS=1 -s SAFE_HEAP=1 \
		      -s WASM_MEM_MAX=2GB -O3

##############################################################################

all: $(DIR)/libs
	echo $(PLUGIN_SAUCES) > $(DIR)/res

$(DIR)/libs: $(DIR)/export.a
	echo $(DEPS) openal.candle/$< > $@

$(DIR)/export.a: init $(OBJS_REL)
	$(AR) rs $(DIR)/export.a $(OBJS_REL)

$(DIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS_REL)

##############################################################################

debug: $(DIR)/libs_debug
	echo $(PLUGIN_SAUCES) > $(DIR)/res

$(DIR)/libs_debug: $(DIR)/export_debug.a
	echo $(DEPS) openal.candle/$< > $@

$(DIR)/export_debug.a: init $(OBJS_DEB)
	$(AR) rs $(DIR)/export_debug.a $(OBJS_DEB)

$(DIR)/%.debug.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS_DEB)

##############################################################################

emscripten: $(DIR)/libs_emscripten
	echo $(PLUGIN_SAUCES) > $(DIR)/res

$(DIR)/libs_emscripten: $(DIR)/export_emscripten.a
	echo $(DEPS_EMS) openal.candle/$< > $@

$(DIR)/export_emscripten.a: init $(OBJS_EMS)
	emar rs build/export_emscripten.a $(OBJS_EMS)

$(DIR)/%.emscripten.o: %.c
	emcc -o $@ -c $< $(CFLAGS_EMS)

##############################################################################

init:
	mkdir -p $(DIR)

##############################################################################

clean:
	rm -r $(DIR)

# vim:ft=make
