within CellularAutomataLib.Examples.CS_2D.CHIPS;
function CHIPExtInput
  import CellularAutomataLib.Components.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  input Real value;
  input Integer input_id;

  external "C" CHIPExtInput(space, x, y, z, value, input_id);
  annotation (
    Include = "#include <chip.c>", Documentation(info="<html>
<p>External input function</p>
</html>"));
end CHIPExtInput;
