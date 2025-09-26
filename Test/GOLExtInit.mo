within CellularAutomataLib.Test;
function GOLExtInit "External init function for Game of Life models"
    input CellularAutomataLib.Components.ExternalObj.CS space;
  input Integer x;
  input Integer y;
  input Integer z=1;
  input Real value;
  external "C" GOLExtInit(space, x, y, z, value);
  annotation (
    Include = "#include <gol.c>");
end GOLExtInit;
