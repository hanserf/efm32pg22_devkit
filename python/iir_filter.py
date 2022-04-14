
# import required library
from unicodedata import name
import numpy as np
import scipy.signal as signal
import matplotlib.pyplot as plt
from collections import namedtuple
__debug = True


def __debug_print(str):
    if __debug == True:
        print(str)


SAMPTPL = namedtuple('SAMPTPL', ['F_Low', 'F_High'])
FILT_TUPLE = namedtuple('FILT_TUPLE', ['F_pass', 'F_stop'])
COEFF_TUPLE = namedtuple('COEFF_TUPLE', ['Numerator', 'Denominator'])


def mfreqz(b, a, Fs):

    # Compute frequency response of the filter
    # using signal.freqz function
    wz, hz = signal.freqz(b, a)

    # Calculate Magnitude from hz in dB
    Mag = 20*np.log10(abs(hz))

    # Calculate phase angle in degree from hz
    Phase = np.unwrap(np.arctan2(np.imag(hz), np.real(hz)))*(180/np.pi)

    # Calculate frequency in Hz from wz
    Freq = wz*Fs/(2*np.pi)
    return (Freq, Mag, Phase)


def iir_filter_plot_magphase(Fs, freq, mag, phase):
    # Plot filter magnitude and phase responses using subplot.
    fig = plt.figure(1, figsize=(10, 6))

    # Plot Magnitude response
    sub1 = plt.subplot(2, 1, 1)
    sub1.plot(freq, mag, 'r', linewidth=2)
    sub1.axis([1, Fs/2, -100, 5])
    sub1.set_title('Magnitude Response', fontsize=20)
    sub1.set_xlabel('Frequency [Hz]', fontsize=20)
    sub1.set_ylabel('Magnitude [dB]', fontsize=20)
    sub1.grid()

    # Plot phase angle
    sub2 = plt.subplot(2, 1, 2)
    sub2.plot(freq, phase, 'g', linewidth=2)
    sub2.set_ylabel('Phase (degree)', fontsize=20)
    sub2.set_xlabel(r'Frequency (Hz)', fontsize=20)
    sub2.set_title(r'Phase response', fontsize=20)
    sub2.grid()

    plt.subplots_adjust(hspace=0.5)
    fig.tight_layout()
    plt.show()


# Define impz(b,a) to calculate impulse
# response and step response of a system
# input: b= an array containing numerator
# coefficients,a= an array containing
# denominator coefficients
def impz(b, a):

    # Define the impulse sequence of length 64
    impulse = np.repeat(0., 64)
    impulse[0] = 1.
    x = np.arange(0, 64)

    # Compute the impulse response
    response = signal.lfilter(b, a, impulse)
    return x, response


def iir_filter_plot_impulse(x, response):
    # Plot filter impulse and step response:
    fig = plt.figure(2, figsize=(10, 6))
    plt.subplot(211)
    plt.stem(x, response, 'm', use_line_collection=True)
    plt.ylabel('Amplitude', fontsize=15)
    plt.xlabel(r'n (samples)', fontsize=15)
    plt.title(r'Impulse response', fontsize=15)

    plt.subplot(212)
    step = np.cumsum(response)

    plt.stem(x, step, 'g', use_line_collection=True)
    plt.ylabel('Amplitude', fontsize=15)
    plt.xlabel(r'n (samples)', fontsize=15)
    plt.title(r'Step response', fontsize=15)
    plt.subplots_adjust(hspace=0.5)
    fig.tight_layout()
    plt.show()


def make_stopband(transistion, freq=SAMPTPL):
    f_low = freq.F_Low*(1 - transistion)
    f_high = freq.F_High*(1 + transistion)
    return SAMPTPL(f_low, f_high)


def make_passband(passband, center):
    f_low = center*(1 - passband/2)
    f_high = center*(1 + passband/2)
    return SAMPTPL(f_low, f_high)


def generate_filterbank(center_freqs, passband, transition):
    filterbank = []
    for i in center_freqs:
        temp = make_passband(passband=passband, center=i)
        fp = np.array([temp.F_Low, temp.F_High])
        fs_temp = make_stopband(transition, temp)
        fs = np.array([fs_temp.F_Low, fs_temp.F_High])
        filterbank.append(FILT_TUPLE(F_pass=fp, F_stop=fs))
    return filterbank


'''
    Inputs
    bp -bandpass np array,
    Fs - sampling Freq
    Ap - Pass Band Ripple
    As - Stop band attenuation
    Returns:
    Numerator and Denominator with filter coefficients
'''


def generate_coefficients(bp, Fs, Ap, As):
    wpass = None
    wstop = None
    w_filter = None

    bp = FILT_TUPLE._make(bp)

    wpass = bp.F_pass/(Fs/2)
    # Normalized stopband
    # edge frequencies
    wstop = bp.F_stop/(Fs/2)

    # Compute order of the Chebyshev type-2
    # digital filter using signal.cheb2ord
    N, w_filter = signal.cheb2ord(wpass, wstop, Ap, As)

    # Print the order of the filter
    # and cutoff frequencies
    __debug_print('#'*40)
    __debug_print('Order of the filter={}'.format(N))
    __debug_print('Cut-off frequency={}'.format(w_filter))

    # Design digital Chebyshev type-2 bandpass
    # filter using signal.cheby2 function
    z, p = signal.cheby2(N, As, w_filter, 'bandpass')

    # Print numerator and denomerator
    # coefficients of the filter
    __debug_print('Numerator Coefficients:{}'.format(z))
    __debug_print('Denominator Coefficients:{}'.format(p))
    return COEFF_TUPLE(z, p)


def main():
    # Given specification
    center_freqs = [100, 400, 800, 1200, 2000, 4000, 8000, 16000]
    passband = 0.5
    transition = 0.25
    # Sampling frequency in Hz
    Fs = 48000
    # Pass band ripple in dB
    Ap = 3
    # Stop band attenuation in dB
    As = 40
    # Pass band frequency in Hz
    filterbank = generate_filterbank(
        center_freqs=center_freqs, passband=passband, transition=transition)
    # Compute pass band and stop band edge frequencies
    # Normalized passband edge
    # frequencies w.r.t. Nyquist rate
    for bp in filterbank:
        band_pass_filter = generate_coefficients(bp, Fs, Ap, As)
        freq, mag, phase = mfreqz(
            band_pass_filter.Numerator, band_pass_filter.Denominator, Fs)
        iir_filter_plot_magphase(Fs, freq, mag, phase)
        # Call impz function to plot impulse
        # and step response of the filter
        x, resp = impz(band_pass_filter.Numerator,
                       band_pass_filter.Denominator)
        iir_filter_plot_impulse(x, resp)
    plt.show()


if __name__ == "__main__":
    main()
