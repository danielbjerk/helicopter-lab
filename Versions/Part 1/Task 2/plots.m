%% Just press f5 to run everything, and read the section that has something you need

% Press (ctrl+enter) to run the section your cursor is currently in ( Marked in yellow)
clear all
close all

%% Init
input = load('p1t2_Vs-offset_elevation_v1.mat');
plot_title = 'Vs offset';
xaxis = 'Time [s]';
yaxis = 'Vs [V]';

time = input.ans(1,:);
values = input.ans(2,:);

time1 = 0;
time2 = time(end);


% figure; % Calling figure => Plot/write in a new window
hold on
title(plot_title);

plot(time, values);
xlim([time1 time2]);


% Set desctiptions on the axis
xlabel(xaxis);
ylabel(yaxis);

%% Plot only part of plot
time1 = 20;
time2 = 25;
xlim([time1 time2]);


%% Legend
% Legend must come after you call plot()
% GIves a name to the plotted lines
%   
legend(['legend("text")']); 
hold off

%% Save plot
% TO save the current plot use:
    % print( filename, '-d'+ filename )
    % Use epsc instad of eps to get colours
print(plot_title, '-djpeg');
print(plot_title, '-depsc');


%% Plotting values against each other

figure
hold on 
title('Ploting values against each other');
%Methon 1:
    %Give the inputs in pairs
    % X1 and X2 can have different lengths as long as the length is the
    % same for between X1 and Y1 (and so on)
plot(X1, Y1, X2, Y2);
legend(['It is fine to have more plots that legends']);
% Or more legends than plots (But it causes a warning)
hold off




% %Method 2:
%     % Give the X-values first and then a list of all Y-values 
%     %(Separate with ; )
        % plot( X1, [Y1; sin(X1) ] ); 





%% SUBPLOTS

figure;
hold on
title('Subplots');


% Subplot(n, m, i)
    %   Divides the window into a grid of n * m plots
    %   i is the position of the plot (left to right, top to bottom)  

    
subplot(2, 1, 1);
plot(X1, Y1);

% They work just like normal between hold on and hold off
subplot(2,1, 2); 
hold on
plot(X2, Y2, X2, -Y2);
legend('Subplot 2');
xlabel('X'); 
ylabel('Y'); 

legend(['Multiple subplots', 'Title is not working']);
hold off
hold off



%% Colours and styles
figure
hold on 
title('Colours and styles');
plot(X1, Y1, 'r', X2, Y2, 'b--', X1, Y1.*(-1) , 'pk');
% Add a string after X and Y to change colour and style
% The first letter is colour
    % The colours are:
        % blue      b
        % black     k	
        % red       r	
        % green     g	
        % yellow	y	
        % cyan      c	
        % magenta	m	
        % white     w
    
% The next letters are for style:
    % Line-types
        % '-'       Whole line(Default)
        % '--'      Dasked line
        % ':'       Dotted line
        % '-.'      Dasshed and dotted line
    % Marking data-points (Just some of them)
        % 'o'   circle
        % 'x'   cross
        % '*'   asterisk
        % 'p'   star (pentagram)

 
    
 

legend(['Add a string after X1 and Y1 to give colour or style', 'string = b--','Read comments for more']);


hold off;


%% Automatically Save Plot
figure;

    

hold on 
title('Automatically Save Plot');

plot(X1, Y1); 
legend('A curve...');
xlabel('X');
ylabel('Y');
hold off 

% TO save the current plot use:
    % print( filename, '-d'+ filename )
    % Use epsc instad of eps to get colours
print('Plot_filename', '-depsc');
print('Plot_filename', '-djpeg')

% string(10) makes the number 10 into '10' (Might be usefull for making filenames)
disp('Saved Plot as .jpeg and .eps '); 


%% Change Window-size
% The parameters can be given when:
    % making the figure(), or with the
    % set()-function

f = figure('color' , 'cyan'); 

% The variable gcf returns the current figure
set(gcf, 'color', 'green'); 



% Units sets how position is calculated
    % 'pixels'      :   (Default) 
    % 'normalized'  :   Positions on the window is represented with a
                        % number from 0 to 1            
    %'centimeters'  :   
    %'characters'   :   Character-width= width of character 'x' in the
                        % default size

                        
Units = 'normalized';  % Normalized is probably easiest to use  
set(gcf, 'Units', Units); 
    
% Position 0, 0 is in the bottom left corner
% Position = [    Position of left border ,
%                 Position of bottom border, 
%                 width, 
%                 height   ]; 
Position = [0,0, 1, 1]; %  ==>  Full screen if 'units' = 'normalized'
set(gcf, 'Position', Position);



hold on 
title('Change Window-size');  

plot(X1, Y1); 
legend('bg- colour set to green'); 

hold off



%% Misc. 
% Just so the windows are propperly placed, without cluttering the code

%Get handle of all open windows
figHandles = get(groot, 'Children');


winSize = 0.5
for i = size(figHandles, 1):-1:2
    x0 = 0.5-winSize/2;
    y0 = 0.5-winSize/2;
    Position = [x0,y0 winSize, winSize]
    
    set(figHandles(i), 'units', 'normalized');
    set(figHandles(i), 'Position', Position);
end;
   
uistack(figHandles(1), 'bottom'); % Put fullscreen-window behind all others 