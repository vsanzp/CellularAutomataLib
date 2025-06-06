within CellularAutomataLib.Examples.CS_2D.Furnace;
function FURSetInput
  import CellularAutomataLib.Components.*;
  input CS Fspace;
  input Integer XF;
  input Integer YF;
  input Integer ZF;
  input CS Tspace;
  input Integer XT;
  input Integer YT;
  input Integer ZT;
  input Integer input_id;

  external "C" FURSetInput(Fspace, XF, YF, ZF, Tspace, XT, YT, ZT, input_id);
  annotation (
    Include = "#include <furnace.c>", Documentation(info="<html>
<p>Input function.</p>
</html>"));
end FURSetInput;
