CC = cc
LD = cc
AR = ar

emscripten: CC = emcc
emscripten: LD = emcc
emscripten: AR = emar

DIR = build

SRCS = openal.c sound.c speaker.c

ALUT = /home/pudds/projects/third_party/emsdk/emscripten/1.38.27/tests/freealut

DEPS = -lopenal -lalut
DEPS_EMS = -lopenal $(ALUT)/build/libalut.a

SAUCES = speaker.png

SAUCES_SRC = $(patsubst %, $(DIR)/%.sauce.c, $(SAUCES))
SAUCES_OBJ = $(patsubst $(DIR)/%.c, $(DIR)/%.o, $(SAUCES_SRC))

SAUCES_EMS_SRC  = $(patsubst %, $(DIR)/%.emscripten_sauce.c, $(SAUCES))
SAUCES_EMS_OBJ = $(patsubst $(DIR)/%.c, $(DIR)/%.o, $(SAUCES_EMS_SRC))

OBJS_REL = $(SAUCES_OBJ) $(patsubst %.c, $(DIR)/%.o, $(SRCS))
OBJS_DEB = $(SAUCES_OBJ) $(patsubst %.c, $(DIR)/%.debug.o, $(SRCS))
OBJS_EMS = $(SAUCES_EMS_OBJ) $(patsubst %.c, $(DIR)/%.emscripten.o, $(SRCS))

CFLAGS = $(shell pkg-config openal --cflags) -I../candle \
	-Wuninitialized -Wno-unused-function $(PARENTCFLAGS)

CFLAGS_REL = $(CFLAGS) -O3

CFLAGS_DEB = $(CFLAGS) -g3

CFLAGS_EMS = $(CFLAGS) -s USE_SDL=2

##############################################################################

all: $(DIR)/export.a
	echo -n $(DEPS) > $(DIR)/deps

$(DIR)/export.a: init $(OBJS_REL)
	$(AR) rs $(DIR)/export.a $(OBJS_REL)

$(DIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS_REL)

##############################################################################

debug: $(DIR)/export_debug.a
	echo -n $(DEPS) > $(DIR)/deps

$(DIR)/export_debug.a: init $(OBJS_DEB)
	$(AR) rs $(DIR)/export_debug.a $(OBJS_DEB)

$(DIR)/%.debug.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS_DEB)

##############################################################################

emscripten: $(DIR)/export_emscripten.a
	echo $(DEPS_EMS) > $(DIR)/deps

$(DIR)/export_emscripten.a: init $(OBJS_EMS)
	emar rs build/export_emscripten.a $(OBJS_EMS)

$(DIR)/%.emscripten.o: %.c
	emcc -o $@ -c $< $(CFLAGS_EMS)

$(DIR)/%.emscripten_sauce.c: %
	xxd -i $< > $@

##############################################################################

$(DIR)/%.sauce.c: %
	xxd -i $< > $@

##############################################################################

init:
	mkdir -p $(DIR)

##############################################################################

clean:
	rm -r $(DIR)

# vim:ft=make
