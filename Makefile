
#make win=1 to use cross compiler
#make to make for linux
#make release=1 to use release compile flags
#	else use debug flags

# Specify the main target
TARGET := zakes
# Which directories contain source files
DIRS := src/core \
			src \
			src/tinyxml \
			src/fsm\
			src/game_states

# Which libraries are linked
LIBS := SDL_ttf SDL_image SDL_mixer z
# Dynamic libraries
DLIBS :=
#back up directory
BACKUP_DIR := backup
#directory for windows .exe.  all the .dlls should be in here
WINDIR := win

COMPILER_FLAGS :=

ifdef release
	COMPILER_FLAGS = -O3
else
	COMPILER_FLAGS = -g -Wall
endif

ifdef win	# windows flags
	SDL_FLAGS = `i586-mingw32msvc-sdl-config --cflags`
	SDL_LIBS = `i586-mingw32msvc-sdl-config --libs`
	OPENGL_LIBS =  -lopengl32 -lglu32
	CC=i386-mingw32-g++ $(COMPILER_FLAGS)
	TARGET:= $(WINDIR)/$(TARGET).exe
else	# nix flags
	SDL_FLAGS = `sdl-config --cflags`
	SDL_LIBS = `sdl-config --libs`
	OPENGL_LIBS = -lX11  -lGL -glut -lGLU
	CC=g++ $(COMPILER_FLAGS)
endif


CCPARAM := $(SDL_FLAGS) 
LDPARAM := $(SDL_LIBS) $(OPENGL_LIBS)

# Add directories to the include and library paths
INCPATH := include \
	include/tinyxml \
	include/core \
	include/fsm \
	include/game_states \
	include/zlib

LIBPATH :=

# Which files to add to backups, apart from the source code
EXTRA_FILES := Makefile README

# The compiler


# Where to store object and dependancy files.
STORE := objs
# Makes a list of the source (.cpp) files.
SOURCE := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.cpp))
# List of header files.
HEADERS := $(foreach DIR,$(INCPATH),$(wildcard $(DIR)/*.h))
# Makes a list of the object files that will have to be created.
OBJECTS := $(addprefix $(STORE)/, $(SOURCE:.cpp=.o))
# Same for the .d (dependancy) files.
DFILES := $(addprefix $(STORE)/,$(SOURCE:.cpp=.d))

# Specify phony rules. These are rules that are not real files.
.PHONY: clean backup dirs zip

# Main target. The @ in front of a command prevents make from displaying
# it to the standard output.
$(TARGET): dirs $(OBJECTS)
	@echo Linking $(TARGET).
	@$(CC) -o $(TARGET) $(OBJECTS) $(LDPARAM)  $(foreach LIBRARY, \
		$(LIBS),-l$(LIBRARY)) $(foreach LIB,$(LIBPATH),-L$(LIB))

# Rule for creating object file and .d file, the sed magic is to add
# the object path at the start of the file because the files gcc
# outputs assume it will be in the same dir as the source file.
$(STORE)/%.o: %.cpp
	@echo Creating object file for $*...
	@$(CC) -Wp,-MMD,$(STORE)/$*.dd $(CCPARAM) $(foreach INC,$(INCPATH),-I$(INC))\
		$(foreach MACRO,$(MACROS),-D$(MACRO)) -c $< -o $@
	@sed -e '1s/^\(.*\)$$/$(subst /,\/,$(dir $@))\1/' $(STORE)/$*.dd > $(STORE)/$*.d
	@rm -f $(STORE)/$*.dd

# Empty rule to prevent problems when a header is deleted.
#%.hpp: ;

# Cleans up the objects, .d files and executables.
clean:
	@echo Making clean.
	@-rm -rf $(STORE)
#	@-rm -f $(WINDIR)/$(TARGET).exe win/*.txt
#		-rm -rf $(foreach DIR,$(DIRS),$(STORE)/$(DIR)/*.d $(STORE)/$(DIR)/*.o)
	@-rm -f $(TARGET)

# Backup the source files.
backup:
		@-if [ ! -e ${BACKUP_DIR} ]; then mkdir ${BACKUP_DIR}; fi;
#		@zip ${BACKUP_DIR}/backup_`date +%d-%m-%y_%H.%M`.zip $(SOURCE) $(HEADERS) $(EXTRA_FILES)
		@tar czf ${BACKUP_DIR}/$(TARGET)-`date +%d-%m-%y_%H.%M`.tgz $(SOURCE) $(HEADERS) $(EXTRA_FILES)
		@echo "Backed up."

# Create necessary directories
dirs:
	@-if [ ! -e $(STORE) ]; then mkdir -p $(STORE); fi;
	@-$(foreach DIR,$(DIRS), if [ ! -e $(STORE)/$(DIR) ]; \
	then mkdir -p $(STORE)/$(DIR); fi; )
	@-if [ ! -e $(WINDIR) ]; then mkdir -p $(WINDIR); fi;

# Includes the .d files so it knows the exact dependencies for every
# source.
-include $(DFILES)

