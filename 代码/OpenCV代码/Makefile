# 定义变量
CXX = g++
SRC_DIR = .
OUT_DIR = out
LIBS_DIR = /usr/local/lib
INCLUDE_DIR = /usr/local/include/opencv4
CXXFLAGS = -std=c++11 -fsigned-char -W -Wall -Wreturn-type -Wnon-virtual-dtor -Waddress -Wsequence-point -Wformat -Wformat-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Wsuggest-override -Wno-delete-non-virtual-dtor -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -fvisibility-inlines-hidden -O3 -DNDEBUG  -DNDEBUG
LDFLAGS = -lopencv_calib3d -lopencv_core -lopencv_dnn -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_videoio -lopencv_video -lopencv_bgsegm -lpthread -Wl,--exclude-libs,libippicv.a -Wl,--exclude-libs,libippiw.a   -Wl,--gc-sections -Wl,--as-needed -Wl,--no-undefined

SRC_FILES = $(filter-out demo.cpp, $(wildcard $(SRC_DIR)/*.cpp))  # 排除demo.cpp并列出所有.cpp文件

# 默认目标
all: $(addprefix $(OUT_DIR)/, $(basename $(notdir $(SRC_FILES))))

# 生成可执行文件
$(OUT_DIR)/%: %.cpp
	@mkdir -p $(OUT_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS) $(CXXFLAGS) -L$(LIBS_DIR) -I$(INCLUDE_DIR)

# 清理目标文件和生成的可执行文件
clean:
	rm -rf $(OUT_DIR)/*.o $(OUT_DIR)/*

# 声明伪目标
.PHONY: all clean
