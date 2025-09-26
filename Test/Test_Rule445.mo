within CellularAutomataLib.Test;
model Test_Rule445 "Test based on the Rule445 CA model"
  extends Modelica.Icons.Example;
  parameter Integer X= 14;
  parameter Integer Y= 14;
  parameter Integer Z= 14;

  CellularAutomataLib.Examples.CS_3D.Simple.Rule445 rule445_1(
    X=X,
    Y=Y,
    Z=Z) annotation (Placement(transformation(extent={{-40,-20},{-20,0}})));
  constant Integer result[4] = {1,1,1,1}; // at step 4
  Boolean fail( start = false);
  CellularAutomataLib.Components.Interfaces.OutputRegion O1(
    XFromRange={1,1},
    YFromRange={1,1},
    ZFromRange={1,1},
    Output_type=4,
    output_rate=1,redeclare function ExtOutput = GOLOutput)
    annotation (Placement(transformation(extent={{-80,40},{-60,60}})));
  CellularAutomataLib.Components.Interfaces.OutputRegion O2(
    XFromRange={2,2},
    YFromRange={2,2},
    ZFromRange={2,2},
    Output_type=4,
    output_rate=1,redeclare function ExtOutput = GOLOutput)
    annotation (Placement(transformation(extent={{-60,30},{-40,50}})));
  CellularAutomataLib.Components.Interfaces.OutputRegion O3(
    XFromRange={3,3},
    YFromRange={3,3},
    ZFromRange={3,3},
    Output_type=4,
    output_rate=1,redeclare function ExtOutput = GOLOutput)
    annotation (Placement(transformation(extent={{-40,20},{-20,40}})));
  CellularAutomataLib.Components.Interfaces.OutputRegion O4(
    XFromRange={4,4},
    YFromRange={4,4},
    ZFromRange={4,4},
    Output_type=4,
    output_rate=1,redeclare function ExtOutput = GOLOutput)
    annotation (Placement(transformation(extent={{-20,10},{0,30}})));
algorithm
  when terminal() then
    if integer(O1.y) <> 4 then
      Modelica.Utilities.Streams.print( "******* -- TEST FAILED on cell[1,1,1]: is "+String(O1.y)+" instead of 4");
      fail := true;
    end if;
    if integer(O2.y) <> 3 then
      Modelica.Utilities.Streams.print( "******* -- TEST FAILED on cell[2,2,2]: is "+String(O2.y)+" instead of 3");
      fail := true;
    end if;
    if integer(O3.y) <> 2 then
      Modelica.Utilities.Streams.print( "******* -- TEST FAILED on cell[3,3,3]: is "+String(O3.y)+" instead of 2");
      fail := true;
    end if;
    if integer(O4.y) <> 1 then
      Modelica.Utilities.Streams.print( "******* -- TEST FAILED on cell[4,4,4]: is "+String(O4.y)+" instead of 1");
      fail := true;
    end if;

    if not fail then
        Modelica.Utilities.Streams.print("*******************");
        Modelica.Utilities.Streams.print("******* -- TEST OK!");
        Modelica.Utilities.Streams.print("*******************");
    end if;
  end when;
equation
  connect(rule445_1.Space, O1.FROM) annotation (Line(points={{-29,1},{-30,1},{
          -30,10},{-76.2,10},{-76.2,50}},
                                  color={0,0,0}));
  connect(rule445_1.Space, O2.FROM) annotation (Line(points={{-29,1},{-30,1},{
          -30,10},{-56.2,10},{-56.2,40}},
                                  color={0,0,0}));
  connect(rule445_1.Space, O3.FROM)
    annotation (Line(points={{-29,1},{-30,1},{-30,10},{-36.2,10},{-36.2,30}},
                                                        color={0,0,0}));
  connect(rule445_1.Space, O4.FROM) annotation (Line(points={{-29,1},{-30,1},{
          -30,10},{-16,10},{-16,20},{-16.2,20}},
                                       color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>Model that includes a Rule445 model and an Animation model.</p>
</html>"),
    experiment(StopTime=4, __Dymola_Algorithm="Dassl"));
end Test_Rule445;
