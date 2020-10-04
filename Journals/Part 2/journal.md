# Part 1

## Task 1

For manual control we mapped x axis and y axis of the joystick to pitch and elevation respectively. Having too small
gain we didn't get a response initially for the input, but using a scope we saw that there was input from the joystick,
so we made the gain larger and got the helicopter to fly around using the joystick. We saw that the pitch gain was a bit
high and the the elevation gain a bit low, so we sat those lower and higher respectively (to 2.5 and 10). It was still
a bit hard to control the helicopter this way, but at least it was possible.


## Task 2


### Initial thoughts
We noticed that there are essentially two sensor systems: the IMU and the encoders. We thought that we were going to use
the IMU for reading angles initially (by integrating the rate), but found out that the encoders were already available
in the helicopter simulink template. 


### Coordinate systems
We define that travel is 0 when propellers are to the right of the computers and the block is to the left of the
computers.

Pitch angle rotation system: seen from propellers, counter clockwise
Elevation angle rotation system: seen from computers, counter clockwise
Travel angle rotation system: Seen from above, clockwise.


### Find the elevation offset
We used a bubble level app reading the gyroscope from a smart phone to check the elevation angle when the helicopter 
is level, as it is initialized to zero when it is stationary at ground. 

We found, using data exported from the simulink folder using the file block attached to the elevation output and 
average calculations in matlab, that the average value of the elevation in radians when the helicopter is level is 
0.4352. We only used the interval when the elevation had stabilzed (from 10 seconds to the end in our case).  

Thereafter we spent some time to make a system for plotting files easily.

We found out that we'd rather do the offset correction on the encoder output instead of the calculated elevation in
radians, so we did the calibration once more where we got data directly from the encoder. Using the same procedure with
getting the data and taking an average of it between time 35 and the end of the data, we ended up with an average of 
-292.5548.

After correcting with this value we got quite close to having elevation encoder output at 0 for level elevation, but
were still at an average offset of -29.7063. Thus we added this value to the correction offset, which then was
-322.2611. The results from this value was quite good, resulting in an average error of 0.5232 steps, which corresponds
to ~0.05 degrees, which we were satisfied with. *The main error sources in this is of course the phone measurements*.


### Finding Vs_0
We tried to apply a step input to Vs in order to Find Vs_0, but the method proved to be inefficient as we have to try
many values and since the pitch angle isn't stable at this point.

We applied the standard for data files: part-x_task-7_what-we-are-looking-for_variable_version.mat

The offset in Vs_0 is of course reliant on the error in the elevation offset we found.

The second method we tried was to disable the pitch for the joystick and only control elevation. The first tries we 
used scopes in simulink to try to look at the voltage when the elevation was 0, but we found this to be a bit
inaccurate as well. The third method was to export the voltage and elevation data from simulink and analyse it in
matlab. In that way we could get the elevation to a horizontal level without concering ourselves about pitch. 
As we did this we recorded the data for elevation angle and Vs, plotting these against each other, with voltage 
as x and elevation as y, yielded how much voltage the motors needed for keeping at a level elevation. 
We found the voltages when this graph crossed 0 (0 in elevation) and took the average of these values to find the 
voltage Vs_0. The result we got is Vs_0 = 7.5443 V. 

We wanted to remove the outliers when we were rising and falling, and at the same time passing through the elevation
of 0, thus not staying stationary at elevation 0. Thus we tried to remove the lower and upper 10 percent of the dataset
within the margin of a step size of 5 steps. Taking the average of this resulted in Vs_0 = 7.4953 V. Inserting a step 
response of this resulted in almost a level elevation.

We tried another run having the helicopter more stable with manual control (not going up and down around equilibrium) 
and it resulted in an average of Vs_0 = 7.8394 V. When we then applied a step response with this voltage the response
was much better and we got much closer to a level elevation within +-0.1 [rad]. 


### Finding Kf

We calculated the Kf in the init file using the equations derived in the preperation work, using the Vs_0 we had found
experimentally and setting e = p = 0.



## Task 3


### Elevation controller

We sat up the connections in simulink, added Vs_0 offset to Vs and constructed the pitch PD controller. We then sat out
to test the elevation controller with the default values not using the pitch controller (setting Vd to 0). The elevation
PID controller worked quite good, even when we try to introduce disturbences through yanking it down or up.

### Pitch controller


#### Using the tuning diagram

