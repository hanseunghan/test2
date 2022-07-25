################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
device/%.obj: ../device/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/device" --include_path="C:/ti/c2000/C2000Ware_4_00_00_00/driverlib/f2838x/driverlib" --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/source/L0" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/source/L1" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/source/L2" --advice:performance=all --define=_FLASH --define=DEBUG --define=CPU2 -g --symdebug:dwarf_version=4 --c89 --c++03 --relaxed_ansi --float_operations_allowed=all --printf_support=full --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --cla_background_task=off --cla_signed_compare_workaround=off --silicon_errata_fpu1_workaround=off --sat_reassoc=off --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

device/%.obj: ../device/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/device" --include_path="C:/ti/c2000/C2000Ware_4_00_00_00/driverlib/f2838x/driverlib" --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/source/L0" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/source/L1" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/source/L2" --advice:performance=all --define=_FLASH --define=DEBUG --define=CPU2 -g --symdebug:dwarf_version=4 --c89 --c++03 --relaxed_ansi --float_operations_allowed=all --printf_support=full --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --cla_background_task=off --cla_signed_compare_workaround=off --silicon_errata_fpu1_workaround=off --sat_reassoc=off --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


