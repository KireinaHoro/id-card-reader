all: controller scanner

scanner: scanner/scanner

controller: controller/controller

scanner/scanner:
	$(MAKE) -C scanner/

controller/controller:
	$(MAKE) -C controller/

clean:
	$(MAKE) -C scanner/ clean
	$(MAKE) -C controller/ clean
