within CellularAutomataLib.Test;
function RSetInput "Input function for Wolfram models"
  input CellularAutomataLib.Components.CS Fspace;
  input Integer XF;
  input Integer YF;
  input Integer ZF;
  input CellularAutomataLib.Components.CS Tspace;
  input Integer XT;
  input Integer YT;
  input Integer ZT;
  input Integer input_id;

  external "C" RSetInput(Fspace, XF, YF, ZF, Tspace, XT, YT, ZT, input_id);
  annotation (
    Include = "#include <wolfram.c>");
end RSetInput;
