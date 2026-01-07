#include "everything.h"

float sawtoothV(float phase, int maxHarmonics) {
    float v = 0;
    for (int n = 1; n <= maxHarmonics; n++)
        v += sin(n * phase) / n;
    v /= 2.0;
    return(v);

}

int main(int argc, char* argv[]) {
    float phase = 0;
    float note = 60;
    float frequency = mtof(note);
    int maxHarmonics = (int)(SAMPLE_RATE / (2 * frequency));

    for(int i = 0; i < 1e5; i++) {
        float v = sawtoothV(phase, maxHarmonics);
        mono(v * 0.707);
        phase += 2 * pi * frequency / SAMPLE_RATE;
        if (phase > 2 * pi)
            phase -= 2 * pi;
    }
}
