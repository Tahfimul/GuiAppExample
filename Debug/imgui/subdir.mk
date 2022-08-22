################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../imgui/imgui.cpp \
../imgui/imgui_demo.cpp \
../imgui/imgui_draw.cpp \
../imgui/imgui_impl_glfw.cpp \
../imgui/imgui_impl_opengl3.cpp \
../imgui/imgui_tables.cpp \
../imgui/imgui_widgets.cpp 

OBJS += \
./imgui/imgui.o \
./imgui/imgui_demo.o \
./imgui/imgui_draw.o \
./imgui/imgui_impl_glfw.o \
./imgui/imgui_impl_opengl3.o \
./imgui/imgui_tables.o \
./imgui/imgui_widgets.o 

CPP_DEPS += \
./imgui/imgui.d \
./imgui/imgui_demo.d \
./imgui/imgui_draw.d \
./imgui/imgui_impl_glfw.d \
./imgui/imgui_impl_opengl3.d \
./imgui/imgui_tables.d \
./imgui/imgui_widgets.d 


# Each subdirectory must supply rules for building sources it contributes
imgui/%.o: ../imgui/%.cpp imgui/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


