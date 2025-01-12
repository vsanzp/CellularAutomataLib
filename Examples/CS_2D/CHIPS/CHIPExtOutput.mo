within CellularAutomataLib.Examples.CS_2D.CHIPS;
function CHIPExtOutput
    import CellularAutomataLib.Components.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = CHIPOutput(space, x, y, z);
  annotation (
    Include = "#include <chip.c>", Documentation(info="<html>
<p>Output function</p>
</html>"));
end CHIPExtOutput;
