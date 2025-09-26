within CellularAutomataLib.Examples.CS_2D.Furnace;
function FURExtOutput
  input CellularAutomataLib.Components.ExternalObj.CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = FUROutput(space, x, y, z);
  annotation (
    Include = "#include <furnace.c>", Documentation(info="<html>
<p>Ouput generation function</p>
</html>"));
end FURExtOutput;
