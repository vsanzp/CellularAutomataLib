within CellularAutomataLib.Examples.CS_2D.TempControl;
function TEMPExtOutput "Temperature controller output function"
extends Modelica.Icons.Function;
  input CellularAutomataLib.Components.ExternalObj.CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = TEMPOutput(space, x, y, z);
  annotation (
    Include = "#include <tempcontrol.c>", Documentation(info="<html>
<p>Output function</p>
</html>"));
end TEMPExtOutput;
