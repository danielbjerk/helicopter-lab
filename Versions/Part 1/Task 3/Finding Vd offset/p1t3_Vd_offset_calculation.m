margin = 5;

input1 = load('p1t3_Vd-offset_Vd_v1.mat');
voltages = input1.ans(2,:);

input2 = load('p1t3_Vd-offset_pitch_v1.mat');
pitches = input2.ans(2,:);

candidates = zeros(1, size(voltages, 2));

candidate_count = 0;

%plot(voltages);
%title('Observed voltages for Vd');
%xlabel('Counts');
%ylabel('Vd [V]');
%print('p1t3_Vd_offset_observed_voltages_v1', '-djpeg');
%print('p1t3_Vd_offset_observed_voltages_v1', '-depsc');

for i = 6000:24000
    if abs(pitches(i)) < margin
        candidate_count = candidate_count + 1;
        candidates(candidate_count) = voltages(i);
    end
end

candidates = sort(candidates(1,1:candidate_count),'ascend');
plot(candidates);
figure;

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

plot(voltages, pitches);
title('Phase plot of Vd offset analysis first try');
xlabel('Vd [V]');
ylabel('Pitch [steps]');
print('p1t3_Vd_offset_phase_plot_v1', '-djpeg');
print('p1t3_Vd_offset_phase_plot_v1', '-depsc');