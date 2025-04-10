within CellularAutomataLib.Test;
model Test_GliderExtInput
  Examples.CS_2D.GameOfLife.CSGol_glider cSGol_glider(
    X=10,
    Y=10,
    n_inputs=3,
    initial_step=1,
    init_cells=[1,2; 2,3; 3,1; 3,2; 3,3])
    annotation (Placement(transformation(extent={{20,-20},{40,0}})));
  Components.OutputRegionM O(
    XFromRange={1,7},
    YFromRange={1,6},
    output_rate=1,
    redeclare function ExtOutput = GOLOutput)
    annotation (Placement(transformation(extent={{22,20},{42,40}})));

  Modelica.Blocks.Sources.Constant const(k=1)
    annotation (Placement(transformation(extent={{-50,-12},{-30,8}})));
  Components.ExtInputRegion extInputRegion1(
    XToRange={1,1},
    YToRange={2,2},
    Input_type=5,
    q_t=100,
    start_sample=13,
                   redeclare function ExtInput = GOLExtInput)
    annotation (Placement(transformation(extent={{-18,18},{2,38}})));
  Modelica.Blocks.Sources.Constant const1(k=1)
    annotation (Placement(transformation(extent={{-50,18},{-30,38}})));
  Modelica.Blocks.Sources.Constant const2(k=1)
    annotation (Placement(transformation(extent={{-50,-42},{-30,-22}})));
  Components.ExtInputRegion extInputRegion3(
    input_id=2,
    XToRange={2,2},
    YToRange={3,3},
    Input_type=5,
    q_t=100,
    start_sample=13,
                   redeclare function ExtInput = GOLExtInput)
    annotation (Placement(transformation(extent={{-18,-12},{2,8}})));
  Components.ExtInputRegion extInputRegion2(
    input_id=3,
    XToRange={3,3},
    YToRange={1,3},
    Input_type=5,
    q_t=100,
    start_sample=13,
                   redeclare function ExtInput = GOLExtInput)
    annotation (Placement(transformation(extent={{-18,-42},{2,-22}})));

  constant Integer result[7,6] = [0,1,0,0,0,0; 0,0,1,0,0,0; 1,1,1,0,0,0; 0,0,0,0,0,0; 0,0,0,0,0,1; 0,0,0,1,0,1; 0,0,0,0,1,1];
  Boolean fail( start = false);
algorithm
  when terminal() then
    for i in 1:7 loop
      for j in 1:6 loop
        if result[i,j] <> integer(O.yM[i,j,1]) then
          Modelica.Utilities.Streams.print( "******* -- TEST FAILED on cell["+String(i+O.XFromRange[1]-1)+","+String(j+O.YFromRange[1]-1)+"]: is "+String(O.yM[i,j,1])+" instead of "+String(result[i,j]));
          fail := true;
        end if;
      end for;
    end for;
    if not fail then
        Modelica.Utilities.Streams.print("*******************");
        Modelica.Utilities.Streams.print("******* -- TEST OK!");
        Modelica.Utilities.Streams.print("*******************");
    end if;
  end when;
equation
  connect(cSGol_glider.Space, O.FROM) annotation (Line(points={{31,1},{32,1},{
          32,30}},                    color={0,0,0}));
  connect(const1.y, extInputRegion1.u)
    annotation (Line(points={{-29,28},{-16,28}}, color={0,0,127}));
  connect(const.y, extInputRegion3.u)
    annotation (Line(points={{-29,-2},{-16,-2}},
                                               color={0,0,127}));
  connect(const2.y, extInputRegion2.u)
    annotation (Line(points={{-29,-32},{-16,-32}}, color={0,0,127}));
  connect(extInputRegion1.TO, cSGol_glider.Space) annotation (Line(points={{-5,28},
          {14,28},{14,8},{31,8},{31,1}},           color={0,0,0}));
  connect(extInputRegion3.TO, cSGol_glider.Space) annotation (Line(points={{-5,-2},
          {14,-2},{14,8},{31,8},{31,1}},         color={0,0,0}));
  connect(extInputRegion2.TO, cSGol_glider.Space) annotation (Line(points={{-5,-32},
          {14,-32},{14,8},{31,8},{31,1}},                            color={0,0,
          0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>This model includes a CSGol_glider model combined with the Animation model in order to generate the graphical animation during the simulation.</p>
</html>"),
    experiment(StopTime=54, __Dymola_Algorithm="Dassl"));
end Test_GliderExtInput;
