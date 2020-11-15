start_time = 20;
start_step = start_time/0.002;
stop_time = 90;
stop_step = stop_time/0.002;

input1 = load('p4t1_noise-estimation-laying-still_full-IMU_v1.mat');
input2 = load('p4t1_noise-estimation-flying_full-IMU_v2.mat');

input1.ans = input1.ans(:,start_step:stop_step);
input2.ans = input2.ans(:,start_step:stop_step);

time1 = input1.ans(1,:);
p1 = input1.ans(2,:);
p_dot1 = input1.ans(3,:);
e1 = input1.ans(4,:);
e_dot1 = input1.ans(5,:);
l_dot1 = input1.ans(6,:);

time2 = input2.ans(1,:);
p2 = input2.ans(2,:);
p_dot2 = input2.ans(3,:);
e2 = input2.ans(4,:);
e_dot2 = input2.ans(5,:);
l_dot2 = input2.ans(6,:);


figure
plot(time2, l_dot2, time1, l_dot1);
hold on

R_d_11 = cov(p2);
R_d_22 = cov(p_dot2);
R_d_33 = cov(e2);
R_d_44 = cov(e_dot2);
R_d_55 = cov(l_dot2);

R_d = cov((input2.ans(2:6,:))');
% R_d = diag([R_d_11 R_d_22 R_d_33 R_d_44 R_d_55]);