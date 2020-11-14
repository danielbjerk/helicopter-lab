data = load('p4t1_noise-estimation-flying_full-IMU_v1.mat');


delta_t = 0.002;
time = data.ans(1,:);
total_time = delta_t * length(time);
pitch = data.ans(2,:);

N = length(pitch);
xdft = fft(pitch);
xdft = xdft(1:N/2+1);
psdx = (1/(Fs*N)) * abs(xdft).^2;
psdx(2:end-1) = 2*psdx(2:end-1);
freq = 0:Fs/length(pitch):Fs/2;
plot(freq,10*log10(psdx));
grid on
title('Periodogram Using FFT')
xlabel('Frequency (Hz)')
ylabel('Power/Frequency (dB/Hz)')

%% 
Fs = 1/delta_t;       % Sampling frequency                    
T = delta_t;             % Sampling period       
L = length(time);     % Length of signal
t = (0:L-1)*T;        % Time vector


Y = fft(pitch);
P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);

f = Fs*(0:(L/2))/L;
plot(f,P1);
xlabel('f (Hz)');
ylabel('|P1(f)|');
