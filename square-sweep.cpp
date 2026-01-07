#include "everything.h"

float squareV(float phase, int maxHarmonics) {
    float v = 0;
    for (int n = 1; n <= maxHarmonics; n += 2)
        v += sin(n * phase) / n;
    v *= 4.0 / pi;
    return(v);
}

int main(int argc, char* argv[]) {
    float phase = 0;
    for(float note = 100; note > 10; note -= 0.001) {
        float frequency = mtof(note);
        int maxHarmonics = (int)(SAMPLE_RATE / (2 * frequency));
        float v = squareV(phase, maxHarmonics);
        mono(v * 0.707);
        phase += 2 * pi * frequency / SAMPLE_RATE;
        if (phase > 2 * pi)
            phase -= 2 * pi;
    }
}
