within CellularAutomataLib.Examples.CS_3D.Simple;
model Rule445
  parameter Integer midpos = integer(X/2);
  import CellularAutomataLib.Components.*;
  extends CellSpace( X = 20, Y = 20, Z = 20,
  init_cells = [midpos,midpos,midpos; midpos-1,midpos,midpos; midpos,midpos-1,midpos; midpos-1,midpos-1,midpos;
                midpos,midpos,midpos-1; midpos-1,midpos,midpos-1; midpos,midpos-1,midpos-1; midpos-1,midpos-1,midpos-1;
                midpos,midpos,midpos+1;midpos-1,midpos,midpos+1;midpos,midpos-1,midpos+1;midpos-1,midpos-1,midpos+1],
     redeclare function Default = S3Default,
    redeclare function Initial = S3Init,
    redeclare function Rule = S3445Step);
//[50,50,50; 49,50,50; 50,49,50; 49,49,50; 50,50,49; 49,50,49; 50,49,49; 49,49,49; 50,50,51; 49,50,51; 50,49,51; 49,49,51]
    function S3Default
    input CS space;
    output Integer out;

    external "C" out = S3Default(space);
    annotation (
      Include = "#include \"s3.c\"", Documentation(info="<html>
<p>Default state function</p>
</html>"));
    end S3Default;

  function S3Init
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" S3Initial(space, x, y, z);
    annotation (
      Include = "#include \"s3.c\"", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end S3Init;

  function S3445Step
    input CS space;
    output Integer out;

    external "C" out = S3445Step(space);
    annotation (
      Include = "#include \"s3.c\"", Documentation(info="<html>
<p>Transition function</p>
</html>"));
  end S3445Step;

  annotation (Documentation(info="<html>
<p>A life-like model with the rule 445. The state of living cells is an integer number greater than 0, and with 0 representing a dead cell. In this model, living cells degrade their state until they become dead. Also, dead cells with 4 neighbors become alive and living cells with other than 4 neighbors alive become dead.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/s3.c</span></p>
</html>"));
end Rule445;
