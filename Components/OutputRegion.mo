within CellularAutomataLib.Components;
model OutputRegion
  import CellularAutomataLib.Components.*;
  parameter Integer XFromRange[2] = {1,1} "FROM region in X";
  parameter Integer YFromRange[2] = {1,1} "FROM region in Y";
  parameter Integer ZFromRange[2] = {1,1} "FROM region in Z";
  parameter Integer Output_type = 1 "Output observation method" annotation (
    choices(choice = 1 "Average", choice = 2 "Max", choice = 3 "Min", choice = 4 "Sum"));
  parameter Real output_rate "Output sampling interval";
  //parameter String name "output";

  replaceable function ExtOutput "External output function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;
    output Real value;
  end ExtOutput;

  input CAport FROM "Reference to cellular space" annotation (Placement(
        transformation(extent={{-10,-10},{10,10}}), iconTransformation(extent={{
            -10,-10},{10,10}})));
  Modelica.Blocks.Interfaces.RealOutput y annotation (
    Placement(transformation(extent = {{50, -10}, {70, 10}}), iconTransformation(extent = {{50, -10}, {70, 10}})));
protected
  Real sum;
  Real min;
  Real max;
  Real v;
  // Integer m,      n;
algorithm
  when sample(0, output_rate) then
      if Output_type == 1 then
      //AVERAGE
      sum := 0;
      for i in XFromRange[1]:XFromRange[2] loop
        for j in YFromRange[1]:YFromRange[2] loop
          for k in ZFromRange[1]:ZFromRange[2] loop
            sum := sum + ExtOutput(FROM.space, i, j, k);
          end for;
        end for;
      end for;
      y := sum/(((XFromRange[2]+1)-XFromRange[1]) * ((YFromRange[2]+1)-YFromRange[1]) * ((ZFromRange[2]+1)-ZFromRange[1]));
    elseif Output_type == 2 then
      // MAX
      max := -Modelica.Constants.inf;
      for i in XFromRange[1]:XFromRange[2] loop
        for j in YFromRange[1]:YFromRange[2] loop
          for k in ZFromRange[1]:ZFromRange[2] loop
            v := ExtOutput(FROM.space, i, j, k);
            if v > max then
              max := v;
            end if;
          end for;
        end for;
      end for;
      y := max;
    elseif Output_type == 3 then
      // MIN
      min := Modelica.Constants.inf;
      for i in XFromRange[1]:XFromRange[2] loop
        for j in YFromRange[1]:YFromRange[2] loop
          for k in ZFromRange[1]:ZFromRange[2] loop
            v := ExtOutput(FROM.space, i, j, k);
            if v < min then
              min := v;
            end if;
          end for;
        end for;
      end for;
      y := min;
    elseif Output_type == 4 then
      //SUM
      sum := 0;
      for i in XFromRange[1]:XFromRange[2] loop
        for j in YFromRange[1]:YFromRange[2] loop
          for k in ZFromRange[1]:ZFromRange[2] loop
            sum := sum + ExtOutput(FROM.space, i, j, k);
          end for;
        end for;
      end for;
      //Modelica.Utilities.Streams.print(String(time)+" : "+name+" sum = "+String(sum/6));
      y := sum;
    end if;
  end when;
  annotation (
    Documentation(info="<html>
<p>The Output Region model can be used to observe the state of the cells in a region of the automata connected to the FROM port. The state is translated into an output Real signal that can be used by other Modelica models. The region of selected cells is defined by the coordinates defined by XFromRange, YFromRange and ZFromRange.</p>
<p>This model has been divided in two, the OutputRegion and the OutputRegionM models. </p>
<p><br>The OutputRegion model contains an output Real port, y. Depending on the value of the parameter Output_type, the state is observed in different ways:</p>
<ul>
<li>(AVERAGE): the value of y is calculated as the average value of the states of the cells in the region. </li>
<li>(MAX): the value of y is calculated as the maximum value of the states of the cells in the region. </li>
<li>(MIN): the value of y is calculated as the minimum value of the states of the cells in the region. </li>
<li>(SUM): the value of y is calculated as the sum of the values of the states of the cells in the region. </li>
</ul>
<p><br>The value of the state is translated into a Real value using the ExtOutput function, that can be redeclared using the double ExtOutput(void* space, int x, int y, int z) function included in draft.c.</p>
</html>"),
    Icon(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics={  Line(points = {{-30, 60}, {-30, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-10, 60}, {-10, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{10, 60}, {10, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{30, 60}, {30, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, 40}, {50, 40}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, 20}, {50, 20}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, 0}, {50, 0}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, -20}, {50, -20}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, -40}, {50, -40}}, color = {0, 0, 255}, smooth = Smooth.None), Text(extent = {{-50, 100}, {-10, 60}}, lineColor = {0, 0, 255}, textString = "%Cstart"), Text(extent = {{10, 100}, {50, 60}}, lineColor = {0, 0, 255}, textString = "%Cend"), Text(extent = {{-90, 60}, {-50, 20}}, lineColor = {0, 0, 255}, textString = "%Rstart"), Text(extent = {{-90, 0}, {-50, -40}}, lineColor = {0, 0, 255}, textString = "%Rend"), Text(extent = {{-70, -60}, {70, -100}}, lineColor = {0, 0, 255}, textString = "%name"), Text(extent = {{50, 46}, {70, 26}}, lineColor = {0, 0, 255}, textString = "yM"), Text(extent = {{50, -4}, {70, -24}}, lineColor = {0, 0, 255}, textString = "y")}),
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics));
end OutputRegion;