We sat a arbitary number for Kpp to 5 and sat Kpd to 0 just to get a simple controller and eliminate as many variables as
possible and sources of error. The PD controller was a bit aggressive, oscillating and almost becoming unstable, 
we tried to reduced it until the helicopter didn't oscillate in pitch, but decided to drop the elevation controller and
only tune on the pitch controller.


##### Adding a feedforwarded constant voltage
We realized that we have to start the helicopter level at the ground so the pitch is also 0 when level. We noticed 
that there is a slight inbalance between the left and right motor, and discussed whether we should include an integral
in the controller or add a constant voltage so the pitch was level. We landed on adding a constant extra voltage 
to one of the motor to compensate, as we did in finding the voltage Vs_0. After observing the voltages we cut out the
outliers by inspection (and after by percentile) and arrived at a Vd_0 = -1.3979. This resulted in a level pitch. Thus
we have feedforward componsated for a difference in mass between the two propellars.


##### Further tuning
We moved forward inputing a square wave and seeing the response, figuring out the p-value that didn't give much
oscillations, was stable and a some what responsive. We then experience with the D component. With the D component we
sat it to 0.1P, increased it until we removed the remaining oscillations then we increased P until we got oscillations
and decreased it until they were more or less gone.


#### Testing manual input 
We then tested some manual input with the pitch controller. We found there were some high frequency noise on the
input making the helicopter jitter. We therefore applied a low pass filter on the input. This fixed the jitter.

Thereafter we saw quite a lot of oscillations on manual control, therefore we reduced P to a previous known value which
had worse responsiveness, but less oscillations. We ended up with Kpp = 2.75 and Kpd = 2.


#### Running without compensation and tuning manually
We wanted to explore not having a Vd_0, since we get less responsive control when rotating counter clockwise. We added
an offset in the pitch angle and noticed that the problem was somewhat solved due to the fact that the constant
compansisation now went through the controller. The compansisation was not fully correct and we concluded that it could
often be error prone shifting the angle, so we ended up placing some weight on the one side to compenstate such that 
the rotors were level without any compensation from the controller. The simple solutions are often the best. We then did
some manual tuning and found some parameters for Kpp and Kpd which turned out to be far better than anything we've had
so far.


#### Tuning using pole placement

We used the equations derived in the preperation work to get Kpp and Kpd given some arbitrary poles in simulink.


Looking at the response for poles -3 +- i we saw that the response was fairly good, the only downside is that when we
pitch, the pitch part of the controller dominates initially because the elevation can still keep up, but then the
helicopter drops because abs(Vd) >> 1, and then elevation kicks in and dominates pitch. When elevation is satisfied,
pitch can dominate again and get to the setpoint. When we move the poles closer to the imaginary axis we get less
competition between the two regulators and the elevation can keep up. 

Then we sat the pitch controller tuned quite aggressive at poles -4 +- 1 and looked at how the system didn't saturate
when we had no elevation controller and did saturate when we also had the elevation controller.

After that we showed that the system didn't saturate for poles -2 +- 1 and -1 +- 1.

Then we experimented with shifthing the poles with a given angle from -2 +- 1. We shifted with -18.4 degrees at a time,
yielding better response at the first shift, but more oscillations at the second shift, which is obvious given the
larger imaginary component. Then we shifted towards the real axis (positiv angle of 18.4), which yielded a slower
response, which corresponds with what the textbook has specified. This is somewhat counter intuitive when only looking
at the poles, but with the system as a whole and saturation in mind, this makes sense.

We wanted to see how placing with resonance frequency and damping factor. We tried some different values for this just
to experiment. With this we sat it to be critically damped and increased the omega_0.





# Part 2

## Task 1

We implemented the model with feedback control using the F and K matrices, where we decided to have the F and K matrices
represented by gains in simulink and where we specified the F and K matrices as variables in our initialization script.
We essentially just replaced the previous controller, turning u into F * r - K * x.


## Task 2

We set up the A and B matrices in our init script, chose some poles and got the K matrix from using the place function.
Thereafter we constructed the F matrix from the values we got in the K matrix. The first runs yielded a system with
quite poor response. We tried to understand the equations derived a bit more and saw that we had a wrong derivation of
the K_2 constant, which yielded a positive feedback loop for the elevation rate controller. 

