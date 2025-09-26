within CellularAutomataLib.Test;
function GOLExtInput "External init function for Game of Life models"
    input CellularAutomataLib.Components.ExternalObj.CS space;
  input Integer x;
  input Integer y;
  input Integer z=1;
  input Real value;
  input Integer input_id;
  external "C" GOLExtInput(space, x, y, z, value,input_id);
  annotation (
    Include = "#include <gol.c>");
end GOLExtInput;
