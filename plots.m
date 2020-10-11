%% Just press f5 to run everything, and read the section that has something you need

% Press (ctrl+enter) to run the section your cursor is currently in ( Marked in yellow)
clear all
close all

%% Init one file
input = load('p3t1_accelerometer.mat');
plot_title = 'Accelerometer measurements';
file_name = 'p3t1_testing-accelerometer';
xaxis = 'Time [s]';
yaxis = 'Acceleration [rad/s^2]';

time = input.ans(1,:);
setpoint = input.ans(2,:);
values = input.ans(3,:);
values2 = input.ans(4,:);

time_start = 0;
time_end = time(end);


% figure; % Calling figure => Plot/write in a new window
hold on
title(plot_title);

plot(time, setpoint);
plot(time, values);
plot(time, values2);
xlim([time_start time_end]);


% Set desctiptions on the axis
xlabel(xaxis);
ylabel(yaxis);

lgd = legend('x', 'y', 'z');
lgd.Location = 'southeast';

%% Init multiple files
figure
input1 = load('p3t1_gyro-and-enc-one-axis_pitch-rate.mat');
input2 = load('p3t1_gyro-and-enc-one-axis_elevation-rate.mat');
input3 = load('p3t1_gyro-and-enc-one-axis_travel-rate.mat');
%input4 = load('p1t3_pole-placement-a=-1-b=2-with-elev_pitch-measurement_v1.mat');
plot_title = 'Multivariable control, different choice of feed foreward matrix F';
file_name = 'p2t4_LQR-comparing-F_elevation-rate';
xaxis = 'Time [s]';
yaxis = 'Elevation rate [rad/s]';

time1 = input1.ans(1,:);
reference1 = input1.ans(2,:);
%values1 = input1.ans(3,:);

time2 = input2.ans(1,:);
reference2 = input2.ans(2,:);
%values2 = input2.ans(3,:);

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
input1 = load('p3t1_gyro-and-enc-multiple-axis_pitch-rate_elevation-affecting-travel.mat');
input2 = load('p3t1_gyro-and-enc-multiple-axis_elevation-rate_elevation-affecting-travel.mat');
input3 = load('p3t1_gyro-and-enc-multiple-axis_travel-rate_elevation-affecting-travel.mat');
plot_title = 'Elevation affecting measured travel rate';
file_name = 'p3t1_gyro-vs-enc_elevation-affecting-travel';

time1 = input1.ans(1,:);
reference1 = input1.ans(2,:);
values1 = input1.ans(3,:);

time2 = input2.ans(1,:);
reference2 = input2.ans(2,:);
values2 = input2.ans(3,:);

reference2 = cumtrapz(time2, reference2);
values2 = cumtrapz(time2, values2);

time3 = input3.ans(1,:);
reference3 = input3.ans(2,:);
values3 = input3.ans(3,:);

time_start = 0;
time_end = time1(end);



hold on

subplot(3,1,1);
h(:,1) = plot(time1, reference1, time1, values1);
title(plot_title);
xaxis = 'Time [s]';
yaxis = 'p dot [rad/s]';
%xlabel(xaxis);
ylabel(yaxis);
time_start = 5; 
time_end = time_end;  
xlim([time_start time_end]);


subplot(3,1,2);
h(:,2) = plot(time2, reference2, time2, values2);
xaxis = 'Time [s]';
yaxis = 'e [rad]';
%xlabel(xaxis);
ylabel(yaxis);
xlim([time_start time_end]);


subplot(3,1,3);
h(:,3) = plot(time3, reference3, time3, values3);
xaxis = 'Time [s]';
yaxis = 'lambda dot [rad/s]';
xlabel(xaxis);
ylabel(yaxis);
xlim([time_start time_end]);

lg = legend('Gyro measurement', 'Encoder measurement');
lg.Position(1:2) = [.7 .02];

%% Plot only part of plot
time_start = 55; 
time_end = 75;  
xlim([time_start time_end]);


%% Legend
% Legend must come after you call plot()
% GIves a name to the plotted lines
%   
lgd = legend('Reference', 'Measurement, optimal F', 'Measurement, F = identity matrix'); 
lgd.Location = 'southeast';
%legend('Measured value, Q = 20'); 
hold off

%% Save plot
% TO save the current plot use:
    % print( filename, '-d'+ filename )
    % Use epsc instad of eps to get colours
print(file_name, '-djpeg');
print(file_name, '-depsc');
