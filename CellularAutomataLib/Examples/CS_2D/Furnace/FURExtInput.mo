within CellularAutomataLib.Examples.CS_2D.Furnace;
function FURExtInput "Furnace external input function"
extends Modelica.Icons.Function;
  input CellularAutomataLib.Components.ExternalObj.CS space;
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
