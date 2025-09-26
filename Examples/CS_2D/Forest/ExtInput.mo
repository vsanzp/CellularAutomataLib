within CellularAutomataLib.Examples.CS_2D.Forest;
function ExtInput "external input function"
  import CellularAutomataLib.Components.ExternalObj.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  input Real value;
  input Integer input_id;

  external "C" ExtInput(space, x, y, z, value, input_id);
  annotation (
    Include = "#include <forest.c>", Documentation(info="<html>
<p>External input function</p>
</html>"));
end ExtInput;
