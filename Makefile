#export target_dir=/mnt/hgfs/sdk_branch/navsdk_phenix-ruitu/libs
define MY_CPP_FILES_UNDER
$(wildcard $(1)/*.cpp)
endef
CXX=g++
CXXFLAGS := -D__linux__ -std=c++0x -ggdb -D_GLIBCXX_PERMIT_BACKWARD_HASH -DMOREACCURATEFIXED \
			-DFT2_BUILD_LIBRARY \
			-DFT_DEBUG_LEVEL_ERROR \
			-DFT_DEBUG_LEVEL_TRACE \
			-DMSDNAV_EXPORT \
			-DMANUAL_PROFILE \
			-DNAVITSYSDEBUG \
			-DSTLPORT \
			-D_LEGACEL_LINUX_ \
			-DTERMINAL_TEST\

CPPFLAGS += 

LOCAL_PATH := .
LOCAL_MODULE := main
CXXFLAGS += -Wall \
			-I$(LOCAL_PATH)/Test \
			-I$(LOCAL_PATH)/TestContainer \
			-I$(LOCAL_PATH)/TestPicture \
			-I$(LOCAL_PATH)/Algorithm \
			-I$(LOCAL_PATH)/Container \
			-I$(LOCAL_PATH)/include \ 
			-I$(LOCAL_PATH)/PictureRead \
			-I$(LOCAL_PATH)/SmartPtr \
			-I$(LOCAL_PATH)/TypeOf

LOCAL_SRC_FILES := test_instruction.cpp \
				   test_pressure.cpp
				   #RoutProxy.cpp
	       	   	
OBJS := $(addprefix obj/, $(addsuffix .o, $(basename $(LOCAL_SRC_FILES))))
LDFLAGS:=-L../libs -lnavi -lPOISearch -luni_platform -llzo -lzib -lsdsl -lcds -lcmph
.PHONY:clean
$(LOCAL_MODULE) : $(OBJS)
	if [ ! -d $(TARGET_DIR) ]; then mkdir -p $(TARGET_DIR); fi
	$(CXX) $(OBJS) $(LDFLAGS) -o $@
obj/%.o:%.cpp
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJS) $(LOCAL_MODULE)
check:
	@echo "CXX:$(CXX)"
	@echo "SRC_FIELS:$(LOCAL_SRC_FILES)"
