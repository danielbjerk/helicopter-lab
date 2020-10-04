margin = 5;

input1 = load('p1t2_Vs-offset_Vs_v2.mat');
voltages = input1.ans(2,:);

input2 = load('p1t2_Vs-offset_elevation_v2.mat');
elevations = input2.ans(2,:);

candidates = zeros(1, size(voltages, 2));

candidate_count = 0;

for i = 1:size(voltages, 2)
    if abs(elevations(i)) < margin
        candidate_count = candidate_count + 1;
        candidates(candidate_count) = voltages(i);
    end
end

candidates = sort(candidates(1,1:candidate_count),'ascend');

min_voltage = candidates(1);
max_voltage = candidates(end);
delta_voltage = max_voltage - min_voltage;
percentile = 0.1;
lower_tresh = min_voltage + percentile*delta_voltage;
upper_tresh = min_voltage + (1-percentile)*delta_voltage;

candidates_no_outliers = zeros(1, size(candidates, 2));

candidates_no_outliers_count = 0;

for i = 1:size(candidates, 2)
    if lower_tresh < candidates(i) && candidates(i) < upper_tresh
        candidates_no_outliers_count = candidates_no_outliers_count + 1;
        candidates_no_outliers(candidates_no_outliers_count) = candidates(i);
    end
end

candidates_no_outliers = sort(candidates_no_outliers(1,1:candidates_no_outliers_count),'ascend');

plot(candidates_no_outliers);
figure;

avg_voltage = mean(candidates_no_outliers,2);

%%

plot(voltages, elevations);
title('Phase plot of Vs offset analysis first try');
xlabel('Vs [V]');
ylabel('Elevation [steps]');
print('p1t2_Vs_offset_phase_plot_first_try', '-djpeg');
print('p1t2_Vs_offset_phase_plot_first_try', '-depsc');