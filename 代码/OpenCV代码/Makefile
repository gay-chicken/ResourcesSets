# 定义变量
CXX = g++
SRC_DIR = .
OUT_DIR = out
LIBS_DIR = /usr/local/lib
INCLUDE_DIR = /usr/local/include/opencv4
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lopencv_calib3d -lopencv_core -lopencv_dnn -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_videoio -lopencv_video -lpthread
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
