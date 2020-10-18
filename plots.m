%% Just press f5 to run everything, and read the section that has something you need

% Press (ctrl+enter) to run the section your cursor is currently in ( Marked in yellow)
clear all
close all

%% Init one file
input = load('p3t1_acc-and-enc-multiple-axis-transformed_pitch.mat');
plot_title = 'Transformed acceleratometer measurements, high pitch';
file_name = 'p3t1_acc-vs-enc_transformed-acc-high-pitch';
xaxis = 'Time [s]';
yaxis = 'Pitch [rad]';

time = input.ans(1,:);
setpoint = input.ans(2,:);
values = input.ans(3,:);
%values2 = input.ans(4,:);

time_start = 55;
time_end = time(end);


% figure; % Calling figure => Plot/write in a new window
hold on
title(plot_title);

plot(time, setpoint);
plot(time, values);
%plot(time, values2);
xlim([time_start time_end]);


% Set desctiptions on the axis
xlabel(xaxis);
ylabel(yaxis);

lgd = legend('Acc. measurements', 'Encoder measurements');
lgd.Location = 'northeast';
%lgd.Position(1:2) = [.7 .02];

%% Init multiple files
figure
input1 = load('p3t4_minimal-C_p.mat');
input2 = load('p3t4_maximum-C_p.mat');
%input3 = load('p3t1_gyro-and-enc-one-axis_travel-rate.mat');
%input4 = load('p1t3_pole-placement-a=-1-b=2-with-elev_pitch-measurement_v1.mat');
plot_title = 'State estimation, different choice of measurement matrix C';
file_name = 'p3t4_L-optimal-tuning';
xaxis = 'Time [s]';
yaxis = 'Pitch [rad]';

time1 = input1.ans(1,:);
reference1 = input1.ans(4,:);
values1 = input1.ans(3,:);

time2 = input2.ans(1,:);
reference2 = input2.ans(4,:);
values2 = input2.ans(3,:);

%time3 = input3.ans(1,:);
%reference3 = input3.ans(2,:);
%values3 = input3.ans(3,:);

%time4 = input4.ans(1,:);
%reference4 = input4.ans(2,:);
%values3 = input3.ans(2,:);

time_start = 0;
time_end = time1(end);


% figure; % Calling figure => Plot/write in a new window
hold on
title(plot_title);

plot(time1, reference1);
plot(time1, values1);
%plot(time2, reference2);
plot(time2, values2);
%plot(time3, reference3);
%plot(time3, values3);
%plot(time4, reference4);
% plot(time4, values4);
xlim([time_start time_end]);


% Set desctiptions on the axis
xlabel(xaxis);
ylabel(yaxis);


%% Plot multiple plots in same figure
figure
input1 = load('p3t4_optimal-tuning-manual-input_p.mat');
input2 = load('p3t4_optimal-tuning-manual-input_p-dot.mat');
%input3 = load('p3t1_acc-and-enc-multiple-axis-transformed_travel.mat');
plot_title = 'Results with optimal tuning of L';
file_name = 'p3t4_conv-l-dot-corrected';

time1 = input1.ans(1,:);
reference1 = input1.ans(4,:);
%values1 = input1.ans(2,:);

%reference1 = cumtrapz(time1, reference1);
%values1 = cumtrapz(time1, values1);

time2 = input2.ans(1,:);
reference2 = input2.ans(2,:);
values2 = input2.ans(3,:);
ex2 = input2.ans(4,:);

%reference2 = cumtrapz(time2, reference2);
%values2 = cumtrapz(time2, values2);

%time3 = input3.ans(1,:);
%reference3 = input3.ans(2,:);
%values3 = input3.ans(3,:);

time_start = 0;
time_end = time1(end);



hold on

subplot(2,1,1);
p1 = plot(time1, reference1, 'g');
%p1.legend('Encoder measurement');
title(plot_title);
xaxis = 'Time [s]';
yaxis = 'Travel rate [rad/s]';
%xlabel(xaxis);
ylabel(yaxis);
time_start = 0; 
time_end = time_end;  
xlim([time_start time_end]);


