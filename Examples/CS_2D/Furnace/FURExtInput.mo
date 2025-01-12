within CellularAutomataLib.Examples.CS_2D.Furnace;
function FURExtInput
  import CellularAutomataLib.Components.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  input Real value;
  input Integer input_id;

  external "C" FURExtInput(space, x, y, z, value, input_id);
  annotation (
    Include = "#include <furnace.c>", Documentation(info="<html>
<p>External input function for the furnace model.</p>
</html>"));
end FURExtInput;