The K matrix moves the poles to the desired position for the closed loop no reference system. The F matrix puts on a
offset from the equilibrium, then we make sure that the values in F corresponds to values in K such that the gain for
reference and state are both from the same k element value, which yields that we essentially only have to change n k
elements. 

We noticed that the joystick isn't offset at 0 when we initialize the system, so we had to compensate for this by
increasing the dead zone to +- 0.12.

We saw that when applying a high elevation rate reference, the helicopter rose to a given angle and stayed stationary.
In this process we saw that the elevation rate could thus not follow the elevation rate reference, and eventually
decreased to zero after a step response. We thought this was illogical given that the motor can supply 12V and we were 
under that, but upon close inspection we saw that the input to the motors were saturated at 5 and -5 V. This makes the
observations we saw logical.

We sat the poles so that it became marginally stable with poles at the imaginary axis, as well as poles in the right
half plane just for a laugh.

We then set out to place the poles optimally, with them evenly around a circle sector. The first circle sector had
theta = 45 and radius = sqrt(2). We then wanted to see if we could get a faster response, so we increased the circle and
decrased theta, so that it became theta = ~26 and radius = sqrt(5). We increased the radius until we saw oscillations.
Then we moved down and found.


## Task 3

Using the LQR function in matlab we sat up a K matrix. The first responses were not that good. The elevation was quite 
sloppy, so we increased the entry for it in the Q matrix. Then we saw that we didn't saturate the actuators, 
so we decreased the elements in the R matrix. Then, to get better pitch responds we increased the pitch element in 
the Q matrix and reduced the cost for Vd in R. After that we incresed the elevation rate element in the Q matrix a 
bit more to get better elevation response. After that we also increased Vs until we reached the border of saturation.

As we were not so satisfied with the LQR, we wanted to start from scratch. We penalized high elevation rate error 
(Q = 1 1 100) in the Q matrix until we got a stable elevation, then we increased the penalty for pitch until we got 
a good response (Q = 20 1 100). We got to the point (Q = 40 1 100) where we couldn't notice the difference between 
two Q matrices, so we spent some time plotting them against each other to really see the difference.

When we saw that the difference between the increased value for pitch in the Q matrix yielded minimal difference in 
response (20 -> 40), but at the same time we observed that the elevation seemed to struggle more. So at that point we 
decreased Vs (1 -> 0.1) to give the controller more room for actuation, then we saw a clear difference while pitch
remained more or less spot on.

As we didn't have a good system for plotting this, we spent some time constructing that.

The files for these experiments were called LQR tuning [...].


### Tuning after task 4

After going through with task 4 we wanted to step back to task 3 to tune it a bit better. So we set up a step respsonse
on pitch and had elevtion change on a square pulse.

### The dip

Realize p-dot is the way to stop the dip, Q_22 -> 20
This definetly helped with the dip
Q_22 -> 30 
ran with manual input
No discernible difference
Plot elevation rate response with Q_22 = 20 against Q_22 = 30
Too difficult to make out a difference when looking at manual input, decide to test both values with square wave input to get a better dataset for what is better.
No discernible difference in the dip between 20 and 30 with sqare wwave input
Try out Q_22 = 80
This resulted in a much lower dip, plot the computed_input 20 and 80 against each other
Then tried to use manual control with Q_22 = 80 to see how this affected the overall response.
The pitch seemed to be more sluggish, and not as able to reach the reference, but as we defined our goal to be "avoiding the dip at all cost", we were willing to sacrifice some speed for a safer helicopter.
We still tried out increasing Q_11 from 40 to 80. This resulted in a bigger dip, but the heli didnt crash.
We wanted to see if this new value caused a faster overall response, and therefore tested it with manual input
This didnt seem to have much of a difference


Lærepenge: kontroller manuelt, bruk square wave for å se forskjell mellom to verdier funnet manuelt


## Task 4

We have implemented the system with integral effect, by just integrating up the values for gamma dot and zeta dot.
We were not sure where G went in the system. Also we didn't understand why we introduce integral effect, when we don't
have any obvious disturbances and state feedback allegedly gives zero stationary error. We also don't understand how the
integral effect affects how we choose F.

We experimented some with increasing the values for zeta and gamma. With increasing gamma to 100, we got a far better
elevation response. With increasing gamma, we got more overshoot, which we concluded was because we weighted that the
integral of the error in pitch should be zero, yielding that the pitch will overshoot.  

Since the equations for F yielded that no matter what we choose for the F matrix, we will achieve a steady state, the
values for the F matrix are somewhat irrelevant.