subplot(2,1,2);
p2 = plot(time2, values2, time2, ex2, time2, reference2, 'g');
%p2.legend('Encoder measurement', 'IMU measurement');
xaxis = 'Time [s]';
yaxis = 'Elevation [rad]';
%xlabel(xaxis);
ylabel(yaxis);
xlim([time_start time_end]);


% subplot(3,1,3);
% h(:,3) = plot(time3, reference3, time3, values3);
% xaxis = 'Time [s]';
% yaxis = 'lambda [rad]';
% xlabel(xaxis);
% ylabel(yaxis);
% xlim([time_start time_end]);

lg = legend('IMU measurement', 'IMU measurement corrected', 'Encoder measurement');
lg.Position(1:2) = [.6 .02];


%% Plot a lot of figures together
figure
input1 = load('p3t4_optimal-tuning-manual-input_p.mat');
input2 = load('p3t4_optimal-tuning-manual-input_p-dot.mat');
input3 = load('p3t4_optimal-tuning-manual-input_e.mat');
input4 = load('p3t4_optimal-tuning-manual-input_e-dot.mat');
input5 = load('p3t4_optimal-tuning-manual-input_l-dot.mat');

plot_title = 'Results with optimal tuning of L';
file_name = 'p3t4_L-optimal-tuning';

time1 = input1.ans(1,:);
est1 = input1.ans(3,:);
enc1 = input1.ans(4,:);

time2 = input2.ans(1,:);
est2 = input2.ans(3,:);
enc2 = input2.ans(4,:);

time3 = input3.ans(1,:);
est3 = input3.ans(3,:);
enc3 = input3.ans(4,:);

time4 = input4.ans(1,:);
est4 = input4.ans(3,:);
enc4 = input4.ans(4,:);

time5 = input5.ans(1,:);
est5 = input5.ans(3,:);
enc5 = input5.ans(4,:);


time_start = 20;
time_end = 60;


hold on

subplot(3,2,1);
p1 = plot(time1, est1, time1, enc1);
%title(plot_title);
xaxis = 'Time [s]';
yaxis = 'Pitch [rad]';
xlabel(xaxis);
ylabel(yaxis);
xlim([time_start time_end]);


subplot(3,2,2);
p2 = plot(time2, est2, time2, enc2);
xaxis = 'Time [s]';
yaxis = 'Pitch rate [rad/s]';
xlabel(xaxis);
ylabel(yaxis);
xlim([time_start time_end]);


subplot(3,2,3);
p3 = plot(time3, est3, time3, enc3);
xaxis = 'Time [s]';
yaxis = 'Elevation [rad]';
xlabel(xaxis);
ylabel(yaxis);
xlim([time_start time_end]);

subplot(3,2,4);
p4 = plot(time4, est4, time4, enc4);
xaxis = 'Time [s]';
yaxis = 'Elevation rate [rad/s]';
xlabel(xaxis);
ylabel(yaxis);
xlim([time_start time_end]);

subplot(3,2,5);
p5 = plot(time5, est5, time5, enc5);
xaxis = 'Time [s]';
yaxis = 'Travel rate [rad/s]';
xlabel(xaxis);
ylabel(yaxis);
xlim([time_start time_end]);

lg = legend('State estimate', 'Encoder measurement');
lg.Position(1:2) = [.6 .02];


%% Plot only part of plot
time_start = 55; 
time_end = 75;  
xlim([time_start time_end]);


%% Legend
% Legend must come after you call plot()
% GIves a name to the plotted lines
%   
lgd = legend('Encoder measurement', 'Estimate, minimal C', 'Estimate, maximum C'); 
lgd.Location = 'southeast';
%legend('Measured value, Q = 20'); 
hold off

%% Save plot
% TO save the current plot use:
    % print( filename, '-d'+ filename )
    % Use epsc instad of eps to get colours
print(file_name, '-djpeg');
print(file_name, '-depsc');
