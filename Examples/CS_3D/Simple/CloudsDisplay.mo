within CellularAutomataLib.Examples.CS_3D.Simple;
function CloudsDisplay
  input Components.Anim animation;
    input Components.CS space;

  external "C" SetDisplayClouds(animation,space);
  annotation (Include = "#include <s3.c>", Documentation(info="<html>
<p>Display function for the Clouds1 model</p>
</html>"));

end CloudsDisplay;
