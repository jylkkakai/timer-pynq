################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#-include ../makefile.init

RM := rm -rf

ELFSIZE += \
timer.elf.size \

LIBS := -Wl,--start-group,-lxil,-lgcc,-lc,--end-group

OBJS += \
./build/main.o \
./build/timer.o \
./build/intrupt.o \

C_DEPS += \
./build/main.d \
./build/timer.d \
./build/intrupt.d \

# Every subdirectory with source files must be described here
SUBDIRS := \
src \
# build\

# All Target
all: pre-build main-build

# Main-build Target
main-build: $(OBJS) timer.elf secondary-outputs

build/%.o: ./src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	@mkdir -p $(@D)
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../timer_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



# Tool invocations
timer.elf: $(OBJS) src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM v7 gcc linker'
	arm-none-eabi-gcc -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none -specs=Xilinx.spec -Wl,-T -Wl,src/lscript.ld -L../timer_bsp/ps7_cortexa9_0/lib -o "timer.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

timer.elf.size: timer.elf
	@echo 'Invoking: ARM v7 Print Size'
	arm-none-eabi-size timer.elf  |tee "timer.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(S_UPPER_DEPS)$(C_DEPS)$(ELFSIZE) timer.elf
	-@echo ' '

pre-build:
	-a9-linaro-pre-build-step
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

# -include ../makefile.targets
