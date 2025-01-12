within CellularAutomataLib.Examples.CS_3D.Simple;
function Display445
    input Components.CS space;

  external "C" SetDisplay445(space);
  annotation (Include = "#include <s3.c>", Documentation(info="<html>
<p>Rule 445 display function</p>
</html>"));

end Display445;
