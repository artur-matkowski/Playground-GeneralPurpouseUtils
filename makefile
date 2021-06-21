OUT		 = bitforgeutils
VERSION	 = .1.0.0

ARCHITECTURE = $(shell dpkg --print-architecture)

CC 		 = g++ -std=c++14 #-DDEBUG_MEMORY_ALLOC


INCDIR	 	= inc/
OBJDIR	 	= obj/
VENDOR_DIR  = vendor/lib/
INSTALLDIR	= /usr/lib/
HEADERDIR	= /usr/include/

SRCDIR	 	= src/
SOURCES		= $(shell find $(SRCDIR) -type f | grep cpp | cut -f 1 -d '.')
DIRSTRUCTURE = $(shell find $(INCDIR) -type d)
INCSTRUCTURE = $(patsubst %, -I%, $(DIRSTRUCTURE))


OBJECTS 	= $(SOURCES:%.cpp=$(OBJDIR)%.o)
OBJECTS2 	= $(patsubst %, %.o, $(SOURCES))
OBJECTS 	= $(OBJECTS2:%.cpp=$(OBJDIR)%.o)

#################################################################################

all:
	./prebuild.sh
	make debug
	make release

debug: CC += -g -ggdb3 -DLOG_LEVEL=DebugLevel::ALL
debug: BUILDPATH = build/$(ARCHITECTURE)/dbg/
#debug: OBJDIR = build/$(ARCHITECTURE)/dbg/obj/
#debug: OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)%.o)
#debug: DEPS_OBJ		= 	$(addsuffix /build/dbg/obj/*,$(DEPS))
debug: $(SOURCES) $(OUT) 

release: CC += -O3 -DLOG_LEVEL=DebugLevel::INFO -DNOTRACE
release: BUILDPATH = build/$(ARCHITECTURE)/rel/
#release: OBJDIR = build/$(ARCHITECTURE)/rel/obj/
#release: OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)%.o)
#release: DEPS_OBJ		= 	$(addsuffix /build/rel/obj/*,$(DEPS))
release: $(SOURCES) $(OUT) 
	

$(OUT):
	$(CC) -shared -o $(BUILDPATH)lib$@.so $(CPPFLAGS) $(BUILDPATH)*.o  
	#as rcs $(BUILDPATH)$@.a $(BUILDPATH)*.o
	$(CC) -o $(BUILDPATH)$@_tests $(CPPFLAGS) $(INCSTRUCTURE) $(BUILDPATH)lib$@.so  main.cpp 
	#$(CC) -o $(BUILDPATH)$@_testO $(CPPFLAGS) $(INCSTRUCTURE) $(BUILDPATH)*.o  main.cpp 


$(SOURCES): $(INCDIR)$(@:%.cpp=%.hpp) $@
	$(CC) -c $(CPPFLAGS) $(INCSTRUCTURE) $@.cpp -o $(BUILDPATH)$(notdir $@).o -fpic


test:
	@$(MAKE) ${OUT} -B
	@$(MAKE) r

clean: 
	rm -fr build/*
	./prebuild.sh
	rm Logs/*

remove:
	rm -rf $(HEADERDIR)bitforge/utils
	rm ${INSTALLDIR}lib${OUT}.so*


install:
	mkdir -p $(HEADERDIR)bitforge
	mkdir -p $(HEADERDIR)bitforge/utils
	cp build/${ARCHITECTURE}/dbg/lib${OUT}.so ${INSTALLDIR}lib${OUT}.so$(VERSION)
	ln -sf ${INSTALLDIR}lib${OUT}.so$(VERSION) ${INSTALLDIR}lib${OUT}.so
	cp -r inc/* $(HEADERDIR)bitforge/utils
