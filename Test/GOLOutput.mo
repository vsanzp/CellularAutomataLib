within CellularAutomataLib.Test;
function GOLOutput "Output function for Game of Life models"
    input CellularAutomataLib.Components.CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;
  external "C" value = GOLOutput(space, x, y, z);
  annotation (
    Include = "#include <gol.c>");
end GOLOutput;
