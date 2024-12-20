

void cv::goodFeaturesToTrack(InputArray image,
                             OutputArray corners,
                             int maxCorners,
                             double qualityLevel,
                             double minDistance,
                             InputArray mask = noArray(),
                             int blockSize = 3,
                             bool useHarrisDetector = false,
                             double k = 0.04)