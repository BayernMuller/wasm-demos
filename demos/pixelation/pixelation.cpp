#include <emscripten/emscripten.h>

extern "C" {

void EMSCRIPTEN_KEEPALIVE pixelate(
    unsigned char* pixels,
    int width,
    int height,
    int blockSize
) {
    for (int y = 0; y < height; y += blockSize) {
        for (int x = 0; x < width; x += blockSize) {
            int rSum = 0, gSum = 0, bSum = 0, count = 0;

            for (int dy = 0; dy < blockSize; ++dy) {
                for (int dx = 0; dx < blockSize; ++dx) {
                    int px = x + dx;
                    int py = y + dy;
                    if (px >= width || py >= height) continue;

                    int idx = (py * width + px) * 4;
                    rSum += pixels[idx];
                    gSum += pixels[idx + 1];
                    bSum += pixels[idx + 2];
                    count++;
                }
            }

            if (count == 0) continue;
            int r = rSum / count;
            int g = gSum / count;
            int b = bSum / count;

            // 블록 전체를 평균 색으로 덮기
            for (int dy = 0; dy < blockSize; ++dy) {
                for (int dx = 0; dx < blockSize; ++dx) {
                    int px = x + dx;
                    int py = y + dy;
                    if (px >= width || py >= height) continue;

                    int idx = (py * width + px) * 4;
                    pixels[idx]     = r;
                    pixels[idx + 1] = g;
                    pixels[idx + 2] = b;
                    // Alpha 유지
                }
            }
        }
    }
}

}
