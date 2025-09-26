within CellularAutomataLib.Components.Interfaces;
model ExtInputRegion "Values from u are used as inputs for TO.space CA"
  parameter Integer input_id = 1 "ID for input in TO.space model";
  parameter Integer XToRange[2] = {1,1} "TO region in X";
  parameter Integer YToRange[2] = {1,1} "TO region in Y";
  parameter Integer ZToRange[2] = {1,1} "TO region in Z";
  parameter Integer Input_type = 1 "Input observation method" annotation (
    choices(choice = 1 "Quantized", choice = 2 "Cross_UP", choice = 3 "Cross_DOWN", choice = 4 "Cross_ANY", choice = 5 "Sampled"));
  replaceable Real q_t = 1 "Quantum/threshold/interval value";
  parameter Real q_aux = 1e-010 "Detection value threshold";
  parameter Real start_preU = 0 "start value for preU";
  parameter Boolean start_above = false "start value for above";
  parameter Boolean start_below = false "start value for below";
  parameter Real start_sample = 0 "start sampling time";

  replaceable function ExtInput "External input function"
    input CellularAutomataLib.Components.ExternalObj.CS space;
    input Integer x;
    input Integer y;
    input Integer z;
    input Real value;
    input Integer input_id;
  end ExtInput;

  Real Y;
  Modelica.Blocks.Interfaces.RealInput u annotation (
    Placement(transformation(extent = {{-100, -20}, {-60, 20}}), iconTransformation(extent = {{-100, -20}, {-60, 20}})));
  Real preU(start = start_preU, fixed = true);
  Boolean above(start = start_above, fixed = true);
  Boolean below(start = start_below, fixed = true);
//  Real next_t(start = start_sample, fixed = true);
  input CAport TO annotation (Placement(transformation(extent={{50,-10},{70,10}}),
                       iconTransformation(extent={{50,-10},{70,10}})));
algorithm
  // FIRST ORDER QUANTIFIER
  when (Input_type == 1) and ((u >= preU + q_t + q_aux) or (u <= preU - q_t - q_aux)) and (time > 0) then
    // Modelica.Utilities.Streams.print("Quantizer: u "+String(u));
    for i in XToRange[1]:XToRange[2] loop
      for j in YToRange[1]:YToRange[2] loop
        for k in ZToRange[1]:ZToRange[2] loop
          ExtInput(TO.space, i, j, k, u, input_id);
        end for;
      end for;
    end for;
    preU := u;
  end when;
  //CROSS UP
algorithm
  when (Input_type == 2 or Input_type == 4) and (u > q_t) and time > 0 and pre(below) then
    //Modelica.Utilities.Streams.print("Cross UP: u " + String(u));
    below := false;
    for i in XToRange[1]:XToRange[2] loop
      for j in YToRange[1]:YToRange[2] loop
        for k in ZToRange[1]:ZToRange[2] loop
          ExtInput(TO.space, i, j, k, u, input_id);
        end for;
      end for;
    end for;
  end when;
  when (Input_type == 2 or Input_type == 4) and (u < q_t) and time > 0 and not below then
    below := true;
  end when;
  //CROSS DOWN
algorithm
  when (Input_type == 3 or Input_type == 4) and (u < q_t) and time > 0 and above then
    // Modelica.Utilities.Streams.print("CROSS DOWN: u "+String(u)+" value "+String(Value));
    above := false;
    for i in XToRange[1]:XToRange[2] loop
      for j in YToRange[1]:YToRange[2] loop
        for k in ZToRange[1]:ZToRange[2] loop
          ExtInput(TO.space, i, j, k, u, input_id);
        end for;
      end for;
    end for;
  end when;
  when (Input_type == 3 or Input_type == 4) and (u > q_t) and time > 0 and not above then
    above := true;
  end when;
equation
  // TIME SAMPLER
algorithm
  when (Input_type == 5 and sample(start_sample,q_t)) then
    //Modelica.Utilities.Streams.print("SAMPLE: u "+String(u)+" id "+String(input_id));
    for i in XToRange[1]:XToRange[2] loop
      for j in YToRange[1]:YToRange[2] loop
        for k in ZToRange[1]:ZToRange[2] loop
          ExtInput(TO.space, i, j, k, u, input_id);
          Y:=u;
        end for;
      end for;
    end for;
  end when;
  annotation (
    Documentation(info="<html>
<p>Similarly to the Input Region model, the model ExtInputRegion can be used to set an input to a region of cells in the automata. In this case the input is generated using an external signal instead of the state of the cells of other automata.</p>
<p>This model receives an external Real input signal through port u, which is used as input for a region of cells in the automata connected to port TO. Similarly to the other interface models, the region is defined by the coordinates declared using parameters XToRange, YToRange and ZToRange.</p>
<p>The input is assigned to the position input_id of the vector of inputs, that is available for the user in the transition function. The external signal, u, can be observed using the following methods (defined by the parameter Input_type), in order to be converted into an input:</p>
<ul>
<li>Quantizer: the input is set every time the value of the signal changes by a defined value or quantum.</li>
<li>Cross_UP: the input is set every time the value of the signal crosses a defined threshold in the upwards direction.</li>
<li>Cross_DOWN: the input is set every time the value of the signal crosses a defined threshold in the downwards direction.</li>
<li>Cross_ANY: the input is set every time the value of the signal crosses a defined threshold in any direction.</li>
<li>Sample: the input is set periodically using the sample operator.</li>
</ul>
<p>The signal is translated into an input using the function ExtInput, that can be redeclared using the void ExtInput(void* space,int x, int y, int z, double value, int input_id) function included in draft.c. </p>
</html>"),
    Icon(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics={                                                                                                                                                                                                        Text(extent={{-70,-40},
              {70,-80}},                                                                                                                                                                                                        lineColor = {0, 0, 255}, textString = "%name"), Text(extent={{-20,80},
              {20,0}},                                                                                                                                                                                                        lineColor = {0, 0, 0}, textString = "%input_id"),
        Rectangle(
          extent={{-10,2},{6,-2}},
          lineColor={28,108,200},
          fillColor={0,0,255},
          fillPattern=FillPattern.Solid),
        Line(points={{60,40},{60,0}}, color={28,108,200}),
        Line(points={{100,0},{60,0}}, color={28,108,200}),
        Line(points={{30,-30},{60,0}}, color={28,108,200}),
        Text(
          extent={{80,0},{100,-8}},
          textColor={0,0,0},
          textString="XTo"),
        Text(
          extent={{60,40},{80,32}},
          textColor={0,0,0},
          textString="YTo"),
        Text(
          extent={{34,-24},{54,-32}},
          textColor={0,0,0},
          textString="ZTo"),
        Text(
          extent={{-100,40},{-60,20}},
          textColor={0,0,255},
          textString="u"),                                                                                                                                                                                                        Polygon(points={{6,8},{
              14,0},{6,-8},{6,8}},                                                                                                                                                                                                        lineColor = {0, 0, 255}, smooth = Smooth.None, fillColor = {0, 0, 255}, fillPattern = FillPattern.Solid)}),
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics));
end ExtInputRegion;
