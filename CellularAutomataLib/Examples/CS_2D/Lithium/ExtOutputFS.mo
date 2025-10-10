within CellularAutomataLib.Examples.CS_2D.Lithium;
function ExtOutputFS "Output function"
  import CellularAutomataLib.Components.ExternalObj.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = OutputFS(space, x, y, z);
  annotation (
    Include = "#include <lithium.c>", Documentation(info="<html>
<p>Output function</p>
</html>"));
end ExtOutputFS;
