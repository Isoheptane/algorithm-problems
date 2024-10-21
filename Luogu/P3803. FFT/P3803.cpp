#include <cstdio>
#include <cmath>
#include <vector>

using std::vector;

struct Complex {
    double real, imag;
    Complex(double real = 0.0, double imag = 0.0): real(real), imag(imag) {}
    friend Complex operator*(const Complex a, const double b) {
        return Complex(a.real * b, a.imag * b);
    }
    friend Complex operator/(const Complex a, const double b) {
        return Complex(a.real / b, a.imag / b);
    }
    friend Complex operator+(const Complex a, const Complex b) {
        return Complex(a.real + b.real, a.imag + b.imag);
    }
    friend Complex operator-(const Complex a, const Complex b) {
        return Complex(a.real - b.real, a.imag - b.imag);
    }
    friend Complex operator*(const Complex a, const Complex b) {
        return Complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
    }
};

Complex ei(double theta) {
    return Complex(cos(theta), sin(theta));
}

vector<Complex> fft(const vector<Complex> array, bool inverse = false) {
    size_t N = array.size();
    vector<Complex> result;
    if (N == 1) {
        result.push_back(ei(0) * array[0]);
        return result;
    };
    result.resize(N, Complex());
    vector<Complex> even, odd;
    for (size_t i = 0; i < N; i++)
        (i % 2 == 0 ? even : odd).push_back(array[i]);
    vector<Complex> result_even = fft(even, inverse);
    vector<Complex> result_odd = fft(odd, inverse);
    for (size_t k = 0; k < (N / 2); k++) {
        Complex factor = ei((2.0 * M_PI) / (double)N * (double)k * (inverse ? -1.0 : 1.0));
        result[k] = result_even[k] + result_odd[k] * factor;
        result[k + (N / 2)] = result_even[k] - result_odd[k] * factor;
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    size_t len = 1;
    while (len <= (n + m + 1))
        len *= 2;
    vector<Complex> fc, gc;
    fc.resize(len, Complex());
    gc.resize(len, Complex());
    for (int i = 0; i <= n; i++) {
        int v;
        scanf("%d", &v);
        fc[i].real = v;
    }
    for (int i = 0; i <= n; i++) {
        int v;
        scanf("%d", &v);
        gc[i].real = v;
    }
    vector<Complex> fk = fft(fc);
    vector<Complex> gk = fft(gc);
    for (size_t i = 0; i < len; i++)
        fk[i] = fk[i] * gk[i];
    vector<Complex> fgc = fft(fk, true);
    for (size_t i = 0; i < len; i++)
        fgc[i] = fgc[i] / len;
    for (size_t i = 0; i <= (n + m); i++)
        printf("%.2f ", fgc[i].real);
    return 0;
}