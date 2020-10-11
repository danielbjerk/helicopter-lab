%% Just press f5 to run everything, and read the section that has something you need

% Press (ctrl+enter) to run the section your cursor is currently in ( Marked in yellow)
clear all
close all

%% Init one file
input = load('p2t2_pole-place-K_poles-2-2i-sqrt(8)_e_dot-c-and-e_dot.mat');
plot_title = 'Multivariable control, pole placement, manual input';
file_name = 'p2t2_pole-placement-manual-input_elevation-rate';
xaxis = 'Time [s]';
yaxis = 'Elevation rate [rad/s]';

time = input.ans(1,:);
setpoint = input.ans(2,:);
values = input.ans(3,:);

time_start = 0;
time_end = time(end);


% figure; % Calling figure => Plot/write in a new window
hold on
title(plot_title);

plot(time, setpoint);
plot(time, values);
xlim([time_start time_end]);


% Set desctiptions on the axis
xlabel(xaxis);
ylabel(yaxis);

lgd = legend('Reference', 'Measurement');
lgd.Location = 'southeast';

%% Init multiple files
figure
input1 = load('p2t4_LQR-computed-input-F-optimal_e-dot-c-and-e-dot.mat');
input2 = load('p2t4_LQR-computed-input-F-0-1-0-1_e-dot-c-and-e-dot.mat');
%input3 = load('p2t2_pole-place-controlled-input-K_poles-2,5-2,5i-sqrt(2,5^2+2,5^2)_e_dot-c-and-e_dot.mat');
%input4 = load('p1t3_pole-placement-a=-1-b=2-with-elev_pitch-measurement_v1.mat');
plot_title = 'Multivariable control, different choice of feed foreward matrix F';
file_name = 'p2t4_LQR-comparing-F_elevation-rate';
xaxis = 'Time [s]';
yaxis = 'Elevation rate [rad/s]';

time1 = input1.ans(1,:);
reference1 = input1.ans(2,:);
values1 = input1.ans(3,:);

time2 = input2.ans(1,:);
%reference2 = input2.ans(2,:);
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
input1 = load('p2t3_LQR-integration-test-step-inputs-Q-100-1-60_p-c-and-p_v1_weird-drop.mat');
input2 = load('p2t3_LQR-integration-test-step-inputs-Q-100-1-60_e-dot-c-and-e-dot_weird-drop.mat');
plot_title = 'LQR tuning, large drop';
file_name = 'p2t3_LQR-tuning_large-drop';

time1 = input1.ans(1,:);
reference1 = input1.ans(2,:);
values1 = input1.ans(3,:);

time2 = input2.ans(1,:);
reference2 = input2.ans(2,:);
values2 = input2.ans(3,:);

time_start = 0;
time_end = time1(end);



hold on
title(plot_title);

subplot(1,2,1);
plot(time1, reference1, time1, values1);
xaxis = 'Time [s]';
yaxis = 'Pitch [rad]';
xlabel(xaxis);
ylabel(yaxis);
time_start = 5; 
time_end = 35;  
xlim([time_start time_end]);


subplot(1,2,2);
plot(time2, reference2, time2, values2);
xaxis = 'Time [s]';
yaxis = 'Elevation rate [rad/s]';
xlabel(xaxis);
ylabel(yaxis);
xlim([time_start time_end]);

%% Plot only part of plot
time_start = 8; 
time_end = 20;  
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
