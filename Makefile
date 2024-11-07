
run_all: build_elf program_fpga run_on_device

build_elf:
	$(MAKE) -C timer/ all
	@echo ' '
	
build_libs:
	$(MAKE) -C timer_bsp/ all
	@echo ' '

run_on_device:
	@echo 'Launching program on hardware'
	xsdk -batch "run_program.tcl"
	@echo 'Launch finished'
	@echo ' '

program_fpga:
	@echo 'Programming FPGA'
	vivado  -mode tcl -nolog -nojournal -source program_fpga.tcl 
	@echo 'Finished programming'
	@echo ' '


clean: 
	$(MAKE) -C timer/ clean


.PHONY: run_all build_elf build_libs run_on_device program_fpga clean
