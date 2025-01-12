within CellularAutomataLib.Examples.CS_2D.Forest;
function ExtOutput
  import CellularAutomataLib.Components.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = Output(space, x, y, z);
  annotation (
    Include = "#include <forest.c>", Documentation(info="<html>
<p>Output function.</p>
</html>"));
end ExtOutput;
