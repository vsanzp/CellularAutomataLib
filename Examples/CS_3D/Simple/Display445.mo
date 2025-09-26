within CellularAutomataLib.Examples.CS_3D.Simple;
function Display445 "Rule 445 display function"
    import CellularAutomataLib.Components.ExternalObj.*;
    input Anim animation;
  input CS space;

  external "C" SetDisplay445(animation,space);
  annotation (Include = "#include <s3.c>", Documentation(info="<html>
<p>Rule 445 display function</p>
</html>"));

end Display445;
