################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.c" 

COMPILED_SRCS += \
"Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.src" 

C_DEPS += \
"./Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.d" 

OBJS += \
"Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.o" 


# Each subdirectory must supply rules for building sources it contributes
"Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.src":"../Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.c" "Libraries/Service/CpuGeneric/SysSe/Time/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/AVEES/AURIX-v1.10.6-workspace/BlinkingLED/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.o":"Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.src" "Libraries/Service/CpuGeneric/SysSe/Time/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-Service-2f-CpuGeneric-2f-SysSe-2f-Time

clean-Libraries-2f-Service-2f-CpuGeneric-2f-SysSe-2f-Time:
	-$(RM) ./Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.d ./Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.o ./Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.src

.PHONY: clean-Libraries-2f-Service-2f-CpuGeneric-2f-SysSe-2f-Time

