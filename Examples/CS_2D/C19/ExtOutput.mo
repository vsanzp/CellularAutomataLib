within CellularAutomataLib.Examples.CS_2D.C19;
function ExtOutput "Output function"
  import CellularAutomataLib.Components.ExternalObj.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = Output(space, x, y, z);
  annotation (
    Include = "#include <c19.c>", Documentation(info="<html>
<p>Output function</p>
</html>"));
end ExtOutput;
