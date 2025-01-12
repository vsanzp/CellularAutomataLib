within CellularAutomataLib.Components;
model InputRegion
  "Input Regionregion of FROM.space CA is used as input for TO.space CA"
  parameter Integer input_id = 1 "ID for input in TO.space model";
  parameter Integer XFromRange[2] = {1,1} "FROM region in X";
  parameter Integer YFromRange[2] = {1,1} "FROM region in Y";
  parameter Integer ZFromRange[2] = {1,1} "FROM region in Z";
  parameter Integer XTo = 1 "TO region in X";
  parameter Integer YTo = 1 "TO region in Y";
  parameter Integer ZTo = 1 "TO region in Z";
  parameter Real comm_start = 0 "Time for starting communication";
  parameter Real comm_rate = 1 "Communication sampling interval";

  replaceable function SetInput "External function used to communicate CA states"
    input CS Fspace "FROM space";
    input Integer XF "FROM X";
    input Integer YF "FROM Y";
    input Integer ZF "FROM Z";
    input CS Tspace "TO space";
    input Integer XT "TO X";
    input Integer YT "TO Y";
    input Integer ZT "TO Z";
    input Integer input_id "input ID";
  end SetInput;

  input CAport FROM "Input CA model" annotation (Placement(
        transformation(extent={{-80,-10},{-60,10}}), iconTransformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={-50,0})));
  input CAport TO "Output CA model" annotation (Placement(
        transformation(extent={{40,-10},{60,10}}), iconTransformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={50,0})));
protected
  Integer iTo;
  Integer jTo;
  Integer kTo;
algorithm
  when sample(comm_start, comm_rate) then
    //2D - 2D
    iTo := XTo;
    for i in XFromRange[1]:XFromRange[2] loop
      jTo := YTo;
      for j in YFromRange[1]:YFromRange[2] loop
        kTo := ZTo;
        for k in ZFromRange[1]:ZFromRange[2] loop
          SetInput(FROM.space, i, j,k, TO.space, iTo, jTo, kTo, input_id);
          kTo := kTo + 1;
        end for;
        jTo := jTo + 1;
      end for;
      iTo := iTo + 1;
    end for;
  end when;
  annotation (
    Documentation(info="<html>
<p>CellularAutomataLib supports describing models composed of several cellular spaces. The communication between spaces is described using the Input Region model (InputRegion). </p>
<p>The combination of cellular spaces is performed by translating the state of some cells (e.g., a region) from one space as inputs for the another. The prototype of the Rule function in C includes a vector of the received inputs, in order to allow the user to manage them during the transition. Each Input Region has associated an input identifier, set using the parameter input_id, that can be used as index for the vector of inputs of the transition function. </p>
<p>The Input Region model has two interface ports: FROM and TO. These interface ports are used to connect to the involved cellular spaces. The state of the cell [i, j]|i &isin; [XFromRange[1],XFromRange[2]], j &isin; [YFromRange[1],YFromRange[2]], and k &isin; [ZFromRange[1],ZFromRange[2]] in the FROM space, is translated using the SetInput function into an input for the cell [l, m, n]|l &isin; [XTo, XTo + XFromRange[2]-XFromRange[1]], m &isin; [YTo, YTo + YFromRange[2] - YFromRange[1]] , m &isin; [ZTo, ZTo + ZFromRange[2] - ZFromRange[1]] in the TO space. XFromRange, YFromRange, ZFromRange, XTo, YTo, and ZTo are parameters of the model. The communication is started at time = comm_start and is performed every comm_rate time.</p>
<p>The function void SetInput(void* Fspace, int Fx, int Fy, int Fz, void* Tspace, int Tx, int Ty, int Tz, int input_id) from the draft.c file can be used to redeclare the SetInput function of this model. </p>
</html>"),
    Icon(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics={  Line(points = {{-10, 60}, {-10, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{10, 60}, {10, -60}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-30, 40}, {30, 40}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-30, 20}, {30, 20}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-30, 0}, {30, 0}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-30, -20}, {30, -20}}, color = {0, 0, 255}, smooth = Smooth.None), Line(points = {{-30, -40}, {30, -40}}, color = {0, 0, 255}, smooth = Smooth.None),                                                                                                                                                                                                        Text(extent = {{-70, -60}, {70, -100}}, lineColor = {0, 0, 255}, textString = "%name"),                                                                                                                                                                                 Polygon(points = {{-62, 30}, {-30, 0}, {-62, -30}, {-62, 30}}, lineColor = {0, 0, 255}, smooth = Smooth.None, fillColor = {0, 0, 255}, fillPattern = FillPattern.Solid), Polygon(points = {{38, 30}, {70, 0}, {38, -30}, {38, 30}}, lineColor = {0, 0, 255}, smooth = Smooth.None, fillColor = {0, 0, 255}, fillPattern = FillPattern.Solid), Text(extent = {{-10, 0}, {10, -40}}, lineColor = {0, 0, 0}, fillColor = {0, 0, 255}, fillPattern = FillPattern.Solid, textString = "%input_id")}),
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics));
end InputRegion;
