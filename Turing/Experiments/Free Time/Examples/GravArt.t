setscreen ("graphics:1380,768,noecho")

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                      Colours of Objects                     %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
const wallColour := grey % the colour of the walls
const edgeColour := black
var probeColour : int

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                      Constants                              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% the gravitational push of the walls
const wallGravityConstant := 100
% the gravitational pull of the planets
const planetGravity := -200
% the maximum initial speed is maxSpeed / maxDivider
const maxSpeed : real := 40
const maxDivider : real := 10
% the size in pixels of planet 1 and planet 2
const planet1Size := 60
const planet2Size := 60
% the closest that objects will be placed to the edge of the screen
const border := 10

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                      Variables                              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
var planet1X, planet1Y : real % the position of planet 1 in pixels
var planet2X, planet2Y : real % the position of planet 2 in pixels
var probeX, probeY : real % the probe's position in pixels
%var rProbeX, rProbeY : int % the probe's position in hundredths of pixels
var probeVelocityX, probeVelocityY : real % the probe's velocity in
%                                           hundredths of pixels
var planet1Colour, planet2Colour : int % the colour of planet 1

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   This procedure sets up the planets' and probe's position. %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
procedure InitPositions
    % the distance from planet 1 and planet 2 to the probe in pixels.
    var planet1Distance, planet2Distance : real
    % the distance between planet 1 and planet 2 in pixels.
    var distanceBetweenPlanets : real

    probeX := Rand.Int (border, maxx - border)
    probeY := Rand.Int (border, maxy - border)

    loop
	planet1X := Rand.Int (border, maxx - border)
	planet1Y := Rand.Int (border, maxy - border)
	planet1Distance := Math.Distance (planet1X, planet1Y, probeX, probeY)
	planet1Colour := Rand.Int (9, 14)
	exit when planet1Distance > 3 * planet1Size
    end loop
    loop
	planet2X := Rand.Int (border, maxx - border)
	planet2Y := Rand.Int (border, maxy - border)
	planet2Distance := Math.Distance (planet2X, planet2Y, probeX, probeY)
	planet2Colour := Rand.Int (9, 14)
	distanceBetweenPlanets :=
	    Math.Distance (planet2X, planet2Y, planet1X, planet1Y)
	exit when planet2Distance > 3 * planet2Size and
	    distanceBetweenPlanets > 3 * planet2Size and
	    planet1Colour not= planet2Colour
    end loop
    
    probeColour := Rand.Int (1, 8)
end InitPositions

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   This procedure determines the probe's initial velocity.   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
procedure InitProbeVelocity
    var endNow : boolean := false
    probeVelocityX := 0
    probeVelocityY := 0
    var c : string (1)
    loop
	c := getchar
	Draw.ThickLine (round (probeX), round (probeY), round (probeX + probeVelocityX),
	    round (probeY + probeVelocityY), 3, white)
	case c of
		% The 7 key (on the keypad)
	    label KEY_HOME :
		probeVelocityX -= 2
		probeVelocityY += 2
		% The 8 key (on the keypad)
	    label KEY_UP_ARROW :
		probeVelocityY += 2
		% The 9 key (on the keypad)
	    label KEY_PGUP :
		probeVelocityX += 2
		probeVelocityY += 2
		% The 4 key (on the keypad)
	    label KEY_LEFT_ARROW :
		probeVelocityX -= 2
		% The 6 key (on the keypad)
	    label KEY_RIGHT_ARROW :
		probeVelocityX += 2
		% The 1 key (on the keypad)
	    label KEY_END :
		probeVelocityX -= 2
		probeVelocityY -= 2
		% The 2 key (on the keypad)
	    label KEY_DOWN_ARROW :
		probeVelocityY -= 2
		% The 3 key (on the keypad)
	    label KEY_PGDN :
		probeVelocityX += 2
		probeVelocityY -= 2
	    label " ", KEY_ENTER :
		endNow := true
	    label :
	end case
	if probeVelocityX < -maxSpeed then
	    probeVelocityX := -maxSpeed
	elsif probeVelocityX > maxSpeed then
	    probeVelocityX := maxSpeed
	end if
	if probeVelocityY < -maxSpeed then
	    probeVelocityY := -maxSpeed
	elsif probeVelocityY > maxSpeed then
	    probeVelocityY := maxSpeed
	end if
	Draw.ThickLine (round (probeX), round (probeY),
	    round (probeX + probeVelocityX), round (probeY + probeVelocityY),
	    3, edgeColour)
	Input.Flush
	exit when endNow
    end loop

    probeVelocityX /= maxDivider
    probeVelocityY /= maxDivider
