within CellularAutomataLib.Examples.CS_2D.CHIPS;
function CHIPSetInput
    import CellularAutomataLib.Components.*;
  input CS Fspace;
  input Integer Fx;
  input Integer Fy;
  input Integer Fz;
  input CS Tspace;
  input Integer Tx;
  input Integer Ty;
  input Integer Tz;
  input Integer input_id;

  external "C" CHIPSetInput(Fspace, Fx, Fy, Fz, Tspace, Tx, Ty, Tz, input_id);
  annotation (
    Include = "#include <chip.c>", Documentation(info="<html>
<p>Input function</p>
</html>"));
end CHIPSetInput;
