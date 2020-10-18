%% Init multiple files
figure
input1 = load('p3t4_sentripetal-acc_l-dot.mat');
input2 = load('p3t4_sentripetal-acc_e.mat');
plot_title = 'Effect of travel rate on measured elevation';
file_name = 'p3t4_sentripetal-acc-model';
xaxis = 'Travel rate [rad/s]';
yaxis = 'Elevation [rad]';

% Measurements
reference1 = input1.ans(4,:);
values2 = input2.ans(2,:);

% Model
l_h = 0.66;
g = -10;

x = 0:0.01:3.5;
y = atan((x.^2*l_h)/g);

% figure; % Calling figure => Plot/write in a new window
hold on
title(plot_title);

plot(reference1, values2);
plot(x, y);
xlim([0,3]);

legend('Measurements', 'Model');

%xlim([time_start time_end]);


% Set desctiptions on the axis
xlabel(xaxis);
ylabel(yaxis);

%% Save plot
% TO save the current plot use:
    % print( filename, '-d'+ filename )
    % Use epsc instad of eps to get colours
print(file_name, '-djpeg');
print(file_name, '-depsc');
