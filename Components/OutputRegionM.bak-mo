within CellularAutomataLib.Components;
model OutputRegionM
  parameter Integer XFromRange[2] = {1,1} "region initial column";
  parameter Integer YFromRange[2] = {1,1} "region final column";
  parameter Integer ZFromRange[2] = {1,1} "region final column";
  parameter Real output_rate "Output sampling interval";

  replaceable function ExtOutput "External output function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;
    output Real value;
  end ExtOutput;

  input CAport FROM "Reference to cellular space" annotation (Placement(transformation(
          extent={{-10,-10},{10,10}}), iconTransformation(extent={{-10,-10},{10,10}})));
  Modelica.Blocks.Interfaces.RealOutput yM[XFromRange[2]-XFromRange[1]+1, YFromRange[2]-YFromRange[1]+1, ZFromRange[2]-ZFromRange[1]+1] annotation (
    Placement(transformation(extent = {{50, -10}, {70, 10}}), iconTransformation(extent = {{50, -10}, {70, 10}})));
protected
  Integer m, n, l;
algorithm
  when sample(0, output_rate) then
    m := 1;
    n := 1;
    l := 1;
    // MATRIX
    for i in XFromRange[1]:XFromRange[2] loop
      for j in YFromRange[1]:YFromRange[2] loop
        for k in ZFromRange[1]:ZFromRange[2] loop
          yM[m, n, l] := ExtOutput(FROM.space, i, j, k);
          l := l+1;
        end for;
        l := 1;
        n := n + 1;
      end for;
      n := 1;
      m := m + 1;
    end for;
  end when;
  annotation (
    Documentation(info="<html>
<p>The Output Region model can be used to observe the state of the cells in a region of the automata connected to the FROM port. The state is translated into an output Real signal that can be used by other Modelica models. The region of selected cells is defined by the coordinates defined by XFromRange, YFromRange and ZFromRange.</p>
<p><br>Depending on the value of the parameter Output_type, the state is observed in different ways:</p>
<ul>
<li>(AVERAGE): the value of y is calculated as the average value of the states of the cells in the region. </li>
<li>(MAX): the value of y is calculated as the maximum value of the states of the cells in the region. </li>
<li>(MIN): the value of y is calculated as the minimum value of the states of the cells in the region. </li>
<li>(SUM): the value of y is calculated as the sum of the values of the states of the cells in the region. </li>
</ul>
<p><br>The OutputRegionM model contains a matrix of output Real ports, yM[XFromRange[2]-XFromRange[1]+1, YFromRange[2]-YFromRange[1]+1, ZFromRange[2]-ZFromRange[1]+1]. The value of the state of the i,j,z-th cell in the space is assigned to yM[l,m,n] (where l=1:(XFromRange[2]-XFromRange[1]+1), m = 1:(YFromRange[2]-YFromRange[1]+1) and n=1:(ZFromRange[2]-ZFromRange[1]+1)). Since the size of yM can be the size of the cellular space, and the matrix is defined in Modelica, the automatic translation of the model has to manage the definition of yM affecting the scalability and the performance of the simulation. This has to be taken into account when including the OutputRegionM model in CA models.</p>
<p>The value of the state is translated into a Real value using the ExtOutput function, that can be redeclared using the double ExtOutput(void* space, int x, int y, int z) function included in draft.c. </p>
</html>"),
    Icon(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics={  Line(points = {{-30, 60}, {-30, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-10, 60}, {-10, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{10, 60}, {10, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{30, 60}, {30, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, 40}, {50, 40}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, 20}, {50, 20}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, 0}, {50, 0}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, -20}, {50, -20}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, -40}, {50, -40}}, color = {0, 0, 255}, smooth = Smooth.None), Text(extent = {{-50, 100}, {-10, 60}}, lineColor = {0, 0, 255}, textString = "%Cstart"), Text(extent = {{10, 100}, {50, 60}}, lineColor = {0, 0, 255}, textString = "%Cend"), Text(extent = {{-90, 60}, {-50, 20}}, lineColor = {0, 0, 255}, textString = "%Rstart"), Text(extent = {{-90, 0}, {-50, -40}}, lineColor = {0, 0, 255}, textString = "%Rend"), Text(extent = {{-70, -60}, {70, -100}}, lineColor = {0, 0, 255}, textString = "%name"), Text(extent = {{50, 46}, {70, 26}}, lineColor = {0, 0, 255}, textString = "yM"), Text(extent = {{50, -4}, {70, -24}}, lineColor = {0, 0, 255}, textString = "y")}),
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics));
end OutputRegionM;
