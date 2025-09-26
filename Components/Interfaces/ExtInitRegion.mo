within CellularAutomataLib.Components.Interfaces;
model ExtInitRegion "Initialize TO.space CA cells with values from u"
  parameter Integer XRange[2] = {1,1} "X region";
  parameter Integer YRange[2] = {1,1} "Y region";
  parameter Integer ZRange[2] = {1,1} "Z region";

  replaceable function ExtInit "External initalization function"
    input CellularAutomataLib.Components.ExternalObj.CS space;
    input Integer x;
    input Integer y;
    input Integer z;
    input Real value;
  end ExtInit;

  Modelica.Blocks.Interfaces.RealInput u "External input value" annotation (
    Placement(transformation(extent = {{-100, -20}, {-60, 20}}), iconTransformation(extent = {{-100, -20}, {-60, 20}})));
  //Boolean init(start=false, fixed=true);
  input CAport TO "Reference to the cellular space" annotation (
      Placement(transformation(extent={{50,-10},{70,10}}), iconTransformation(
          extent={{50,-10},{70,10}})));
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
    Icon(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics={                                                                                                                                                                                                        Text(extent={{-70,-40},
              {70,-80}},                                                                                                                                                                                                        lineColor = {0, 0, 255}, textString = "%name"), Text(extent={{-52,42},
              {52,22}},                                                                                                                                                                                                        lineColor={0,0,0},
          textString="Ext Init"),
        Line(points={{60,40},{60,0}},   color={28,108,200}),
        Line(points={{100,0},{60,0}},  color={28,108,200}),
        Line(points={{30,-30},{60,0}},   color={28,108,200}),
        Text(
          extent={{80,0},{100,-8}},
          textColor={0,0,0},
          textString="XRange"),
        Text(
          extent={{60,40},{80,32}},
          textColor={0,0,0},
          textString="YRange"),
        Text(
          extent={{34,-24},{54,-32}},
          textColor={0,0,0},
          textString="ZRange"),
        Rectangle(
          extent={{-10,2},{6,-2}},
          lineColor={28,108,200},
          fillColor={0,0,255},
          fillPattern=FillPattern.Solid),
        Text(
          extent={{-100,40},{-60,20}},
          textColor={0,0,255},
          textString="u"),                                                                                                                                                                                                        Polygon(points={{6,8},{
              14,0},{6,-8},{6,8}},                                                                                                                                                                                                        lineColor = {0, 0, 255}, smooth = Smooth.None, fillColor = {0, 0, 255}, fillPattern = FillPattern.Solid)}),
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics));
end ExtInitRegion;
