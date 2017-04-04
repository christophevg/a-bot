PROJECT  ?= blink
PARTICLE ?= particle
TTY      ?= /dev/tty.usbmodemFD121
BAUDRATE ?= 9600
SCREEN   ?= screen $(TTY) $(BAUDRATE)

-include Makefile.local
-include $(PROJECT)/Makefile

ifndef ID
$(error "Definieer ID met de identificatie van je Photon!")
endif

all: flash console

console:
ifdef CONSOLE
	@sleep 2
	@echo "*** Start van console uitvoer. Beëindig met 'Ctrl+a k y'."
	@echo "    Druk op een toets om verder te gaan..."
	@read
	@$(SCREEN)
else
	@echo
endif

flash:
	@echo "*** Compileren en flashen van $(PROJECT)"
	$(PARTICLE) flash $(ID) $(PROJECT)
