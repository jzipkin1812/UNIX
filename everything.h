#pragma once

#include <cmath>  // sin, cos, log
#include <vector>
#include <cstdio>

const double SAMPLE_RATE = 48000;
const double pi =
    3.141592653589793238462643383279502884197169399375105820974944592307816406286;
const double e =
    2.718281828459045235360287471352662497757247093699959574966967627724076630353;

double mtof(double m) { return 440.0 * pow(2.0, (m - 69.0) / 12.0); }
double ftom(double f) { return 12.0 * log2(f / 440.0) + 69.0; }
double dbtoa(double db) { return pow(10.0, db / 20.0); }
double atodb(double a) { return 20.0 * log10(a); }

double scale(double value, double low, double high, double Low, double High) {
  return Low + (High - Low) * ((value - low) / (high - low));
}

double uniform(double high = 1, double low = 0) {
  return low + (high - low) * double(rand()) / RAND_MAX;
}

void mono(double f) { printf("%lf\n", f); }
void stereo(double f, double v) { printf("%lf,%lf\n", f, v); }

void stableWav(float note, float (*fptr)(float, int)) {
    float phase = 0;
    float frequency = mtof(note);
    int maxHarmonics = (int)(SAMPLE_RATE / (2 * frequency));

    for(int i = 0; i < 1e5; i++) {
        float v = fptr(phase, maxHarmonics);
        mono(v * 0.707);
        phase += 2 * pi * frequency / SAMPLE_RATE;
        if (phase > 2 * pi)
            phase -= 2 * pi;
    }
}

void sweepWav(float topNote, float bottomNote, float (*fptr)(float, int)) {
    float phase = 0;
    for(float note = topNote; note > bottomNote; note -= 0.001) {
        float frequency = mtof(note);
        int maxHarmonics = (int)(SAMPLE_RATE / (2 * frequency));
        float v = fptr(phase, maxHarmonics);
        mono(v * 0.707);
        phase += 2 * pi * frequency / SAMPLE_RATE;
        if (phase > 2 * pi)
            phase -= 2 * pi;
    }
}

float squareV(float phase, int maxHarmonics) {
    float v = 0;
    for (int n = 1; n <= maxHarmonics; n += 2)
        v += sin(n * phase) / n;
    v *= 4.0 / pi;
    return(v);
}

float impulseV(float phase, int maxHarmonics) {
    float v = 0;
    for (int n = 1; n <= maxHarmonics; n++)
        v += sin(n * phase);
    v /= (float)(maxHarmonics);
    return(v);
}

float sawtoothV(float phase, int maxHarmonics) {
    float v = 0;
    for (int n = 1; n <= maxHarmonics; n++)
        v += sin(n * phase) / n;
    v /= 2.0;
    return(v);

}

float triangleV(float phase, int maxHarmonics) {
    float v = 0;
    for (int n = 1; n <= maxHarmonics; n += 2) {
        float sign = ((n - 1) / 2 % 2 == 0) ? 1.0f : -1.0f;
        v += ( sign / (n * n)) * sin(n * phase);
    }
    v *= 8 / (pi * pi);
    return(v);
}
