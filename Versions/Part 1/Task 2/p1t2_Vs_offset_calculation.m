margin = 5;

input1 = load('p1t2_Vs-offset_Vs_v3.mat');
voltages = input1.ans(2,:);

input2 = load('p1t2_Vs-offset_elevation_v3.mat');
elevations = input2.ans(2,:);

candidates = zeros(1, size(voltages, 2));

candidate_count = 0;


tmp_plot_volt = zeros(1, size(voltages, 2));
tmp_plot_elev = zeros(1, size(voltages, 2));

for i = 1:size(voltages, 2)
    if abs(elevations(i)) < margin
        candidate_count = candidate_count + 1;
        candidates(candidate_count) = voltages(i);
        
        tmp_plot_volt(candidate_count) = voltages(i);
        tmp_plot_elev(candidate_count) = elevations(i);
    end
end

candidates = sort(candidates(1,1:candidate_count),'ascend');

tmp_plot_volt = sort(tmp_plot_volt(1,1:candidate_count), 'ascend');
tmp_plot_elev = sort(tmp_plot_elev(1,1:candidate_count), 'ascend');


min_voltage = candidates(1);
max_voltage = candidates(end);
delta_voltage = max_voltage - min_voltage;
percentile = 0.1;
lower_tresh = min_voltage + percentile*delta_voltage;
upper_tresh = min_voltage + (1-percentile)*delta_voltage;

candidates_no_outliers = zeros(1, size(candidates, 2));

candidates_no_outliers_count = 0;


tmp_plot_volt_sheared = zeros(1, size(tmp_plot_volt, 2));
tmp_plot_elev_sheared = zeros(1, size(tmp_plot_volt, 2));


for i = 1:size(candidates, 2)
    if lower_tresh < candidates(i) && candidates(i) < upper_tresh
        candidates_no_outliers_count = candidates_no_outliers_count + 1;
        candidates_no_outliers(candidates_no_outliers_count) = candidates(i);
        
        tmp_plot_volt_sheared(candidates_no_outliers_count) = tmp_plot_volt(i);
        tmp_plot_elev_sheared(candidates_no_outliers_count) = tmp_plot_elev(i);
    end
end


candidates_no_outliers = sort(candidates_no_outliers(1,1:candidates_no_outliers_count),'ascend');


tmp_plot_volt_sheared = sort(tmp_plot_volt_sheared(1,1:candidates_no_outliers_count), 'ascend');
tmp_plot_elev_sheared = sort(tmp_plot_elev_sheared(1,1:candidates_no_outliers_count), 'ascend');


plot(candidates_no_outliers);
figure;

avg_voltage = mean(candidates_no_outliers,2);

%%
hold on
% scatter(tmp_plot_volt_sheared, tmp_plot_elev_sheared);
scatter(tmp_plot_volt_sheared, tmp_plot_elev_sheared,'jitter','on', 'jitterAmount', 0.03);
x_vals = [0:0.1:9];
plot(x_vals, zeros(1, length(x_vals)));
y_vals = [-50:0.1:350];
plot(7.839*ones(length(y_vals)), y_vals, 'r');
title('Scatter plot of Vs offset analysis');
xlim([7.4 8.1]);
ylim([-6 4]);
xlabel('Vs [V]');
ylabel('Elevation [steps]');
lgd = legend('Datapoints','e = 0','Calculated V_{s,offset}');
lgd.Location = 'northwest';
%%
print('p1t2_Vs_offset_phase_plot_scatter', '-djpeg');
print('p1t2_Vs_offset_phase_plot_scatter', '-depsc');