OUT		 = bitforgeutils
VERSION	 = .1.0.0


CC 		 = g++ -std=c++11 -DDEBUG_MEMORY_ALLOC

CPPFLAGS += -Iinc

INCDIR	 	= inc/
OBJDIR	 	= obj/
SRCDIR	 	= src/
INSTALLDIR	= /usr/lib/
HEADERDIR	= /usr/include/

SOURCES	= $(shell ls $(SRCDIR))
ARCHITECTURE = $(shell dpkg --print-architecture)

DEPOBJ =  


#################################################################################

all:
	./prebuild.sh
	make debug
	make release

debug: CC += -g -DLOG_LEVEL=DebugLevel::ALL
debug: BUILDPATH = build/$(ARCHITECTURE)/dbg/
debug: OBJDIR = build/$(ARCHITECTURE)/dbg/obj/
debug: OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)%.o)
#debug: DEPS_OBJ		= 	$(addsuffix /build/dbg/obj/*,$(DEPS))
debug: $(SOURCES) $(OUT) 

release: CC += -O3 -DLOG_LEVEL=DebugLevel::INFO -DNOTRACE
release: BUILDPATH = build/$(ARCHITECTURE)/rel/
release: OBJDIR = build/$(ARCHITECTURE)/rel/obj/
release: OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)%.o)
#release: DEPS_OBJ		= 	$(addsuffix /build/rel/obj/*,$(DEPS))
release: $(SOURCES) $(OUT) 
	

$(OUT): $(OBJECTS)
	$(CC) -shared -o $(BUILDPATH)$@.so $(CPPFLAGS) $(OBJDIR)* $(DEPOBJ) 
	$(CC) -o $(BUILDPATH)$@_tests $(CPPFLAGS) $(BUILDPATH)$@.so $(DEPOBJ) main.cpp 
	#$(CC) -o $(BUILDPATH)$@ $(CPPFLAGS) $(OBJDIR)* $(DEPOBJ) main.cpp 


$(SOURCES): $(INCDIR)$(@:%.cpp=%.hpp) $(SRCDIR)$@
	$(CC) -c $(CPPFLAGS) $(SRCDIR)$@ -o $(@:%.cpp=$(OBJDIR)%.o) -fpic

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
	cp build/${ARCHITECTURE}/dbg/${OUT}.so ${INSTALLDIR}lib${OUT}.so$(VERSION)
	ln -sf ${INSTALLDIR}lib${OUT}.so$(VERSION) ${INSTALLDIR}lib${OUT}.so
	cp -r inc/* $(HEADERDIR)bitforge/utils
