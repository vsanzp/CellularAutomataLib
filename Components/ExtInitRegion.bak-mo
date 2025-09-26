within CellularAutomataLib.Components;
model ExtInitRegion
  parameter Integer XRange[2] = {1,1} "X region";
  parameter Integer YRange[2] = {1,1} "Y region";
  parameter Integer ZRange[2] = {1,1} "Z region";

  replaceable function ExtInit "External initalization function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;
    input Real value;
  end ExtInit;

  Modelica.Blocks.Interfaces.RealInput u "External input value" annotation (
    Placement(transformation(extent = {{-100, -20}, {-60, 20}}), iconTransformation(extent = {{-100, -20}, {-60, 20}})));
  //Boolean init(start=false, fixed=true);
  input CAport TO "Reference to the cellular space" annotation (
      Placement(transformation(extent={{20,-10},{40,10}}), iconTransformation(
          extent={{20,-10},{40,10}})));
initial algorithm
  //when initial() and not init then
  for i in XRange[1]:XRange[2] loop
    for j in YRange[1]:YRange[2] loop
      for k in ZRange[1]:ZRange[2] loop
        ExtInit(TO.space, i, j, k, u);
      end for;
    end for;
  end for;
  //init := true;
  //end when;
equation
  if cardinality(u) == 0 then
    u = 0;
  end if;
  annotation (
    Documentation(info="<html>
<p>The ExtInitRegion model can be used to set the initial state of a region of cells in the space using the value of an external signal. The model has an input port, named u, where a Real signal is received, and a port named TO that connects to the CA. The value of u is translated, using the ExtInit function, into a cell state that will be used to initialize the cells in the region of the connected automaton. If u is not connected to another model its value is set to 0.</p>
<p>The region is defined by the coodirnates defined by parameters XRange, YRange and ZRange. </p>
<p>The ExtInit function can be redeclared using the void ExtInit(void* space, int x, int y, int z, double value) function included in draft.c. </p>
</html>"),
    Icon(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics={  Line(points = {{-30, 60}, {-30, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-10, 60}, {-10, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{10, 60}, {10, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{30, 60}, {30, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, 40}, {50, 40}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, 20}, {50, 20}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, 0}, {50, 0}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, -20}, {50, -20}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-50, -40}, {50, -40}}, color = {0, 0, 255}, smooth = Smooth.None), Text(extent = {{40, 40}, {60, 20}}, lineColor = {0, 0, 255}, textString = "%Rstart"), Text(extent = {{40, -20}, {60, -40}}, lineColor = {0, 0, 255}, textString = "%Rend"), Text(extent = {{-40, 80}, {-20, 60}}, lineColor = {0, 0, 255}, textString = "%Cstart"), Text(extent = {{20, 80}, {40, 60}}, lineColor = {0, 0, 255}, textString = "%Cend"), Text(extent = {{-70, -60}, {70, -100}}, lineColor = {0, 0, 255}, textString = "%name"), Text(extent = {{-48, 40}, {56, 20}}, lineColor = {0, 0, 0}, textString = "init")}),
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics));
end ExtInitRegion;
