################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/L2/%.obj: ../source/L2/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -Ooff --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/device" --include_path="C:/ti/c2000/C2000Ware_4_00_00_00/driverlib/f2838x/driverlib" --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/source/L0" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/source/L1" --include_path="E:/TOOLBD/01 SW/000 workspace/BD6B0_CPU2/source/L2" --include_path="C:/Users/HHI/Desktop/BD6Tx_ToolBD/01 SW/workspace/BD6Tx_CPU1/source/L0" --define=DEBUG --define=CPU2 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="source/L2/$(basename $(<F)).d_raw" --obj_directory="source/L2" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


