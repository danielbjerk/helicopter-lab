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




