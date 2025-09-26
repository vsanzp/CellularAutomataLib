within CellularAutomataLib.Test;
function ROutput "Output function for Wolfram models"
    input CellularAutomataLib.Components.ExternalObj.CS space;
  input Integer x;
  input Integer y=1;
  input Integer z=1;
  output Real value;
  external "C" value = ROutput(space, x, y, z);
  annotation (
    Include = "#include <wolfram.c>");
end ROutput;