end InitProbeVelocity

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   This procedure draws the planets, probe and edge of the screen. %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
procedure DrawPlayingField
    cls
    drawbox (0, 0, maxx, maxy, wallColour)
    drawfilloval (round (probeX), round (probeY), 3, 3, probeColour)
    drawfilloval (round (planet1X), round (planet1Y), planet1Size, planet1Size, planet1Colour)
    drawfilloval (round (planet2X), round (planet2Y), planet2Size, planet2Size, planet2Colour)
end DrawPlayingField

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                     Main Procedure                       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

loop
    % Determine all the starting positions and velocity
    InitPositions
    DrawPlayingField
    InitProbeVelocity
    DrawPlayingField

    % The movement loop
    loop
	% Calculate the gravitational pull of the walls
	%
	% Gravitation Pull / Push = G / (r**2)
	%
	const wallGravityX := wallGravityConstant / (probeX ** 2) -
	    wallGravityConstant / ((maxx - probeX) ** 2)
	const wallGravityY := wallGravityConstant / (probeY ** 2) -
	    wallGravityConstant / ((maxy - probeY) ** 2)
	const wallGravity := sqrt (wallGravityX ** 2 + wallGravityY ** 2)

	% Calculate the gravitational pull of planet 1
	const d1x := planet1X - probeX
	const d1y := planet1Y - probeY
	const planet1Distance := sqrt (d1x ** 2 + d1y ** 2)
	exit when planet1Distance <= planet1Size % Hit planet 1 ?
	const planet1Gravity := planetGravity / (planet1Distance ** 2)
	const divisor1 := abs (d1x) + abs (d1y)
	const planet1GravityX := planet1Gravity * d1x / divisor1
	const planet1GravityY := planet1Gravity * d1y / divisor1

	% Calculate the gravitational pull of planet 2
	const d2x := planet2X - probeX
	const d2y := planet2Y - probeY
	const planet2Distance := sqrt (d2x ** 2 + d2y ** 2)
	exit when planet2Distance <= planet2Size
	const planet2Gravity := planetGravity / (planet2Distance ** 2)
	const divisor2 := abs (d2x) + abs (d2y)
	const planet2GravityX := planet2Gravity * d2x / divisor2
	const planet2GravityY := planet2Gravity * d2y / divisor2

	% Calculate the acceleration of the probe (x, y and total)
	const probeAccelerationX : real := wallGravityX + planet1GravityX +
	    planet2GravityX
	const probeAccelerationY : real := wallGravityY + planet1GravityY +
	    planet2GravityY
	const acceleration := sqrt (probeAccelerationX ** 2 +
	    probeAccelerationY ** 2)

	% Add the probe's acceleration to its velocity
	probeVelocityX += probeAccelerationX
	probeVelocityY += probeAccelerationY

	% This draws the three lines representing the gravitational
	% pull of the walls and planet 1 and planet 2
	const wallDX : int := round (probeX - wallGravityX * 500)
	const wallDY : int := round (probeY - wallGravityY * 500)
	const planet1DX := round (probeX - planet1GravityX * 500)
	const planet1DY := round (probeY - planet1GravityY * 500)
	const planet2DX := round (probeX - planet2GravityX * 500)
	const planet2DY := round (probeY - planet2GravityY * 500)
	Draw.ThickLine (round (probeX), round (probeY), planet1DX, planet1DY, 2, planet1Colour)
	Draw.ThickLine (round (probeX), round (probeY), planet2DX, planet2DY, 2, planet2Colour)
	% Add the probe's velocity to its position
	probeX += probeVelocityX
	probeY += probeVelocityY

	% Make some sound if the acceleration is really high.  (i.e. near
	% a wall or a planet
	if acceleration > 50 then
	    %            sound (round (200 + 2 * acceleration), 1)
	end if
	exit when hasch
	delay (15)
    end loop

    locate (24, 10)
    put "Play Again (Y for Yes)?   " ..
    Input.Flush
    var ch : string (1)
    getch (ch)
    exit when ch not= "Y" and ch not= "y"
end loop
