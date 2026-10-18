"""
Live microphone viewer: time waveform + FFT, with slider-controlled y-axes.

Install:  pip install numpy matplotlib sounddevice
Run:      python mic_scope_slider.py
Author:   Claude
"""

import queue

import numpy as np
import sounddevice as sd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.widgets import Slider

SAMPLE_RATE = 44100   # Hz
BLOCK_SIZE = 1024     # samples per audio callback
WINDOW_SIZE = 4096    # samples shown / used for the FFT
MAX_FREQ = 5000       # Hz, upper limit of the spectrum plot

audio_q = queue.Queue()
buffer = np.zeros(WINDOW_SIZE)


def audio_callback(indata, frames, time_info, status):
    if status:
        print(status)
    audio_q.put(indata[:, 0].copy())


def update(_):
    global buffer
    while not audio_q.empty():
        block = audio_q.get()
        buffer = np.roll(buffer, -len(block))
        buffer[-len(block):] = block

    line_time.set_ydata(buffer)

    windowed = buffer * np.hanning(len(buffer))
    spectrum = np.abs(np.fft.rfft(windowed)) / len(buffer)
    line_fft.set_ydata(spectrum)

    peak_hz = freqs[np.argmax(spectrum[1:]) + 1]
    ax_fft.set_title(f"FFT spectrum  (peak ≈ {peak_hz:.0f} Hz)")
    return line_time, line_fft


# ---- Plot setup ----
t = np.arange(WINDOW_SIZE) / SAMPLE_RATE * 1000  # ms
freqs = np.fft.rfftfreq(WINDOW_SIZE, 1 / SAMPLE_RATE)

fig, (ax_time, ax_fft) = plt.subplots(2, 1, figsize=(9, 8))
fig.subplots_adjust(bottom=0.2, hspace=0.35)

(line_time,) = ax_time.plot(t, buffer, lw=0.8)
ax_time.set_title("Time waveform")
ax_time.set_xlabel("Time (ms)")
ax_time.set_ylabel("Amplitude")
ax_time.set_xlim(0, t[-1])
ax_time.set_ylim(-1, 1)
ax_time.grid(alpha=0.3)

(line_fft,) = ax_fft.plot(freqs, np.zeros_like(freqs), lw=0.8, color="tab:orange")
ax_fft.set_xlabel("Frequency (Hz)")
ax_fft.set_ylabel("Magnitude")
ax_fft.set_xlim(0, MAX_FREQ)
ax_fft.set_ylim(0, 0.01)
ax_fft.grid(alpha=0.3)

# ---- Sliders (log10 scale so you can dial in tiny or large ranges) ----
ax_s_time = fig.add_axes([0.15, 0.09, 0.7, 0.03])
ax_s_fft = fig.add_axes([0.15, 0.03, 0.7, 0.03])

s_time = Slider(ax_s_time, "Wave ±", -3, 0, valinit=0, valfmt="%.2f")   # 0.001 .. 1
s_fft = Slider(ax_s_fft, "FFT max", -5, 0, valinit=-2, valfmt="%.2f")   # 1e-5 .. 1

# Show the real value instead of the log exponent
s_time.valtext.set_text(f"{10 ** s_time.val:.4f}")
s_fft.valtext.set_text(f"{10 ** s_fft.val:.5f}")


def on_time_slider(val):
    limit = 10 ** val
    ax_time.set_ylim(-limit, limit)
    s_time.valtext.set_text(f"{limit:.4f}")
    fig.canvas.draw_idle()


def on_fft_slider(val):
    limit = 10 ** val
    ax_fft.set_ylim(0, limit)
    s_fft.valtext.set_text(f"{limit:.5f}")
    fig.canvas.draw_idle()


s_time.on_changed(on_time_slider)
s_fft.on_changed(on_fft_slider)
on_fft_slider(s_fft.val)  # apply initial FFT range

# ---- Run ----
with sd.InputStream(
    channels=1,
    samplerate=SAMPLE_RATE,
    blocksize=BLOCK_SIZE,
    callback=audio_callback,
):
    anim = FuncAnimation(fig, update, interval=30, blit=False, cache_frame_data=False)
    plt.show()
