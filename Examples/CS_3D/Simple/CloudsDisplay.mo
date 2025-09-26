within CellularAutomataLib.Examples.CS_3D.Simple;
function CloudsDisplay "Clouds display function"
  import CellularAutomataLib.Components.ExternalObj.*;
  input Anim animation;
    input CS space;

  external "C" SetDisplayClouds(animation,space);
  annotation (Include = "#include <s3.c>", Documentation(info="<html>
<p>Display function for the Clouds1 model</p>
</html>"));

end CloudsDisplay;
