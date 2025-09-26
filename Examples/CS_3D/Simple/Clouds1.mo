within CellularAutomataLib.Examples.CS_3D.Simple;
model Clouds1 "Clouds model"
  import CellularAutomataLib.Components.Basic.*;
  import CellularAutomataLib.Components.ExternalObj.*;
  extends CellSpace(
    X=100,
    Y=100,
    Z=100,
    init_cells=[X,Y,Z],
    redeclare function Default = S3Default,
    redeclare function Initial = S3RandomInit,
    redeclare function Rule = S3Rule);

    function S3Default
    input CS space;
    output Integer out;

    external "C" out = S3Default(space);
    annotation (
      Include = "#include \"s3.c\"", Documentation(info="<html>
<p>Default state function</p>
</html>"));
    end S3Default;

  function S3RandomInit
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" S3RandomInitial(space, x, y, z);
    annotation (
      Include = "#include \"s3.c\"", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end S3RandomInit;

  function S3Rule
    input CS space;
    output Integer out;

    external "C" out = S3Clouds1Step(space);
    annotation (
      Include = "#include \"s3.c\"", Documentation(info="<html>
<p>Transition function</p>
</html>"));
  end S3Rule;

  annotation (experiment(StopTime=200, __Dymola_Algorithm="Dassl"),
      Documentation(info="<html>
<p>A life-like model with the rule B13-19/S13-26. A dead cell becomes alive with 13 to 19 neighbors alive. A living cell survives with more than 12 neighbors alive. </p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/s3.c</span></p>
</html>"));
end Clouds1;
