within CellularAutomataLib.Components;
class Anim
  extends ExternalObject;

  function constructor
    input Integer winWidth "animation window width";
    input Integer winHeight "animation window height";
    input Integer WX "number of cells displayed in the X dim.";
    input Integer WY "number of cells displayed in the Y dim.";
    input Integer WZ "number of cells displayed in the Z dim.";
    input Real displayDelay "time delay between animation steps";
    input Integer vector "scalar(0) or vector(1) field?";
    input Boolean save_video "save animation in video format?";
    input String name "name for the window and video file";
    output Anim a "Reference to the created animation";
  external "C" a = CS_CreateAnimation(winWidth,winHeight,WX, WY, WZ, displayDelay, vector, save_video, name);
    annotation (
      Include = "#include <CellularAutomataLib-animation.c>",
      Library = {"raylib","avformat","avcodec","avutil","swscale"},
      Documentation(info="<html>
<p>CS constructor function</p>
</html>"));
  end constructor;

  function destructor
    input Anim a;

    external "C" CS_DeleteAnimation(a);
    annotation (
      Include = "#include <CellularAutomataLib-animation.c>", Documentation(info="<html>
<p>CS destructor function</p>
</html>"));
  end destructor;
equation

  annotation (Documentation(info="<html>
<p>The <span style=\"font-family: monospace;\">Anim</span> model corresponds to the extenal object, defined in C, that is used to represent the graphical animation of the simulation.</p>
<p>The constructor and destructor functions are automatically executed when instatiating this class, and their C code is contained in the C<span style=\"font-family: monospace;\">ellularAutomatalib-animation.c</span> file.</p>
</html>"));
end Anim;