We found that doing the tests with square pulses doesn't give a good indicator since we're switching too quickly. Thus
we moved to step response.

For gamma, we tested a lot of random things initially, then we got some achieved some intuition for what the integral
part does. Then we experimented a bit more sytematically, finding a value which gave us zero stationary error, and a
fairly quick response.

After that we went with elevation rate integral. We saw that we ought to go back to task 3 to tune that regulator
better (see above).






After going back and tuning task 3 appropratiatly, we went back to task 4.
We now have a system where the response not always reach the reference value, and therefore integral effect might be useful.

Plan: Test loads of stuff to build intuition. then go back to make nice plots of what weve learnt, using controlled inputs, then lastly tune the controller with manual flying using controlled inputs to discern between too similar responses

First test system with neither integral effect, large stationary error in pitch

Test with only integral in pitch, less to none stationary error, seemingly slower respoinse

Test with both integrators, less error in general in elevation rate, seemingly no difference to pitch responseo
(all these plots are stored in "ddatasets comparing integrator ...")

We realize: no integrator the controllers alone will reach the reference, but when put together this doesnt happen and we get stationary error. then, implementing integral effect the combined controllers are devoid of stationary error.

Realize step input on the pitch still gives stationary error, but only after a while. Previous result was incorrect. Try Q = 40 80 100 5 1 with step of 0.3
Realize this doesnt happen when the heli isnt allowed to rotate.
Realiaze this is due to the elevation rate controller "stealing" some of the motor voltage when the heli starts pitching and therefore falling. When the heli is held the elevation rate controller has 0 output, so the pitch controller doesnt get a stationary error. 

lov til å isolere variabler når man forsøker å finne ut små forskjeller eller teste hypoteser.

next: test different values of F given Q = 40 80 100 1 1
test step in pitch of 0.3 and plot and then test step in e rate and plot.
F = 0 32; 7.8 0; (optimal): Both steps cause heli to quickly approach reference.

---
Sidestep: why does changes in e rate cause it to temporarily increase then bottom out?
working hypothesis: 
- higher elevation requires higher motor force
- speed can only be increased so much as the motors saturate
Plot it, see that the motors saturate (but why?)
---

F=0 1 1 0: Slow pitch response, elevation rate doesnt seem to even increase but this is in line with there being an upper limit to how long the heli may attempt to increase e rate before it reaches the elevation at which it equlibriums.
conclusion: the elevation rate plots are useless and we cant do anything about it, but in pitch it is easy to see that the optimal feed foreward causes the heli to resach stationary value more quickly.
(these files are stored in "datasets comparing F optimal with F arbritrary")

Laslty: tuning.

Goal: Tune the LQR values so that we achieved maximum speed and zero stationary error without sacrificing neither the dip nor overshoot.

Method: Control the heli with the controller, change variables to increase performance, when change of variables doesnt create noticable difference: use a computed input and plot values against each other and/or decrease corresponding values of R

Q = 40 80 100 1 1:
Seems fine, maybe a bit slow in pitvh, takes 2 seconds to completely turn

-> increase p integral

Q = 40 80 100 20 1:
faster pitch, 1 second to turn, more overshoot, no discernible difference in e rate

-> decrease p integral to minimize overshoot

Q = 40 80 100 10 1:
No discernible difference, perhaps slower?

Test Q = 40 80 100 10 1 vs 40 80 100 20 1:
plot them against each other, see very little difference, but 20 definetively gives more overshoot but faster response.

PLaying around:

Decrease R_22 to 0.1, get unstable response, decide this means the previous tunings were too aggressive,

Decrease Q to 10 1 100 1 1:
No difference in speed, some overshoot

Q = 10 1 100 0.5 1:
Less overshoot. Question: why care about Q_11 at all?

Q = 200 1 100 0.5 1:
Large oscillations. Back to previous

Q = 10 1 10 0.5 1:
Perfect when looked at from a distance, elevation rate low

Q = 10 1 100 0.5 0.5:
Best so far, no difference in pitch dynamics, elevation rate flats out closer to reference

Just for fun:

Q = 10 1 1 0.5 10:
Higher overshoot and elevation rate flats out closer to 0

Back to previous:
Q = 10 1 100 0.5 0.5:
Pitch reference changed to plus minus 0.5
No large differences
Test this tuning with controller:
Looks amazeballs.
